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
                ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
                if (ImGui::Button("Repair Sabotage")) {
                    RepairSabotage(*Game::pLocalPlayer);
                }
                ImGui::SameLine();
                if (HotKey(State.KeyBinds.Repair_Sabotage)) {
                    State.Save();
                }
                ImGui::NewLine();
                if (ImGui::Button("Sabotage Lights")) {
                    State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Sabotage, SystemTypes__Enum::Electrical));
                }
                if (State.mapType == Settings::MapType::Ship || State.mapType == Settings::MapType::Hq) {
                    if (ImGui::Button("Sabotage Reactor")) {
                        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Sabotage, SystemTypes__Enum::Reactor));
                    }
                } else if (State.mapType == Settings::MapType::Pb) {
                    if (ImGui::Button("Sabotage Seismic")) {
                        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Sabotage, SystemTypes__Enum::Laboratory));
                    }
                } else if (State.mapType == Settings::MapType::Airship) {
                    if (ImGui::Button("Sabotage Heli")) {
                        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Sabotage, SystemTypes__Enum::Reactor));
                    }
                }
                if (State.mapType == Settings::MapType::Ship || State.mapType == Settings::MapType::Hq) {
                    if (ImGui::Button("Sabotage Oxygen")) {
                        State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Sabotage, SystemTypes__Enum::LifeSupp));
                    }
                }
                if (ImGui::Button("Sabotage Comms")) {
                    State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Sabotage, SystemTypes__Enum::Comms));
                }

                ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
                ImGui::Separator();
                ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

                if (ImGui::Checkbox("Disable Lights", &State.DisableLights)) {
                    if (auto switchSystem = (SwitchSystem*)il2cpp::Dictionary((*Game::pShipStatus)->fields.Systems)[SystemTypes__Enum::Electrical]) {
                        auto actualSwitches = switchSystem->fields.ActualSwitches;
                        auto expectedSwitches = switchSystem->fields.ExpectedSwitches;

                        auto switchMask = 1 << ((State.DisableLights ? 0 : 5) & 0x1F);

                        if ((actualSwitches & switchMask) != ((State.DisableLights ? ~expectedSwitches : expectedSwitches) & switchMask))
                            State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Electrical, 5));
                    }
                }

                ImGui::EndTabItem();
            }
        }
    }
}