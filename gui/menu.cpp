#include "menu.hpp"

using namespace app;

namespace Menu {
	void Init() {
		ImGui::SetNextWindowSize(ImVec2(500, 270), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	bool firstRender = true;
	void Render() {
		if (!init)
			Menu::Init();

		ImGui::Begin("AmongUsMenu", &State.ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::BeginTabBar("AmongUs#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		if(!firstRender)
			SettingsTab::Render();
		GameTab::Render();
		SelfTab::Render();
		RadarTab::Render();
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