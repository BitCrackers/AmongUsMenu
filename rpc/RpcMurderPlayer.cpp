#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcMurderPlayer::RpcMurderPlayer(const PlayerSelection& target)
{
	this->target = target;
}

void RpcMurderPlayer::Process()
{
	PlayerControl_RpcMurderPlayer(*Game::pLocalPlayer, target.get_PlayerControl().value_or(nullptr), NULL);
}