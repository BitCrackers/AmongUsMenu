#include "pch-il2cpp.h"
#include "players_tab.h"
#include "game.h"
#include "state.hpp"
#include "utility.h"
#include "gui-helpers.hpp"

namespace PlayersTab {

	int framesPassed = -1;
	Vector2 previousPlayerPosition;

	void Render() {
		if (IsInGame() || IsInLobby()) {
			if (ImGui::BeginTabItem("Players")) {
				ImGui::BeginChild("players#list", ImVec2(200, 0) * State.dpiScale, true);
				auto selectedPlayer = State.selectedPlayer.validate();
				bool shouldEndListBox = ImGui::ListBoxHeader("###players#list", ImVec2(200, 150) * State.dpiScale);
				auto localData = GetPlayerData(*Game::pLocalPlayer);
				for (auto playerData : GetAllPlayerData()) {
					if (playerData->fields.Disconnected)
						continue;

					app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);
					if (outfit == NULL) continue;
					std::string playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0) * State.dpiScale);
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0) * State.dpiScale);
					if (ImGui::Selectable(std::string("##" + playerName).c_str(), selectedPlayer.equals(playerData))) {
						State.selectedPlayer = PlayerSelection(playerData);
						selectedPlayer = State.selectedPlayer.validate();
					}
					ImGui::SameLine();
					ImGui::ColorButton(std::string("##" + playerName + "_ColorButton").c_str(), AmongUsColorToImVec4(GetPlayerColor(outfit->fields.ColorId)), ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
					ImGui::SameLine();
					ImGui::PopStyleVar(2);
					ImGui::Dummy(ImVec2(0, 0) * State.dpiScale);
					ImGui::SameLine();

					ImVec4 nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->White);
					if (State.RevealRoles)
					{
						std::string roleName = GetRoleName(playerData->fields.Role);
						playerName = playerName + " (" + roleName + ")";
						nameColor = AmongUsColorToImVec4(GetRoleColor(playerData->fields.Role));
					}
					else if(PlayerIsImpostor(localData) && PlayerIsImpostor(playerData))
						nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->ImpostorRed);
					else if (PlayerSelection(playerData).is_LocalPlayer() || std::count(State.aumUsers.begin(), State.aumUsers.end(), playerData->fields.PlayerId))
						nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->Orange);

					if (playerData->fields.IsDead)
						nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->DisabledGrey);

					ImGui::TextColored(nameColor, playerName.c_str());
				}
				if (shouldEndListBox)
					ImGui::ListBoxFooter();

				if (selectedPlayer.has_value()) //Upon first startup no player is selected.  Also rare case where the playerdata is deleted before the next gui cycle
				{
					ImGui::Text("Is using AUM: %s",
						selectedPlayer.is_LocalPlayer() || std::count(State.aumUsers.begin(), State.aumUsers.end(), selectedPlayer.get_PlayerData()->fields.PlayerId)
						? "Yes" : "No");
				}


				if (IsInMultiplayerGame() && IsInGame()) {
					float taskPercentage = (float) (*Game::pGameData)->fields.CompletedTasks / (float) (*Game::pGameData)->fields.TotalTasks;
					ImGui::TextColored(ImVec4(1.0f - taskPercentage, 1.0f, 1.0f - taskPercentage, 1.0f), "%.1f%% Total Tasks Completed", taskPercentage * 100);
				}

				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("players#actions", ImVec2(200, 0) * State.dpiScale, true);

				GameOptions options;
				if (IsInGame() && options.GetGameMode() != GameModes__Enum::HideNSeek && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) { //Player selection doesn't matter
					if (ImGui::Button("Call Meeting")) {
						State.rpcQueue.push(new RpcReportPlayer(PlayerSelection()));
					}
				}
				if (State.activeImpersonation)
				{
					if (ImGui::Button("Reset Impersonation"))
					{
						std::queue<RPCInterface*> *queue = nullptr;

						if (IsInGame())
							queue = &State.rpcQueue;
						else if (IsInLobby())
							queue = &State.lobbyRpcQueue;
						if (queue != nullptr) {
							queue->push(new RpcSetColor(State.originalColor));
							queue->push(new RpcSetPet(State.originalPet));
							queue->push(new RpcSetSkin(State.originalSkin));
							queue->push(new RpcSetHat(State.originalHat));
							queue->push(new RpcSetVisor(State.originalVisor));
							queue->push(new RpcSetNamePlate(State.originalNamePlate));
							queue->push(new RpcSetName(State.originalName));
							State.activeImpersonation = false;
						}
					}
				}
				if (selectedPlayer.has_value())
				{
					if (IsInGame() && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead && selectedPlayer.get_PlayerData()->fields.IsDead) {
						ImGui::NewLine();
						if (ImGui::Button("Report Body")) {
							State.rpcQueue.push(new RpcReportPlayer(State.selectedPlayer));
						}
					}
					ImGui::NewLine();

					if (IsInGame() && !selectedPlayer.is_Disconnected() && !selectedPlayer.is_LocalPlayer())
					{
						if (State.playerToFollow.equals(State.selectedPlayer)) {
							if (ImGui::Button("Stop Spectating")) {
								State.playerToFollow = PlayerSelection();
							}
						} else {
							if (ImGui::Button("Spectate")) {
								State.FreeCam = false;
								State.playerToFollow = State.selectedPlayer;
							}
						}
					}

					if (selectedPlayer.is_LocalPlayer() && State.originalName != "-") {
						if (ImGui::Button("Reset Name")) {
							if (IsInGame())
								State.rpcQueue.push(new RpcSetName(State.originalName));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new RpcSetName(State.originalName));
						}
					}
					else if(!selectedPlayer.is_LocalPlayer()) {
						if ((IsInMultiplayerGame() || IsInLobby()) && ImGui::Button("Steal Name")) {
							ImpersonateName(State.selectedPlayer);
						}
					}
					if ((IsInGame() || IsInLobby())) {
						if (!selectedPlayer.is_LocalPlayer()) {
							app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(selectedPlayer.get_PlayerData());
							if (outfit != NULL) {
								if (ImGui::Button("Impersonate")) {

									auto petId = outfit->fields.PetId;
									auto skinId = outfit->fields.SkinId;
									auto hatId = outfit->fields.HatId;
									auto visorId = outfit->fields.VisorId;
									auto colorId = outfit->fields.ColorId;
									auto namePlateId = outfit->fields.NamePlateId;
									std::queue<RPCInterface*>* queue = nullptr;

									if (IsInGame())
										queue = &State.rpcQueue;
									else if (IsInLobby())
										queue = &State.lobbyRpcQueue;

									if (queue != nullptr) {
										if (IsHost())
											queue->push(new RpcSetColor(colorId, true));
										else
											queue->push(new RpcSetColor(GetRandomColorId()));
										queue->push(new RpcSetPet(petId));
										queue->push(new RpcSetSkin(skinId));
										queue->push(new RpcSetVisor(visorId));
										queue->push(new RpcSetHat(hatId));
										queue->push(new RpcSetNamePlate(namePlateId));
										ImpersonateName(State.selectedPlayer);
										State.activeImpersonation = true;
									}
								}
							}
						}
					}

					if (IsInGame() && PlayerIsImpostor(GetPlayerData(*Game::pLocalPlayer))
						&& !selectedPlayer.get_PlayerData()->fields.IsDead
						&& !selectedPlayer.get_PlayerControl()->fields.inVent
						&& !selectedPlayer.get_PlayerControl()->fields.inMovingPlat
						&& !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead && ((*Game::pLocalPlayer)->fields.killTimer <= 0.0f)
						&& !selectedPlayer.get_PlayerControl()->fields.protectedByGuardian)
					{
						if (ImGui::Button("Kill Player"))
						{
							previousPlayerPosition = GetTrueAdjustedPosition(*Game::pLocalPlayer);
							State.rpcQueue.push(new CmdCheckMurder(State.selectedPlayer));
							framesPassed = 40;
						}
					}

					if (framesPassed == 0)
					{
						State.rpcQueue.push(new RpcSnapTo(previousPlayerPosition));
						framesPassed--;
					}
					else framesPassed--;

					if (!selectedPlayer.is_LocalPlayer()) {
						if (ImGui::Button("Teleport To")) {
							if(IsInGame())
								State.rpcQueue.push(new RpcSnapTo(GetTrueAdjustedPosition(selectedPlayer.get_PlayerControl())));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new RpcSnapTo(GetTrueAdjustedPosition(selectedPlayer.get_PlayerControl())));
						}
					}

					ImGui::NewLine();

					if (IsInGame() && !selectedPlayer.is_Disconnected() && IsInMultiplayerGame())
					{
						auto tasks = GetNormalPlayerTasks(selectedPlayer.get_PlayerControl());

						if (State.RevealRoles && PlayerIsImpostor(selectedPlayer.get_PlayerData()))
						{
							ImGui::TextColored(ImVec4(0.8F, 0.2F, 0.0F, 1.0F), "Fake Tasks:");
						}
						else
						{
							ImGui::Text("Tasks:");
						}

						bool shouldEndListBox = ImGui::ListBoxHeader("###tasks#list", ImVec2(181, 94) * State.dpiScale);

						if (selectedPlayer.get_PlayerControl()->fields.myTasks == nullptr)
						{
							ImGui::Text("ERROR: Could not load tasks.");
						}
						else
						{
							for (auto task : tasks)
							{
								if (task->fields.taskStep == task->fields.MaxStep)
									ImGui::TextColored(ImVec4(0.0F, 1.0F, 0.0F, 1.0F), (std::string(TranslateTaskTypes(task->fields._.TaskType))).c_str());
								else
									ImGui::Text((std::string(TranslateTaskTypes(task->fields._.TaskType))).c_str());
							}
						}
						if (shouldEndListBox)
							ImGui::ListBoxFooter();
					}
				}

				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
}