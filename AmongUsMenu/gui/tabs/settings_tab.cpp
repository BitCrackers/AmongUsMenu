#include "settings_tab.h"

namespace SettingsTab {
	void Render() {
		if (ImGui::BeginTabItem("Settings")) {

			ImGui::Dummy(ImVec2(4, 4));
			ImGui::Text("Change Theme Color:");
			ImGui::Dummy(ImVec2(4, 4));
			ImGui::PushItemWidth(ImGui::GetWindowWidth() / 3.5f);
			ImGui::ColorPicker4("##picker", (float*)&State.SelectedColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel);
			ImGui::PopItemWidth();
			ImGui::Dummy(ImVec2(4, 4));

			if (ImGui::Button("Reset Theme Color")) {
				State.SelectedColor = State.DefaultColor;
			}
#ifdef _DEBUG
			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7));
			ImGui::Checkbox("Show Debug Tab", &State.showDebugTab);
#endif
			ImGui::EndTabItem();
		}
	}
} 