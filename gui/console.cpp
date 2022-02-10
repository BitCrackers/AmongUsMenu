#include "pch-il2cpp.h"
#include "console.hpp"
#include "imgui/imgui.h"
#include "gui-helpers.hpp"
#include "state.hpp"

namespace ConsoleGui {
	std::vector<std::pair<const char*, bool>> exclude_filter =
	{
		{"Kill", false},
		{"Vent", false},
		{"Task", false},
		{"Report", false},
		{"Meeting", false},
		{"Vote", false},
		{"Cheat", false},
		{"Disconnect", false},
		{"Shapeshift", false},
		{"Protect", false}
	};

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
		ImGui::Text("Exclude\t");
		ImGui::SameLine();
		CustomListBoxIntMultiple("Event Types", &ConsoleGui::exclude_filter, 100.f);
		ImGui::EndChild();
		ImGui::Separator();
		ImGui::BeginChild("console#scroll", ImVec2(490, 225), true);
		for (int i = State.consoleEvents.size() - 1; i >= 0; i--) {
			if (State.consoleEvents[i]->getType() == EVENT_WALK
				|| ConsoleGui::exclude_filter.at(State.consoleEvents[i]->getType() - 1 /* exclude EVENT_NONE */).second)
				continue;

			State.consoleEvents[i]->ColoredEventOutput();
			ImGui::SameLine();
			State.consoleEvents[i]->Output();
		}
		ImGui::EndChild();
		ImGui::End();
	}
}