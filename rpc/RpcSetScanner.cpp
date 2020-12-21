#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetScanner::RpcSetScanner(bool playAnimation)
{
	this->playAnimation = playAnimation;
}

void RpcSetScanner::Process()
{
	PlayerControl_RpcSetScanner(*Game::pLocalPlayer, playAnimation, NULL);
}