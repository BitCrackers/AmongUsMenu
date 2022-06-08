#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

CheatDetectedEvent::CheatDetectedEvent(const EVENT_PLAYER& source, CHEAT_ACTIONS action) : EventInterface(source, EVENT_TYPES::EVENT_CHEAT) {
	this->action = action;
}

void CheatDetectedEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text(">");
	ImGui::SameLine();
	ImGui::Text("Cheat detected: %s", CHEAT_ACTION_NAMES[(int)this->action]);
	ImGui::SameLine();
	ImGui::Text("[%s ago]", std::format("{:%OM:%OS}", (std::chrono::system_clock::now() - this->timestamp)).c_str());
}

void CheatDetectedEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "CHEAT");
	ImGui::SameLine();
	ImGui::Text("]");
}