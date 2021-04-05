#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

void dMainMenuManager_Start(MainMenuManager* __this, MethodInfo* method)
{
	MainMenuManager_Start(__this, method);

	//This hook is good for one-time initializing at the beginning of the game

	State.userName = convert_from_string(SaveManager__TypeInfo->static_fields->lastPlayerName);
}