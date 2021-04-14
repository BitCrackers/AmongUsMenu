#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetPet::RpcSetPet(uint32_t petId)
{
	this->PetId = petId;
}

void RpcSetPet::Process()
{
	PlayerControl_RpcSetPet((*Game::pLocalPlayer), this->PetId, NULL);
}

RpcSetSkin::RpcSetSkin(uint32_t skinId)
{
	this->SkinId = skinId;
}

void RpcSetSkin::Process()
{
	PlayerControl_RpcSetSkin((*Game::pLocalPlayer), this->SkinId, NULL);
}

RpcSetHat::RpcSetHat(uint32_t hatId)
{
	this->HatId = hatId;
}

void RpcSetHat::Process()
{
	PlayerControl_RpcSetHat((*Game::pLocalPlayer), this->HatId, NULL);
}