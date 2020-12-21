#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcPlayAnimation::RpcPlayAnimation(uint8_t animId)
{
	this->animId = animId;
}

void RpcPlayAnimation::Process()
{
	PlayerControl_RpcPlayAnimation(*Game::pLocalPlayer, animId, NULL);
}