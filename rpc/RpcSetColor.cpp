#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetColor::RpcSetColor(uint8_t bodyColor, bool force)
{
	this->bodyColor = bodyColor;
	this->forceColor = force;
}

void RpcSetColor::Process()
{
	if (forceColor)
		PlayerControl_RpcSetColor(*Game::pLocalPlayer, bodyColor, NULL);
	else
		PlayerControl_CmdCheckColor(*Game::pLocalPlayer, bodyColor, NULL);
}