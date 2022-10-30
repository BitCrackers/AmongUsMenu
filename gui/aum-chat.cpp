#include "pch-il2cpp.h"
#include "aum-chat.hpp"
#include "imgui/imgui.h"
#include "gui-helpers.hpp"
#include "state.hpp"
#include "logger.h"

namespace ChatGui
{
	char inputBuffer[250]{ "" };

	void SendChatMessage(std::string message) {
		if (message.length() == 0) return;

		auto gPlayerInfo = GetPlayerDataById((*Game::pLocalPlayer)->fields.PlayerId);
		auto outfit = GetPlayerOutfit(gPlayerInfo);
		auto name = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
		State.chatMessages.emplace_back(std::make_unique<RpcChatMessage>(name, message, (uint32_t)outfit->fields.ColorId, std::chrono::system_clock::now()));
		if (IsInGame()) State.rpcQueue.push(new RpcChatMessage(name, message, (uint32_t)outfit->fields.ColorId, std::chrono::system_clock::now()));
		else if (IsInLobby()) State.lobbyRpcQueue.push(new RpcChatMessage(name, message, (uint32_t)outfit->fields.ColorId, std::chrono::system_clock::now()));
		State.newChatMessage = true;

		for (int i = 0; i < sizeof(inputBuffer); i++) {
			inputBuffer[i] = (char)0;
		}
	}

	void Init() {
		ImGui::SetNextWindowSize(ImVec2(520, 320) * State.dpiScale, ImGuiCond_None);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	void Render() {
		ChatGui::Init();

		ImGui::Begin("Chat", &State.ShowChat, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		ImGui::BeginChild("chat#scroll", ImVec2(511, 270) * State.dpiScale, true, ImGuiWindowFlags_AlwaysVerticalScrollbar);

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

		ImGui::BeginChild("chat#input", ImVec2(520, 20)* State.dpiScale, true);

		if (ImGui::InputText("", inputBuffer, IM_ARRAYSIZE(inputBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
			SendChatMessage(std::string(inputBuffer));
		}

		ImGui::SameLine(340.f * State.dpiScale);

		if (ImGui::Button("Send")) {
			SendChatMessage(std::string(inputBuffer));
		}

		ImGui::EndChild();
		ImGui::End();
	}
}