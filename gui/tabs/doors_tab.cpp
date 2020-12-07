#include "doors_tab.h"

namespace DoorsTab {
	void Render() {
		if (IsInGame() && !State.mapDoors.empty()) {
			if (ImGui::BeginTabItem("Doors")) {
				ImGui::BeginChild("doors#list", ImVec2(200, 0), true);
				ImGui::ListBoxHeader("", ImVec2(200, 150));
				for (size_t i = 0; i < State.mapDoors.size(); i++) {
					auto systemType = State.mapDoors[i];
					auto plainDoor = GetPlainDoorByRoom(systemType);
					if (!(std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), systemType) == State.pinnedDoors.end()))
					{
						ImGui::PushStyleColor(ImGuiCol_Text, *(new ImVec4(0.9f, 0.1f, 0.25f, 1.f)));
						if (ImGui::Selectable(TranslateSystemTypes(systemType), State.selectedDoor == systemType))
							State.selectedDoor = systemType;
						ImGui::PopStyleColor(1);
					}
					else if (!plainDoor->fields.Open)
					{
						ImGui::PushStyleColor(ImGuiCol_Text, *(new ImVec4(0.85f, 0.2f, 0.5f, 1.f)));
						if (ImGui::Selectable(TranslateSystemTypes(systemType), State.selectedDoor == systemType))
							State.selectedDoor = systemType;
						ImGui::PopStyleColor(1);
					}
					else
					{
						if (ImGui::Selectable(TranslateSystemTypes(systemType), State.selectedDoor == systemType))
							State.selectedDoor = systemType;
					}
				}
				ImGui::ListBoxFooter();
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("doors#options", ImVec2(200, 0));
				if (ImGui::Button("Close All Doors"))
				{
					for(auto door : State.mapDoors)
					{
						State.rpcQueue.push(new RpcCloseDoorsOfType(door, false));
					}
				}
				if (ImGui::Button("Open All Doors"))
				{
					for (auto door : GetAllPlainDoors())
					{
						PlainDoor_SetDoorway(door, true, NULL);
					}
				}
				if (ImGui::Button("Pin All Doors"))
				{
					for (auto door : State.mapDoors)
					{
						if (std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), door) == State.pinnedDoors.end())
						{
							State.rpcQueue.push(new RpcCloseDoorsOfType(door, true));
						}
					}
				}
				if (ImGui::Button("Unpin All Doors"))
				{
					State.pinnedDoors.clear();
				}
				ImGui::NewLine();
				if (State.selectedDoor != SystemTypes__Enum_Hallway) {

					if (State.selectedDoor != SystemTypes__Enum_Decontamination && State.selectedDoor != SystemTypes__Enum_Decontamination2) {
						if (GetPlainDoorByRoom(State.selectedDoor)->fields.Open) {
							if (ImGui::Button("Close Door")) {
								State.rpcQueue.push(new RpcCloseDoorsOfType(State.selectedDoor, false));
							}
						}
						else {
							if (ImGui::Button("Open Door")) {
								PlainDoor_SetDoorway(GetPlainDoorByRoom(State.selectedDoor), true, NULL);
							}
						}
					}

					if (std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), State.selectedDoor) == State.pinnedDoors.end()) {
						if (ImGui::Button("Pin Door")) {
							State.rpcQueue.push(new RpcCloseDoorsOfType(State.selectedDoor, true));
						}
					}
					else {
						if (ImGui::Button("Unpin Door")) {
							State.pinnedDoors.erase(std::remove(State.pinnedDoors.begin(), State.pinnedDoors.end(), State.selectedDoor), State.pinnedDoors.end());
						}
					}
				}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
}