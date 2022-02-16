#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

ShapeShiftEvent::ShapeShiftEvent(EVENT_PLAYER source, EVENT_PLAYER target) : EventInterface(source, EVENT_SHAPESHIFT) {
	this->target = target;
}

void ShapeShiftEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text(">");
	ImGui::SameLine();
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(target.colorId)), target.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text(" [%s min ago]", formatDuration<std::chrono::system_clock::duration, std::chrono::minutes, std::chrono::seconds>(std::chrono::system_clock::now() - this->timestamp).c_str());
}

void ShapeShiftEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 0.5f, 0.f, 1.f), "SHAPESHIFT");
	ImGui::SameLine();
	ImGui::Text("]");
}