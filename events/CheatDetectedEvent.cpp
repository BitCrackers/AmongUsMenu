#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

CheatDetectedEvent::CheatDetectedEvent(EVENT_PLAYER source, CHEAT_ACTION action) : EventInterface(source, EVENT_CHEAT) {
	this->action = action;
}

void CheatDetectedEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text(">");
	ImGui::SameLine();

	ImGui::Text("Cheat detected: %s", CHEAT_ACTION_NAMES[this->action]);
}

void CheatDetectedEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "CHEAT");
	ImGui::SameLine();
	ImGui::Text("]");
}