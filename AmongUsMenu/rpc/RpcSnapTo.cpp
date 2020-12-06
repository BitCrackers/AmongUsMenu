#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

RpcSnapTo::RpcSnapTo(Vector2 targetVector)
{
	this->targetVector = targetVector;
}

void RpcSnapTo::Process()
{
	CustomNetworkTransform_RpcSnapTo((*Game::pLocalPlayer)->fields.NetTransform, this->targetVector, NULL);
}