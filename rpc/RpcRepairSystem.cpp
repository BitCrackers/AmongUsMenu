#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcRepairSystem::RpcRepairSystem(SystemTypes__Enum selectedSystem, int32_t amount)
{
	this->selectedSystem = selectedSystem;
	this->amount = amount;
}

void RpcRepairSystem::Process()
{
	ShipStatus_RpcRepairSystem(*Game::pShipStatus, this->selectedSystem, this->amount, NULL);
}