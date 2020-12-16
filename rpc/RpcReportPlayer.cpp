#include "il2cpp-appdata.h"
#include "utility.h"
#include "_rpc.h"

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