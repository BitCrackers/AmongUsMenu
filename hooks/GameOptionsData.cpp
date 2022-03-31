#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

GameOptionsData* dGameOptionsData_Deserialize(BinaryReader* reader, MethodInfo* method) {
	auto gameOptions = GameOptionsData_Deserialize(reader, method);

	State.PrevPlayerSpeed = gameOptions->fields._.playerSpeedMod;
	State.PlayerSpeed = gameOptions->fields._.playerSpeedMod;
	State.PrevKillDistance = gameOptions->fields._.killDistance;
	State.KillDistance = gameOptions->fields._.killDistance;
	State.PrevTaskBarUpdates = (int)gameOptions->fields.TaskBarMode;
	State.TaskBarUpdates = (int)gameOptions->fields.TaskBarMode;
	State.mapHostChoice = gameOptions->fields.MapId;
	State.impostors_amount = gameOptions->fields._.numImpostors;

	return gameOptions;
}

GameOptionsData* dGameOptionsData_Deserialize_1(MessageReader* reader, MethodInfo* method) {
	auto gameOptions = GameOptionsData_Deserialize_1(reader, method);

	State.PrevPlayerSpeed = gameOptions->fields._.playerSpeedMod;
	State.PlayerSpeed = gameOptions->fields._.playerSpeedMod;
	State.PrevKillDistance = gameOptions->fields._.killDistance;
	State.KillDistance = gameOptions->fields._.killDistance;
	State.PrevTaskBarUpdates = (int)gameOptions->fields.TaskBarMode;
	State.TaskBarUpdates = (int)gameOptions->fields.TaskBarMode;
	State.mapHostChoice = gameOptions->fields.MapId;
	State.impostors_amount = gameOptions->fields._.numImpostors;

	return gameOptions;
}