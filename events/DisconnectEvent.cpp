#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

DisconnectEvent::DisconnectEvent(EVENT_PLAYER source) : EventInterface(source, EVENT_DISCONNECT) { }

void DisconnectEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text("has left the game");
	ImGui::SameLine();
	auto sec = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::seconds>(this->timestamp.time_since_epoch()).count();
	auto min = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::minutes>(this->timestamp.time_since_epoch()).count();
	if (sec < 60) ImGui::Text(" [%ds ago]", sec);
	else ImGui::Text(" [%dm ago]", min);
}

void DisconnectEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 1.f), "DISCONNECT");
	ImGui::SameLine();
	ImGui::Text("]");
}