#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

RpcSetName::RpcSetName(String* name)
{
	this->name = name;
}

void RpcSetName::Process()
{
	PlayerControl_CmdCheckName(*Game::pLocalPlayer, name, NULL);
}