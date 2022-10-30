#include "pch-il2cpp.h"
#include "_rpc.h"
#include "imgui/imgui.h"
#include "state.hpp"
#include <chrono>

RpcChatMessage::RpcChatMessage(std::string senderName, std::string message, uint32_t colorId, std::chrono::system_clock::time_point timestamp) {
	this->SenderName = senderName;
	this->Message = message;
	this->ColorId = colorId;
	this->Timestamp = timestamp;
}

void RpcChatMessage::Process() {
	MessageWriter* rpcMessage = InnerNetClient_StartRpc((InnerNetClient*)(*Game::pAmongUsClient), (*Game::pLocalPlayer)->fields._.NetId, 101, (SendOption__Enum)1, NULL);
	MessageWriter_WriteString(rpcMessage, convert_to_string(this->SenderName), NULL);
	MessageWriter_WriteString(rpcMessage, convert_to_string(this->Message), NULL);
	MessageWriter_WriteInt32(rpcMessage, this->ColorId, NULL);
	MessageWriter_EndMessage(rpcMessage, NULL);
}

void RpcChatMessage::PrintUser() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(this->ColorId)), GetPlayerName()._Equal(this->SenderName.c_str()) ? "You" : this->SenderName.c_str());
	ImGui::SameLine();
	ImGui::TextWrapped("]");
	ImGui::SameLine();
	ImGui::TextColored(ImGui::GetStyle().Colors[ImGuiCol_TextDisabled], "(%s)", std::format("{:%OH:%OM:%OS}", this->Timestamp).c_str());
}

void RpcChatMessage::PrintMessage() {
	ImGui::TextWrapped(this->Message.c_str());
}