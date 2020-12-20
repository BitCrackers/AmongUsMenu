#include "radar_tab.h"

namespace RadarTab {
	void Render() {
		if (ImGui::BeginTabItem("Radar")) {
			ImGui::Dummy(ImVec2(4, 4));
			if (ImGui::Checkbox("Show Radar", &State.ShowRadar)) {
				State.Save();
			}
			ImGui::SameLine();
			if (HotKey(State.KeyBinds.Toggle_Radar)) {
				State.Save();
			}

			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));

			if (ImGui::Checkbox("Show Dead Bodies", &State.ShowRadar_DeadBodies)) {
				State.Save();
			}
			if (ImGui::Checkbox("Show Ghosts", &State.ShowRadar_Ghosts)) {
				State.Save();
			}
			if (ImGui::Checkbox("Right Click to Teleport", &State.ShowRadar_RightClick_Teleport)) {
				State.Save();
			}

			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));

			if (ImGui::Checkbox("Hide Radar During Meetings", &State.HideRadar_During_Meetings)) {
				State.Save();
			}
			if (ImGui::Checkbox("Lock Radar Position", &State.LockRadar)) {
				State.Save();
			}
			if (SteppedSliderFloat("Radar Opacity", &State.SelectedColor.w, 0.0f, 1.0f, 0.01f, "%.2f Opacity", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				State.Save();
			}

			ImGui::EndTabItem();
		}
	}
}