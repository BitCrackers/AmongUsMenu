#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "game.h"
#include "state.hpp"

void dChatController_AddChat(ChatController* __this, PlayerControl* sourcePlayer, String* chatText, bool censor, MethodInfo* method) {
	if (State.ReadGhostMessages) {
		bool wasDead = false;
		GameData_PlayerInfo* player = GetPlayerData(sourcePlayer);
		GameData_PlayerInfo* local = GetPlayerData(*Game::pLocalPlayer);

		if (player != NULL && player->fields.IsDead && local != NULL && !local->fields.IsDead) {
			local->fields.IsDead = true;
			wasDead = true;
		}
		ChatController_AddChat(__this, sourcePlayer, chatText, censor, method);
		if (wasDead) {
			local->fields.IsDead = false;
		}
	}
	else
		ChatController_AddChat(__this, sourcePlayer, chatText, censor, method);
}

void dChatController_SetVisible(ChatController* __this, bool visible, MethodInfo* method) {
	State.ChatActiveOriginalState = visible;
	if ( (State.ChatAlwaysActive || (IsInLobby() || State.InMeeting || GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) && !State.RefreshChatButton )
		ChatController_SetVisible(__this, true, method);
	else
		ChatController_SetVisible(__this, false, method);
}

void dChatBubble_SetName(ChatBubble* __this, String* playerName, bool isDead, bool voted, Color color, MethodInfo* method) {
	if (IsInGame()) {
		for (auto playerData : GetAllPlayerData()) {
			app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);
			if (outfit == NULL) continue;
			if (playerName == GameData_PlayerOutfit_get_PlayerName(outfit, nullptr)) {
				if (State.RevealRoles)
					color = GetRoleColor(playerData->fields.Role);
				else
					color = Palette__TypeInfo->static_fields->White;
			}
		}
	}
	ChatBubble_SetName(__this, playerName, isDead, voted, color, method);
}

void dChatController_Update(ChatController* __this, MethodInfo* method)
{
	__this->fields.freeChatField->fields.textArea->fields.characterLimit = 2147483647;
	__this->fields.freeChatField->fields.textArea->fields.allowAllCharacters = true;
	__this->fields.freeChatField->fields.textArea->fields.AllowEmail = true;
	__this->fields.freeChatField->fields.textArea->fields.AllowSymbols = true;
	if (!State.SafeMode)
		__this->fields.timeSinceLastMessage = 3.f;

	if (State.MessageSent && State.SafeMode) {
		__this->fields.timeSinceLastMessage = 0.f;
		State.MessageSent = false;
	}
	State.ChatCooldown = __this->fields.timeSinceLastMessage;
	State.ChatFocused = __this->fields.freeChatField->fields.textArea->fields.hasFocus;

	ChatController_Update(__this, method);
}

bool dTextBoxTMP_IsCharAllowed(TextBoxTMP* __this, uint16_t unicode_char, MethodInfo* method)
{
	return (unicode_char != 0x08 && unicode_char != 0x0D);
}

void dTextBoxTMP_SetText(TextBoxTMP* __this, String* input, String* inputCompo, MethodInfo* method)
{
	if (IsHost() || !State.SafeMode)
		__this->fields.characterLimit = 2147483647;
	else
		__this->fields.characterLimit = 100;

	TextBoxTMP_SetText(__this, input, inputCompo, method);
	
}

void dPlayerControl_RpcSendChat(PlayerControl* __this, String* chatText, MethodInfo* method)
{
	if (__this == *Game::pLocalPlayer && !State.SafeMode && State.activeChatSpoof && State.playerToChatAs.has_value())
		PlayerControl_RpcSendChat(GetPlayerControlById(State.playerToChatAs.get_PlayerId()), chatText, NULL);
	else
		PlayerControl_RpcSendChat(__this, chatText, NULL);
}