#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

KillEvent::KillEvent(EVENT_PLAYER source, EVENT_PLAYER target, Vector2 position) : EventInterface(source, EVENT_KILL) {
	this->target = target;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

void KillEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text(">");
	ImGui::SameLine();
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(target.colorId)), target.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text("(%s)", TranslateSystemTypes(systemType));
}

void KillEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "KILL");
	ImGui::SameLine();
	ImGui::Text("]");
}