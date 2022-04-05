#include "pch-il2cpp.h"
#include "replay_tab.h"
#include "gui-helpers.hpp"
#include "state.hpp"
#include <chrono>

namespace ReplayTab {
	void Render() {
		if (ImGui::BeginTabItem("Replay")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			if (ImGui::Checkbox("Show Replay", &State.ShowReplay)) {
				State.Save();
			}
			ImGui::SameLine();
			if (HotKey(State.KeyBinds.Toggle_Replay)) {
				State.Save();
			}
			if (ImGui::Checkbox("Show only last", &State.Replay_ShowOnlyLastSeconds))
			{
				State.Save();
			}
			ImGui::SameLine();
			if (ImGui::SliderInt("seconds", &State.Replay_LastSecondsValue, 1, 600, "%d", ImGuiSliderFlags_AlwaysClamp))
			{
				State.Save();
			}

			if (ImGui::Checkbox("Clear after meeting", &State.Replay_ClearAfterMeeting))
			{
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