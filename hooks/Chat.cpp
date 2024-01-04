#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "game.h"
#include "state.hpp"

void dChatController_AddChat(ChatController* __this, PlayerControl* sourcePlayer, String* chatText, bool censor, MethodInfo* method) {
	if (!State.DisableSMAU && State.ReadGhostMessages) {
		bool wasDead = false;
		GameData_PlayerInfo* player = GetPlayerData(sourcePlayer);
		GameData_PlayerInfo* local = GetPlayerData(*Game::pLocalPlayer);

		if (player != NULL && player->fields.IsDead && local != NULL && !local->fields.IsDead) {
			local->fields.IsDead = true;
			wasDead = true;
		}
		auto outfit = GetPlayerOutfit(GetPlayerData(sourcePlayer));
		std::string playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
		std::string message = convert_from_string(chatText);
		uint32_t colorId = outfit->fields.ColorId;
		State.chatMessages.emplace_back(std::make_unique<RpcChatMessage>(playerName, message, colorId, std::chrono::system_clock::now()));
		State.newChatMessage = true;
		ChatController_AddChat(__this, sourcePlayer, chatText, censor, method);
		if (wasDead) {
			local->fields.IsDead = false;
		}
	}
	else {
		auto player = *Game::pLocalPlayer;
		if (State.playerToChatAs.has_value())
			player = GetPlayerControlById(State.playerToChatAs.get_PlayerId());
		if (sourcePlayer != player) {
			auto outfit = GetPlayerOutfit(GetPlayerData(sourcePlayer));
			std::string playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
			std::string message = convert_from_string(chatText);
			uint32_t colorId = outfit->fields.ColorId;
			State.chatMessages.emplace_back(std::make_unique<RpcChatMessage>(playerName, message, colorId, std::chrono::system_clock::now()));
			State.newChatMessage = true;
		}
		ChatController_AddChat(__this, sourcePlayer, chatText, censor, method);
	}
}

void dChatController_SetVisible(ChatController* __this, bool visible, MethodInfo* method) {
	if (State.ChatAlwaysActive && !State.DisableSMAU)
		ChatController_SetVisible(__this, true, method);
	else {
		State.ChatActiveOriginalState = visible;
		ChatController_SetVisible(__this, visible, method);
	}
}

void dChatBubble_SetName(ChatBubble* __this, String* playerName, bool isDead, bool voted, Color color, MethodInfo* method) {
	if (!State.DisableSMAU && (IsInGame() || IsInLobby())) {
		for (auto playerData : GetAllPlayerData()) {
			app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);
			if (outfit == NULL) continue;
			if (playerName == GameData_PlayerOutfit_get_PlayerName(outfit, nullptr)) {
				if (State.RevealRoles)
					color = GetRoleColor(playerData->fields.Role);
				else
					color = Palette__TypeInfo->static_fields->White;

				if (State.PlayerColoredDots) {
					Color32&& nameColor = GetPlayerColor(outfit->fields.ColorId);
					std::string dot = std::format("<#{:02x}{:02x}{:02x}{:02x}>●</color>",
						nameColor.r, nameColor.g, nameColor.b,
						nameColor.a);

					if (playerData != GetPlayerData(*Game::pLocalPlayer))
						playerName = convert_to_string(convert_from_string(playerName) + " " + dot);
					else
						playerName = convert_to_string(dot + " " + convert_from_string(playerName));
				}
				if (State.CustomName && !State.ServerSideCustomName && playerData == GetPlayerData(*Game::pLocalPlayer)) {
					if (State.ColoredName && !State.RgbName) {
						playerName = convert_to_string(GetGradientUsername(convert_from_string(playerName)));
					}
					//we don't want to hide our own chat messages
					/*if (State.ResizeName)
						playerName = convert_to_string(std::format("<size={}>", State.NameSize) + convert_from_string(playerName) + "</size>");*/
					if (State.ItalicName)
						playerName = convert_to_string("<i>" + convert_from_string(playerName) + "</i>");
					if (State.UnderlineName && (!State.ColoredName || State.RgbName))
						playerName = convert_to_string("<u>" + convert_from_string(playerName) + "</u>");
					if (State.StrikethroughName && (!State.ColoredName || State.RgbName))
						playerName = convert_to_string("<s>" + convert_from_string(playerName) + "</s>");
					//rgb color doesn't change
					/*if (State.RgbName) {
						playerName = convert_to_string(State.rgbCode + convert_from_string(playerName) + "</color>");
					}*/
				}
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
	//0x08 is backspace, 0x0D is carriage return, 0x3C is <, 0x3E is >
	return (unicode_char != 0x08 && unicode_char != 0x0D && ((State.SafeMode && unicode_char != 0x3C && unicode_char != 0x3E) || !State.SafeMode));
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
	if (!State.DisableSMAU && __this == *Game::pLocalPlayer && !State.SafeMode && State.activeChatSpoof && State.playerToChatAs.has_value())
		PlayerControl_RpcSendChat(GetPlayerControlById(State.playerToChatAs.get_PlayerId()), chatText, NULL);
	else
		PlayerControl_RpcSendChat(__this, chatText, NULL);
}