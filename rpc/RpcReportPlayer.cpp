#include "il2cpp-appdata.h"
#include "_rpc.h"

RpcReportPlayer::RpcReportPlayer(PlayerControl* reporting_player, GameData_PlayerInfo* selected_player)
{
	this->reportingPlayer = reporting_player;
	this->selectedPlayer = selected_player;
}

void RpcReportPlayer::Process()
{
	PlayerControl_CmdReportDeadBody(reportingPlayer, selectedPlayer, NULL);
}