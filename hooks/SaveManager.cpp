#include "_hooks.hpp"

void dSaveManager_set_BodyColor(uint8_t value, MethodInfo* method)
{
	SaveManager_set_BodyColor(min(value,19), method); //Prevent saving any colors over 19 to playerprefs
}

uint8_t dSaveManager_get_BodyColor(MethodInfo* method)
{
	if (State.AntiBan && (*Game::pAmongUsClient)->fields.GameMode != GameModes__Enum_FreePlay)
		return 20;
	else
		return SaveManager_get_BodyColor(method);
}