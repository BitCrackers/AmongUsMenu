#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

CastVoteEvent::CastVoteEvent(const EVENT_PLAYER& source, const std::optional<EVENT_PLAYER>& target) : EventInterface(source, EVENT_TYPES::EVENT_VOTE) {
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
	ImGui::Text("[%s ago]", std::format("{:%OM:%OS}", (std::chrono::system_clock::now() - this->timestamp)).c_str());
}

void CastVoteEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.3f, 0.4f, 1.f, 1.f), "VOTE");
	ImGui::SameLine();
	ImGui::Text("]");
}