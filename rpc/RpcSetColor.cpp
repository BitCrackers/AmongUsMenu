#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetColor::RpcSetColor(uint8_t bodyColor)
{
	this->bodyColor = bodyColor;
}

void RpcSetColor::Process()
{
	PlayerControl_CmdCheckColor(*Game::pLocalPlayer, bodyColor, NULL);
}