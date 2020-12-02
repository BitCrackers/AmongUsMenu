#include "_hooks.hpp"

using namespace app;

void dHudManager_ShowMap(HudManager* __this, Action_1_MapBehaviour_* mapAction, MethodInfo* method) {
	HudManager_ShowMap(__this, mapAction, method);

	//if (State.ChatAlwaysActive)
	//	ChatController_SetVisible(__this->fields.Chat, true, NULL);
	//else
	//	ChatController_SetVisible(__this->fields.Chat, false, NULL);
}

void dHudManager_Update(HudManager* __this,  MethodInfo* method) {
	HudManager_Update(__this, method);

	HudManager_SetHudActive(__this, State.ShowHud, NULL);
}