#include "pch-il2cpp.h"
#include "doors_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"

namespace DoorsTab {
	void Render() {
		if (IsInGame() && !State.mapDoors.empty()) {
			if (ImGui::BeginTabItem("Doors")) {
				ImGui::BeginChild("doors#list", ImVec2(200, 0) * State.dpiScale, true);
				bool shouldEndListBox = ImGui::ListBoxHeader("###doors#list", ImVec2(200, 150) * State.dpiScale);
				for (size_t i = 0; i < State.mapDoors.size(); i++) {
					auto systemType = State.mapDoors[i];
					if (systemType == SystemTypes__Enum::Decontamination || systemType == SystemTypes__Enum::Decontamination2) continue;
					auto plainDoor = GetPlainDoorByRoom(systemType);
					if (!(std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), systemType) == State.pinnedDoors.end()))
					{
						ImGui::PushStyleColor(ImGuiCol_Text, { 0.9f, 0.1f, 0.25f, 1.f });
						if (ImGui::Selectable(TranslateSystemTypes(systemType), State.selectedDoor == systemType))
							State.selectedDoor = systemType;
						ImGui::PopStyleColor(1);
					}
					else if (!plainDoor->fields.Open)
					{
						ImGui::PushStyleColor(ImGuiCol_Text, { 0.85f, 0.2f, 0.5f, 1.f });
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
				if (shouldEndListBox) 
					ImGui::ListBoxFooter();
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("doors#options", ImVec2(200, 0) * State.dpiScale);

				if (ImGui::Button("Close All Doors"))
				{
					for(auto door : State.mapDoors)
					{
						State.rpcQueue.push(new RpcCloseDoorsOfType(door, false));
					}
				}
				ImGui::SameLine();
				if (HotKey(State.KeyBinds.Close_All_Doors)) {
					State.Save();
				}

				if (ImGui::Button("Close Room Door"))
				{
					State.rpcQueue.push(new RpcCloseDoorsOfType(GetSystemTypes(GetTrueAdjustedPosition(*Game::pLocalPlayer)), false));
				}
				ImGui::SameLine();
				if (HotKey(State.KeyBinds.Close_Current_Room_Door)) {
					State.Save();
				}

				if (ImGui::Button("Pin All Doors"))
				{
					for (auto door : State.mapDoors)
					{
						if (std::find(State.pinnedDoors.begin(), State.pinnedDoors.end(), door) == State.pinnedDoors.end())
						{
							if(door != SystemTypes__Enum::Decontamination && door != SystemTypes__Enum::Decontamination2)
								State.rpcQueue.push(new RpcCloseDoorsOfType(door, true));
						}
					}
				}
				if (ImGui::Button("Unpin All Doors"))
				{
					State.pinnedDoors.clear();
				}
				ImGui::NewLine();
				if (State.selectedDoor != SystemTypes__Enum::Hallway) {
					auto plainDoor = GetPlainDoorByRoom(State.selectedDoor);

					if (ImGui::Button("Close Door")) {
						State.rpcQueue.push(new RpcCloseDoorsOfType(State.selectedDoor, false));
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
				if (State.mapType == Settings::MapType::Pb || State.mapType == Settings::MapType::Airship)
				{
					ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
					if (ImGui::Checkbox("Auto Open Doors", &State.AutoOpenDoors)) {
						State.Save();
					}
				}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
}