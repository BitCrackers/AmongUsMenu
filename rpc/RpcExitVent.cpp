#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcExitVent::RpcExitVent(int32_t id)
{
	this->ventId = id;
}

void RpcExitVent::Process()
{
	PlayerPhysics_RpcExitVent((*Game::pLocalPlayer)->fields.MyPhysics, this->ventId, NULL);
}