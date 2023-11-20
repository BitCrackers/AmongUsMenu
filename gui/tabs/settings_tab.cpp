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
			if (ImGui::Checkbox("Panic (Disable SMAU)", &State.DisableSMAU)) {
				State.Save();
			}
			if (State.ShowKeybinds) {
				ImGui::SameLine();
				if (HotKey(State.KeyBinds.Toggle_SMAU)) {
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

			static const std::vector<const char*> DPI_SCALING_LEVEL = { "50%", "55%", "60%", "65%", "70%", "75%", "80%", "85%", "90%", "95%", "100%", "105%", "110%", "115%", "120%", "125%", "130%", "135%", "140%", "145%", "150%", "155%", "160%", "165%", "170%", "175%", "180%", "185%", "190%", "195%", "200%", "205%", "210%", "215%", "220%", "225%", "230%", "235%", "240%", "245%", "250%", "255%", "260%", "265%", "270%", "275%", "280%", "285%", "290%", "295%", "300%" };
			ImGui::SameLine();
			int scaleIndex = (int(std::clamp(State.dpiScale, 0.5f, 3.0f) * 100.0f) - 50) / 5;
			if (CustomListBoxInt("Scaling Level", &scaleIndex, DPI_SCALING_LEVEL, 100 * State.dpiScale)) {
				State.dpiScale = (scaleIndex * 5 + 50) / 100.0f;
				State.dpiChanged = true;
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if (ImGui::ColorEdit3("Menu Theme Color", (float*)&State.MenuThemeColor, ImGuiColorEditFlags__OptionsDefault | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview)) {
				State.Save();
			}

			if (ImGui::Checkbox("RGB Menu Theme", &State.RgbMenuTheme)) {
				State.Save();
			}
			ImGui::SameLine();
			SteppedSliderFloat("Opacity", (float*)&State.MenuThemeColor.w, 0.1f, 1.f, 0.01f, "%.2f", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

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
			char* nameBufferHost[255]{ const_cast<char*>(State.userName.c_str()) };
			if (ImGui::InputText("Username", *nameBufferHost, IM_ARRAYSIZE(nameBufferHost))) {
				State.userName = std::string(*nameBufferHost);
			}

			if (!(IsHost() || !State.SafeMode)) {
				if (State.userName.length() >= (size_t)13)
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Username is too long, gets detected by anticheat. This name will be ignored.");
				else if (!IsNameValid(State.userName))
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Username contains characters blocked by anticheat. This name will be ignored.");
			}
			ImGui::SameLine();
			if (ImGui::Button("Set Name") && (!IsNameValid(State.userName) || (IsHost() || !State.SafeMode))) {
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

			if (ImGui::Checkbox("Hide Friend Code (restart game to apply)", &State.HideFriendCode)) {
				State.Save();
			}
			ImGui::SameLine();/*
			if (ImGui::Checkbox("Spoof Friend Code", &State.SpoofFriendCode)) {
				State.Save();
			}
			char* fcBuffer[14]{ const_cast<char*>(State.FakeFriendCode.c_str()) };
			if (ImGui::InputText("Fake Friend Code", *fcBuffer, IM_ARRAYSIZE(fcBuffer))) {
				State.userName = std::string(*fcBuffer);
			}
			ImGui::SameLine();*/
			if (ImGui::Checkbox("Safe Mode", &State.SafeMode)) {
				State.Save();
			}

			ImGui::Text("Keep safe mode on in official servers (NA, Europe, Asia) to prevent anticheat detection!");
			ImGui::Separator();
			ImGui::Text("SickoModeAU v2.0 | Original menu: https://github.com/Bitcrackers/AmongUsMenu");
			ImGui::Text("Modded by g0aty (GitHub) / @goatwo (YT)");

			ImGui::EndTabItem();
		}
	}
}
