#include "pch-il2cpp.h"
#include "settings_tab.h"
#include "utility.h"
#include "gui-helpers.hpp"
#include "state.hpp"
#include "game.h"
#include "achievements.hpp"
#include "DirectX.h"
#include "imgui/imgui_impl_win32.h" // ImGui_ImplWin32_GetDpiScaleForHwnd

namespace SettingsTab {
	void Render() {
		if (ImGui::BeginTabItem("Settings")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
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

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale); 
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			if (ImGui::Checkbox("Adjust by DPI", &State.AdjustByDPI)) {
				if (!State.AdjustByDPI) {
					State.dpiScale = 1.0f;
				}
				else {
					State.dpiScale = ImGui_ImplWin32_GetDpiScaleForHwnd(DirectX::window);
				}
				ImGui::GetStyle().ScaleAllSizes(State.dpiScale);
				State.Save();
			}
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

#ifdef _DEBUG
			if (ImGui::Checkbox("Show Debug Tab", &State.showDebugTab)) {
				State.Save();
			}
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
#endif
			//Change this to in game only once account is overridden
			{
				char* nameBuffer[12]{ const_cast<char*>(State.userName.c_str()) };
				if (ImGui::InputText("PlayerName", *nameBuffer, IM_ARRAYSIZE(nameBuffer))) {
					State.userName = std::string(*nameBuffer);
				}
			}

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			if (ImGui::Button("Unlock all Steam achievements"))
			{
				for (const char* achievement : steamAchievements)
				{
					Game::SteamUserStats_SetAchievement(convert_to_string(std::string(achievement)));
				}
				Game::SteamUserStats_StoreStats();
			}

			ImGui::EndTabItem();
		}
	}
}