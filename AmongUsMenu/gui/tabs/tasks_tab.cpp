#include "tasks_tab.h"

namespace TasksTab {

	bool playMedbayScan = false;

	void Render() {
		if (IsInGame() && GetPlayerData(*Game::pLocalPlayer)->fields.Tasks != NULL) {
			if (ImGui::BeginTabItem("Tasks")) {
				if (!GetPlayerData(*Game::pLocalPlayer)->fields.IsImpostor) {
					auto tasks = GetNormalPlayerTasks(*Game::pLocalPlayer);

					if (ImGui::Button("Complete All Tasks")) {
						for (auto task : tasks) {
							if (task->fields.taskStep != task->fields.MaxStep)
								State.rpcQueue.push(new RpcCompleteTask(task->fields._._Id_k__BackingField));
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

					ImGui::Dummy(ImVec2(7, 7));
					ImGui::Separator();
					ImGui::Dummy(ImVec2(7, 7));
				}

				if (ImGui::Button("Play Shields Animation"))
				{
					State.rpcQueue.push(new RpcPlayAnimation(1));
				}

				if (ImGui::Button("Play Weapons Animation"))
				{
					State.rpcQueue.push(new RpcPlayAnimation(6));
				}

				if(ImGui::Button("Play Trash Animation"))
				{
					State.rpcQueue.push(new RpcPlayAnimation(10));
				}

				if (ImGui::Checkbox("Play Medbay Scan Animation", &playMedbayScan))
				{
					if (playMedbayScan)
					{
						State.rpcQueue.push(new RpcSetScanner(true));
					}
					else
					{
						State.rpcQueue.push(new RpcSetScanner(false));
					}
				}

				ImGui::EndTabItem();
			}
		}

		if (!IsInGame() || State.InMeeting || GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)
		{
			playMedbayScan = false;
		}
	}
}