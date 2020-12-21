#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"
#include "state.hpp"

RpcCloseDoorsOfType::RpcCloseDoorsOfType(SystemTypes__Enum selectedSystem, bool pinDoor)
{
	this->selectedSystem = selectedSystem;
	this->pinDoor = pinDoor;
}

void RpcCloseDoorsOfType::Process()
{
	app::ShipStatus_RpcCloseDoorsOfType(*Game::pShipStatus, this->selectedSystem, NULL);
	if (this->pinDoor)
		State.pinnedDoors.push_back(this->selectedSystem);
}