#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcReportPlayer::RpcReportPlayer(PlayerSelection target)
{
	this->reportedPlayer = target;
}

void RpcReportPlayer::Process()
{
	if (reportedPlayer.has_value())
	{
		PlayerControl_CmdReportDeadBody(*Game::pLocalPlayer, reportedPlayer.get_PlayerData(), NULL);
	}
	else
	{
		PlayerControl_CmdReportDeadBody(*Game::pLocalPlayer, NULL, NULL);
	}
}