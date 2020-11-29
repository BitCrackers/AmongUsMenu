#include "il2cpp-appdata.h"
#include "_rpc.h"

RpcMurderPlayer::RpcMurderPlayer(PlayerControl* murderer, PlayerControl* selected_player)
{
	this->murderer = murderer;
	this->selectedPlayer = selected_player;
}

void RpcMurderPlayer::Process()
{
	PlayerControl_MurderPlayer(murderer, selectedPlayer, NULL);
}