#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "utility.h"
#include "game.h"

void dHudManager_ShowMap(HudManager* __this, Action_1_MapBehaviour_* mapAction, MethodInfo* method) {
	HudManager_ShowMap(__this, mapAction, method);

	//if (State.ChatAlwaysActive)
	//	ChatController_SetVisible(__this->fields.Chat, true, NULL);
	//else
	//	ChatController_SetVisible(__this->fields.Chat, false, NULL);
}

void dHudManager_Update(HudManager* __this,  MethodInfo* method) {
	static bool bChatAlwaysActivePrevious = false;
	if (bChatAlwaysActivePrevious != State.ChatAlwaysActive)
	{
		if (State.ChatAlwaysActive)
			ChatController_SetVisible(__this->fields.Chat, true, NULL);
		else if (!State.InMeeting && !IsInLobby()) //You will lose chat ability in meeting otherwise
			ChatController_SetVisible(__this->fields.Chat, State.ChatActiveOriginalState, NULL);
		bChatAlwaysActivePrevious = State.ChatAlwaysActive;
	}
	HudManager_Update(__this, method);
	__this->fields.PlayerCam->fields.Locked = State.FreeCam;
	
	//HudManager_SetHudActive(__this, State.ShowHud, NULL);
	if (IsInGame()) {
		GameObject* shadowLayerObject = Component_get_gameObject((Component*)__this->fields.ShadowQuad, NULL);
		GameObject_SetActive(shadowLayerObject,
			!(State.FreeCam || State.EnableZoom || State.playerToFollow.has_value() || State.Wallhack) && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead,
			NULL);
	}
}

void dVersionShower_Start(VersionShower* __this, MethodInfo* method) {
	VersionShower_Start(__this, method);
	std::string versionText = convert_from_string(__this->fields.text->fields._.m_text);
	versionText = versionText + "\n AmongUsMenu - " + GetGitBranch();
	__this->fields.text->fields._.m_text = convert_to_string(versionText);
}