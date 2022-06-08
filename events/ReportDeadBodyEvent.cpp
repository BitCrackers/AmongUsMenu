#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

ReportDeadBodyEvent::ReportDeadBodyEvent(const EVENT_PLAYER& source, const std::optional<EVENT_PLAYER>& target, const Vector2& position, const std::optional<Vector2>& targetPosition)
	: EventInterface(source, (target.has_value() ? EVENT_TYPES::EVENT_REPORT : EVENT_TYPES::EVENT_MEETING)) {
	this->target = target;
	this->position = position;
	this->targetPosition = targetPosition;
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
	ImGui::SameLine();
	ImGui::Text("[%s ago]", std::format("{:%OM:%OS}", (std::chrono::system_clock::now() - this->timestamp)).c_str());
}

void ReportDeadBodyEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored((target) ? ImVec4(1.f, 0.5f, 0.f, 1.f) : ImVec4(1.f, 1.f, 0, 1.f), (target.has_value()) ? "REPORT" : "MEETING");
	ImGui::SameLine();
	ImGui::Text("]");
}