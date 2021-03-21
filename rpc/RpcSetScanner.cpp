#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"

RpcSetScanner::RpcSetScanner(bool playAnimation)
{
	this->playAnimation = playAnimation;
}

void RpcSetScanner::Process()
{
	app::Vector3 medScannerVec = app::MedScannerBehaviour_get_Position((*Game::pShipStatus)->fields.MedScanner, NULL);
	app::Vector2 medScannerLocation;
	medScannerLocation.x = medScannerVec.x;
	medScannerLocation.y = medScannerVec.y += 0.36f;
	CustomNetworkTransform_RpcSnapTo((*Game::pLocalPlayer)->fields.NetTransform, medScannerLocation, NULL);
	PlayerControl_RpcSetScanner(*Game::pLocalPlayer, playAnimation, NULL);
}