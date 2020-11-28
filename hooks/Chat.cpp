#include "_hooks.hpp"

using namespace app;

void dChatController_AddChat(ChatController* __this, PlayerControl* sourcePlayer, String* chatText, MethodInfo* method) {
	if (State.ReadGhostMessages) {
		bool wasDead = false;
		GameData_PlayerInfo* player = GetPlayerData(sourcePlayer);
		GameData_PlayerInfo* local = GetPlayerData(*Game::pLocalPlayer);
		if (player->fields.IsDead && !local->fields.IsDead) {
			local->fields.IsDead = true;
			wasDead = true;
		}
		ChatController_AddChat(__this, sourcePlayer, chatText, method);
		if (wasDead) {
			local->fields.IsDead = false;
		}
	}
	else
		ChatController_AddChat(__this, sourcePlayer, chatText, method);
}

void dChatController_SetVisible(ChatController* __this, bool visible, MethodInfo* method) {
	if (State.ChatAlwaysActive)
		ChatController_SetVisible(__this, true, method);
	else
		ChatController_SetVisible(__this, visible, method);
}

void dChatBubble_SetName(ChatBubble* __this, String* playerName, bool isDead, bool voted, Color color, MethodInfo* method) {
	if (IsInGame()) {
		for (auto playerData : GetAllPlayerData()) {
			if (playerName == playerData->fields.PlayerName) {
				auto localData = GetPlayerData(*Game::pLocalPlayer);
				if (!localData)
					continue;

				if (State.RevealImpostors || localData->fields.IsImpostor)
					color = playerData->fields.IsImpostor
					? Palette__TypeInfo->static_fields->ImpostorRed
					: Palette__TypeInfo->static_fields->White;
				else
					color = Palette__TypeInfo->static_fields->White;
			}
		}
	}
	ChatBubble_SetName(__this, playerName, isDead, voted, color, method);
}

void dHudManager_ShowMap(HudManager* __this, Action_1_MapBehaviour_* mapAction, MethodInfo* method) {
	HudManager_ShowMap(__this, mapAction, method);

	if (State.ChatAlwaysActive)
		ChatController_SetVisible(__this->fields.Chat, true, NULL);
	else
		ChatController_SetVisible(__this->fields.Chat, false, NULL);
}