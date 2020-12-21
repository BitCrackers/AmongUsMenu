#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSnapTo::RpcSnapTo(Vector2 targetVector)
{
	this->targetVector = targetVector;
}

void RpcSnapTo::Process()
{
	CustomNetworkTransform_RpcSnapTo((*Game::pLocalPlayer)->fields.NetTransform, this->targetVector, NULL);
}