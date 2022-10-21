#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"
#include "utility.h"

void dAirshipStatus_OnEnable(AirshipStatus* __this, MethodInfo* method)
{
	AirshipStatus_OnEnable(__this, method);

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

	State.mapType = Settings::MapType::Airship;

	State.userName = GetPlayerName();
	ResetOriginalAppearance();
}

float dAirshipStatus_CalculateLightRadius(AirshipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method)
{
	if (State.MaxVision || State.EnableZoom || State.FreeCam)
		return 10.F;
	else
		return AirshipStatus_CalculateLightRadius(__this, player, method);
}