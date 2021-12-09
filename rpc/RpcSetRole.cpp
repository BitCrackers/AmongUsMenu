#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetRole::RpcSetRole(PlayerControl* player, RoleTypes__Enum role)
{
	this->Player = player;
	this->Role = role;
}

void RpcSetRole::Process()
{
	PlayerControl_RpcSetRole(Player, Role, NULL);
}