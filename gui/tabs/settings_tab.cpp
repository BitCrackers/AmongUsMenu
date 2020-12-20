#include "settings_tab.h"

namespace SettingsTab {
	void Render() {
		if (ImGui::BeginTabItem("Settings")) {

			ImGui::Dummy(ImVec2(4, 4));
			ImGui::Text("Change Theme Color:");
			ImGui::Dummy(ImVec2(4, 4));
			ImGui::PushItemWidth(ImGui::GetWindowWidth() / 3.5f);
			if (ImGui::ColorPicker4("##picker", (float*)&State.SelectedColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel)) {
				State.Save();
			}
			ImGui::PopItemWidth();
			ImGui::Dummy(ImVec2(4, 4));

			if (ImGui::Button("Reset Theme Color")) {
				State.SelectedColor = State.DefaultColor;
				State.Save();
			}

			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));

			ImGui::Text("Show/Hide Menu Keybind:");
			ImGui::SameLine();
			if (HotKey(State.KeyBinds.Toggle_Menu)) {
				State.Save();
			}

			ImGui::Text("Show/Hide Console Keybind:");
			ImGui::SameLine();
			if (HotKey(State.KeyBinds.Toggle_Console)) {
				State.Save();
			}
#ifdef _DEBUG
			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));
			if (ImGui::Checkbox("Show Debug Tab", &State.showDebugTab)) {
				State.Save();
			}
#endif
			ImGui::EndTabItem();
		}
	}
} 