#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

VentEvent::VentEvent(EVENT_PLAYER source, Vector2 position, VENT_ACTION action) : EventInterface(source, EVENT_VENT)
{
	this->position = position;
	this->systemType = GetSystemTypes(position);
	this->action = action;
}

void VentEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text("(%s)", TranslateSystemTypes(systemType));
}

void VentEvent::ColoredEventOutput() {
	ImGui::Text("[ VENT");
	ImGui::SameLine();

	ImVec4 color;
	((action == VENT_ENTER) ? color = ImVec4(0.f, 1.f, 0.f, 1.f) : color = ImVec4(1.f, 0.f, 0.f, 1.f));

	ImGui::TextColored(color, ((action == VENT_ENTER) ? "IN" : "OUT"));
	ImGui::SameLine();
	ImGui::Text("]");
}