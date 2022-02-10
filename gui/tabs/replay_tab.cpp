#include "pch-il2cpp.h"
#include "replay_tab.h"
#include "state.hpp"

namespace ReplayTab {
	void Render() {
		if (ImGui::BeginTabItem("Replay")) {
			ImGui::Dummy(ImVec2(4, 4));
			if (ImGui::Checkbox("Show Replay", &State.ShowReplay)) {
				State.Save();
			}
			if (ImGui::ColorEdit4("Replay Map Color",
				(float*)&State.SelectedReplayMapColor,
				ImGuiColorEditFlags__OptionsDefault
				| ImGuiColorEditFlags_NoInputs
				| ImGuiColorEditFlags_AlphaBar
				| ImGuiColorEditFlags_AlphaPreview)) {
				State.Save();
			}
			ImGui::EndTabItem();
		}
	}
}