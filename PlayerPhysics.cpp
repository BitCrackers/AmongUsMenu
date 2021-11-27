#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "game.h"

void dPlayerPhysics_FixedUpdate(PlayerPhysics* __this, MethodInfo* method)
{
	bool oldInVentState = (*Game::pLocalPlayer)->fields.inVent;
	(*Game::pLocalPlayer)->fields.inVent = !State.MoveInVent && oldInVentState;
	app::PlayerPhysics_FixedUpdate(__this, method);
	(*Game::pLocalPlayer)->fields.inVent = oldInVentState;
}