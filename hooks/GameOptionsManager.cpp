#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

void dGameOptionsManager_set_CurrentGameOptions(GameOptionsManager* __this, IGameOptions* value, MethodInfo* method) {
	GameOptionsManager_set_CurrentGameOptions(__this, value, method);
	GameOptions gameOptions(value);
	if (gameOptions.HasOptions()) {
		SaveGameOptions(gameOptions);
	}
}