#include "pch-il2cpp.h"
#include "replay.hpp"
#include "DirectX.h"
#include "state.hpp"
#include "gui-helpers.hpp"
#include <sstream>
#include "profiler.h"
#include "logger.h"

namespace Replay
{
	std::mutex replayEventMutex;

	// TODO: improve this by building it dynamically based on the EVENT_TYPES enum
	std::vector<std::pair<const char*, bool>> event_filter =
	{
		{"Kill", false},
		{"Vent", false},
		{"Task", false},
		{"Report", false},
		{"Meeting", false},
		{"", false},
		{"", false},
		{"", false},
		{"", false},
		{"", false},
		{"Walk", false}
	};

	std::vector<std::pair<PlayerSelection, bool>> player_filter;

	std::vector<__int64> lastWalkEventIndexPerPlayer;
	std::vector<ImVec2> lastWalkEventPosPerPlayer;

	ImU32 GetReplayPlayerColor(uint8_t colorId) {
		return ImGui::ColorConvertFloat4ToU32(AmongUsColorToImVec4(GetPlayerColor(colorId)));
	}

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
				Replay::lastWalkEventIndexPerPlayer.push_back(-1);
				Replay::lastWalkEventPosPerPlayer.push_back(ImVec2(0.f, 0.f));
			}
			init = true;
		}
	}

	void Reset()
	{
		Replay::lastWalkEventIndexPerPlayer.clear();
		Replay::lastWalkEventPosPerPlayer.clear();
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			Replay::lastWalkEventIndexPerPlayer.push_back(-1);
			Replay::lastWalkEventPosPerPlayer.push_back(ImVec2(0.f, 0.f));
		}
	}
	
	void Render()
	{
		Profiler::BeginSample("ReplayRender");
		Replay::Init();

		int MapType = State.mapType;
		ImGui::SetNextWindowSize(ImVec2(560, 420), ImGuiCond_None);

		ImGui::Begin("Replay", &State.ShowReplay, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

		ImGui::BeginChild("replay#filter", ImVec2(560, 20), true);
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

		ImGui::BeginChild("replay#map");
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImVec2 winSize = ImGui::GetWindowSize();
		ImVec2 winPos = ImGui::GetWindowPos();

		// calculate proper cursorPosition for centerered rendering
		float cursorPosX = winPos.x + (winSize.x * 0.5f) - ((float)(maps[MapType].mapImage.imageWidth * 0.5f) * 0.5f);
		float cursorPosY = winPos.y + (winSize.y * 0.15f) - ((float)(maps[MapType].mapImage.imageHeight * 0.15f) * 0.5f);

		// TODO: Center image in childwindow and calculate new cursorPos
		drawList->AddImage((void*)maps[MapType].mapImage.shaderResourceView,
			ImVec2(cursorPosX + 5.0f, cursorPosY + 5.0f),
			ImVec2(cursorPosX + 5.0f + ((float)maps[MapType].mapImage.imageWidth * 0.5f), cursorPosY + 5.0f + ((float)maps[MapType].mapImage.imageHeight * 0.5f)),
			(State.FlipSkeld && MapType == 0) ? ImVec2(1.0f, 0.0f) : ImVec2(0.0f, 0.0f),
			(State.FlipSkeld && MapType == 0) ? ImVec2(0.0f, 1.0f) : ImVec2(1.0f, 1.0f),
			ImGui::GetColorU32(State.SelectedReplayMapColor));

		// pre-processing of filters
		bool isUsingEventFilter = false;
		for (size_t evtFiltIdx = 0; evtFiltIdx < Replay::event_filter.size(); evtFiltIdx++)
		{
			if (Replay::event_filter[evtFiltIdx].second == true)
			{
				isUsingEventFilter = true;
				break;
			}
		}
		bool isUsingPlayerFilter = false;
		for (size_t plyFiltIdx = 0; plyFiltIdx < Replay::player_filter.size(); plyFiltIdx++)
		{
			if ((Replay::player_filter[plyFiltIdx].second == true) && (Replay::player_filter[plyFiltIdx].first.has_value() == true))
			{
				isUsingPlayerFilter = true;
				break;
			}
		}

		// core processing loop
		Profiler::BeginSample("ReplayLoop");
		std::lock_guard<std::mutex> replayLock(Replay::replayEventMutex);
		size_t evtIdx = State.events.size() - 1;
		for (std::vector<std::unique_ptr<EventInterface>>::reverse_iterator riter = State.events.rbegin(); riter != State.events.rend(); riter++, evtIdx--)
		//for (__int64 evtIdx = State.flatEvents.size() - 1; evtIdx >= 0; evtIdx--)
		{
			EventInterface* curEvent = (*riter).get();
			//EventInterface* curEvent = State.flatEvents.at(evtIdx);
			EVENT_TYPES evtType = curEvent->getType();
			std::chrono::system_clock::time_point evtTime = curEvent->GetTimeStamp();
			EVENT_PLAYER evtPlayerSource = curEvent->getSource();

			// filters
			if ((isUsingEventFilter == true) && (Replay::event_filter[(int)evtType].second == false))
				continue;
			if ((isUsingPlayerFilter == true) && 
				((evtPlayerSource.playerId < 0) || (evtPlayerSource.playerId > Replay::player_filter.size() - 1) || 
					(Replay::player_filter[evtPlayerSource.playerId].second == false) || 
					(Replay::player_filter[evtPlayerSource.playerId].first.has_value() == false)))
				continue;

			// processing
			if (evtType == EVENT_TYPES::EVENT_KILL)
			{
				Profiler::BeginSample("ReplayKillEvent");
				auto kill_event = dynamic_cast<KillEvent*>(curEvent);
				auto position = kill_event->GetTargetPosition();
				IconTexture icon = icons.at(ICON_TYPES::KILL);
				float mapX = maps[MapType].x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapY = maps[MapType].y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;
				float mapXMax = maps[MapType].x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapYMax = maps[MapType].y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(mapX, mapY),
					ImVec2(mapXMax, mapYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
				Profiler::EndSample("ReplayKillEvent");
			}
			else if (evtType == EVENT_TYPES::EVENT_VENT)
			{
				Profiler::BeginSample("ReplayVentEvent");
				auto vent_event = dynamic_cast<VentEvent*>(curEvent);
				auto position = vent_event->GetPosition();
				ICON_TYPES iconType;

				switch (vent_event->GetEventActionEnum())
				{
					case VENT_ACTIONS::VENT_ENTER:
						iconType = ICON_TYPES::VENT_IN;
						break;

					case VENT_ACTIONS::VENT_EXIT:
						iconType = ICON_TYPES::VENT_OUT;
						break;

					default:
						iconType = ICON_TYPES::VENT_IN;
						break;
				}

				IconTexture icon = icons.at(iconType);
				float mapX = maps[MapType].x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapY = maps[MapType].y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;
				float mapXMax = maps[MapType].x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapYMax = maps[MapType].y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(mapX, mapY),
					ImVec2(mapXMax, mapYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
				Profiler::EndSample("ReplayVentEvent");
			}
			else if (evtType == EVENT_TYPES::EVENT_TASK)
			{
				Profiler::BeginSample("ReplayTaskEvent");
				auto task_event = dynamic_cast<TaskCompletedEvent*>(curEvent);
				auto position = task_event->GetPosition();
				IconTexture icon = icons.at(ICON_TYPES::TASK);
				float mapX = maps[MapType].x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapY = maps[MapType].y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;
				float mapXMax = maps[MapType].x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapYMax = maps[MapType].y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(mapX, mapY),
					ImVec2(mapXMax, mapYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
				Profiler::EndSample("ReplayTaskEvent");
			}
			else if (evtType == EVENT_TYPES::EVENT_REPORT || evtType == EVENT_TYPES::EVENT_MEETING)
			{
				Profiler::BeginSample("ReplayMeetingEvent");
				auto report_event = dynamic_cast<ReportDeadBodyEvent*>(curEvent);
				auto position = report_event->GetPosition();
				auto targetPos = report_event->GetTargetPosition();
				if (targetPos.has_value())
					position = targetPos.value();
				IconTexture icon = icons.at(ICON_TYPES::REPORT);
				float mapX = maps[MapType].x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapY = maps[MapType].y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;
				float mapXMax = maps[MapType].x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapYMax = maps[MapType].y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(mapX, mapY),
					ImVec2(mapXMax, mapYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
				Profiler::EndSample("ReplayMeetingEvent");
			}
			else if (evtType == EVENT_TYPES::EVENT_WALK)
			{
				Profiler::BeginSample("ReplayWalkEvent");
				// TODO: Limit lines to maybe last 5-10 positions (also possible as option)
				auto walk_event = dynamic_cast<WalkEvent*>(curEvent);

				auto position = walk_event->GetPosition();
				float mapX = maps[MapType].x_offset + (position.x * maps[MapType].scale) + cursorPosX;
				float mapY = maps[MapType].y_offset - (position.y * maps[MapType].scale) + cursorPosY;
				// NOTE:
				// on the first walk event per player, these values will be 0.f
				// BUT the if statement will also be true so the 'continue' statement will be hit
				// which will avoid drawing a line to 0,0
				float prevMapX = lastWalkEventPosPerPlayer[evtPlayerSource.playerId].x;
				float prevMapY = lastWalkEventPosPerPlayer[evtPlayerSource.playerId].y;

				lastWalkEventPosPerPlayer[evtPlayerSource.playerId].x = mapX;
				lastWalkEventPosPerPlayer[evtPlayerSource.playerId].y = mapY;

				if (lastWalkEventIndexPerPlayer[evtPlayerSource.playerId] <= evtIdx)
				{
					// draw the player icon if it's their latest walk event (aka: their current position)
					lastWalkEventIndexPerPlayer[evtPlayerSource.playerId] = evtIdx;
					IconTexture icon = icons.at(ICON_TYPES::PLAYER);
					float player_mapX = maps[MapType].x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
					float player_mapY = maps[MapType].y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;
					float player_mapXMax = maps[MapType].x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
					float player_mapYMax = maps[MapType].y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;

					drawList->AddImage((void*)icon.iconImage.shaderResourceView,
						ImVec2(player_mapX, player_mapY),
						ImVec2(player_mapXMax, player_mapYMax),
						ImVec2(0.0f, 1.0f),
						ImVec2(1.0f, 0.0f),
						GetReplayPlayerColor(evtPlayerSource.colorId));

					if (evtPlayerSource.isDead || evtPlayerSource.isAngel)
						drawList->AddImage((void*)icons.at(ICON_TYPES::CROSS).iconImage.shaderResourceView,
							ImVec2(player_mapX, player_mapY),
							ImVec2(player_mapXMax, player_mapYMax),
							ImVec2(0.0f, 1.0f),
							ImVec2(1.0f, 0.0f));

					Profiler::EndSample("ReplayWalkEvent");
					continue;
				}

				//drawList->AddLine(ImVec2(prevMapX, prevMapY), ImVec2(mapX, mapY), GetReplayPlayerColor(evtPlayerSource.colorId));
				Profiler::EndSample("ReplayWalkEvent");
			}
		}
		Profiler::EndSample("ReplayLoop");

		Profiler::BeginSample("ReplayPolyline");
		for (int plrIdx = 0; plrIdx < State.replayWalkPolylineByPlayer.size(); plrIdx++)
		{
			Replay::WalkEvent_LineData plrLineData = State.replayWalkPolylineByPlayer.at(plrIdx);

			// CREDIT:
			// https://github.com/mourner/simplify-js/blob/master/simplify.js#L51
			// https://github.com/mourner/simplify-js/blob/master/LICENSE
			if (plrLineData.pendingPoints.size() < 2)
				continue;
			ImVec2 prevPoint = plrLineData.pendingPoints[0], point = prevPoint;
			size_t numPendingPoints = plrLineData.pendingPoints.size();
			size_t numOldSimpPoints = plrLineData.simplifiedPoints.size();
			size_t numNewPointsAdded = 1;
			// always add the first point
			plrLineData.simplifiedPoints.push_back(ImVec2(prevPoint.x, prevPoint.y));
			for (size_t index = 1; index < numPendingPoints; index++)
			{
				point = plrLineData.pendingPoints[index];
				float diffX = point.x - prevPoint.x, diffY = point.y - prevPoint.y;
				if ((diffX * diffX + diffY * diffY) > 50.f)
				{
					prevPoint = point;
					// add the point if it's beyond 50 squared units of prev point.
					plrLineData.simplifiedPoints.push_back(point);
					numNewPointsAdded++;
				}
			}
			// add the last point if it's not also the first point or has already been added as the last point
			if ((point.x != prevPoint.x) && (point.y != prevPoint.y))
			{
				plrLineData.simplifiedPoints.push_back(ImVec2(point.x, point.y));
				numNewPointsAdded++;
			}

			plrLineData.pendingPoints.clear();
			//STREAM_DEBUG("Using " << numNewPointsAdded << " points out of " << numPendingPoints << "\n\tTotal simp points: " << plrLineData.simplifiedPoints.size());

			// have to loop through any newly added simplifiedPoints and translate to map coords
			// old simplifiedPoints are already translated so it's important we do not touch those
			for (size_t simpIndex = numOldSimpPoints; simpIndex < plrLineData.simplifiedPoints.size(); simpIndex++)
			{
				plrLineData.simplifiedPoints[simpIndex].x += cursorPosX;
				plrLineData.simplifiedPoints[simpIndex].y += cursorPosY;
			}

			drawList->AddPolyline(plrLineData.simplifiedPoints.data(), plrLineData.simplifiedPoints.size(), GetReplayPlayerColor(plrLineData.colorId), false, 1.f);
		}
		Profiler::EndSample("ReplayPolyline");
		

		ImGui::EndChild();

		ImGui::BeginChild("replay#control");
		// slider based on chronos timestamp from beginning of round until now (live)
		ImGui::EndChild();

		ImGui::End();
		Profiler::EndSample("ReplayRender");
	}
}