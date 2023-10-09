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

void RpcChatMessage::Process() {}

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