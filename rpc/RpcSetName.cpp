#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetName::RpcSetName(std::string_view name)
{
	this->name = name;
}

void RpcSetName::Process()
{
	PlayerControl_CmdCheckName(*Game::pLocalPlayer, convert_to_string(name), NULL);
}

RpcForceName::RpcForceName(PlayerControl* player, std::string_view name)
{
	this->Player = player;
	this->name = name;
}

void RpcForceName::Process()
{
	if (!PlayerSelection(Player).has_value())
		return;

	PlayerControl_CmdCheckName(Player, convert_to_string(name), NULL);
}