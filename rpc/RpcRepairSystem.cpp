#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcRepairSystem::RpcRepairSystem(SystemTypes__Enum selectedSystem, SystemTypes__Enum amount)
{
	this->selectedSystem = selectedSystem;
	this->amount = (uint32_t)amount;
}

RpcRepairSystem::RpcRepairSystem(SystemTypes__Enum selectedSystem, uint32_t amount)
{
	this->selectedSystem = selectedSystem;
	this->amount = amount;
}

void RpcRepairSystem::Process()
{
	ShipStatus_RpcRepairSystem(*Game::pShipStatus, this->selectedSystem, this->amount, NULL);
}