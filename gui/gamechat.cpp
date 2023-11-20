#include "pch-il2cpp.h"
#include "gamechat.hpp"
#include "imgui/imgui.h"
#include "gui-helpers.hpp"
#include "state.hpp"
#include "logger.h"

namespace ChatGui
{
	char inputBuffer[100]{ "" };

	void SendChatMessage(std::string message) {
		if (message.length() == 0) return;

		auto gPlayerInfo = GetPlayerDataById((*Game::pLocalPlayer)->fields.PlayerId);
		auto outfit = GetPlayerOutfit(gPlayerInfo);
		auto name = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
		State.chatMessages.emplace_back(std::make_unique<RpcChatMessage>(name, message, (uint32_t)outfit->fields.ColorId, std::chrono::system_clock::now()));
		if (IsInGame()) State.rpcQueue.push(new RpcSendChat(*Game::pLocalPlayer, message));
		else if (IsInLobby()) State.lobbyRpcQueue.push(new RpcSendChat(*Game::pLocalPlayer, message));
		State.newChatMessage = true;
	}

	void Init() {
		ImGui::SetNextWindowSize(ImVec2(520, 320) * State.dpiScale, ImGuiCond_None);
		ImGui::SetNextWindowBgAlpha(State.MenuThemeColor.w);
	}

	void Render() {
		ChatGui::Init();
		ImGui::Begin("Chat", &State.ShowChat, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginChild("chat#scroll", ImVec2(511, 270) * State.dpiScale, true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoBackground);

		size_t i = 0;
		for (auto it = State.chatMessages.begin(); it != State.chatMessages.end(); ++it, ++i) {
			RpcChatMessage* cMsg = (*it).get();
			if (cMsg == NULL)
			{
				STREAM_ERROR("State.chatMessages[" << i << "] was NULL (chatMessages.size(): " << State.chatMessages.size() << ")");
				continue;
			}

			cMsg->PrintUser();
			ImGui::SameLine();
			cMsg->PrintMessage();
		}
		if (State.newChatMessage) {
			State.newChatMessage = false;
			ImGui::SetScrollY(ImGui::GetScrollMaxY() + 50);
		}
		ImGui::EndChild();

		ImGui::Separator();

		ImGui::Dummy(ImVec2(1.0f, 2.0f) * State.dpiScale);

		ImGui::BeginChild("chat#input", ImVec2(520, 20) * State.dpiScale, true, ImGuiWindowFlags_NoBackground);

		if (ImGui::InputText("", inputBuffer, IM_ARRAYSIZE(inputBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
			SendChatMessage(std::string(inputBuffer));
		}

		ImGui::SameLine(340.f * State.dpiScale);

		if (State.ChatCooldown >= 3.f && ImGui::Button("Send")) {
			auto player = *Game::pLocalPlayer;
			if (State.playerToChatAs.has_value())
				player = GetPlayerControlById(State.playerToChatAs.get_PlayerId());
			if (IsInGame())
				State.rpcQueue.push(new RpcSendChat(player, std::string(inputBuffer)));
			else if (IsInLobby())
				State.lobbyRpcQueue.push(new RpcSendChat(player, std::string(inputBuffer)));
			State.MessageSent = true;
		}
		ImGui::SameLine();
		if (!State.SafeMode && ImGui::Button("Send as Everyone")) {
			for (auto player : GetAllPlayerControl()) {
				if (IsInGame())
					State.rpcQueue.push(new RpcSendChat(player, std::string(inputBuffer)));
				else if (IsInLobby())
					State.lobbyRpcQueue.push(new RpcSendChat(player, std::string(inputBuffer)));
			}
		}

		ImGui::EndChild();
		ImGui::End();
	}
}