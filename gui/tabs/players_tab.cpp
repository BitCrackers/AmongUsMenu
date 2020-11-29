#include "players_tab.h"

namespace PlayersTab {
	void Render() {
		if (IsInGame()) {
			if (ImGui::BeginTabItem("Players")) {
				ImGui::BeginChild("players#list", ImVec2(200, 0), true);
				ImGui::ListBoxHeader("", ImVec2(200, 150));
				for (auto playerData : GetAllPlayerData()) {
					if (playerData->fields.Disconnected) continue;

					std::string playerName = convert_from_string(playerData->fields.PlayerName);
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
					if (ImGui::Selectable(std::string("##" + playerName).c_str(), State.selectedPlayerId == playerData->fields.PlayerId)) {
						State.selectedPlayerId = playerData->fields.PlayerId;
						State.selectedPlayer = GetPlayerControlById(playerData->fields.PlayerId);
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
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("players#actions", ImVec2(200, 0), true);

				if (State.selectedPlayerId > -1 && GetPlayerData(GetPlayerControlById(State.selectedPlayerId)) != nullptr)
				{

					if (IsInMultiplayerGame() && !IsHost()) {
						if (!GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) {
							if (ImGui::Button("Call Meeting")) {
								PlayerControl_CmdReportDeadBody(*Game::pLocalPlayer, NULL, NULL);
							}
							ImGui::NewLine();
							if (State.selectedPlayerId > -1 && State.selectedPlayer != *Game::pLocalPlayer && ImGui::Button("Report Body")) {
								PlayerControl_CmdReportDeadBody(*Game::pLocalPlayer, GetPlayerData(State.selectedPlayer), NULL);
							}
						}

						if (State.selectedPlayerId > -1 && !GetPlayerData(State.selectedPlayer)->fields.Disconnected && State.selectedPlayer != *Game::pLocalPlayer)
						{
							if (State.selectedPlayer->fields.PlayerId != State.PlayerToFollow.fields.PlayerId)
							{
								if (ImGui::Button("Spectate"))
								{
									State.FreeCam = false;
									State.PlayerToFollow = *State.selectedPlayer;
									State.FollowPlayer = true;
								}
							}
							else if (State.FollowPlayer)
							{
								if (ImGui::Button("Stop Spectating"))
								{
									State.FollowPlayer = false;
									State.PlayerToFollow = **Game::pLocalPlayer;
								}
							}
							else
							{
								if (ImGui::Button("Spectate"))
								{
									State.FreeCam = false;
									State.PlayerToFollow = *State.selectedPlayer;
									State.FollowPlayer = true;
								}
							}
						}
					}

					if (State.selectedPlayerId > -1 && State.selectedPlayer != *Game::pLocalPlayer) {
						if (ImGui::Button("Teleport To") && !(*Game::pLocalPlayer)->fields.inVent) {
							State.rpcQueue.push(new RpcSnapTo(PlayerControl_GetTruePosition(State.selectedPlayer, NULL)));
						}
					}

					ImGui::NewLine();

					if (State.selectedPlayerId > -1 && !GetPlayerData(State.selectedPlayer)->fields.Disconnected && IsInMultiplayerGame())
					{
						auto tasks = GetNormalPlayerTasks(State.selectedPlayer);

						if (State.RevealImpostors && GetPlayerData(State.selectedPlayer)->fields.IsImpostor)
						{
							ImGui::TextColored(ImVec4(0.8F, 0.2F, 0.0F, 1.0F), "Fake Tasks:");
						}
						else
						{
							ImGui::Text("Tasks:");
						}

						ImGui::ListBoxHeader("", ImVec2(181, 94));

						if (State.selectedPlayer->fields.myTasks == nullptr)
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