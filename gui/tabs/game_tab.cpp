#include "pch-il2cpp.h"
#include "game_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"

namespace GameTab {
	void Render() {
		if (ImGui::BeginTabItem("Game")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			if (SteppedSliderFloat("Player Speed", &State.PlayerSpeed, 0.5f, 3.f, 0.25f, "%.2fx", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				if (!IsInGame()) State.PlayerSpeed = State.PrevPlayerSpeed;
				else {
					(*Game::pGameOptionsData)->fields._.playerSpeedMod = State.PlayerSpeed;
					State.PrevPlayerSpeed = State.PlayerSpeed;
				}
			}
			if (CustomListBoxInt("Kill Distance", &State.KillDistance, KILL_DISTANCE, 225 * State.dpiScale)) {
				if (!IsInGame()) State.KillDistance = State.PrevKillDistance;
				else {
					(*Game::pGameOptionsData)->fields._.killDistance = State.KillDistance;
					State.PrevKillDistance = State.KillDistance;
				}
			}
			if (CustomListBoxInt("Task Bar Updates", &State.TaskBarUpdates, TASKBARUPDATES, 225 * State.dpiScale)) {
				if (!IsInGame()) State.TaskBarUpdates = State.PrevTaskBarUpdates;
				else {
					(*Game::pGameOptionsData)->fields.TaskBarMode = (TaskBarMode__Enum)State.TaskBarUpdates;
					State.PrevTaskBarUpdates = State.TaskBarUpdates;
				}
			}

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			
			if (ImGui::Button("Set Color") && (IsInGame() || IsInLobby()))
			{
				bool colorAvailable = true;

				for (PlayerControl* player : GetAllPlayerControl())
				{
					app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(player));
					if (outfit == NULL) continue;
					if (State.SelectedColorId == outfit->fields.ColorId)
					{
						colorAvailable = false;
						break;
					}
				}

				if (colorAvailable) {
					if (IsInGame())
						State.rpcQueue.push(new RpcSetColor(State.SelectedColorId));
					else if (IsInLobby())
						State.lobbyRpcQueue.push(new RpcSetColor(State.SelectedColorId));
				}
			}

			ImGui::SameLine(87 * State.dpiScale);
			CustomListBoxInt(" ", &State.SelectedColorId, COLORS, 85.0f * State.dpiScale);

			ImGui::SameLine(215 * State.dpiScale);
			if (ImGui::Button("Random Color"))
			{
				State.SelectedColorId = GetRandomColorId();
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if (ImGui::Checkbox("Console", &State.ShowConsole)) {
				State.Save();
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if ((State.mapType == Settings::MapType::Airship) && IsHost() && IsInGame() && ImGui::Button("Switch Moving Platform Side"))
			{
				State.rpcQueue.push(new RpcUsePlatform());
			}

			if (Game::pGameOptionsData != NULL)
			{
				ImGui::Dummy(ImVec2(7, 7));
				ImGui::Separator();
				ImGui::Dummy(ImVec2(7, 7));

				app::GameOptionsData* options = *Game::pGameOptionsData;
				if (options != NULL)
				{
					auto allPlayers = GetAllPlayerControl();
					RoleRates roleRates = RoleRates(options->fields, allPlayers.size());
					// this should be all the major ones. if people want more they're simple enough to add.
					ImGui::Text("Visual Tasks: %s", (options->fields.VisualTasks == true ? "on" : "off"));
					ImGui::Text("Taskbar Update Mode: %s", (options->fields.TaskBarMode == app::TaskBarMode__Enum::Normal ? "Normal" : "MeetingOnly"));
					ImGui::Text("Confirm Impostor: %s", (options->fields.ConfirmImpostor == true ? "on" : "off"));
					ImGui::Text("Kill CD: %.2f", options->fields._.killCooldown);

					ImGui::Dummy(ImVec2(3, 3));
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3));

					ImGui::Text("Max Engineers: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Engineer));
					ImGui::Text("Engineer CD: %.2f", options->fields.RoleOptions->fields.EngineerCooldown);
					ImGui::Text("Engineer Duration: %.2f", options->fields.RoleOptions->fields.EngineerInVentMaxTime);

					ImGui::Dummy(ImVec2(3, 3));
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3));

					ImGui::Text("Max Angels: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::GuardianAngel));
					ImGui::Text("Angel CD: %.2f", options->fields.RoleOptions->fields.GuardianAngelCooldown);
					ImGui::Text("Angel Duration: %.2f", options->fields.RoleOptions->fields.ProtectionDurationSeconds);

					ImGui::Dummy(ImVec2(3, 3));
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3));

					ImGui::Text("Max Shapeshifters: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Shapeshifter));
					ImGui::Text("Shapeshifter CD: %.2f", options->fields.RoleOptions->fields.ShapeshifterCooldown);
					ImGui::Text("Shapeshifter Duration: %.2f", options->fields.RoleOptions->fields.ShapeshifterDuration);

					ImGui::Dummy(ImVec2(3, 3));
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3));
				}
			}

			ImGui::EndTabItem();
		}
	}
}
