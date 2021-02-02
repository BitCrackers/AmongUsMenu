#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcEnterVent::RpcEnterVent(int32_t id)
{
	this->playerId = id;
}

void RpcEnterVent::Process()
{
	PlayerPhysics_RpcEnterVent((*Game::pLocalPlayer)->fields.MyPhysics, (*Game::pLocalPlayer)->fields.PlayerId, NULL);
}