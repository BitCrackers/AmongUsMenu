#include "il2cpp-appdata.h"
#include "_rpc.h"

RpcMurderPlayer::RpcMurderPlayer(PlayerControl* murdering_player, PlayerControl* selected_player)
{
	this->selectedPlayer = selected_player;
	this->murderer = murdering_player;
}

void RpcMurderPlayer::Process()
{
	PlayerControl_MurderPlayer(murderer, selectedPlayer, NULL);
}