#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

RpcMurderPlayer::RpcMurderPlayer(PlayerSelection target)
{
	this->target = target;
}

void RpcMurderPlayer::Process()
{
	PlayerControl_RpcMurderPlayer(*Game::pLocalPlayer, target.get_PlayerControl(), NULL);
}