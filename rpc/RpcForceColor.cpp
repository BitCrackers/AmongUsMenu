#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcForceColor::RpcForceColor(uint8_t bodyColor)
{
	this->Player = player;
	this->bodyColor = bodyColor;
}

void RpcForceColor::Process()
{
	PlayerControl_CmdCheckColor(player, bodyColor, NULL);
}