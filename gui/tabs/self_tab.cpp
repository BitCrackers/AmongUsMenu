#include "pch-il2cpp.h"
#include "self_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "utility.h"
#include "state.hpp"
#include "logger.h"

extern void RevealAnonymousVotes(); // in MeetingHud.cpp

namespace SelfTab {
    void Render() {
        if (ImGui::BeginTabItem("Self")) {
            ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
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

            ImGui::SameLine(145.0f * State.dpiScale);
            SteppedSliderFloat("  ", &State.FreeCamSpeed, 0.5f, 3.f, 0.25f, "%.2fx Speed", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

            ImGui::Checkbox("Zoom", &State.EnableZoom);
            ImGui::SameLine();
            HotKey(State.KeyBinds.Toggle_Zoom);

            ImGui::SameLine(145.0f * State.dpiScale);
            SteppedSliderFloat("   ", &State.CameraHeight, 1.0f, 20.0f, 1.0f, "%.2fx Zoom", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

            ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
            ImGui::Separator();
            ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

            if (ImGui::Checkbox("Always show Chat Button", &State.ChatAlwaysActive)) {
                State.Save();
            }
            ImGui::SameLine();
            if (ImGui::Checkbox("Allow Paste in Chat", &State.ChatPaste)) {
                State.Save();
            }
            if (ImGui::Checkbox("Read Messages by Ghosts", &State.ReadGhostMessages)) {
                State.Save();
            }

            ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
            ImGui::Separator();
            ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

            if (ImGui::Checkbox("Reveal Roles", &State.RevealRoles)) {
                State.Save();
            }
            ImGui::SameLine(120.0f * State.dpiScale);
            if (ImGui::Checkbox("Abbrv. Role", &State.AbbreviatedRoleNames))
            {
                State.Save();
            }
            if (ImGui::Checkbox("Reveal Votes", &State.RevealVotes)) {
                State.Save();
            }
            if (!IsInGame() && !IsInLobby() 
                || GameOptions().GetGameMode() != GameModes__Enum::Normal
                || GameOptions().GetBool(app::BoolOptionNames__Enum::AnonymousVotes)) {
                ImGui::SameLine(120.0f * State.dpiScale);
                if (ImGui::Checkbox("Reveal Anonymous Votes", &State.RevealAnonymousVotes)) {
                    State.Save();
                    RevealAnonymousVotes();
                }
            }

            if (ImGui::Checkbox("See Ghosts", &State.ShowGhosts)) {
                State.Save();
            }
            ImGui::SameLine(120.0f * State.dpiScale);
            if (ImGui::Checkbox("See Protections", &State.ShowProtections))
            {
                State.Save();
            }
            ImGui::SameLine(260.0f * State.dpiScale);
            if (ImGui::Checkbox("See Kill Cooldown", &State.ShowKillCD)) {
                State.Save();
            }

            if (ImGui::Checkbox("Unlock Vents", &State.UnlockVents)) {
                State.Save();
            }
            ImGui::SameLine(120.0f * State.dpiScale);
            if (ImGui::Checkbox("Move While in Vent", &State.MoveInVent) && IsInGame()) {
                if (!State.MoveInVent && (State.InMeeting || (*Game::pLocalPlayer)->fields.inVent)) {
                    (*Game::pLocalPlayer)->fields.moveable = false;
                }
            }

            if (ImGui::Checkbox("No Clip", &State.NoClip)) {
                if (State.LobbyTimer == 0 || !IsInLobby()) {
                    if (!IsInGame() && !IsInLobby()) State.NoClip = false;
                    else {
                        if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
                            if (State.NoClip)
                                app::GameObject_set_layer(app::Component_get_gameObject((Component_1*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
                            else
                                app::GameObject_set_layer(app::Component_get_gameObject((Component_1*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
                        }
                    }
                } else State.NoClip = false;
            }
            ImGui::SameLine();
            HotKey(State.KeyBinds.Toggle_Noclip);

            if (ImGui::Checkbox("Right-click Teleport", &State.RightClickTeleport)) {
                State.Save();
            }

            ImGui::EndTabItem();
        }
    }
}