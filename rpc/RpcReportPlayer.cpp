#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcReportPlayer::RpcReportPlayer(const PlayerSelection& target)
{
	this->reportedPlayer = target;
}

void RpcReportPlayer::Process()
{
	PlayerControl_CmdReportDeadBody(*Game::pLocalPlayer, reportedPlayer.get_PlayerData().value_or(nullptr), nullptr);
}