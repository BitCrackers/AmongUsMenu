#include "pch-il2cpp.h"
#include "debuggui.hpp"
#include <imgui/imgui.h>
#include "state.hpp"
#include "debugtabs/main_debug_tab.h"
#include "debugtabs/class_debug_tab.h"
#include "debugtabs/translations_debug_tab.h"

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

		ImGui::Begin("Debug", &State.showDebugWindow);
		ImGui::BeginTabBar("Debug#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		MainDebugTab::Render();
		ClassDebugTab::Render();
		TranslationsDebugTab::Render();
		
		ImGui::EndTabBar();
		ImGui::End();
	}
}