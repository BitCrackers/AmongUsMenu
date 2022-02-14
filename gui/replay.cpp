#include "pch-il2cpp.h"
#include "replay.hpp"
#include "DirectX.h"
#include "state.hpp"
#include "gui-helpers.hpp"
#include "profiler.h"
#include "logger.h"
#include <sstream>
#include <chrono>


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

	void RenderWalkPaths(ImDrawList* drawList, float cursorPosX, float cursorPosY, int MapType, bool isUsingEventFilter, bool isUsingPlayerFilter, bool isUsingTimeFilter, std::chrono::system_clock::time_point timeFilter)
	{
		Profiler::BeginSample("ReplayPolyline");
		for (int plrIdx = 0; plrIdx < State.replayWalkPolylineByPlayer.size(); plrIdx++)
		{
			Replay::WalkEvent_LineData plrLineData = State.replayWalkPolylineByPlayer.at(plrIdx);
			size_t numPendingPoints = plrLineData.pendingPoints.size();
			if (numPendingPoints < 1)
				continue;
			ImVec2 latestPos = plrLineData.pendingPoints.back();
			if ((numPendingPoints >= 2) &&
				((isUsingEventFilter == false) || ((isUsingEventFilter == true) && (Replay::event_filter[(int)EVENT_TYPES::EVENT_WALK].second == true))))
			{
				// CREDIT:
				// https://github.com/mourner/simplify-js/blob/master/simplify.js#L51
				// https://github.com/mourner/simplify-js/blob/master/LICENSE
				ImVec2 prevPoint = plrLineData.pendingPoints[0], point = prevPoint;
				std::chrono::system_clock::time_point timestamp = plrLineData.pendingTimeStamps[0];
				size_t numPendingPoints = plrLineData.pendingPoints.size();
				size_t numOldSimpPoints = plrLineData.simplifiedPoints.size();
				size_t numNewPointsAdded = 1;
				// always add the first point
				plrLineData.simplifiedPoints.push_back(point);
				plrLineData.simplifiedTimeStamps.push_back(timestamp);
				for (size_t index = 1; index < numPendingPoints; index++)
				{
					point = plrLineData.pendingPoints[index];
					timestamp = plrLineData.pendingTimeStamps[index];
					float diffX = point.x - prevPoint.x, diffY = point.y - prevPoint.y;
					if ((diffX * diffX + diffY * diffY) > 50.f)
					{
						prevPoint = point;
						// add the point if it's beyond 50 squared units of prev point.
						plrLineData.simplifiedPoints.push_back(point);
						plrLineData.simplifiedTimeStamps.push_back(timestamp);
						numNewPointsAdded++;
					}
				}
				// add the last point if it's not also the first point or has already been added as the last point
				if ((point.x != prevPoint.x) && (point.y != prevPoint.y))
				{
					plrLineData.simplifiedPoints.push_back(point);
					plrLineData.simplifiedTimeStamps.push_back(timestamp);
					numNewPointsAdded++;
				}

				plrLineData.pendingPoints.clear();
				plrLineData.pendingTimeStamps.clear();
				//STREAM_DEBUG("Using " << numNewPointsAdded << " points out of " << numPendingPoints << "\n\tTotal simp points: " << plrLineData.simplifiedPoints.size());

				// have to loop through any newly added simplifiedPoints and translate to map coords
				// old simplifiedPoints are already translated so it's important we do not touch those
				for (size_t simpIndex = numOldSimpPoints; simpIndex < plrLineData.simplifiedPoints.size(); simpIndex++)
				{
					plrLineData.simplifiedPoints[simpIndex].x += cursorPosX;
					plrLineData.simplifiedPoints[simpIndex].y += cursorPosY;
				}

				if (isUsingTimeFilter == true)
				{
					// now we figure out the last index that matches the timeFilter
					// then we'll do some quik pointer mafs to pass to the AddPolyline call
					size_t lastTimeIndex = plrLineData.simplifiedTimeStamps.size() - 1;
					for (std::vector<std::chrono::system_clock::time_point>::reverse_iterator riter = plrLineData.simplifiedTimeStamps.rbegin(); riter != plrLineData.simplifiedTimeStamps.rend(); riter++, lastTimeIndex--)
					{
						std::chrono::system_clock::time_point timestamp = *riter;
						if (timestamp < timeFilter)
						{
							lastTimeIndex++;
							break;
						}
					}
					uintptr_t ptrOffset = lastTimeIndex * sizeof(ImVec2);
					drawList->AddPolyline((plrLineData.simplifiedPoints.data() + ptrOffset), plrLineData.simplifiedPoints.size() - lastTimeIndex, GetReplayPlayerColor(plrLineData.colorId), false, 1.f);
				}
				else
				{
					drawList->AddPolyline(plrLineData.simplifiedPoints.data(), plrLineData.simplifiedPoints.size(), GetReplayPlayerColor(plrLineData.colorId), false, 1.f);
				}
			}

			// draw player icon
			IconTexture icon = icons.at(ICON_TYPES::PLAYER);
			// latestPos.x = maps[State.mapType].x_offset + (position.x * maps[State.mapType].scale);
			// float player_mapX = maps[MapType].x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
			float player_mapX = ((latestPos.x / maps[MapType].scale) - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
			float player_mapY = ((latestPos.y / maps[MapType].scale) - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;
			float player_mapXMax = ((latestPos.x / maps[MapType].scale) + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
			float player_mapYMax = ((latestPos.y / maps[MapType].scale) + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;

			drawList->AddImage((void*)icon.iconImage.shaderResourceView,
				ImVec2(player_mapX, player_mapY),
				ImVec2(player_mapXMax, player_mapYMax),
				ImVec2(0.0f, 0.0f),
				ImVec2(1.0f, 1.0f),
				GetReplayPlayerColor(plrLineData.colorId));

			app::GameData_PlayerInfo* plrInfo = GetPlayerDataById(plrLineData.playerId);
			if ((plrInfo != NULL) &&
				((plrInfo->fields.IsDead) ||
					((plrInfo->fields.Role != NULL) &&
						(plrInfo->fields.Role->fields.Role == RoleTypes__Enum::GuardianAngel))))
				drawList->AddImage((void*)icons.at(ICON_TYPES::CROSS).iconImage.shaderResourceView,
					ImVec2(player_mapX, player_mapY),
					ImVec2(player_mapXMax, player_mapYMax),
					ImVec2(0.0f, 0.0f),
					ImVec2(1.0f, 1.0f));
		}
		Profiler::EndSample("ReplayPolyline");
	}

	void RenderEventIcons(ImDrawList* drawList, float cursorPosX, float cursorPosY, int MapType, bool isUsingEventFilter, bool isUsingPlayerFilter, bool isUsingTimeFilter, std::chrono::system_clock::time_point timeFilter)
	{
		// core processing loop
		Profiler::BeginSample("ReplayLoop");
		size_t evtIdx = State.liveReplayEvents.size() - 1;
		for (std::vector<std::unique_ptr<EventInterface>>::reverse_iterator riter = State.liveReplayEvents.rbegin(); riter != State.liveReplayEvents.rend(); riter++, evtIdx--)
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
			if (curEvent->GetTimeStamp() < timeFilter)
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
		}
		Profiler::EndSample("ReplayLoop");
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

		std::chrono::system_clock::time_point timeFilter = std::chrono::system_clock::now();
		if (State.Replay_ShowOnlyLastSeconds)
		{
			std::chrono::seconds seconds(State.Replay_LastSecondsValue);
			timeFilter -= seconds;
		}


		std::lock_guard<std::mutex> replayLock(Replay::replayEventMutex);
		RenderWalkPaths(drawList, cursorPosX, cursorPosY, MapType, isUsingEventFilter, isUsingPlayerFilter, State.Replay_ShowOnlyLastSeconds, timeFilter);
		RenderEventIcons(drawList, cursorPosX, cursorPosY, MapType, isUsingEventFilter, isUsingPlayerFilter, State.Replay_ShowOnlyLastSeconds, timeFilter);
		

		ImGui::EndChild();

		ImGui::BeginChild("replay#control");
		// slider based on chronos timestamp from beginning of round until now (live)
		ImGui::EndChild();

		ImGui::End();
		Profiler::EndSample("ReplayRender");
	}
}