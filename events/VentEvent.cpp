#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"
#include <chrono>

VentEvent::VentEvent(EVENT_PLAYER source, VENT_ACTION action) : EventInterface(source, EVENT_VENT, (action == VENT_ENTER) ? ImColor(0.f, 1.f, 0.f, 1.f) : ImColor(1.f, 0.f, 0.f, 1.f)) {
	this->action = action;
	this->systemType = GetSystemTypes(source.position);
}

void VentEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text("(%s)", TranslateSystemTypes(this->systemType));
	ImGui::SameLine();
	auto sec = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::seconds>(this->timestamp.time_since_epoch()).count();
	auto min = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::minutes>(this->timestamp.time_since_epoch()).count();
	if (sec < 60) ImGui::Text(" [%ds ago]", sec);
	else ImGui::Text(" [%dm ago]", min);
}

void VentEvent::ColoredEventOutput() {
	ImGui::Text("[ VENT");
	ImGui::SameLine();
	ImGui::TextColored(this->getColor(), ((action == VENT_ENTER) ? "IN" : "OUT"));
	ImGui::SameLine();
	ImGui::Text("]");
}