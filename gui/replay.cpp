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
	// any code that modifies State.liveReplayEvents or any other collection should use this mutex
	// failure to do so will invalidate any existing iterator of any thread which will lead to rare and hard to diagnose crashes
	std::mutex replayEventMutex;

	std::vector<std::pair<const char*, bool>> event_filter =
	{
		#define ADD_EVENT(name, desc) {desc, false}
		ALL_EVENTS
		#undef ADD_EVENT
	};

	std::array<std::pair<PlayerSelection, bool>, Game::MAX_PLAYERS> player_filter;

	ImU32 GetReplayPlayerColor(Game::ColorId colorId) {
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
			for (auto it = event_filter.begin(); it != event_filter.end(); it++) {
				// Exclude the following events
				switch (static_cast<EVENT_TYPES>(it - event_filter.begin())) {
				case EVENT_TYPES::EVENT_VOTE:
				case EVENT_TYPES::EVENT_CHEAT:
				case EVENT_TYPES::EVENT_DISCONNECT:
				case EVENT_TYPES::EVENT_SHAPESHIFT:
				case EVENT_TYPES::EVENT_PROTECTPLAYER:
					it->first = "";
					break;
				}
			}
			init = true;
		}
	}

	void Reset(bool all /* = true */)
	{
		synchronized(Replay::replayEventMutex) {
			State.liveReplayEvents.clear();
			if (all) {
				// free all storage
				State.liveReplayEvents.shrink_to_fit();
				std::map<Game::PlayerId, Replay::WalkEvent_LineData>().swap(State.replayWalkPolylineByPlayer);
			}
			else {
				for (auto& pair : State.replayWalkPolylineByPlayer)
				{
					pair.second.playerId = Game::NoPlayerId;
					pair.second.colorId = Game::NoColorId;
					pair.second.pendingPoints.clear();
					pair.second.pendingTimeStamps.clear();
					pair.second.simplifiedPoints.clear();
					pair.second.simplifiedTimeStamps.clear();
				}
			}

			for (size_t plyIdx = 0; plyIdx < Game::MAX_PLAYERS; plyIdx++)
			{
				State.lastWalkEventPosPerPlayer[plyIdx] = ImVec2(0.f, 0.f);
				if (all)
					State.replayDeathTimePerPlayer[plyIdx] = (std::chrono::system_clock::time_point::max)();// TODO: #define NOMINMAX 
			}
		}

		// Set this to true as the default value
		// Everytime we start a new match it will actually be in live mode
		State.Replay_IsLive = true;

		State.Replay_IsPlaying = false;
	}

	void RenderPolyline(ImDrawList* drawList, float cursorPosX, float cursorPosY, 
		std::vector<ImVec2>& points, const std::vector<std::chrono::system_clock::time_point>& timeStamps, Game::ColorId colorId, 
		bool isUsingMinTimeFilter, const std::chrono::system_clock::time_point& minTimeFilter, bool isUsingMaxTimeFilter, const std::chrono::system_clock::time_point& maxTimeFilter)
	{
		if ((isUsingMinTimeFilter == true) && (isUsingMaxTimeFilter == true)
			&& (minTimeFilter >= maxTimeFilter))
		{
			STREAM_ERROR("Min time filter is greater than max time filter (min: " << std::format("{:%OH:%OM:%OS}", minTimeFilter) << " max: " << std::format("{:%OH:%OM:%OS}", maxTimeFilter) << ")");
			return;
		}
		// this is annoying, but we have to transform the points, render, then untransform
		// if we store the transformed points then moving the replay window will cause everything to break..
		auto xOffset = getMapXOffsetSkeld(0);
		for (auto& point : points)
		{
			point.x = (point.x + xOffset) * State.dpiScale + cursorPosX;
			point.y = point.y * State.dpiScale + cursorPosY;
		}

		// earliestTimeIndex will be the very first event to be shown, lastTimeIndex will be the very last even to be shown
		size_t earliestTimeIndex = 0, lastTimeIndex = points.size() - 1;
		bool collectionHasElementsToFilterMin = false, collectionHasElementsToFilterMax = false;
		if ((isUsingMinTimeFilter == true) || (isUsingMaxTimeFilter))
		{
			// now we figure out the last index that matches the minTimeFilter
			// then we'll do some quik pointer mafs to pass to the AddPolyline call
			for (size_t index = 0; isUsingMinTimeFilter && index < timeStamps.size(); index++)
			{
				const std::chrono::system_clock::time_point& timestamp = timeStamps.at(index);
				if (timestamp > minTimeFilter)
				{
					// the first element that *matches* the minTimeFilter is where we begin drawing from
					earliestTimeIndex = index;
					collectionHasElementsToFilterMin = true;
					break;
				}
			}
			for (ptrdiff_t index = timeStamps.size() - 1; isUsingMaxTimeFilter && index >= (ptrdiff_t)earliestTimeIndex; index--)
			{
				const std::chrono::system_clock::time_point& timestamp = timeStamps.at(index);
				if (timestamp < maxTimeFilter)
				{
					// the first element that *exceeds* the maxTimeFilter is where we stop drawing
					lastTimeIndex = index;
					collectionHasElementsToFilterMax = true;
					break;
				}
			}
			
			if (!isUsingMinTimeFilter || collectionHasElementsToFilterMin) {
				// some events occurred before the specified time filter
				// so we want to draw only a portion of the total collection
				// this portion starts from the index of the last matching event and should continue to the end of the collection
				if (!isUsingMaxTimeFilter || collectionHasElementsToFilterMax) {
					size_t numPoints = lastTimeIndex - earliestTimeIndex  + 1;
					drawList->AddPolyline(points.data() + earliestTimeIndex, (int)numPoints, GetReplayPlayerColor(colorId), false, 1.f * State.dpiScale);
				}
			}
		}
		else
		{
			// we're not using any time filter, so just draw the polyline normally.
			drawList->AddPolyline(points.data(), (int)points.size(), GetReplayPlayerColor(colorId), false, 1.f * State.dpiScale);
		}

		// untransform the points before returning
		for (auto& point : points)
		{
			point.x = (point.x - cursorPosX) / State.dpiScale - xOffset;
			point.y = (point.y - cursorPosY) / State.dpiScale;
		}
	}

	void RenderWalkPaths(ImDrawList* drawList, float cursorPosX, float cursorPosY, Settings::MapType MapType, bool isUsingEventFilter, bool isUsingPlayerFilter, 
		bool isUsingMinTimeFilter, const std::chrono::system_clock::time_point& minTimeFilter, bool isUsingMaxTimeFilter, const std::chrono::system_clock::time_point& maxTimeFilter)
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
			/*size_t numPendingPoints = plrLineData.pendingPoints.size();
			if (numPendingPoints >= 100)
			{
				DoPolylineSimplification(plrLineData.pendingPoints, plrLineData.pendingTimeStamps, plrLineData.simplifiedPoints, plrLineData.simplifiedTimeStamps, 50.f, true);
			}*/

			// now the actual rendering, which should be filtered
			// player filter
			if ((isUsingPlayerFilter == true) &&
				((playerPolylinePair.first < 0) || ((size_t)playerPolylinePair.first >= Replay::player_filter.size()) ||
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

	void RenderPlayerIcons(ImDrawList* drawList, float cursorPosX, float cursorPosY, Settings::MapType MapType, bool isUsingEventFilter, bool isUsingPlayerFilter, 
		bool isUsingMinTimeFilter, const std::chrono::system_clock::time_point& minTimeFilter, bool isUsingMaxTimeFilter, const std::chrono::system_clock::time_point& maxTimeFilter)
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
			const auto& plrIdx = playerPolylinePair.first;
			const auto& plrLineData = playerPolylinePair.second;

			// player filter
			if ((isUsingPlayerFilter == true) &&
				((plrIdx < 0) || ((size_t)plrIdx >= Replay::player_filter.size()) ||
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
				size_t lastTimeIndex = plrLineData.pendingTimeStamps.size() - 1;
				for (std::vector<std::chrono::system_clock::time_point>::const_reverse_iterator riter = plrLineData.pendingTimeStamps.rbegin(); riter != plrLineData.pendingTimeStamps.rend(); riter++, lastTimeIndex--)
				{
					const std::chrono::system_clock::time_point& timestamp = *riter;
					if (timestamp <= maxTimeFilter)
					{
						playerPos = plrLineData.pendingPoints[lastTimeIndex];
						if ((isUsingMinTimeFilter == true) && (timestamp < minTimeFilter))
						{
							//STREAM_DEBUG("(not critical) Found a point matching maxTimeFilter, but does not match minTimeFilter. Add check that min < max once free time available.");
							break;
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
						if (timestamp <= maxTimeFilter)
						{
							playerPos = plrLineData.simplifiedPoints[lastTimeIndex];
							if ((isUsingMinTimeFilter == true) && (timestamp < minTimeFilter))
							{
								//STREAM_DEBUG("(not critical) Found a point matching maxTimeFilter, but does not match minTimeFilter. Add check that min < max once free time available.");
								break;
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
				//STREAM_DEBUG("Could not find replay position for player#" << plrIdx << ". Time filter was likely too strict or player hasn't moved yet.");
				continue;
			}

			IconTexture icon = icons.at(ICON_TYPES::PLAYER);
			const auto& map = maps[(size_t)MapType];
			// the latestPos variable is already pre-transformed for line rendering, so we have to un-transform and then re-transform for proper icon positioning
			// existing transformation:
			// latestPos.x = map.x_offset + (position.x * map.scale);
			// void*'s original transformation for icon positioning:
			// float player_mapX = map.x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale + cursorPosX;
			// i'm not mathematically inclined, so i don't really know what i'm doing...
			// but this is what i got for transforming from the existing to void*'s original:
			playerPos.x = getMapXOffsetSkeld(playerPos.x);
			float halfImageWidth = (icon.iconImage.imageWidth * icon.scale * 0.5f) * map.scale, halfImageHeight = (icon.iconImage.imageHeight * icon.scale * 0.5f) * map.scale;
			float player_mapX = (playerPos.x - halfImageWidth);
			float player_mapY = (playerPos.y - halfImageHeight);
			float player_mapXMax = (playerPos.x + halfImageWidth);
			float player_mapYMax = (playerPos.y + halfImageHeight);

			const ImVec2& p_min = ImVec2(player_mapX, player_mapY) * State.dpiScale + ImVec2(cursorPosX, cursorPosY);
			const ImVec2& p_max = ImVec2(player_mapXMax, player_mapYMax) * State.dpiScale + ImVec2(cursorPosX, cursorPosY);

			drawList->AddImage((void*)icon.iconImage.shaderResourceView,
				p_min, p_max,
				ImVec2(0.0f, 0.0f),
				ImVec2(1.0f, 1.0f),
				GetReplayPlayerColor(plrLineData.colorId));

			app::GameData_PlayerInfo* plrInfo = GetPlayerDataById(plrLineData.playerId);
			if ((plrInfo != NULL) &&
				((plrInfo->fields.IsDead) ||
					((plrInfo->fields.Role != NULL) &&
						(plrInfo->fields.Role->fields.Role == RoleTypes__Enum::GuardianAngel))) &&
							(!isUsingMaxTimeFilter || maxTimeFilter >= State.replayDeathTimePerPlayer[plrLineData.playerId]))
				drawList->AddImage((void*)icons.at(ICON_TYPES::CROSS).iconImage.shaderResourceView,
					p_min, p_max,
					ImVec2(0.0f, 0.0f),
					ImVec2(1.0f, 1.0f));
		}
		Profiler::EndSample("ReplayPlayerIcons");
	}

	void RenderEventIcons(ImDrawList* drawList, float cursorPosX, float cursorPosY, Settings::MapType MapType, bool isUsingEventFilter, bool isUsingPlayerFilter,
		bool isUsingMinTimeFilter, const std::chrono::system_clock::time_point& minTimeFilter,  bool isUsingMaxTimeFilter, const std::chrono::system_clock::time_point& maxTimeFilter)
	{
		Profiler::BeginSample("ReplayEventIcons");
		if ((isUsingMinTimeFilter == true) && (isUsingMaxTimeFilter == true)
			&& (minTimeFilter >= maxTimeFilter))
		{
			STREAM_ERROR("Min time filter is greater than max time filter (min: " << std::format("{:%OH:%OM:%OS}", minTimeFilter) << " max: " << std::format("{:%OH:%OM:%OS}", maxTimeFilter) << ")");
			return;
		}

		const auto& map = maps[(size_t)MapType];
		
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
				((evtPlayerSource.playerId < 0) || (evtPlayerSource.playerId >= Replay::player_filter.size()) ||
					(Replay::player_filter[evtPlayerSource.playerId].second == false) ||
					(Replay::player_filter[evtPlayerSource.playerId].first.has_value() == false)))
				continue;

			// processing
			if (evtType == EVENT_TYPES::EVENT_KILL)
			{
				auto kill_event = dynamic_cast<KillEvent*>(curEvent);
				auto position = kill_event->GetTargetPosition();
				IconTexture icon = icons.at(ICON_TYPES::KILL);
				float mapX = map.x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
				float mapY = map.y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;
				float mapXMax = map.x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
				float mapYMax = map.y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(getMapXOffsetSkeld(mapX), mapY) * State.dpiScale + ImVec2(cursorPosX, cursorPosY),
					ImVec2(getMapXOffsetSkeld(mapXMax), mapYMax) * State.dpiScale + ImVec2(cursorPosX, cursorPosY),
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
				float mapX = map.x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
				float mapY = map.y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;
				float mapXMax = map.x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
				float mapYMax = map.y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(getMapXOffsetSkeld(mapX), mapY) * State.dpiScale + ImVec2(cursorPosX, cursorPosY),
					ImVec2(getMapXOffsetSkeld(mapXMax), mapYMax) * State.dpiScale + ImVec2(cursorPosX, cursorPosY),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
			}
			else if (evtType == EVENT_TYPES::EVENT_TASK)
			{
				auto task_event = dynamic_cast<TaskCompletedEvent*>(curEvent);
				auto position = task_event->GetPosition();
				IconTexture icon = icons.at(ICON_TYPES::TASK);
				float mapX = map.x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
				float mapY = map.y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;
				float mapXMax = map.x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
				float mapYMax = map.y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(getMapXOffsetSkeld(mapX), mapY) * State.dpiScale + ImVec2(cursorPosX, cursorPosY),
					ImVec2(getMapXOffsetSkeld(mapXMax), mapYMax) * State.dpiScale + ImVec2(cursorPosX, cursorPosY),
					ImVec2(0.0f, 1.0f),
					ImVec2(1.0f, 0.0f));
			}
			else if (evtType == EVENT_TYPES::EVENT_REPORT || evtType == EVENT_TYPES::EVENT_MEETING)
			{
				auto report_event = dynamic_cast<ReportDeadBodyEvent*>(curEvent);
				auto position = report_event->GetPosition();
				IconTexture icon = icons.at(ICON_TYPES::REPORT);
				float mapX = map.x_offset + (position.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
				float mapY = map.y_offset - (position.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;
				float mapXMax = map.x_offset + (position.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
				float mapYMax = map.y_offset - (position.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;

				drawList->AddImage((void*)icon.iconImage.shaderResourceView,
					ImVec2(getMapXOffsetSkeld(mapX), mapY) * State.dpiScale + ImVec2(cursorPosX, cursorPosY),
					ImVec2(getMapXOffsetSkeld(mapXMax), mapYMax) * State.dpiScale + ImVec2(cursorPosX, cursorPosY),
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

		const auto& map = maps[(size_t)State.mapType];
		ImGui::SetNextWindowSize(ImVec2((map.mapImage.imageWidth * 0.5f) + 50.0f, (map.mapImage.imageHeight * 0.5f) + 90.f) * State.dpiScale, ImGuiCond_None);

		ImGui::Begin("Replay", &State.ShowReplay, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

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

		ImGui::BeginChild("replay#map", ImVec2((map.mapImage.imageWidth * 0.5f) + 50.f, (map.mapImage.imageHeight * 0.5f) + 15.f) * State.dpiScale);
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImVec2 winSize = ImGui::GetWindowSize();
		ImVec2 winPos = ImGui::GetWindowPos();

		// calculate proper cursorPosition for centerered rendering
		float cursorPosX = winPos.x + 15.f * State.dpiScale;
		float cursorPosY = winPos.y + (winSize.y * 0.15f) - ((float)(map.mapImage.imageHeight * 0.15f) * 0.5f) * State.dpiScale;

		// TODO: Center image in childwindow and calculate new cursorPos
		drawList->AddImage((void*)map.mapImage.shaderResourceView,
			ImVec2(cursorPosX, cursorPosY) + 5.0f * State.dpiScale,
			ImVec2(cursorPosX, cursorPosY) + ImVec2(5.0f + ((float)map.mapImage.imageWidth * 0.5f),  5.0f + ((float)map.mapImage.imageHeight * 0.5f)) * State.dpiScale,
			(State.FlipSkeld && State.mapType == Settings::MapType::Ship) ? ImVec2(1.0f, 0.0f) : ImVec2(0.0f, 0.0f),
			(State.FlipSkeld && State.mapType == Settings::MapType::Ship) ? ImVec2(0.0f, 1.0f) : ImVec2(1.0f, 1.0f),
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

		std::chrono::system_clock::time_point minTimeFilter = State.MatchStart;
		if (State.Replay_ShowOnlyLastSeconds)
		{
			std::chrono::seconds seconds(State.Replay_LastSecondsValue);
			minTimeFilter = State.MatchCurrent - seconds;
		}

		synchronized(Replay::replayEventMutex)
		{
			RenderWalkPaths(drawList, cursorPosX, cursorPosY, State.mapType, isUsingEventFilter, isUsingPlayerFilter, State.Replay_ShowOnlyLastSeconds, minTimeFilter, true, State.MatchCurrent);
			RenderPlayerIcons(drawList, cursorPosX, cursorPosY, State.mapType, isUsingEventFilter, isUsingPlayerFilter, false, minTimeFilter, true, State.MatchCurrent);
			RenderEventIcons(drawList, cursorPosX, cursorPosY, State.mapType, isUsingEventFilter, isUsingPlayerFilter, State.Replay_ShowOnlyLastSeconds, minTimeFilter, true, State.MatchCurrent);
		}
		ImGui::EndChild();

		ImGui::Separator();
		ImGui::Dummy(ImVec2(1.0f, 5.0f) * State.dpiScale);

		ImGui::BeginChild("replay#control");
		
		SliderChrono("##replay_slider", &State.MatchCurrent, &State.MatchStart, &State.MatchLive, fmt, ImGuiSliderFlags_None);
		
		ImGui::EndChild();

		ImGui::End();
		Profiler::EndSample("ReplayRender");
	}
}