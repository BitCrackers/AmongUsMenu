#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

KillEvent::KillEvent(EVENT_PLAYER source, EVENT_PLAYER target, Vector2 position, Vector2 targetPosition) : EventInterface(source, EVENT_KILL) {
	this->target = target;
	this->targetPosition = targetPosition;
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
	ImGui::SameLine();
	ImGui::Text(" [%s min ago]", formatDuration<std::chrono::system_clock::duration, std::chrono::minutes, std::chrono::seconds>(std::chrono::system_clock::now() - this->timestamp).c_str());
}

void KillEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "KILL");
	ImGui::SameLine();
	ImGui::Text("]");
}