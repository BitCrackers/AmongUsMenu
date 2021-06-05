#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"
#include "state.hpp"
#include "logger.h"
#include "utility.h"

RpcUsePlatform::RpcUsePlatform()
{

}

void RpcUsePlatform::Process()
{
	if (State.mapType == Settings::MapType::Airship && IsHost())
	{
		auto shipStatus = (AirshipStatus*)*(Game::pShipStatus);
		auto movingPlatform = shipStatus->fields.GapPlatform;
		if (movingPlatform->fields.Target == nullptr) //If the platform is in use, this would cause unknown behaviour.
			MovingPlatformBehaviour_SetSide(movingPlatform, !movingPlatform->fields.IsLeft, NULL);

		STREAM_DEBUG("Moving Platform warped to " << (movingPlatform->fields.IsLeft ? "Left" : "Right"));
	}
}