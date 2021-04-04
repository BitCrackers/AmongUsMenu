#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

void dPolusShipStatus_OnEnable(PolusShipStatus* __this, MethodInfo* method)
{
	PolusShipStatus_OnEnable(__this, method);

	State.events.clear();

	State.selectedDoor = SystemTypes__Enum_Hallway;
	State.mapDoors.clear();
	State.pinnedDoors.clear();

	auto allDoors = __this->fields._.AllDoors;

	for (il2cpp_array_size_t i = 0; i < allDoors->max_length; i++) {
		if (std::find(State.mapDoors.begin(), State.mapDoors.end(), allDoors->vector[i]->fields.Room) == State.mapDoors.end())
			State.mapDoors.push_back(allDoors->vector[i]->fields.Room);
	}

	std::sort(State.mapDoors.begin(), State.mapDoors.end());

	State.mapType = Settings::MapType::Pb;
}