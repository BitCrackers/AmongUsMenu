#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "game.h"
#include "state.hpp"

void dChatController_AddChat(ChatController* __this, PlayerControl* sourcePlayer, String* chatText, bool censor, MethodInfo* method) {
	if (State.ReadGhostMessages) {
		bool wasDead = false;
		auto player = GetPlayerData(sourcePlayer);
		auto local = GetPlayerData(*Game::pLocalPlayer);

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
	if (State.ChatAlwaysActive)
		ChatController_SetVisible(__this, true, method);
	else
	{
		State.ChatActiveOriginalState = visible;
		ChatController_SetVisible(__this, visible, method);
	}
}

void dChatBubble_SetName(ChatBubble* __this, String* playerName, bool isDead, bool voted, Color color, MethodInfo* method) {
	if (IsInGame()) {
		for (auto playerData : GetAllPlayerData()) {
			auto outfit = GetPlayerOutfit(playerData);
			if (outfit == NULL) continue;
			if (playerName == outfit->fields.PlayerName) {
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
	ChatController_Update(__this, method);
}