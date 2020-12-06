#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

RpcSetScanner::RpcSetScanner(bool playAnimation)
{
	this->playAnimation = playAnimation;
}

void RpcSetScanner::Process()
{
	PlayerControl_RpcSetScanner(*Game::pLocalPlayer, playAnimation, NULL);
}