#include "pch-il2cpp.h"
#include "replay.hpp"
#include "DirectX.h"
#include "state.hpp"
#include "gui-helpers.hpp"

namespace Replay
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
		{"Protect", false},
		{"Walk", false}
	};

	std::vector<std::pair<PlayerSelection, bool>> player_filter;

	void SquareConstraint(ImGuiSizeCallbackData* data)
	{
		data->DesiredSize = ImVec2(data->DesiredSize.x, data->DesiredSize.y);
	}

	bool init = false;
	void Init()
	{
		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), SquareConstraint);
		ImGui::SetNextWindowBgAlpha(1.F);

		if (!init)
		{
			// setup player_filter list based on MAX_PLAYERS definition
			for (int i = 0; i < MAX_PLAYERS; i++) {
				Replay::player_filter.push_back({ PlayerSelection(), false });
			}
			init = true;
		}
	}

	
	void Render()
	{
		Replay::Init();

		int MapType = State.mapType;
		ImGui::SetNextWindowSize(ImVec2(560, 400), ImGuiCond_None);

		ImGui::Begin("Replay", &State.ShowReplay, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

		ImGui::BeginChild("console#filter", ImVec2(560, 20), true);
		ImGui::Text("Event Filter: ");
		ImGui::SameLine();
		CustomListBoxIntMultiple("Event Types", &Replay::event_filter, 100.f);
		if (IsInGame()) {
			ImGui::SameLine(0.f, 5.f);
			ImGui::Text("Player Filter: ");
			ImGui::SameLine();
			CustomListBoxPlayerSelectionMultiple("Players", &Replay::player_filter, 150.f);
		}
		ImGui::EndChild();
		ImGui::Separator();

		// TODO: Size it for map and calculate center of the parent window for proper map placement
		ImGui::BeginChild("ReplayMap");

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImGui::Image((void*)maps[MapType].mapImage.shaderResourceView,
			ImVec2((float)maps[MapType].mapImage.imageWidth * 0.5F, (float)maps[MapType].mapImage.imageHeight * 0.5F),
			(State.FlipSkeld && MapType == 0) ? ImVec2(1.0f, 0.0f) : ImVec2(0.0f, 0.0f),
			(State.FlipSkeld && MapType == 0) ? ImVec2(0.0f, 1.0f) : ImVec2(1.0f, 1.0f),
			State.SelectedReplayMapColor);

		// for each player
		for (int n = 0; n < MAX_PLAYERS; n++)
		{
			// include player filter

			// for each event
			for (int x = 0; x < EVENT_TYPES_SIZE; x++)
			{
				// work with event vector here
				// include event filter here
				// visualize each event here (maybe create own class for drawing map related data ?)
			}
		}

		ImGui::EndChild();

		// new child (control)
		// slider based on chronos timestamp from beginning of round until now (live)

		ImGui::End();
	}
}