#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

void dLobbyBehaviour_Start(LobbyBehaviour* __this, MethodInfo* method)
{
	State.LobbyTimer = 15;
	if (State.confuser && State.confuseOnJoin)
		ControlAppearance(true);
	LobbyBehaviour_Start(__this, method);
}