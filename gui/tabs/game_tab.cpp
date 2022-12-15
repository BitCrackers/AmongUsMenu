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
					GameLogicOptions().SetFloat(app::FloatOptionNames__Enum::PlayerSpeedMod, State.PlayerSpeed);
					State.PrevPlayerSpeed = State.PlayerSpeed;
				}
			}
			if (CustomListBoxInt("Kill Distance", &State.KillDistance, KILL_DISTANCE, 225 * State.dpiScale)) {
				if (!IsInGame()) State.KillDistance = State.PrevKillDistance;
				else {
					GameLogicOptions().SetInt(app::Int32OptionNames__Enum::KillDistance, State.KillDistance);
					State.PrevKillDistance = State.KillDistance;
				}
			}
			if (GameOptions().GetGameMode() == GameModes__Enum::Normal) {
				if (CustomListBoxInt("Task Bar Updates", &State.TaskBarUpdates, TASKBARUPDATES, 225 * State.dpiScale)) {
					if (!IsInGame()) State.TaskBarUpdates = State.PrevTaskBarUpdates;
					else {
						GameLogicOptions().SetInt(app::Int32OptionNames__Enum::TaskBarMode, State.TaskBarUpdates);
						State.PrevTaskBarUpdates = State.TaskBarUpdates;
					}
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

			if (ImGui::Checkbox("AUM Chat", &State.ShowChat)) {
				State.Save();
			}

			ImGui::SameLine();

			ImGui::SameLine();
			if (HotKey(State.KeyBinds.Toggle_Chat)) {
				State.Save();
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if ((State.mapType == Settings::MapType::Airship) && IsHost() && IsInGame() && ImGui::Button("Switch Moving Platform Side"))
			{
				State.rpcQueue.push(new RpcUsePlatform());
			}
#ifdef _DEBUG
			if (IsInGame() || IsInLobby())
			{
				ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
				ImGui::Separator();
				ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

				GameOptions options;
				if (options.GetGameMode() == GameModes__Enum::Normal)
				{
					auto allPlayers = GetAllPlayerControl();
					RoleRates roleRates = RoleRates(options, (int)allPlayers.size());
					// this should be all the major ones. if people want more they're simple enough to add.
					ImGui::Text("Visual Tasks: %s", (options.GetBool(app::BoolOptionNames__Enum::VisualTasks) ? "on" : "off"));
					ImGui::Text("Taskbar Update Mode: %s", (options.GetInt(app::Int32OptionNames__Enum::TaskBarMode)
															== (int)app::TaskBarMode__Enum::Normal ? "Normal" : "MeetingOnly"));
					ImGui::Text("Confirm Impostor: %s", (options.GetBool(app::BoolOptionNames__Enum::ConfirmImpostor) ? "on" : "off"));
					ImGui::Text("Kill CD: %.2f", options.GetKillCooldown());

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Max Engineers: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Engineer));
					ImGui::Text("Engineer CD: %.2f", options.GetFloat(app::FloatOptionNames__Enum::EngineerCooldown, 1.0F));
					ImGui::Text("Engineer Duration: %.2f", options.GetFloat(app::FloatOptionNames__Enum::EngineerInVentMaxTime, 1.0F) );

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Max Angels: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::GuardianAngel));
					ImGui::Text("Angel CD: %.2f", options.GetFloat(app::FloatOptionNames__Enum::GuardianAngelCooldown, 1.0F));
					ImGui::Text("Angel Duration: %.2f", options.GetFloat(app::FloatOptionNames__Enum::ProtectionDurationSeconds, 1.0F));

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);

					ImGui::Text("Max Shapeshifters: %d", roleRates.GetRoleCount(app::RoleTypes__Enum::Shapeshifter));
					ImGui::Text("Shapeshifter CD: %.2f", options.GetFloat(app::FloatOptionNames__Enum::ShapeshifterCooldown, 1.0F));
					ImGui::Text("Shapeshifter Duration: %.2f", options.GetFloat(app::FloatOptionNames__Enum::ShapeshifterDuration, 1.0F));

					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(3, 3) * State.dpiScale);
				}
				else if (options.GetGameMode() == GameModes__Enum::HideNSeek) {
					// TODO: HideNSeek
				}
			}
#endif
			ImGui::EndTabItem();
		}
	}
}
