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
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("players#actions", ImVec2(200, 0), true);

				if (!GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) { //Player selection doesn't matter
					if (ImGui::Button("Call Meeting")) {
						State.rpcQueue.push(new RpcReportPlayer(PlayerSelection(*Game::pLocalPlayer)));
					}
				}

				if (State.selectedPlayer.has_value())
				{
					if (!GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) {
						ImGui::NewLine();
						if (!State.selectedPlayer.is_LocalPlayer() && ImGui::Button("Report Body")) {
							State.rpcQueue.push(new RpcReportPlayer(State.selectedPlayer));
						}
					}

					if (!State.selectedPlayer.is_Disconnected() && !State.selectedPlayer.is_LocalPlayer())
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

					if (!State.selectedPlayer.is_LocalPlayer()) {
						if (ImGui::Button("Teleport To") && !(*Game::pLocalPlayer)->fields.inVent) {
							State.rpcQueue.push(new RpcSnapTo(GetTrueAdjustedPosition(State.selectedPlayer.get_PlayerControl())));
						}
					}

					ImGui::NewLine();

					if (!State.selectedPlayer.is_Disconnected() && IsInMultiplayerGame())
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