#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetName::RpcSetName(std::string name)
{
	this->name = convert_to_string(name);
}

void RpcSetName::Process()
{
	PlayerControl_CmdCheckName(*Game::pLocalPlayer, name, NULL);
}