#include "pch-il2cpp.h"
#include "self_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "utility.h"
#include "state.hpp"

namespace SelfTab {
    void Render() {
        if (ImGui::BeginTabItem("Self")) {
            ImGui::Dummy(ImVec2(4, 4));
            if (ImGui::Checkbox("Max Vision", &State.MaxVision)) {
                State.Save();
            }
            if (ImGui::Checkbox("Wallhack", &State.Wallhack)) {
                State.Save();
            }

            if (ImGui::Checkbox("Freecam", &State.FreeCam)) {
                if (IsInGame()) {
                    State.playerToFollow = PlayerSelection();
                }
            }
            ImGui::SameLine();
            if (HotKey(State.KeyBinds.Toggle_Freecam)) {
                State.Save();
            }

            ImGui::SameLine(145.0f);
            SteppedSliderFloat("  ", &State.FreeCamSpeed, 0.5f, 3.f, 0.25f, "%.2fx Speed", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

            ImGui::Checkbox("Zoom", &State.EnableZoom);
            ImGui::SameLine();
            HotKey(State.KeyBinds.Toggle_Zoom);

            ImGui::SameLine(145.0f);
            SteppedSliderFloat("   ", &State.CameraHeight, 1.0f, 20.0f, 1.0f, "%.2fx Zoom", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

            ImGui::Dummy(ImVec2(7, 7));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(7, 7));

            if (ImGui::Checkbox("Always show Chat Button", &State.ChatAlwaysActive)) {
                State.Save();
            }
            if (ImGui::Checkbox("Read Messages by Ghosts", &State.ReadGhostMessages)) {
                State.Save();
            }

            ImGui::Dummy(ImVec2(7, 7));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(7, 7));

            if (ImGui::Checkbox("Reveal Impostors", &State.RevealImpostors)) {
                State.Save();
            }
            if (ImGui::Checkbox("See Ghosts", &State.ShowGhosts)) {
                State.Save();
            }
            if (ImGui::Checkbox("Unlock Vents", &State.UnlockVents)) {
                State.Save();
            }

            if (ImGui::Checkbox("No Clip", &State.NoClip)) {
                if (State.LobbyTimer == 0 || !IsInLobby()) {
                    if (!IsInGame() && !IsInLobby()) State.NoClip = false;
                    else {
                        if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
                            if (State.NoClip)
                                app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
                            else
                                app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
                        }
                    }
                } else State.NoClip = false;
            }
            ImGui::SameLine();
            HotKey(State.KeyBinds.Toggle_Noclip);

            if (IsInGame() && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)
            {
                if (ImGui::Checkbox("Move While in Vent", &State.MoveInVent)) {
                    if (!State.MoveInVent && (State.InMeeting || (*Game::pLocalPlayer)->fields.inVent)) {
                        (*Game::pLocalPlayer)->fields.moveable = false;
                    }
                }
                if (State.MoveInVent)
                {
                    ImGui::SameLine(160.0f);
                    if (ImGui::Button("Enter Closest Vent"))
                    {
                        State.rpcQueue.push(new RpcEnterVent(GetClosestVent()->fields.Id));
                        
                    }
                    ImGui::SameLine(300.0f);
                    if (ImGui::Button("Exit Vents"))
                    {
                        State.rpcQueue.push(new RpcExitVent(GetClosestVent()->fields.Id));
                    }
                }
            }

            ImGui::EndTabItem();
        }
    }
}