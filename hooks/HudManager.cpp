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


	if (!State.InMeeting)
		HudManager_SetHudActive(__this, !State.DisableHud, NULL);

	if ((IsInGame() || IsInLobby())) {
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		if (!localData) {
			// oops: game bug
			return;
		}
		GameObject* shadowLayerObject = Component_get_gameObject((Component_1*)__this->fields.ShadowQuad, NULL);
		if(IsInGame() || IsInLobby()) {
			GameObject_SetActive(shadowLayerObject,
				!(State.FreeCam || State.EnableZoom || State.playerToFollow.has_value() || State.Wallhack || (State.MaxVision && IsInLobby())) && !localData->fields.IsDead,
				NULL);
		}

		if (!State.InMeeting && !State.DisableHud)
		{
			app::RoleBehaviour *playerRole = localData->fields.Role; // Nullable
			app::RoleTypes__Enum role = playerRole != nullptr ? playerRole->fields.Role : app::RoleTypes__Enum::Crewmate;
			GameObject* ImpostorVentButton = app::Component_get_gameObject((Component_1*)__this->fields.ImpostorVentButton, NULL);
			GameObject* ReportButton = app::Component_get_gameObject((Component_1*)__this->fields.ReportButton, NULL);

			if (role == RoleTypes__Enum::Engineer && State.UnlockVents)
			{
				app::EngineerRole *engineerRole = (app::EngineerRole*)playerRole;
				if (engineerRole->fields.cooldownSecondsRemaining > 0.0f)
					engineerRole->fields.cooldownSecondsRemaining = 0.01f; //This will be deducted below zero on the next FixedUpdate call
				engineerRole->fields.inVentTimeRemaining = 30.0f; //Can be anything as it will always be written
			}
			else if ((GetPlayerData(*Game::pLocalPlayer)->fields.IsDead || IsInLobby()))
			{
				app::GameObject_SetActive(ImpostorVentButton, false, nullptr);
			}
			else
			{
				app::GameObject_SetActive(ImpostorVentButton, (State.UnlockVents || (*Game::pLocalPlayer)->fields.inVent) || (PlayerIsImpostor(localData) && GameOptions().GetGameMode() == GameModes__Enum::Normal), nullptr);
			}

			if (IsInLobby() || GetPlayerData(*Game::pLocalPlayer)->fields.IsDead || GameOptions().GetGameMode() == GameModes__Enum::HideNSeek) //fixes a game bug where report button is visible in the lobby or when ur dead
			{
				app::GameObject_SetActive(ReportButton, false, nullptr);
			}
			else
			{
				app::GameObject_SetActive(ReportButton, true, nullptr);
			}

			for (auto player : GetAllPlayerControl())
			{
				auto playerInfo = GetPlayerData(player);
				if (!playerInfo) break; //This happens sometimes during loading

				if (State.KillImpostors && !playerInfo->fields.IsDead && PlayerIsImpostor(localData))
					playerInfo->fields.Role->fields.CanBeKilled = true;
				else if (PlayerIsImpostor(playerInfo))
					playerInfo->fields.Role->fields.CanBeKilled = false;
			}
			if (PlayerIsImpostor(localData)) {
				auto selfInfo = GetPlayerData(*Game::pLocalPlayer);
				selfInfo->fields.Role->fields.CanUseKillButton = true;
			}
		}
	}
}

void dVersionShower_Start(VersionShower* __this, MethodInfo* method) {
	app::VersionShower_Start(__this, method);
	const auto& versionText = std::format("<size=75%>{} ~ <#0f0>SickoMode</color><#f00>AU</color> v1.0_pr2</size>",
		convert_from_string(app::TMP_Text_get_text((app::TMP_Text*)__this->fields.text, nullptr)));
	app::TMP_Text_set_text((app::TMP_Text*)__this->fields.text, convert_to_string(versionText), nullptr);
}

void dPingTracker_Update(PingTracker* __this, MethodInfo* method) {
	app::PingTracker_Update(__this, method);
	std::string ping = convert_from_string(app::TMP_Text_get_text((app::TMP_Text*)__this->fields.text, nullptr));
	std::string noClip = State.NoClip ? "\nNoClip" : "";
	std::string freeCam = State.FreeCam ? "\nFreecam" : "";
	std::string spectating = "";
	if (State.playerToFollow.has_value()) {
		app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(GetPlayerControlById(State.playerToFollow.get_PlayerId())));
		spectating = "\nNow Spectating: " + convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
	}
	else spectating = "";
	std::string pingText = std::format("{}\n<#0f0>SickoMode</color><#f00>AU</color> v1.0_pr2{}{}{}", ping, noClip, freeCam, spectating);
	app::TMP_Text_set_alignment((app::TMP_Text*)__this->fields.text, app::TextAlignmentOptions__Enum::TopRight, nullptr);
	app::TMP_Text_set_text((app::TMP_Text*)__this->fields.text, convert_to_string(pingText), nullptr);
}