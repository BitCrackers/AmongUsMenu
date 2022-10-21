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

	State.MatchStart = std::chrono::system_clock::now();
	State.MatchCurrent = State.MatchStart;

	State.selectedDoor = SystemTypes__Enum::Hallway;
	State.mapDoors.clear();
	State.pinnedDoors.clear();

	il2cpp::Array allDoors = __this->fields._.AllDoors;

	for (auto door : allDoors) {
		if (std::find(State.mapDoors.begin(), State.mapDoors.end(), door->fields.Room) == State.mapDoors.end())
			State.mapDoors.push_back(door->fields.Room);
	}

	std::sort(State.mapDoors.begin(), State.mapDoors.end());

	State.mapType = Settings::MapType::Pb;

	State.userName = GetPlayerName();
	ResetOriginalAppearance();
}