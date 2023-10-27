#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcUpdateSystem::RpcUpdateSystem(SystemTypes__Enum selectedSystem, SystemTypes__Enum amount)
{
	this->selectedSystem = selectedSystem;
	this->amount = (uint32_t)amount;
}

RpcUpdateSystem::RpcUpdateSystem(SystemTypes__Enum selectedSystem, uint32_t amount)
{
	this->selectedSystem = selectedSystem;
	this->amount = amount;
}

void RpcUpdateSystem::Process()
{
	ShipStatus_RpcUpdateSystem(*Game::pShipStatus, this->selectedSystem, this->amount, NULL);
}