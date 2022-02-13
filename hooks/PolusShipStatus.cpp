#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"
#include "utility.h"
#include "replay.hpp"
#include "profiler.h"

void dPolusShipStatus_OnEnable(PolusShipStatus* __this, MethodInfo* method)
{
	PolusShipStatus_OnEnable(__this, method);

	Replay::Reset();
    for (auto& e : State.rawEvents)
        e.reset();
    State.rawEvents.clear();
	for (auto& e : State.liveReplayEvents)
		e.reset();
	State.liveReplayEvents.clear();
	for (auto& pair : State.replayWalkPolylineByPlayer)
	{
		pair.second.playerId = 0;
		pair.second.colorId = 0;
		pair.second.pendingPoints.clear();
		pair.second.simplifiedPoints.clear();
	}

	for (int plyIdx = 0; plyIdx < MAX_PLAYERS; plyIdx++)
	{
		State.lastWalkEventPosPerPlayer[plyIdx] = ImVec2(0.f, 0.f);
	}

	State.selectedDoor = SystemTypes__Enum::Hallway;
	State.mapDoors.clear();
	State.pinnedDoors.clear();

	auto allDoors = __this->fields._.AllDoors;

	for (il2cpp_array_size_t i = 0; i < allDoors->max_length; i++) {
		if (std::find(State.mapDoors.begin(), State.mapDoors.end(), allDoors->vector[i]->fields.Room) == State.mapDoors.end())
			State.mapDoors.push_back(allDoors->vector[i]->fields.Room);
	}

	std::sort(State.mapDoors.begin(), State.mapDoors.end());

	State.mapType = Settings::MapType::Pb;

	State.userName = convert_from_string(SaveManager__TypeInfo->static_fields->lastPlayerName);
	ResetOriginalAppearance();
}