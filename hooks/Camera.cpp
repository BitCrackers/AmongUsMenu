#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "esp.hpp"
#include <iostream>

Vector3 dCamera_ScreenToWorldPoint(Camera* __this, Vector3 position, MethodInfo* method)
{
	if (State.EnableZoom)
	{
		app::Camera_set_orthographicSize(__this, 3.0f, NULL);
		app::Vector3 ret = app::Camera_ScreenToWorldPoint(__this, position, method);
		app::Camera_set_orthographicSize(__this, State.CameraHeight, NULL);
		return ret;
	}

	return app::Camera_ScreenToWorldPoint(__this, position, method);
}