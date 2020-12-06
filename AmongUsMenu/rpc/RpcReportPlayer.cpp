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
	{	//Conditional is to prevent you reporting yourself (as much as I enjoy that)
		PlayerControl_CmdReportDeadBody(*Game::pLocalPlayer, (reportedPlayer.is_LocalPlayer()) ? NULL : reportedPlayer.get_PlayerData(), NULL);
	}
}