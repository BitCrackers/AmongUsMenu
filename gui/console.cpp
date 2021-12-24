#include "pch-il2cpp.h"
#include "console.hpp"
#include "imgui/imgui.h"
#include "gui-helpers.hpp"
#include "state.hpp"

namespace ConsoleGui {
	int selectedType = 0;

	void Init() {
		ImGui::SetNextWindowSize(ImVec2(520, 320), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	void Render() {
		if (!init)
			ConsoleGui::Init();

		ImGui::Begin("Console", &State.ShowConsole, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginChild("console#filter", ImVec2(490, 20), true);
		ImGui::Text("Filter\t");
		ImGui::SameLine();
		CustomListBoxInt("By Type", &ConsoleGui::selectedType, ConsoleGui::BY_TYPE, 100.f);
		ImGui::EndChild();
		ImGui::Separator();
		ImGui::BeginChild("console#scroll", ImVec2(490, 225), true);
		for (int i = State.consoleEvents.size() - 1; i >= 0; i--) {
			if (State.consoleEvents[i]->getType() == EVENT_WALK)
				continue;

			if (ConsoleGui::selectedType > 0)
				if (State.consoleEvents[i]->getType() != (EVENT_TYPES)ConsoleGui::selectedType)
					continue;

			State.consoleEvents[i]->ColoredEventOutput();
			ImGui::SameLine();
			State.consoleEvents[i]->Output();
		}
		ImGui::EndChild();
		ImGui::End();
	}
}