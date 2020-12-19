#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

RpcSetColor::RpcSetColor(uint8_t bodyColor)
{
	this->bodyColor = bodyColor;
}

void RpcSetColor::Process()
{
	PlayerControl_CmdCheckColor(*Game::pLocalPlayer, bodyColor, NULL);
}