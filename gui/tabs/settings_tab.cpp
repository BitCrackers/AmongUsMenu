#include "pch-il2cpp.h"
#include "settings_tab.h"
#include "utility.h"
#include "gui-helpers.hpp"
#include "state.hpp"
#include "game.h"
#include "achievements.hpp"
#include "DirectX.h"
#include "imgui/imgui_impl_win32.h" // ImGui_ImplWin32_GetDpiScaleForHwnd
#include "theme.hpp" // ApplyTheme

namespace SettingsTab {
	void Render() {
		if (ImGui::BeginTabItem("Settings")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			if (ImGui::Checkbox("Show Keybinds", &State.ShowKeybinds)) {
				State.Save();
			}
			if (State.ShowKeybinds) {
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
				State.dpiChanged = true;
				State.Save();
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			if (SteppedSliderFloat("Menu Size", &State.dpiScale, 0.5f, 3.f, 0.05f, "%.2fx", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput)) {
				State.Save();
			}

			if (ImGui::ColorEdit4("Menu Theme Color", (float*)&State.MenuThemeColor, ImGuiColorEditFlags__OptionsDefault | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview)) {
				State.Save();
			}

			if (ImGui::Checkbox("RGB Menu Theme", &State.RgbMenuTheme)) {
				State.Save();
			}

			if (ImGui::Button("Reset Menu Theme Color"))
			{
				State.MenuThemeColor = ImVec4(0.502f, 0.075f, 0.256f, 1.f);
			}

#ifdef _DEBUG
			if (ImGui::Checkbox("Show Debug Tab", &State.showDebugTab)) {
				State.Save();
			}
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
#endif
			//Change this to in game only once account is overridden
			{
				if (IsHost() || State.SafeMode == false) {
					char* nameBufferHost[255]{ const_cast<char*>(State.userName.c_str()) };
					if (ImGui::InputText("Username", *nameBufferHost, IM_ARRAYSIZE(nameBufferHost))) {
						State.userName = std::string(*nameBufferHost);
					}
				}
				else {
					char* nameBuffer[13]{ const_cast<char*>(State.userName.c_str()) };
					if (ImGui::InputText("Username", *nameBuffer, IM_ARRAYSIZE(nameBuffer))) {
						State.userName = std::string(*nameBuffer);
					}
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Set Name")) {
				SetPlayerName(State.userName);
				LOG_INFO("Successfully set name to \"" + State.userName + "\"");
				if (IsInGame())
					State.rpcQueue.push(new RpcSetName(State.userName));
				else if (IsInLobby())
					State.lobbyRpcQueue.push(new RpcSetName(State.userName));
			}
			if (ImGui::Checkbox("Automatically Set Name", &State.SetName)) {
				State.Save();
			}

			char* codeBuffer[15]{ const_cast<char*>(State.customCode.c_str()) };
			if (ImGui::InputText("Custom Code", *codeBuffer, IM_ARRAYSIZE(codeBuffer))) {
				State.customCode = std::string(*codeBuffer);
			}
			if (ImGui::Checkbox("Replace Streamer Mode Lobby Code", &State.HideCode)) {
				State.Save();
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("RGB Lobby Code", &State.RgbLobbyCode)) {
				State.Save();
			}

			if (ImGui::Checkbox("Spoof Level", &State.SetLevel)) {
				State.Save();
			}
			ImGui::SameLine();
			if (ImGui::InputInt("Level", &State.FakeLevel, 0, 1)) {
				State.Save();
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

			if (Achievements::IsSupported() && ImGui::Button("Unlock all achievements"))
			{
				Achievements::UnlockAll();
			}

			ImGui::SameLine();
			if (ImGui::Checkbox("Unlock Cosmetics", &State.UnlockCosmetics)) {
				State.Save();
			}

			if (ImGui::Checkbox("Hide Friend Code", &State.HideFriendCode)) {
				State.Save();
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Safe Mode", &State.SafeMode)) {
				State.Save();
			}

			ImGui::Text("Keep safe mode on in official servers (NA, Europe, Asia) to prevent anticheat detection!");
			ImGui::Text("SickoModeAU v1.0_pr2 | Original menu: Bitcrackers/AmongUsMenu | Modded by @goatwo (YT)");

			ImGui::EndTabItem();
		}
	}
}