#include "radar_tab.h"

namespace RadarTab {
	void Render() {
		if (ImGui::BeginTabItem("Radar")) {
			ImGui::Dummy(ImVec2(4, 4));
			ImGui::Checkbox("Show Radar", &State.ShowRadar);

			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));

			ImGui::Checkbox("Show Dead Bodies", &State.ShowRadar_DeadBodies);
			ImGui::Checkbox("Show Ghosts", &State.ShowRadar_Ghosts);
			ImGui::Checkbox("Right Click to Teleport", &State.ShowRadar_RightClick_Teleport);

			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));

			ImGui::Checkbox("Hide Radar During Meetings", &State.HideRadar_During_Meetings);
			ImGui::Checkbox("Lock Radar Position", &State.LockRadar);
			SteppedSliderFloat("Radar Opacity", &State.SelectedColor.w, 0.0f, 1.0f, 0.01f, "%.2f Opacity", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

			ImGui::EndTabItem();
		}
	}
}