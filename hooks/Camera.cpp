#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "esp.hpp"
#include <iostream>

Vector3 dCamera_ScreenToWorldPoint(Camera* __this, Vector3 position, MethodInfo* method)
{
	try {
		if (!State.DisableSMAU && State.EnableZoom)
		{	//Figured it is better to restore the current camera height than using state
			float orthographicSize = Camera_get_orthographicSize(__this, NULL);
			Camera_set_orthographicSize(__this, 3.0f, NULL);
			Vector3 ret = Camera_ScreenToWorldPoint(__this, position, method);
			Camera_set_orthographicSize(__this, orthographicSize, NULL);
			return ret;
		}
	}
	catch (...) {
		LOG_DEBUG("Exception occurred in Camera_ScreenToWorldPoint (Camera)"); //better safe than sorry
	}

	return Camera_ScreenToWorldPoint(__this, position, method);
}

void dFollowerCamera_Update(FollowerCamera* __this, MethodInfo* method) {
	try {
		if (!State.DisableSMAU) {
			if (auto playerToFollow = State.playerToFollow.validate(); playerToFollow.has_value())
			{
				__this->fields.Target = (MonoBehaviour*)playerToFollow.get_PlayerControl();
			}
			else if (__this->fields.Target != (MonoBehaviour*)(*Game::pLocalPlayer)) {
				__this->fields.Target = (MonoBehaviour*)(*Game::pLocalPlayer);
			}
		}
		else __this->fields.Target = (MonoBehaviour*)(*Game::pLocalPlayer);
	}
	catch (...) {
		LOG_DEBUG("Exception occurred in FollowerCamera_Update (Camera)");
	}
	FollowerCamera_Update(__this, method);
}