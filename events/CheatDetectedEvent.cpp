#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

CheatDetectedEvent::CheatDetectedEvent(EVENT_PLAYER source, CHEAT_ACTION action) : EventInterface(source, EVENT_CHEAT, ImColor(1.f, 0.f, 0.f, 1.f)) {
	this->action = action;
	this->systemType = GetSystemTypes(source.position);
}

void CheatDetectedEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text(">");
	ImGui::SameLine();
	ImGui::Text("Cheat detected: %s", CHEAT_ACTION_NAMES[this->action]);
	ImGui::SameLine();
	auto sec = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::seconds>(this->timestamp.time_since_epoch()).count();
	auto min = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::minutes>(this->timestamp.time_since_epoch()).count();
	if (sec < 60) ImGui::Text(" [%ds ago]", sec);
	else ImGui::Text(" [%dm ago]", min);
}

void CheatDetectedEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(this->getColor(), "CHEAT");
	ImGui::SameLine();
	ImGui::Text("]");
}