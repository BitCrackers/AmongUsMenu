#include "il2cpp-appdata.h"
#include "utility.h"
#include "_rpc.h"

RpcReportPlayer::RpcReportPlayer(PlayerSelection selected_player)
{
	this->reportedPlayer = selected_player;
}

void RpcReportPlayer::Process()
{
	if (reportedPlayer.has_value())
		PlayerControl_CmdReportDeadBody(*Game::pLocalPlayer, reportedPlayer.get_PlayerData(), NULL);
}