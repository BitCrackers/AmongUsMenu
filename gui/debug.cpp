#include "debug.hpp"

namespace DebugGui
{
	void Init() {
		ImGui::SetNextWindowSize(ImVec2(800, 500), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	void Render() {
		if (!init)
			DebugGui::Init();

		ImGui::Begin("Debug", &State.ShowDebugWindow);
		ImGui::BeginTabBar("Debug#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		MainDebugTab::Render();
		ClassDebugTab::Render();
		TranslationsDebugTab::Render();
		
		ImGui::EndTabBar();
		ImGui::End();
	}
}