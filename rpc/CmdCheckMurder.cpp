#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

CmdCheckMurder::CmdCheckMurder(const PlayerSelection& target)
{
	this->target = target;
}

void CmdCheckMurder::Process()
{
	PlayerControl_CmdCheckMurder(*Game::pLocalPlayer, target.get_PlayerControl().value_or(nullptr), NULL);
}