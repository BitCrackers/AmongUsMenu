#include "radar_tab.h"

namespace RadarTab {
	void Render() {
		if (ImGui::BeginTabItem("Radar")) {
			ImGui::Checkbox("Show Radar", &State.ShowRadar);
			ImGui::Checkbox("Show Dead Bodies", &State.ShowRadar_DeadBodies);
			ImGui::Checkbox("Show Ghosts", &State.ShowRadar_Ghosts);
			ImGui::Checkbox("Right Click to Teleport", &State.ShowRadar_RightClick_Teleport);
			ImGui::EndTabItem();
		}
	}
}