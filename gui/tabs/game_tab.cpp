#include "game_tab.h"

namespace GameTab {
	void Render() {
		if (ImGui::BeginTabItem("Game")) {
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
			ImGui::NewLine();
			/*if (ImGui::Button("Edit Hotkeys")) {
				ImGui::OpenPopup("Hotkeys Editor");
			}
			ImGui::SameLine();*/
			ImGui::Checkbox("Console", &State.ShowConsole);
			//ImHotKey::Edit(State.Hotkeys.data(), State.Hotkeys.size(), "Hotkeys Editor");

			ImGui::EndTabItem();
		}
	}
}
