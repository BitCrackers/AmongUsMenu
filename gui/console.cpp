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

	std::vector<std::pair<PlayerSelection, bool>> player_filter;

	void Init() {
		ImGui::SetNextWindowSize(ImVec2(520, 320), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);

		// setup player_filter list based on MAX_PLAYERS definition
		for (int i = 0; i < MAX_PLAYERS; i++) {
			player_filter.push_back({ PlayerSelection(), false });
		}
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
		if (IsInGame()) {
			ImGui::SameLine();
			ImGui::Text("Filter By Source\t");
			ImGui::SameLine();
			CustomListBoxPlayerSelectionMultiple("Players", &player_filter, 150.f);
		}
		ImGui::EndChild();
		ImGui::Separator();
		ImGui::BeginChild("console#scroll", ImVec2(490, 225), true);
		for (int i = State.consoleEvents.size() - 1; i >= 0; i--) {
			if (State.consoleEvents[i]->getType() == EVENT_WALK
				|| ConsoleGui::exclude_filter.at(State.consoleEvents[i]->getType() - 1 /* exclude EVENT_NONE */).second)
				continue;

			bool playerFound = false, anyFilterSelected = false;
			for (auto player : player_filter) {
				if (player.second
					&& player.first.has_value()
					&& player.first.get_PlayerId() == State.consoleEvents[i]->getSource().playerId)
				{
					playerFound = true;
					anyFilterSelected = true;
					break;
				}
				else if (player.second) // if no player was selected we want to make sure that any filter was set in the first place before we continue
					anyFilterSelected = true;
			}

			if (!playerFound && anyFilterSelected)
				continue;

			State.consoleEvents[i]->ColoredEventOutput();
			ImGui::SameLine();
			State.consoleEvents[i]->Output();
		}
		ImGui::EndChild();
		ImGui::End();
	}
}