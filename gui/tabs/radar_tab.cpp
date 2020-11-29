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
			ImGui::Checkbox("Hide Radar During Meetings", &State.HideRadar_During_Meetings);
			ImGui::Checkbox("Right Click to Teleport", &State.ShowRadar_RightClick_Teleport);

			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));

			ImGui::PushItemWidth(ImGui::GetWindowWidth() / 3.5);
			ImGui::ColorPicker4("##picker", (float*)&State.SelectedColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::PopItemWidth();

			ImGui::EndTabItem();
		}
	}
}