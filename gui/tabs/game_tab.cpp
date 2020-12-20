#include "game_tab.h"

namespace GameTab {
	void Render() {
		if (ImGui::BeginTabItem("Game")) {
			ImGui::Dummy(ImVec2(4, 4));
			if (SteppedSliderFloat("Player Speed", &State.PlayerSpeed, 0.5f, 3.f, 0.25f, "%.2fx", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				if (!IsInGame()) State.PlayerSpeed = State.PrevPlayerSpeed;
				else {
					(*Game::pGameOptionsData)->fields.PlayerSpeedMod = State.PlayerSpeed;
					State.PrevPlayerSpeed = State.PlayerSpeed;
				}
			}
			if (CustomListBoxInt("Kill Distance", &State.KillDistance, KILL_DISTANCE)) {
				if (!IsInGame()) State.KillDistance = State.PrevKillDistance;
				else {
					(*Game::pGameOptionsData)->fields.KillDistance = State.KillDistance;
					State.PrevKillDistance = State.KillDistance;
				}
			}
			if (CustomListBoxInt("Task Bar Updates", &State.TaskBarUpdates, TASKBARUPDATES)) {
				if (!IsInGame()) State.TaskBarUpdates = State.PrevTaskBarUpdates;
				else {
					(*Game::pGameOptionsData)->fields.TaskBarUpdates = (TaskBarUpdates__Enum)State.TaskBarUpdates;
					State.PrevTaskBarUpdates = State.TaskBarUpdates;
				}
			}

			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));
			
			if (ImGui::Checkbox("Anti Kick/Ban", &State.AntiBan))
			{
				if (IsInLobby() || IsInGame())
				{
					State.AntiBan = !State.AntiBan;
				}
			}
			if (ImGui::Checkbox("Console", &State.ShowConsole)) {
				State.Save();
			}

			ImGui::EndTabItem();
		}
	}
}
