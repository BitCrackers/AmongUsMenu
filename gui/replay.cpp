#include "pch-il2cpp.h"
#include "replay.hpp"
#include "DirectX.h"
#include "state.hpp"
#include "gui-helpers.hpp"
#include "profiler.h"
#include "logger.h"
#include "utility.h"
#include <sstream>
#include <chrono>


namespace Replay
{
	// NOTE:
	// any code that modifies State.rawEvents or State.liveReplayEvents or any other collection should use this mutex
	// failure to do so will invalidate any existing iterator of any thread which will lead to rare and hard to diagnose crashes
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
			}
			init = true;
		}
	}

	void Reset()
	{
		std::lock_guard<std::mutex> replayLock(Replay::replayEventMutex);
		for (auto& e : State.liveReplayEvents)
			e.reset();
		State.liveReplayEvents.clear();
		for (auto& pair : State.replayWalkPolylineByPlayer)
		{
			pair.second.playerId = 0;
			pair.second.colorId = 0;
			pair.second.pendingPoints.clear();
			pair.second.pendingTimeStamps.clear();
			pair.second.simplifiedPoints.clear();
			pair.second.simplifiedTimeStamps.clear();
		}

		for (int plyIdx = 0; plyIdx < MAX_PLAYERS; plyIdx++)
		{
			State.lastWalkEventPosPerPlayer[plyIdx] = ImVec2(0.f, 0.f);
		}

		// Set this to true as the default value
		// Everytime we start a new match it will actually be in live mode
		State.Replay_IsLive = true;

		State.Replay_IsPlaying = false;
	}

	void RenderPolyline(ImDrawList* drawList, float cursorPosX, float cursorPosY, 
		std::vector<ImVec2>& points, std::vector<std::chrono::system_clock::time_point>& timeStamps, uint8_t colorId, 
		bool isUsingMinTimeFilter, std::chrono::system_clock::time_point& minTimeFilter, bool isUsingMaxTimeFilter, std::chrono::system_clock::time_point& maxTimeFilter)
	{
		if ((isUsingMinTimeFilter == true) && (isUsingMaxTimeFilter == true)
			&& (minTimeFilter >= maxTimeFilter))
		{
			STREAM_ERROR("Min time filter is greater than max time filter (min: " << std::format("{:%OH:%OM:%OS}", minTimeFilter) << " max: " << std::format("{:%OH:%OM:%OS}", maxTimeFilter) << ")");
			return;
		}
		// this is annoying, but we have to transform the points, render, then untransform
		// if we store the transformed points then moving the replay window will cause everything to break..
		for (auto& point : points)
		{
			point.x = getMapXOffsetSkeld(point.x) + cursorPosX;
			point.y += cursorPosY;
		}

		// earliestTimeIndex will be the very first event to be shown, lastTimeIndex will be the very last even to be shown
		int earliestTimeIndex = 0, lastTimeIndex = 0;
		bool collectionHasElementsToFilterMin = false, collectionHasElementsToFilterMax = false;
		if ((isUsingMinTimeFilter == true) || (isUsingMaxTimeFilter))
		{
			// now we figure out the last index that matches the minTimeFilter
			// then we'll do some quik pointer mafs to pass to the AddPolyline call
			for (size_t index = 0; index < timeStamps.size() - 1; index++)
			{
				const std::chrono::system_clock::time_point& timestamp = timeStamps.at(index);
				if ((timestamp > minTimeFilter) && (collectionHasElementsToFilterMin == false))
				{
					// the first element that *matches* the minTimeFilter is where we begin drawing from
					earliestTimeIndex = index;
					collectionHasElementsToFilterMin = true;
				}
				if ((timestamp > maxTimeFilter) && (collectionHasElementsToFilterMax == false))
				{
					// the first element that *exceeds* the maxTimeFilter is where we stop drawing
					lastTimeIndex = index;
					collectionHasElementsToFilterMax = true;
				}
			}
			
			uintptr_t startPtr = 0, endPtr = (points.size() - 1) * sizeof(ImVec2);
			if (collectionHasElementsToFilterMin == true)
			{
				// some events occurred before the specified time filter
				// so we want to draw only a portion of the total collection
				// this portion starts from the index of the last matching event and should continue to the end of the collection
				// since we're modifying the *pointer*, we have to multiply by the size of each element in the collection.
				startPtr = earliestTimeIndex * sizeof(ImVec2);
			}
			if (collectionHasElementsToFilterMax == true)
			{
				endPtr = lastTimeIndex * sizeof(ImVec2);
			}
			int numPoints = (endPtr - startPtr) / sizeof(ImVec2);
			drawList->AddPolyline((ImVec2*)((uintptr_t)points.data() + startPtr), numPoints, GetReplayPlayerColor(colorId), false, 1.f);
		}
		else
		{
			// we're not using any time filter, so just draw the polyline normally.
			drawList->AddPolyline(points.data(), points.size(), GetReplayPlayerColor(colorId), false, 1.f);
		}

		// untransform the points before returning
		for (auto& point : points)
		{
			float xPoint = getMapXOffsetSkeld(point.x);
			if (xPoint != point.x)
				xPoint += 100.f;

			point.x = xPoint - cursorPosX;
			point.y -= cursorPosY;
		}
	}

	void RenderWalkPaths(ImDrawList* drawList, float cursorPosX, float cursorPosY, int MapType, bool isUsingEventFilter, bool isUsingPlayerFilter, 
		bool isUsingMinTimeFilter, std::chrono::system_clock::time_point& minTimeFilter, bool isUsingMaxTimeFilter, std::chrono::system_clock::time_point& maxTimeFilter)
	{
		Profiler::BeginSample("ReplayPolyline");
		if ((isUsingMinTimeFilter == true) && (isUsingMaxTimeFilter == true)
			&& (minTimeFilter >= maxTimeFilter))
		{
			STREAM_ERROR("Min time filter is greater than max time filter (min: " << std::format("{:%OH:%OM:%OS}", minTimeFilter) << " max: " << std::format("{:%OH:%OM:%OS}", maxTimeFilter) << ")");
			return;
		}
		for (auto& playerPolylinePair : State.replayWalkPolylineByPlayer)
		{
			// first we check if the player has enough points pending simplification
			// we want to do the simplification regardless of filters so that if the filters change
			// and we start showing the walk path for that player we don't have to simplify tens of thousands of points on that first frame
			Replay::WalkEvent_LineData& plrLineData = playerPolylinePair.second;
			size_t numPendingPoints = plrLineData.pendingPoints.size();
			if (numPendingPoints >= 100)
			{
				DoPolylineSimplification(plrLineData.pendingPoints, plrLineData.pendingTimeStamps, plrLineData.simplifiedPoints, plrLineData.simplifiedTimeStamps, 50.f, true);
			}

			// now the actual rendering, which should be filtered
			// player filter
			if ((isUsingPlayerFilter == true) &&
				((playerPolylinePair.first < 0) || (playerPolylinePair.first > Replay::player_filter.size() - 1) ||
					(Replay::player_filter[playerPolylinePair.first].second == false) ||
					(Replay::player_filter[playerPolylinePair.first].first.has_value() == false)))
				continue;

			// event filter
			if ((isUsingEventFilter == true) && (Replay::event_filter[(int)EVENT_TYPES::EVENT_WALK].second == false))
				continue;

			if (plrLineData.simplifiedPoints.size() > 0)
				RenderPolyline(drawList, cursorPosX, cursorPosY, plrLineData.simplifiedPoints, plrLineData.simplifiedTimeStamps, plrLineData.colorId, isUsingMinTimeFilter, minTimeFilter, isUsingMaxTimeFilter, maxTimeFilter);
			// pendingPoints picks up where simplifiedPoints leaves off. there should only ever be 100 or less pendingPoints at any one time, so this is fine.
			if (plrLineData.pendingPoints.size() > 0)
				RenderPolyline(drawList, cursorPosX, cursorPosY, plrLineData.pendingPoints, plrLineData.pendingTimeStamps, plrLineData.colorId, isUsingMinTimeFilter, minTimeFilter, isUsingMaxTimeFilter, maxTimeFilter);
		}
		Profiler::EndSample("ReplayPolyline");
	}

	void RenderPlayerIcons(ImDrawList* drawList, float cursorPosX, float cursorPosY, int MapType, bool isUsingEventFilter, bool isUsingPlayerFilter, 
		bool isUsingMinTimeFilter, std::chrono::system_clock::time_point& minTimeFilter, bool isUsingMaxTimeFilter, std::chrono::system_clock::time_point& maxTimeFilter)
	{
		Profiler::BeginSample("ReplayPlayerIcons");
		if ((isUsingMinTimeFilter == true) && (isUsingMaxTimeFilter == true)
			&& (minTimeFilter >= maxTimeFilter))
		{
			STREAM_ERROR("Min time filter is greater than max time filter (min: " << std::format("{:%OH:%OM:%OS}", minTimeFilter) << " max: " << std::format("{:%OH:%OM:%OS}", maxTimeFilter) << ")");
			return;
		}
		// event filter
		if ((isUsingEventFilter == true) && (Replay::event_filter[(int)EVENT_TYPES::EVENT_WALK].second == false))
			return;

		for (auto& playerPolylinePair : State.replayWalkPolylineByPlayer)
		{
			const int& plrIdx = playerPolylinePair.first;
			const Replay::WalkEvent_LineData& plrLineData = playerPolylinePair.second;

			// player filter
			if ((isUsingPlayerFilter == true) &&
				((plrIdx < 0) || (plrIdx > Replay::player_filter.size() - 1) ||
					(Replay::player_filter[plrIdx].second == false) ||
					(Replay::player_filter[plrIdx].first.has_value() == false)))
				continue;

			// we get the player's position from the line data which is constructed from WalkEvents
			// pendingPoints will have the absolute freshest data, while simplifiedPoints will be behind by ~100 points or so (depends on how often we run the simplification)
			// if the player has not moved at all then we'll have zero line data (since there are zero WalkEvents) and we continue to the next player
			bool foundMatchingPlayerPos = false;
			ImVec2 playerPos;
			if (isUsingMaxTimeFilter == true)
			{
				// now we have to loop through and find the last position that matches the time filters
				int lastTimeIndex = plrLineData.pendingTimeStamps.size() - 1;
				for (std::vector<std::chrono::system_clock::time_point>::const_reverse_iterator riter = plrLineData.pendingTimeStamps.rbegin(); riter != plrLineData.pendingTimeStamps.rend(); riter++, lastTimeIndex--)
				{
					const std::chrono::system_clock::time_point& timestamp = *riter;
					if (timestamp < maxTimeFilter)
					{
						playerPos = plrLineData.pendingPoints[lastTimeIndex];
						if ((isUsingMinTimeFilter == true) && (timestamp < minTimeFilter))
						{
							STREAM_DEBUG("(not critical) Found a point matching maxTimeFilter, but does not match minTimeFilter. Add check that min < max once free time available.");
						}
						foundMatchingPlayerPos = true;
						break;
					}
				}
				if (foundMatchingPlayerPos == false)
				{
					// if we couldn't find a match using pendingPoints then we must try again using simplifiedPoints.
					lastTimeIndex = plrLineData.simplifiedTimeStamps.size() - 1;
					for (std::vector<std::chrono::system_clock::time_point>::const_reverse_iterator riter = plrLineData.simplifiedTimeStamps.rbegin(); riter != plrLineData.simplifiedTimeStamps.rend(); riter++, lastTimeIndex--)
					{
						const std::chrono::system_clock::time_point& timestamp = *riter;
						if (timestamp < maxTimeFilter)
						{
							playerPos = plrLineData.simplifiedPoints[lastTimeIndex];
							if ((isUsingMinTimeFilter == true) && (timestamp < minTimeFilter))
							{
								STREAM_DEBUG("(not critical) Found a point matching maxTimeFilter, but does not match minTimeFilter. Add check that min < max once free time available.");
							}
							foundMatchingPlayerPos = true;
							break;
						}
					}
				}
			}
			else
			{
				// if we're not using a max time filter we can just use the absolute latest position
				// this holds true even if we're using a min time filter
				if (plrLineData.pendingPoints.size() > 0)
					playerPos = plrLineData.pendingPoints.back();
				else if (plrLineData.simplifiedPoints.size() > 0)
					playerPos = plrLineData.simplifiedPoints.back();
				foundMatchingPlayerPos = true;
			}
			if (foundMatchingPlayerPos == false)
			{
				STREAM_DEBUG("Could not find replay position for player#" << plrIdx << ". Time filter was likely too strict or player hasn't moved yet.");
				continue;
			}

			IconTexture icon = icons.at(ICON_TYPES::PLAYER);
			// the latestPos variable is already pre-transformed for line rendering, so we have to un-transform and then re-transform for proper icon positioning
			// existing transformation:
			// latestPos.x = maps[State.mapType].x_offset + (position.x * maps[State.mapType].scale);
			// void*'s original transformation for icon positioning:
			// float player_mapX = maps[MapType].x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
			// i'm not mathematically inclined, so i don't really know what i'm doing...
			// but this is what i got for transforming from the existing to void*'s original:
			float halfImageWidth = (icon.iconImage.imageWidth * icon.scale * 0.5f) * maps[MapType].scale, halfImageHeight = (icon.iconImage.imageHeight * icon.scale * 0.5f) * maps[MapType].scale;
			float player_mapX = (playerPos.x - halfImageWidth) + cursorPosX;
			float player_mapY = (playerPos.y - halfImageHeight) + cursorPosY;
			float player_mapXMax = (playerPos.x + halfImageWidth) + cursorPosX;
			float player_mapYMax = (playerPos.y + halfImageHeight) + cursorPosY;

			drawList->AddImage((void*)icon.iconImage.shaderResourceView,
				ImVec2(getMapXOffsetSkeld(player_mapX), player_mapY),
				ImVec2(getMapXOffsetSkeld(player_mapXMax), player_mapYMax),
				ImVec2(0.0f, 0.0f),
				ImVec2(1.0f, 1.0f),
				GetReplayPlayerColor(plrLineData.colorId));

			app::GameData_PlayerInfo* plrInfo = GetPlayerDataById(plrLineData.playerId);
			if ((plrInfo != NULL) &&
				((plrInfo->fields.IsDead) ||
					((plrInfo->fields.Role != NULL) &&
						(plrInfo->fields.Role->fields.Role == RoleTypes__Enum::GuardianAngel))))
				drawList->AddImage((void*)icons.at(ICON_TYPES::CROSS).iconImage.shaderResourceView,
					ImVec2(getMapXOffsetSkeld(player_mapX), player_mapY),
					ImVec2(getMapXOffsetSkeld(player_mapXMax), player_mapYMax),
					ImVec2(0.0f, 0.0f),
					ImVec2(1.0f, 1.0f));
		}
		Profiler::EndSample("ReplayPlayerIcons");
	}

	void RenderEventIcons(ImDrawList* drawList, float cursorPosX, float cursorPosY, int MapType, bool isUsingEventFilter, bool isUsingPlayerFilter, 
		bool isUsingMinTimeFilter, std::chrono::system_clock::time_point& minTimeFilter,  bool isUsingMaxTimeFilter, std::chrono::system_clock::time_point& maxTimeFilter)
	{
		Profiler::BeginSample("ReplayEventIcons");
		if ((isUsingMinTimeFilter == true) && (isUsingMaxTimeFilter == true)
			&& (minTimeFilter >= maxTimeFilter))
		{
			STREAM_ERROR("Min time filter is greater than max time filter (min: " << std::format("{:%OH:%OM:%OS}", minTimeFilter) << " max: " << std::format("{:%OH:%OM:%OS}", maxTimeFilter) << ")");
			return;
		}
		
		for (std::vector<std::unique_ptr<EventInterface>>::iterator it = State.liveReplayEvents.begin(); it != State.liveReplayEvents.end(); ++it)
		{
			EventInterface* curEvent = (*it).get();
			EVENT_TYPES evtType = curEvent->getType();
			std::chrono::system_clock::time_point evtTime = curEvent->GetTimeStamp();
			EVENT_PLAYER evtPlayerSource = curEvent->getSource();

			// filters
			if ((isUsingMaxTimeFilter == true) && (evtTime > maxTimeFilter))
				continue;
			if ((isUsingMinTimeFilter == true) && (evtTime < minTimeFilter))
				continue;
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
				auto kill_event = dynamic_cast<KillEvent*>(curEvent);
				auto position = kill_event->GetTargetPosition();
				IconTexture icon = icons.at(ICON_TYPES::KILL);
				float mapX = maps[MapType].x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapY = maps[MapType].y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;
				float mapXMax = maps[MapType].x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapYMax = maps[MapType].y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(getMapXOffsetSkeld(mapX), mapY),
					ImVec2(getMapXOffsetSkeld(mapXMax), mapYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
			}
			else if (evtType == EVENT_TYPES::EVENT_VENT)
			{
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
					ImVec2(getMapXOffsetSkeld(mapX), mapY),
					ImVec2(getMapXOffsetSkeld(mapXMax), mapYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
			}
			else if (evtType == EVENT_TYPES::EVENT_TASK)
			{
				auto task_event = dynamic_cast<TaskCompletedEvent*>(curEvent);
				auto position = task_event->GetPosition();
				IconTexture icon = icons.at(ICON_TYPES::TASK);
				float mapX = maps[MapType].x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapY = maps[MapType].y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;
				float mapXMax = maps[MapType].x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosX;
				float mapYMax = maps[MapType].y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[MapType].scale + cursorPosY;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(getMapXOffsetSkeld(mapX), mapY),
					ImVec2(getMapXOffsetSkeld(mapXMax), mapYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
			}
			else if (evtType == EVENT_TYPES::EVENT_REPORT || evtType == EVENT_TYPES::EVENT_MEETING)
			{
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
					ImVec2(getMapXOffsetSkeld(mapX), mapY),
					ImVec2(getMapXOffsetSkeld(mapXMax), mapYMax),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
			}
		}
		Profiler::EndSample("ReplayEventIcons");
	}
	
	void Render()
	{
		Profiler::BeginSample("ReplayRender");
		Replay::Init();

		int MapType = State.mapType;
		ImGui::SetNextWindowSize(ImVec2((maps[MapType].mapImage.imageWidth * 0.5f) + 50.0f, (maps[MapType].mapImage.imageHeight * 0.5f) + 90.f) * State.dpiScale, ImGuiCond_None);

		ImGui::Begin("Replay", &State.ShowReplay, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
		ImGui::SetWindowFontScale(State.dpiScale);

		ImGui::BeginChild("replay#filter", ImVec2(0, 20) * State.dpiScale, true);
		ImGui::Text("Event Filter: ");
		ImGui::SameLine();
		CustomListBoxIntMultiple("Event Types", &Replay::event_filter, 100.f * State.dpiScale);
		if (IsInGame()) {
			ImGui::SameLine(0.f * State.dpiScale, 5.f * State.dpiScale);
			ImGui::Text("Player Filter: ");
			ImGui::SameLine();
			CustomListBoxPlayerSelectionMultiple("Players", &Replay::player_filter, 150.f * State.dpiScale);
		}
		ImGui::EndChild();
		ImGui::Separator();

		ImGui::BeginChild("replay#map", ImVec2((maps[MapType].mapImage.imageWidth * 0.5f) + 50.f, (maps[MapType].mapImage.imageHeight * 0.5f) + 15.f) * State.dpiScale);
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImVec2 winSize = ImGui::GetWindowSize();
		ImVec2 winPos = ImGui::GetWindowPos();

		// calculate proper cursorPosition for centerered rendering
		float cursorPosX = winPos.x + 15.f;
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

		std::chrono::system_clock::time_point minTimeFilter = State.MatchStart;
		if (State.Replay_ShowOnlyLastSeconds)
		{
			std::chrono::seconds seconds(State.Replay_LastSecondsValue);
			minTimeFilter = State.MatchCurrent - seconds;
		}

		std::lock_guard<std::mutex> replayLock(Replay::replayEventMutex);
		RenderWalkPaths(drawList, cursorPosX, cursorPosY, MapType, isUsingEventFilter, isUsingPlayerFilter, State.Replay_ShowOnlyLastSeconds, minTimeFilter, true, State.MatchCurrent);
		RenderPlayerIcons(drawList, cursorPosX, cursorPosY, MapType, isUsingEventFilter, isUsingPlayerFilter, State.Replay_ShowOnlyLastSeconds, minTimeFilter, true, State.MatchCurrent);
		RenderEventIcons(drawList, cursorPosX, cursorPosY, MapType, isUsingEventFilter, isUsingPlayerFilter, State.Replay_ShowOnlyLastSeconds, minTimeFilter, true, State.MatchCurrent);
		
		ImGui::EndChild();

		ImGui::Separator();
		ImGui::Dummy(ImVec2(1.0f, 5.0f) * State.dpiScale);

		ImGui::BeginChild("replay#control");
		
		std::string fmt("placeholder");
		State.MatchLive = std::chrono::system_clock::now();
		if (State.Replay_IsLive && !State.Replay_IsPlaying)
		{
			State.MatchCurrent = State.MatchLive;
			fmt = std::format("{:%OH:%OM:%OS}", State.MatchLive - State.MatchStart);
		}
		else
		{
			fmt = std::format("{:%OH:%OM:%OS}", State.MatchCurrent - State.MatchLive);
		}
		SliderChrono("##replay_slider", &State.MatchCurrent, &State.MatchStart, &State.MatchLive, fmt, ImGuiSliderFlags_None);
		
		ImGui::EndChild();

		ImGui::End();
		Profiler::EndSample("ReplayRender");
	}
}