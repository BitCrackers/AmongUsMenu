#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

void dAirshipStatus_OnEnable(AirshipStatus* __this, MethodInfo* method)
{
	AirshipStatus_OnEnable(__this, method);

	State.events.clear();

	State.selectedDoor = SystemTypes__Enum_Hallway;
	State.mapDoors.clear();
	State.pinnedDoors.clear();
	State.playerSkinLocations.clear();

	auto allDoors = __this->fields._.AllDoors;

	for (il2cpp_array_size_t i = 0; i < allDoors->max_length; i++) {
		if (std::find(State.mapDoors.begin(), State.mapDoors.end(), allDoors->vector[i]->fields.Room) == State.mapDoors.end())
			State.mapDoors.push_back(allDoors->vector[i]->fields.Room);
	}

	std::sort(State.mapDoors.begin(), State.mapDoors.end());

	State.mapType = Settings::MapType::Airship;
}

float dAirshipStatus_CalculateLightRadius(AirshipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method)
{
	if (State.MaxVision || State.EnableZoom || State.FreeCam)
		return 10.F;
	else
		return AirshipStatus_CalculateLightRadius(__this, player, method);
}