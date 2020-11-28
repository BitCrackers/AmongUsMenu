#include "menu.hpp"

using namespace app;

namespace Menu {
	void Init() {
		ImGui::SetNextWindowSize(ImVec2(400, 270), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	void Render() {
		if (!init)
			Menu::Init();

		ImGui::Begin("AmongUsMenu", &State.ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::BeginTabBar("AmongUs#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		GameTab::Render();
		SelfTab::Render();
		RadarTab::Render();
		PlayersTab::Render();
		TasksTab::Render();
		SabotageTab::Render();
		DoorsTab::Render();
		HostTab::Render();

		ImGui::EndTabBar();
		ImGui::End();
	}
}