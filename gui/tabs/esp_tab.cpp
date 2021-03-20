#include "pch-il2cpp.h"
#include "esp_tab.h"
#include "game.h"
#include "state.hpp"
#include "utility.h"

namespace EspTab {

	void Render() {
		if (IsInGame())
		{
			if (ImGui::BeginTabItem("Esp"))
			{
				ImGui::Checkbox("Enable", &State.ShowEsp);

				ImGui::Checkbox("Show Ghosts", &State.ShowEsp_Ghosts);
				ImGui::Checkbox("Hide During Meetings", &State.HideEsp_During_Meetings);

				ImGui::Checkbox("Show Box", &State.ShowEsp_Box);
				ImGui::Checkbox("Show Tracers", &State.ShowEsp_Tracers);
				ImGui::Checkbox("Show Distance", &State.ShowEsp_Distance);

				ImGui::EndTabItem();
			}
		}
	}
}