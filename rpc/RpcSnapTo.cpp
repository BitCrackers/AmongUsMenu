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

RpcForceSnapTo::RpcForceSnapTo(PlayerControl* Player, Vector2 targetVector)
{
	this->Player = Player;
	this->targetVector = targetVector;
}

void RpcForceSnapTo::Process()
{
	CustomNetworkTransform_RpcSnapTo((Player)->fields.NetTransform, this->targetVector, NULL);
}