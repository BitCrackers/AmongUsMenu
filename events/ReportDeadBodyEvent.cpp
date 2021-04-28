#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

ReportDeadBodyEvent::ReportDeadBodyEvent(EVENT_PLAYER source, std::optional<EVENT_PLAYER> target)
	: EventInterface(source, (target.has_value() ? EVENT_REPORT : EVENT_MEETING), (target) ? ImColor(1.f, 0.5f, 0.f, 1.f) : ImColor(1.f, 1.f, 0.f, 1.f)) {
	this->target = target;
	this->systemType = GetSystemTypes(source.position);
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
	ImGui::Text("(%s)", TranslateSystemTypes(this->systemType));
	ImGui::SameLine();
	auto sec = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::seconds>(this->timestamp.time_since_epoch()).count();
	auto min = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::minutes>(this->timestamp.time_since_epoch()).count();
	if (sec < 60) ImGui::Text(" [%ds ago]", sec);
	else ImGui::Text(" [%dm ago]", min);
}

void ReportDeadBodyEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(this->getColor(), (target.has_value()) ? "REPORT" : "MEETING");
	ImGui::SameLine();
	ImGui::Text("]");
}