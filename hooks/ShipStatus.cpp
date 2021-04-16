#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "game.h"

float dShipStatus_CalculateLightRadius(ShipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method) {
	if (State.MaxVision || State.EnableZoom || State.FreeCam)
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

	State.mapType = (Settings::MapType)(__this->fields.Type);
	if (State.HideNSeek) {
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Electrical, 7));
	}
}

void dShipStatus_RpcRepairSystem(ShipStatus* __this, SystemTypes__Enum systemType, int32_t amount, MethodInfo* method) {
	if (State.HideNSeek) {
		return;
	}
	ShipStatus_RpcRepairSystem(__this, systemType, amount, method);
}

void dGameStartManager_Update(GameStartManager* __this, MethodInfo* method) {
	if (State.HideCode) {
		TMP_Text_SetText((TMP_Text*)__this->fields.GameRoomName, convert_to_string(State.CustomCode), false, NULL);
	}
	else {
		TMP_Text_SetText((TMP_Text*)__this->fields.GameRoomName, InnerNet_GameCode_IntToGameName((*Game::pAmongUsClient)->fields._.GameId, NULL), false, NULL);
	}
	GameStartManager_Update(__this, method);
}