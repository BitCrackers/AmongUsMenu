#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "esp.hpp"
#include <iostream>

Vector3 dCamera_ScreenToWorldPoint(Camera* __this, Vector3 position, MethodInfo* method)
{
	if (State.EnableZoom)
	{
		Camera_set_orthographicSize(__this, 3.0f, NULL);
		Vector3 ret = Camera_ScreenToWorldPoint(__this, position, method);
		Camera_set_orthographicSize(__this, State.CameraHeight, NULL);
		return ret;
	}

	return Camera_ScreenToWorldPoint(__this, position, method);
}