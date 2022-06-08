#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

VentEvent::VentEvent(const EVENT_PLAYER& source, const Vector2& position, VENT_ACTIONS action) : EventInterface(source, EVENT_TYPES::EVENT_VENT)
{
	this->position = position;
	this->systemType = GetSystemTypes(position);
	this->action = action;
}

void VentEvent::Output()
{
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text("(%s)", TranslateSystemTypes(systemType));
	ImGui::SameLine();
	ImGui::Text("[%s ago]", std::format("{:%OM:%OS}", (std::chrono::system_clock::now() - this->timestamp)).c_str());
}

void VentEvent::ColoredEventOutput()
{
	ImGui::Text("[ VENT");
	ImGui::SameLine();

	ImVec4 color;
	((action == VENT_ACTIONS::VENT_ENTER) ? color = ImVec4(0.f, 1.f, 0.f, 1.f) : color = ImVec4(1.f, 0.f, 0.f, 1.f));

	ImGui::TextColored(color, ((action == VENT_ACTIONS::VENT_ENTER) ? "IN" : "OUT"));
	ImGui::SameLine();
	ImGui::Text("]");
}