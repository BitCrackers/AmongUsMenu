#include "il2cpp-appdata.h"
#include "_events.h"
#include "utility.h"

TaskCompletedEvent::TaskCompletedEvent(EVENT_PLAYER source, std::optional<TaskTypes__Enum> taskType, Vector2 position) : EventInterface(source, EVENT_TASK) {
	this->taskType = taskType;
	this->position = position;
	this->systemType = GetSystemTypes(position);
}

void TaskCompletedEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text("> %s (%s)", (taskType.has_value()) ? TranslateTaskTypes(*taskType) : "UNKOWN" , TranslateSystemTypes(systemType));
}

void TaskCompletedEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "TASK");
	ImGui::SameLine();
	ImGui::Text("]");
}