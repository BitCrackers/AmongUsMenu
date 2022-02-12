#include "pch-il2cpp.h"
#include "console.hpp"
#include "imgui/imgui.h"
#include "gui-helpers.hpp"
#include "state.hpp"

namespace ConsoleGui
{
	// TODO: improve this by building it dynamically based on the EVENT_TYPES enum
	std::vector<std::pair<const char*, bool>> event_filter =
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

	bool init = false;
	void Init() {
		ImGui::SetNextWindowSize(ImVec2(520, 320), ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.F);

		if (!init)
		{
			// setup player_filter list based on MAX_PLAYERS definition
			for (int i = 0; i < MAX_PLAYERS; i++) {
				ConsoleGui::player_filter.push_back({ PlayerSelection(), false });
			}
			init = true;
		}
	}


	void Render() {
		ConsoleGui::Init();

		ImGui::Begin("Console", &State.ShowConsole, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginChild("console#filter", ImVec2(520, 20), true);
		ImGui::Text("Event Filter: ");
		ImGui::SameLine();
		CustomListBoxIntMultiple("Event Types", &ConsoleGui::event_filter, 100.f);
		if (IsInGame()) {
			ImGui::SameLine(0.f, 5.f);
			ImGui::Text("Player Filter: ");
			ImGui::SameLine();
			CustomListBoxPlayerSelectionMultiple("Players", &ConsoleGui::player_filter, 150.f);
		}
		ImGui::EndChild();
		ImGui::Separator();
		ImGui::BeginChild("console#scroll", ImVec2(511, 270), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
		for (int i = State.events.size() - 1; i >= 0; i--) {
			if (State.events[i].get()->getType() == EVENT_WALK)
				continue;

			bool typeFound = false, anyTypeFilterSelected = false;
			for (int n = 0; n < ConsoleGui::event_filter.size(); n++) {
				if (ConsoleGui::event_filter[n].second
					&& (EVENT_TYPES)n == State.events[i].get()->getType()) {
					typeFound = true;
					anyTypeFilterSelected = true;
					break;
				}
				else if (ConsoleGui::event_filter[n].second)
					anyTypeFilterSelected = true;
			}

			if (!typeFound && anyTypeFilterSelected)
				continue;

			bool playerFound = false, anyPlayerFilterSelected = false;
			for (auto player : ConsoleGui::player_filter) {
				if (player.second
					&& player.first.has_value()
					&& player.first.get_PlayerId() == State.events[i].get()->getSource().playerId)
				{
					playerFound = true;
					anyPlayerFilterSelected = true;
					break;
				}
				else if (player.second) // if no player was selected we want to make sure that any filter was set in the first place before we continue
					anyPlayerFilterSelected = true;
			}

			if (!playerFound && anyPlayerFilterSelected)
				continue;

			State.events[i].get()->ColoredEventOutput();
			ImGui::SameLine();
			State.events[i].get()->Output();
		}
		ImGui::EndChild();
		ImGui::End();
	}
}