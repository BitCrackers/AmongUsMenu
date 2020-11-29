#include "_hooks.hpp"

using namespace app;

float dShipStatus_CalculateLightRadius(ShipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method) {
	if (State.MaxVision && IsInGame())
		return 10.F;
	else
		return ShipStatus_CalculateLightRadius(__this, player, method);
}

void dShipStatus_OnEnable(ShipStatus* __this, MethodInfo* method) {
	ShipStatus_OnEnable(__this, method);

	State.events.clear();

	State.selectedDoor = SystemTypes__Enum_Hallway;
	State.mapDoors.clear();
	State.pinnedDoors.clear();

	auto allDoors = __this->fields.AllDoors;

	for (il2cpp_array_size_t i = 0; i < allDoors->max_length; i++) {
		if (std::find(State.mapDoors.begin(), State.mapDoors.end(), allDoors->vector[i]->fields.Room) == State.mapDoors.end())
			State.mapDoors.push_back(allDoors->vector[i]->fields.Room);
	}

	std::sort(State.mapDoors.begin(), State.mapDoors.end());
}