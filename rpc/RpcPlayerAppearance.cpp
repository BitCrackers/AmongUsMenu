#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetPet::RpcSetPet(String* petId)
{
	this->PetId = petId ? petId : convert_to_string("0");
}

void RpcSetPet::Process()
{
	PlayerControl_RpcSetPet((*Game::pLocalPlayer), this->PetId, NULL);
}

RpcForcePet::RpcForcePet(PlayerControl* Player, String* petId)
{
	this->Player = Player;
	this->PetId = petId ? petId : convert_to_string("0");
}

void RpcForcePet::Process()
{
	PlayerControl_RpcSetPet(Player, this->PetId, NULL);
}

RpcSetSkin::RpcSetSkin(String* skinId)
{
	this->SkinId = skinId ? skinId : convert_to_string("0");
}

void RpcSetSkin::Process()
{
	PlayerControl_RpcSetSkin((*Game::pLocalPlayer), this->SkinId, NULL);
}

RpcForceSkin::RpcForceSkin(PlayerControl* Player, String* skinId)
{
	this->Player = Player;
	this->SkinId = skinId ? skinId : convert_to_string("0");
}

void RpcForceSkin::Process()
{
	PlayerControl_RpcSetSkin(Player, this->SkinId, NULL);
}

RpcSetHat::RpcSetHat(String* hatId)
{
	this->HatId = hatId ? hatId : convert_to_string("0");
}

void RpcSetHat::Process()
{
	PlayerControl_RpcSetHat((*Game::pLocalPlayer), this->HatId, NULL);
}

RpcForceHat::RpcForceHat(PlayerControl* Player, String* hatId)
{
	this->Player = Player;
	this->HatId = hatId ? hatId : convert_to_string("0");
}

void RpcForceHat::Process()
{
	PlayerControl_RpcSetHat(Player, this->HatId, NULL);
}

RpcSetVisor::RpcSetVisor(String* visorId)
{
	this->VisorId = visorId ? visorId : convert_to_string("0");
}

void RpcSetVisor::Process()
{
	PlayerControl_RpcSetVisor((*Game::pLocalPlayer), this->VisorId, NULL);
}

RpcForceVisor::RpcForceVisor(PlayerControl* Player, String* visorId)
{
	this->Player = Player;
	this->VisorId = visorId ? visorId : convert_to_string("0");
}

void RpcForceVisor::Process()
{
	PlayerControl_RpcSetVisor(Player, this->VisorId, NULL);
}

RpcSetNamePlate::RpcSetNamePlate(String* namePlateId)
{
	this->NamePlateId = namePlateId ? namePlateId : convert_to_string("0");
}

void RpcSetNamePlate::Process()
{
	PlayerControl_RpcSetNamePlate((*Game::pLocalPlayer), this->NamePlateId, NULL);
}

RpcForceNamePlate::RpcForceNamePlate(PlayerControl* Player, String* namePlateId)
{
	this->Player = Player;
	this->NamePlateId = namePlateId ? namePlateId : convert_to_string("0");
}

void RpcForceNamePlate::Process()
{
	PlayerControl_RpcSetNamePlate(Player, this->NamePlateId, NULL);
}