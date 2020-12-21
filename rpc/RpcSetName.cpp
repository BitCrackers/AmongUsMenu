#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetName::RpcSetName(String* name)
{
	this->name = name;
}

void RpcSetName::Process()
{
	PlayerControl_CmdCheckName(*Game::pLocalPlayer, name, NULL);
}