#include "pch-il2cpp.h"
#include "_hooks.h"
#include <iostream>

Vector3 dCamera_ScreenToWorldPoint(Camera* __this, Vector3 position, MethodInfo* method)
{
	app::Vector3 ret = app::Camera_ScreenToWorldPoint(__this, position, method);
	
	return ret;
}