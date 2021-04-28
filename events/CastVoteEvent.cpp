#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

CastVoteEvent::CastVoteEvent(EVENT_PLAYER source, std::optional<EVENT_PLAYER> target) : EventInterface(source, EVENT_VOTE) {
	this->target = target;
}

void CastVoteEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text(">");
	ImGui::SameLine();
	if (target.has_value()) ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(target->colorId)), target->playerName.c_str());
	else ImGui::Text("Skipped");
	ImGui::SameLine();
	auto sec = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::seconds>(this->timestamp.time_since_epoch()).count();
	auto min = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now().time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::minutes>(this->timestamp.time_since_epoch()).count();
	if (sec < 60) ImGui::Text(" [%d sec ago]", sec);
	else ImGui::Text(" [%d min ago]", min);
}

void CastVoteEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.3f, 0.4f, 1.f, 1.f), "VOTE");
	ImGui::SameLine();
	ImGui::Text("]");
}