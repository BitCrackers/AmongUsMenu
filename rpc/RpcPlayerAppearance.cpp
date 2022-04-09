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

RpcSetSkin::RpcSetSkin(String* skinId)
{
	this->SkinId = skinId ? skinId : convert_to_string("0");
}

void RpcSetSkin::Process()
{
	PlayerControl_RpcSetSkin((*Game::pLocalPlayer), this->SkinId, NULL);
}

RpcSetHat::RpcSetHat(String* hatId)
{
	this->HatId = hatId ? hatId : convert_to_string("0");
}

void RpcSetHat::Process()
{
	PlayerControl_RpcSetHat((*Game::pLocalPlayer), this->HatId, NULL);
}

RpcSetVisor::RpcSetVisor(String* visorId)
{
	this->VisorId = visorId ? visorId : convert_to_string("");
}

void RpcSetVisor::Process()
{
	PlayerControl_RpcSetVisor((*Game::pLocalPlayer), this->VisorId, NULL);
}

RpcSetNamePlate::RpcSetNamePlate(String* namePlateId)
{
	this->NamePlateId = namePlateId ? namePlateId : convert_to_string("");
}

void RpcSetNamePlate::Process()
{
	PlayerControl_RpcSetNamePlate((*Game::pLocalPlayer), this->NamePlateId, NULL);
}