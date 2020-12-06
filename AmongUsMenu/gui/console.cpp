#include "console.hpp"

namespace ConsoleGui {
	int selectedType = 0;

	void Init() {
		ImGui::SetNextWindowSize(ImVec2(500, 270), ImGuiCond_Once);
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
		for (int i = State.events.size() - 1; i >= 0; i--) {
			if (State.events[i]->getType() == EVENT_WALK)
				continue;

			if (ConsoleGui::selectedType > 0)
				if (State.events[i]->getType() != (EVENT_TYPES)ConsoleGui::selectedType)
					continue;

			State.events[i]->ColoredEventOutput();
			ImGui::SameLine();
			State.events[i]->Output();
		}
		ImGui::EndChild();
		ImGui::End();
	}
}