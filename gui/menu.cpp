#include "pch-il2cpp.h"
#include "menu.hpp"
#include "imgui/imgui.h"
#include "tabs/doors_tab.h"
#include "tabs/game_tab.h"
#include "tabs/host_tab.h"
#include "tabs/players_tab.h"
#include "tabs/radar_tab.h"
#include "tabs/replay_tab.h"
#include "tabs/esp_tab.h"
#include "tabs/sabotage_tab.h"
#include "tabs/self_tab.h"
#include "tabs/settings_tab.h"
#include "tabs/tasks_tab.h"
#ifdef _DEBUG
#include "tabs/debug_tab.h"
#endif
#include "state.hpp"

namespace Menu {
	void Init() {
		ImGui::SetNextWindowSize(ImVec2(520, 320) * State.dpiScale, ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	bool firstRender = true;
	void Render() {
		if (!init)
			Menu::Init();

		ImGui::Begin("AmongUsMenu", &State.ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowFontScale(State.dpiScale);
		ImGui::BeginTabBar("AmongUs#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		if(!firstRender)
			SettingsTab::Render();
		GameTab::Render();
		SelfTab::Render();
		RadarTab::Render();
		ReplayTab::Render();
		EspTab::Render();
		PlayersTab::Render();
		TasksTab::Render();
		SabotageTab::Render();
		DoorsTab::Render();
		HostTab::Render();
#ifdef _DEBUG
		if (State.showDebugTab)
			DebugTab::Render();
#endif

		if(firstRender)
			firstRender = false;

		ImGui::EndTabBar();
		ImGui::End();
	}
}