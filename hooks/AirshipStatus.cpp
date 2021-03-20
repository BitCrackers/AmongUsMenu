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
}