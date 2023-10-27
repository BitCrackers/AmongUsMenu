#include "pch-il2cpp.h"
#include "esp_tab.h"
#include "game.h"
#include "state.hpp"
#include "utility.h"

namespace EspTab {

	void Render() {
		bool changed = false;
		if (ImGui::BeginTabItem("ESP")) {

			changed |= ImGui::Checkbox("Enable", &State.ShowEsp);

			changed |= ImGui::Checkbox("Show Ghosts", &State.ShowEsp_Ghosts);
			changed |= ImGui::Checkbox("Hide During Meetings", &State.HideEsp_During_Meetings);

			changed |= ImGui::Checkbox("Show Box", &State.ShowEsp_Box);
			changed |= ImGui::Checkbox("Show Tracers", &State.ShowEsp_Tracers);
			changed |= ImGui::Checkbox("Show Distance", &State.ShowEsp_Distance);

			changed |= ImGui::Checkbox("Role-based", &State.ShowEsp_RoleBased);

			if (State.ShowEsp_RoleBased) {
				ImGui::SameLine();
				changed |= ImGui::Checkbox("Crewmates", &State.ShowEsp_Crew);
				ImGui::SameLine();
				changed |= ImGui::Checkbox("Impostors", &State.ShowEsp_Imp);
			}

			ImGui::EndTabItem();
		}
		if (changed) {
			State.Save();
		}
	}
}