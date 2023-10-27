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

RpcForceColor::RpcForceColor(PlayerControl* player, uint8_t bodyColor, bool force)
{
	this->Player = player;
	this->bodyColor = bodyColor;
	this->forceColor = force;
}

void RpcForceColor::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;

	if (forceColor)
		PlayerControl_RpcSetColor(Player, bodyColor, NULL);
	else
		PlayerControl_CmdCheckColor(Player, bodyColor, NULL);
}