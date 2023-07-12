#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "utility.h"
#include "game.h"

void dHudManager_Update(HudManager* __this, MethodInfo* method) {
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

	if (__this->fields.Chat && __this->fields.Chat->fields.freeChatField) {
		__this->fields.Chat->fields.freeChatField->fields.textArea->fields.AllowPaste = State.ChatPaste;
	}


	//HudManager_SetHudActive(__this, State.ShowHud, NULL);
	if (IsInGame()) {
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		if (!localData) {
			// oops: game bug
			return;
		}
		GameObject* shadowLayerObject = Component_get_gameObject((Component_1*)__this->fields.ShadowQuad, NULL);
		GameObject_SetActive(shadowLayerObject,
			!(State.FreeCam || State.EnableZoom || State.playerToFollow.has_value() || State.Wallhack) && !localData->fields.IsDead,
			NULL);

		if (!State.InMeeting)
		{
			app::RoleBehaviour *playerRole = localData->fields.Role; // Nullable
			app::RoleTypes__Enum role = playerRole != nullptr ? playerRole->fields.Role : app::RoleTypes__Enum::Crewmate;
			GameObject* ImpostorVentButton = app::Component_get_gameObject((Component_1*)__this->fields.ImpostorVentButton, NULL);

			if (role == RoleTypes__Enum::Engineer && State.UnlockVents)
			{
				app::EngineerRole *engineerRole = (app::EngineerRole*)playerRole;
				if (engineerRole->fields.cooldownSecondsRemaining > 0.0f)
					engineerRole->fields.cooldownSecondsRemaining = 0.01f; //This will be deducted below zero on the next FixedUpdate call
				engineerRole->fields.inVentTimeRemaining = 30.0f; //Can be anything as it will always be written
			}
			else if(role == RoleTypes__Enum::GuardianAngel)
			{
				app::GameObject_SetActive(ImpostorVentButton, false, nullptr);
			}
			else
			{
				app::GameObject_SetActive(ImpostorVentButton, State.UnlockVents || PlayerIsImpostor(localData), nullptr);
			}
		}
	}
}

void dVersionShower_Start(VersionShower* __this, MethodInfo* method) {
	app::VersionShower_Start(__this, method);
	const auto& versionText = std::format("{}\n<size=70%>AmongUsMenu - {} - {}</size>",
		convert_from_string(app::TMP_Text_get_text((app::TMP_Text*)__this->fields.text, nullptr)),
		GetGitCommit().substr(0, 7), GetGitBranch()
	);
	app::TMP_Text_set_alignment((app::TMP_Text*)__this->fields.text, app::TextAlignmentOptions__Enum::TopLeft, nullptr);
	app::TMP_Text_set_text((app::TMP_Text*)__this->fields.text, convert_to_string(versionText), nullptr);
}