#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"
#include "utility.h"
#include "replay.hpp"
#include "profiler.h"
#include "game.h"

float dShipStatus_CalculateLightRadius(ShipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method) {
	if (State.MaxVision || State.EnableZoom || State.FreeCam)
		return 420.F;
	else
		return ShipStatus_CalculateLightRadius(__this, player, method);
}

void dShipStatus_OnEnable(ShipStatus* __this, MethodInfo* method) {
	ShipStatus_OnEnable(__this, method);

	Replay::Reset();

	if (Constants_ShouldFlipSkeld(NULL))
		State.FlipSkeld = true;
	else
		State.FlipSkeld = false;

	State.MatchStart = std::chrono::system_clock::now();
	State.MatchCurrent = State.MatchStart;

	State.selectedDoor = SystemTypes__Enum::Hallway;
	State.mapDoors.clear();
	State.pinnedDoors.clear();

	il2cpp::Array allDoors = __this->fields.AllDoors;

	for (auto door : allDoors) {
		if (std::find(State.mapDoors.begin(), State.mapDoors.end(), door->fields.Room) == State.mapDoors.end())
			State.mapDoors.push_back(door->fields.Room);
	}

	std::sort(State.mapDoors.begin(), State.mapDoors.end());

	State.mapType = (Settings::MapType)(__this->fields.Type);

	if (State.DisableSabotages) {
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Electrical, 7));
	}
}

void dShipStatus_RpcRepairSystem(ShipStatus* __this, SystemTypes__Enum systemType, int32_t amount, MethodInfo* method) {
	if (State.DisableSabotages) {
		return;
	}
	ShipStatus_RpcRepairSystem(__this, systemType, amount, method);
}

void dShipStatus_RpcCloseDoorsOfType (ShipStatus* __this, SystemTypes__Enum type, MethodInfo* method) {
	if (State.DisableSabotages) {
		return;
	}
	ShipStatus_RpcCloseDoorsOfType(__this, type, method);
}

void dGameStartManager_Update(GameStartManager* __this, MethodInfo* method) {
	if (State.HideCode && IsStreamerMode()) {
		if (State.RgbLobbyCode)
			TMP_Text_set_text((TMP_Text*)__this->fields.GameRoomNameCode, convert_to_string(State.rgbCode + State.customCode), NULL);
		else
			TMP_Text_set_text((TMP_Text*)__this->fields.GameRoomNameCode, convert_to_string(State.customCode), NULL);
	}
	else {
		std::string LobbyCode = convert_from_string(InnerNet_GameCode_IntToGameName((*Game::pAmongUsClient)->fields._.GameId, NULL));
		if (State.RgbLobbyCode)
			TMP_Text_set_text((TMP_Text*)__this->fields.GameRoomNameCode, convert_to_string(State.rgbCode + LobbyCode), NULL);
		else
			TMP_Text_set_text((TMP_Text*)__this->fields.GameRoomNameCode, convert_to_string(LobbyCode), NULL);
	}
	GameStartManager_Update(__this, method);
}