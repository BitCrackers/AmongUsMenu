#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "game.hpp"
#include "utility.h"

RpcReportPlayer::RpcReportPlayer(PlayerControl* reporting_player, PlayerControl* selected_player)
{
	this->reportingPlayer = reporting_player;
	this->selectedPlayer = selected_player;
}

void RpcReportPlayer::Process()
{
	PlayerControl_CmdReportDeadBody(reportingPlayer, GetPlayerData(selectedPlayer), NULL);
}