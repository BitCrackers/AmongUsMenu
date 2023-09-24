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

RpcForceReportPlayer::RpcForceReportPlayer(PlayerControl* Player, const PlayerSelection& target)
{
	this->Player = Player;
	this->reportedPlayer = target;
}

void RpcForceReportPlayer::Process()
{
	PlayerControl_CmdReportDeadBody(Player, reportedPlayer.get_PlayerData().value_or(nullptr), nullptr);
}

RpcForceMeeting::RpcForceMeeting(PlayerControl* Player, const PlayerSelection& target)
{
	this->Player = Player;
	this->reportedPlayer = target;
}

void RpcForceMeeting::Process()
{
	PlayerControl_RpcStartMeeting(Player, reportedPlayer.get_PlayerData().value_or(nullptr), nullptr);
}