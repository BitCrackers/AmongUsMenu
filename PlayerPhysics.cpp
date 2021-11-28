#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "game.h"

void dPlayerPhysics_FixedUpdate(PlayerPhysics* __this, MethodInfo* method)
{
	if (((*Game::pLocalPlayer) != NULL) && (*Game::pLocalPlayer)->fields.inVent && State.MoveInVent)
	{
		(*Game::pLocalPlayer)->fields.inVent = false;
		app::PlayerPhysics_FixedUpdate(__this, method);
		(*Game::pLocalPlayer)->fields.inVent = true;
	} else
		app::PlayerPhysics_FixedUpdate(__this, method);
}