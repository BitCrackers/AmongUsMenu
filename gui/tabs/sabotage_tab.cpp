#include "pch-il2cpp.h"
#include "sabotage_tab.h"
#include "utility.h"
#include "gui-helpers.hpp"
#include "_rpc.h"
#include "game.h"
#include "state.hpp"

namespace SabotageTab {
    void Render() {
        if (IsInGame()) {
            if (ImGui::BeginTabItem("Sabotage")) {
                ImGui::Dummy(ImVec2(4, 4));
                if (ImGui::Button("Repair Sabotage")) {
                    RepairSabotage(*Game::pLocalPlayer);
                }
                ImGui::SameLine();
                if (HotKey(State.KeyBinds.Repair_Sabotage)) {
                    State.Save();
                }
                ImGui::NewLine();
                if (ImGui::Button("Sabotage Lights")) {
                    State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Electrical));
                }
				ImGui::SameLine();
                if (HotKey(State.KeyBinds.Sabotage_Light)) {
                    State.Save();
                }
                if (State.mapType == Settings::MapType::Ship || State.mapType == Settings::MapType::Hq) {
                    if (ImGui::Button("Sabotage Reactor")) {
                        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Reactor));
                    }
                } else if (State.mapType == Settings::MapType::Pb) {
                    if (ImGui::Button("Sabotage Seismic")) {
                        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Laboratory));
                    }
                } else if (State.mapType == Settings::MapType::Airship) {
                    if (ImGui::Button("Sabotage Heli")) {
                        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Reactor));
                    }
                }
                if (State.mapType == Settings::MapType::Ship || State.mapType == Settings::MapType::Hq) {
                    if (ImGui::Button("Sabotage Oxygen")) {
                        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_LifeSupp));
                    }
                }
                if (ImGui::Button("Sabotage Comms")) {
                    State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Sabotage, SystemTypes__Enum_Comms));
                }

                ImGui::Dummy(ImVec2(7, 7));
                ImGui::Separator();
                ImGui::Dummy(ImVec2(7, 7));

                if (ImGui::Checkbox("Disable Lights", &State.DisableLights)) {
                    if (State.DisableLights) {
                        SwitchSystem* switchSystem = nullptr;
                        std::vector<std::pair<SystemTypes__Enum, ISystemType*>> systems = GetEntriesFromDictionary<Dictionary_2_SystemTypes_ISystemType_*, SystemTypes__Enum, ISystemType*>((*Game::pShipStatus)->fields.Systems);

                        for (auto system : systems) {
                            if (system.first == SystemTypes__Enum_Electrical) {
                                switchSystem = (SwitchSystem*)system.second;
                            }
                        }

                        if (switchSystem != nullptr) {
                            auto actualSwitches = switchSystem->fields.ActualSwitches;
                            auto expectedSwitches = switchSystem->fields.ExpectedSwitches;

                            auto switchMask = 1 << (0 & 0x1F);

                            if ((actualSwitches & switchMask) != (~expectedSwitches & switchMask))
                                State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Electrical, 5));
                        }
                    } else {
                        SwitchSystem* switchSystem = nullptr;
                        std::vector<std::pair<SystemTypes__Enum, ISystemType*>> systems = GetEntriesFromDictionary<Dictionary_2_SystemTypes_ISystemType_*, SystemTypes__Enum, ISystemType*>((*Game::pShipStatus)->fields.Systems);

                        for (auto system : systems) {
                            if (system.first == SystemTypes__Enum_Electrical) {
                                switchSystem = (SwitchSystem*)system.second;
                            }
                        }

                        if (switchSystem != nullptr) {
                            auto actualSwitches = switchSystem->fields.ActualSwitches;
                            auto expectedSwitches = switchSystem->fields.ExpectedSwitches;

                            auto switchMask = 1 << (5 & 0x1F);

                            if ((actualSwitches & switchMask) != (expectedSwitches & switchMask))
                                State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Electrical, 5));
                        }
                    }
                }

                ImGui::EndTabItem();
            }
        }
    }
}