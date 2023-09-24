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