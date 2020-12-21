#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcMurderPlayer::RpcMurderPlayer(PlayerSelection target)
{
	this->target = target;
}

void RpcMurderPlayer::Process()
{
	PlayerControl_RpcMurderPlayer(*Game::pLocalPlayer, target.get_PlayerControl(), NULL);
}