#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetPet::RpcSetPet(String* petId)
{
	this->PetId = petId;
}

void RpcSetPet::Process()
{
	PlayerControl_RpcSetPet((*Game::pLocalPlayer), this->PetId, NULL);
}

RpcSetSkin::RpcSetSkin(String* skinId)
{
	this->SkinId = skinId;
}

void RpcSetSkin::Process()
{
	PlayerControl_RpcSetSkin((*Game::pLocalPlayer), this->SkinId, NULL);
}

RpcSetHat::RpcSetHat(String* hatId)
{
	this->HatId = hatId;
}

void RpcSetHat::Process()
{
	PlayerControl_RpcSetHat((*Game::pLocalPlayer), this->HatId, NULL);
}