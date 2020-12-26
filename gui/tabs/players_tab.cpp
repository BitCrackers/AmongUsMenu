#include "pch-il2cpp.h"
#include "players_tab.h"
#include "game.h"
#include "state.hpp"
#include "utility.h"

namespace PlayersTab {

	int framesPassed = -1;
	Vector2 previousPlayerPosition;

	void Render() {
		if (IsInGame() || IsInLobby()) {
			if (ImGui::BeginTabItem("Players")) {
				ImGui::BeginChild("players#list", ImVec2(200, 0), true);
				ImGui::ListBoxHeader("", ImVec2(200, 150));
				for (auto playerData : GetAllPlayerData()) {
					if (playerData->fields.Disconnected) continue;

					std::string playerName = convert_from_string(playerData->fields.PlayerName);
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
					if (ImGui::Selectable(std::string("##" + playerName).c_str(), State.selectedPlayer.equals(playerData))) {
						State.selectedPlayer = PlayerSelection(playerData);
					}
					ImGui::SameLine();
					ImGui::ColorButton(std::string("##" + playerName + "_ColorButton").c_str(), AmongUsColorToImVec4(GetPlayerColor(playerData->fields.ColorId)), ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
					ImGui::SameLine();
					ImGui::PopStyleVar(2);
					ImGui::Dummy(ImVec2(0, 0));
					ImGui::SameLine();

					ImVec4 nameColor;
					if (State.RevealImpostors && playerData->fields.IsImpostor)
						nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->ImpostorRed);
					else
						nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->White);

					if (playerData->fields.IsDead) nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->DisabledGrey);

					ImGui::TextColored(nameColor, playerName.c_str());
				}
				ImGui::ListBoxFooter();

				if (IsInMultiplayerGame() && IsInGame()) {
					float taskPercentage = (float) (*Game::pGameData)->fields.CompletedTasks / (float) (*Game::pGameData)->fields.TotalTasks;
					ImGui::TextColored(ImVec4(1.0f - taskPercentage, 1.0f, 1.0f - taskPercentage, 1.0f), "%.1f%% Total Tasks Completed", taskPercentage * 100);
				}

				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("players#actions", ImVec2(200, 0), true);

				if (IsInGame() && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) { //Player selection doesn't matter
					if (ImGui::Button("Call Meeting")) {
						State.rpcQueue.push(new RpcReportPlayer(PlayerSelection()));
					}
				}

				if (State.selectedPlayer.has_value())
				{
					if (IsInGame() && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) {
						ImGui::NewLine();
						if (ImGui::Button("Report Body")) {
							State.rpcQueue.push(new RpcReportPlayer(State.selectedPlayer));
						}
					}

					if (IsInGame() && !State.selectedPlayer.is_Disconnected() && !State.selectedPlayer.is_LocalPlayer())
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

					if (State.selectedPlayer.is_LocalPlayer() && State.originalName != "-") {
						if (ImGui::Button("Reset Name")) {
							if (IsInGame())
								State.rpcQueue.push(new RpcSetName(State.originalName));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new RpcSetName(State.originalName));
						}
					}
					else if(!State.selectedPlayer.is_LocalPlayer()) {
						if (!State.selectedPlayer.is_LocalPlayer() && (!State.AntiBan || !IsInMultiplayerGame()) && ImGui::Button("Steal Name")) {
							if (convert_from_string(State.selectedPlayer.get_PlayerData()->fields.PlayerName).length() < 10) {
								if(IsInGame())
									State.rpcQueue.push(new RpcSetName(convert_from_string(State.selectedPlayer.get_PlayerData()->fields.PlayerName) + " "));
								else if (IsInLobby())
									State.lobbyRpcQueue.push(new RpcSetName(convert_from_string(State.selectedPlayer.get_PlayerData()->fields.PlayerName) + " "));
							}
							else {
								if(IsInGame())
									State.rpcQueue.push(new RpcSetName(convert_from_string(State.selectedPlayer.get_PlayerData()->fields.PlayerName)));
								else if(IsInLobby())
									State.lobbyRpcQueue.push(new RpcSetName(convert_from_string(State.selectedPlayer.get_PlayerData()->fields.PlayerName)));
							}
						}
					}

					if (IsInGame() && GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor && !State.selectedPlayer.get_PlayerData()->fields.IsDead
						&& !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead && ((*Game::pLocalPlayer)->fields.killTimer <= 0.0f))
					{
						if (ImGui::Button("Kill Player"))
						{
							previousPlayerPosition = GetTrueAdjustedPosition(*Game::pLocalPlayer);
							State.rpcQueue.push(new RpcMurderPlayer(State.selectedPlayer));
							framesPassed = 14;
						}
					}

					if (framesPassed == 0)
					{
						State.rpcQueue.push(new RpcSnapTo(previousPlayerPosition));
						framesPassed--;
					}
					else framesPassed--;

					if (!State.selectedPlayer.is_LocalPlayer()) {
						if (ImGui::Button("Teleport To")) {
							if(IsInGame())
								State.rpcQueue.push(new RpcSnapTo(GetTrueAdjustedPosition(State.selectedPlayer.get_PlayerControl())));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new RpcSnapTo(GetTrueAdjustedPosition(State.selectedPlayer.get_PlayerControl())));
						}
					}

					ImGui::NewLine();

					if (IsInGame() && !State.selectedPlayer.is_Disconnected() && IsInMultiplayerGame())
					{
						auto tasks = GetNormalPlayerTasks(State.selectedPlayer.get_PlayerControl());

						if (State.RevealImpostors && State.selectedPlayer.get_PlayerData()->fields.IsImpostor)
						{
							ImGui::TextColored(ImVec4(0.8F, 0.2F, 0.0F, 1.0F), "Fake Tasks:");
						}
						else
						{
							ImGui::Text("Tasks:");
						}

						ImGui::ListBoxHeader("", ImVec2(181, 94));

						if (State.selectedPlayer.get_PlayerControl()->fields.myTasks == NULL)
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
						ImGui::ListBoxFooter();
					}
				}

				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
}