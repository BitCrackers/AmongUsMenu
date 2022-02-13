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
#ifdef _DEBUG
			ImGui::SameLine();
			ImGui::Text("Num Raw Events: %d", State.rawEvents.size());
			ImGui::Text("Num Live Events: %d", State.liveReplayEvents.size());
#endif
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