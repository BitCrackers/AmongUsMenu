#include "pch-il2cpp.h"
#include "tasks_tab.h"
#include "game.h"
#include "state.hpp"
#include "utility.h"
#include "gui-helpers.hpp"

namespace TasksTab {
	void Render() {
		if (IsInGame() && GetPlayerData(*Game::pLocalPlayer)->fields.Tasks != NULL) {
			if (ImGui::BeginTabItem("Tasks")) {
				ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
				//if (!PlayerIsImpostor(GetPlayerData(*Game::pLocalPlayer))) {
					auto tasks = GetNormalPlayerTasks(*Game::pLocalPlayer);

					if (ImGui::Button("Complete All Tasks")) {
						for (auto task : tasks) {
							if (task->fields.taskStep != task->fields.MaxStep)
								State.rpcQueue.push(new RpcCompleteTask(task->fields._._Id_k__BackingField));
						}
					}
					if (State.ShowKeybinds) {
						ImGui::SameLine();
						HotKey(State.KeyBinds.Complete_Tasks);
					}
					if (!State.SafeMode) {
						ImGui::SameLine();
					}
					if (!State.SafeMode && ImGui::Button("Complete Everyone's Tasks")) {
						for (auto player : GetAllPlayerControl()) {
							auto playerTasks = GetNormalPlayerTasks(player);
							for (auto playerTask : playerTasks) {
								State.rpcQueue.push(new RpcForceCompleteTask(player, playerTask->fields._._Id_k__BackingField));
							}
						}
					}

					ImGui::NewLine();

					for (auto task : tasks) {
						if (ImGui::Button(("Complete##Button" + std::to_string(task->fields._._Id_k__BackingField)).c_str()) && !NormalPlayerTask_get_IsComplete(task, NULL)) {
							State.rpcQueue.push(new RpcCompleteTask(task->fields._._Id_k__BackingField));
						}

						ImGui::SameLine();

						ImGui::TextColored(NormalPlayerTask_get_IsComplete(task, NULL)
							? ImVec4(0.0F, 1.0F, 0.0F, 1.0F)
							: AmongUsColorToImVec4(app::Palette__TypeInfo->static_fields->White)
							, TranslateTaskTypes(task->fields._.TaskType));
					}

					ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
					ImGui::Separator();
					ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
				//}

				GameOptions options;
				if (options.GetGameMode() == GameModes__Enum::Normal && !options.GetBool(app::BoolOptionNames__Enum::VisualTasks)) {
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Visual tasks are turned OFF in this lobby.");
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Any animations (other than cameras) are client-sided only!");
				}
				else if (options.GetGameMode() == GameModes__Enum::HideNSeek)
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Animations other than cameras are client-sided only in Hide n Seek!");

				if (State.mapType == Settings::MapType::Ship) {
					if ((options.GetGameMode() == GameModes__Enum::Normal && !options.GetBool(app::BoolOptionNames__Enum::VisualTasks)) || options.GetGameMode() == GameModes__Enum::HideNSeek) {
						if (ImGui::Button("Play Shields Animation (Client-sided)"))
						{
							State.rpcQueue.push(new RpcPlayAnimation(1));
						}
					}
					else {
						if (ImGui::Button("Play Shields Animation"))
						{
							State.rpcQueue.push(new RpcPlayAnimation(1));
						}
					}
				}

				if (State.mapType == Settings::MapType::Ship) {
					if ((options.GetGameMode() == GameModes__Enum::Normal && !options.GetBool(app::BoolOptionNames__Enum::VisualTasks)) || options.GetGameMode() == GameModes__Enum::HideNSeek) {
						if (ImGui::Button("Play Trash Animation (Client-sided)"))
						{
							State.rpcQueue.push(new RpcPlayAnimation(10));
						}
					}
					else {
						if (ImGui::Button("Play Trash Animation"))
						{
							State.rpcQueue.push(new RpcPlayAnimation(10));
						}
					}
				}

				if (State.mapType == Settings::MapType::Ship || State.mapType == Settings::MapType::Pb) {
					
					if ((options.GetGameMode() == GameModes__Enum::Normal && !options.GetBool(app::BoolOptionNames__Enum::VisualTasks)) || options.GetGameMode() == GameModes__Enum::HideNSeek) {
						if (ImGui::Checkbox("Play Weapons Animation (Client-sided)", &State.PlayWeaponsAnimation))
						{
							State.Save();
						}
					}
					else {
						if (ImGui::Checkbox("Play Weapons Animation", &State.PlayWeaponsAnimation))
						{
							State.Save();
						}
					}
				}

				if ((options.GetGameMode() == GameModes__Enum::Normal && !options.GetBool(app::BoolOptionNames__Enum::VisualTasks)) || options.GetGameMode() == GameModes__Enum::HideNSeek) {
					if (ImGui::Checkbox("Play Medbay Scan Animation (Client-sided)", &State.PlayMedbayScan))
					{
						if (State.PlayMedbayScan)
						{
							State.rpcQueue.push(new RpcSetScanner(true));
						}
						else
						{
							State.rpcQueue.push(new RpcSetScanner(false));
						}
					}
				}
				else {
					if (ImGui::Checkbox("Play Medbay Scan Animation", &State.PlayMedbayScan))
					{
						if (State.PlayMedbayScan)
						{
							State.rpcQueue.push(new RpcSetScanner(true));
						}
						else
						{
							State.rpcQueue.push(new RpcSetScanner(false));
						}
					}
				}

				if (ImGui::Checkbox("Fake Cameras In Use", &State.FakeCameraUsage))
				{
					State.rpcQueue.push(new RpcUpdateSystem(SystemTypes__Enum::Security, (State.FakeCameraUsage ? 1 : 0)));
				}

				if (IsInMultiplayerGame() && IsInGame()) {
					float taskPercentage = (float)(*Game::pGameData)->fields.CompletedTasks / (float)(*Game::pGameData)->fields.TotalTasks;
					ImGui::TextColored(ImVec4(1.0f - taskPercentage, 1.0f, 1.0f - taskPercentage, 1.0f), "%.2f%% Total Tasks Completed", taskPercentage * 100);
				}

				ImGui::EndTabItem();
			}
		}
	}
}