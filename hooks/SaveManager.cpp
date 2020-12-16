#include "_hooks.hpp"

void dSaveManager_set_BodyColor(uint8_t value, MethodInfo* method)
{
	SaveManager_set_BodyColor(value, method);
}

uint8_t dSaveManager_get_BodyColor(MethodInfo* method)
{
	if (State.AntiBan)
		return 20;
	else
		return SaveManager_get_BodyColor(method);
}