#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

void dHudManager_ShowMap(HudManager* __this, Action_1_MapBehaviour_* mapAction, MethodInfo* method) {
	HudManager_ShowMap(__this, mapAction, method);

	//if (State.ChatAlwaysActive)
	//	ChatController_SetVisible(__this->fields.Chat, true, NULL);
	//else
	//	ChatController_SetVisible(__this->fields.Chat, false, NULL);
}

void dHudManager_Update(HudManager* __this,  MethodInfo* method) {
	HudManager_Update(__this, method);
	__this->fields.PlayerCam->fields.Locked = (State.FreeCam);
	//HudManager_SetHudActive(__this, State.ShowHud, NULL);
}

void dChatController_Update(ChatController* __this, MethodInfo* method) {
	SaveManager__TypeInfo->static_fields->chatModeType = 1;
	SaveManager__TypeInfo->static_fields->isGuest = false;
	ChatController_Update(__this, method);
}

void dAccountTab_Open(AccountTab* __this, MethodInfo* method) {
	AccountTab_Open(__this, method);
	FullAccount_CanSetCustomName(__this->fields.fullAccount, true, NULL);
}