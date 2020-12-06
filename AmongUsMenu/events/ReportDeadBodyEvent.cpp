#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

ReportDeadBodyEvent::ReportDeadBodyEvent(EVENT_PLAYER source, std::optional<EVENT_PLAYER> target, Vector2 position)
	: EventInterface(source, (target.has_value() ? EVENT_REPORT : EVENT_MEETING)) {
	this->target = target;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

void ReportDeadBodyEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();

	if (target.has_value()) {
		ImGui::Text(">");
		ImGui::SameLine();
		ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(target->colorId)), target->playerName.c_str());
		ImGui::SameLine();
	}

	ImGui::Text("(%s)", TranslateSystemTypes(systemType));
}

void ReportDeadBodyEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored((target) ? ImVec4(1.f, 0.5f, 0.f, 1.f) : ImVec4(1.f, 1.f, 0, 1.f), (target.has_value()) ? "REPORT" : "MEETING");
	ImGui::SameLine();
	ImGui::Text("]");
}