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
            ImGui::SameLine();
            if (ImGui::Checkbox("Wallhack", &State.Wallhack)) {
                State.Save();
            }
            ImGui::SameLine();
            ImGui::Checkbox("Disable HUD", &State.DisableHud);
            if (State.ShowKeybinds) {
                ImGui::SameLine();
                HotKey(State.KeyBinds.Toggle_Hud);
            }

            if (ImGui::Checkbox("Freecam", &State.FreeCam)) {
                if (IsInGame()) {
                    State.playerToFollow = PlayerSelection();
                }
            }
            if (State.ShowKeybinds) {
                ImGui::SameLine();
                if (HotKey(State.KeyBinds.Toggle_Freecam)) {
                    State.Save();
                }
            }

            ImGui::SameLine(145.0f * State.dpiScale);
            SteppedSliderFloat("  ", &State.FreeCamSpeed, 0.f, 10.f, 0.05f, "%.2fx Speed", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

            ImGui::Checkbox("Zoom", &State.EnableZoom);
            if (State.ShowKeybinds) {
                ImGui::SameLine();
                HotKey(State.KeyBinds.Toggle_Zoom);
            }

            ImGui::SameLine(145.0f * State.dpiScale);
            SteppedSliderFloat("   ", &State.CameraHeight, 0.5f, 10.0f, 0.1f, "%.2fx Zoom", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_NoInput);

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
            ImGui::SameLine();
            if (ImGui::Checkbox("Read Messages by Ghosts", &State.ReadGhostMessages)) {
                State.Save();
            }
            /*static int framesPassed = 0;
            if (ImGui::Button("Refresh Chat Button")) {
                State.RefreshChatButton = true;
                framesPassed = 100;
            }

            if (framesPassed == 0) State.RefreshChatButton = false;
            else framesPassed--;*/

            if (IsHost() || !State.SafeMode) {
                if (ImGui::Checkbox("Custom Name", &State.CustomName)) {
                    State.Save();
                }
            }
            else {
                if (ImGui::Checkbox("Custom Name (Client-sided ONLY)", &State.CustomName)) {
                    State.Save();
                }
            }

            if ((IsHost() || !State.SafeMode))
                ImGui::SameLine();

            if ((IsHost() || !State.SafeMode) && State.CustomName && ImGui::Checkbox("Server-sided", &State.ServerSideCustomName)) {
                State.Save();
            }

            if (State.CustomName && ImGui::CollapsingHeader("Custom Name Options"))
            {
                if (ImGui::Checkbox("Size", &State.ResizeName)) {
                    State.Save();
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("Italics", &State.ItalicName)) {
                    State.Save();
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("Underline", &State.UnderlineName)) {
                    State.Save();
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("Strikethrough", &State.StrikethroughName)) {
                    State.Save();
                }

                if (ImGui::ColorEdit4("Starting Gradient Color", (float*)&State.NameColor1, ImGuiColorEditFlags__OptionsDefault | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview)) {
                    State.Save();
                }
                ImGui::SameLine();
                if (ImGui::ColorEdit4("Ending Gradient Color", (float*)&State.NameColor2, ImGuiColorEditFlags__OptionsDefault | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview)) {
                    State.Save();
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("Colored", &State.ColoredName)) {
                    State.Save();
                }
                
                if (ImGui::Checkbox("RGB", &State.RgbName)) {
                    State.Save();
                }
                ImGui::SameLine();
                if (ImGui::InputFloat("Name Size", &State.NameSize)) {
                    State.Save();
                }
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
            ImGui::SameLine(240.0f * State.dpiScale);
            if (ImGui::Checkbox("Player Colored Dots Next To Names", &State.PlayerColoredDots))
            {
                State.Save();
            }
            if (ImGui::Checkbox("Show Player Info in Lobby", &State.ShowPlayerInfo))
            {
                State.Save();
            }
            if (IsHost() || !State.SafeMode) {
                ImGui::SameLine();
                if (ImGui::Checkbox("God Mode", &State.GodMode))
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
            if (ImGui::Checkbox("Move While in Vent & Shapeshifting", &State.MoveInVent)) {
                if (!State.MoveInVent && (State.InMeeting || (*Game::pLocalPlayer)->fields.inVent)) {
                    (*Game::pLocalPlayer)->fields.moveable = false;
                }
            }
            ImGui::SameLine();
            if (ImGui::Checkbox("Always Move", &State.AlwaysMove)) {
                State.Save();
            }

            if (ImGui::Checkbox("Shapeshift without Animation", &State.AnimationlessShapeshift)) {
                State.Save();
            }
            ImGui::SameLine();
            if (ImGui::Checkbox("Disable Kill Animation", &State.DisableKillAnimation)) {
                State.Save();
            }

            if (ImGui::Checkbox("NoClip", &State.NoClip)) {
                State.Save();
            }
            if (State.ShowKeybinds) {
                ImGui::SameLine();
                HotKey(State.KeyBinds.Toggle_Noclip);
            }

            if (ImGui::Checkbox("Kill Other Impostors", &State.KillImpostors)) {
                State.Save();
            }
            ImGui::SameLine();
            if (ImGui::Checkbox("Kill/Protect Through Walls", &State.KillThroughWalls)) {
                State.Save();
            }

            ImGui::SameLine();
            if (ImGui::Checkbox("Infinite Kill/Protect Range", &State.InfiniteKillRange)) {
                State.Save();
            }

            if (ImGui::Checkbox("Do Tasks as Impostor", &State.DoTasksAsImpostor)) {
                State.Save();
            }
            ImGui::SameLine();
            if (ImGui::Checkbox("Fake Alive", &State.FakeAlive)) {
                State.Save();
            }
            ImGui::SameLine();
            if (ImGui::Checkbox("Show Host", &State.ShowHost)) {
                State.Save();
            }
            ImGui::SameLine();
            if (ImGui::Checkbox("Show Vote Kicks", &State.ShowVoteKicks)) {
                State.Save();
            }

            if (ImGui::Checkbox("(Shift + Right Click) to Teleport", &State.ShiftRightClickTP)) {
                State.Save();
            }
            ImGui::SameLine();
            if (!State.SafeMode && ImGui::Checkbox("Hold ALT to Teleport Everyone", &State.TeleportEveryone)) {
                State.Save();
            }
            if (ImGui::Checkbox("Rotate Everyone", &State.RotateEveryone)) {
                State.Save();
            }
            ImGui::SameLine();
            if (!State.SafeMode && State.RotateEveryone && ImGui::Checkbox("Server-sided", &State.RotateServerSide)) {
                State.Save();
            }
            if (ImGui::InputFloat("Radius", &State.RotateRadius, 0.0f, 0.0f, "%.2f m")) {
                State.Save();
            }

            if (ImGui::InputFloat("X Coordinate", &State.xCoordinate, 0.0f, 0.0f, "%.4f X")) {
                State.Save();
            }

            if (ImGui::InputFloat("Y Coordinate", &State.yCoordinate, 0.0f, 0.0f, "%.4f Y")) {
                State.Save();
            }

            if ((IsInGame() || IsInLobby()) && ImGui::Button("Get Current Position"))
            {
                Vector2 position = GetTrueAdjustedPosition(*Game::pLocalPlayer);
                State.xCoordinate = position.x;
                State.yCoordinate = position.y;
            }
            if (IsInGame() || IsInLobby())
                ImGui::SameLine();

            if (ImGui::Button("Teleport To"))
            {
                Vector2 target = {State.xCoordinate, State.yCoordinate};
                if (IsInGame()) {
                    State.rpcQueue.push(new RpcSnapTo(target));
                }
                else if (IsInLobby()) {
                    State.lobbyRpcQueue.push(new RpcSnapTo(target));
                }
            }
            if (!State.SafeMode && (IsInGame() || IsInLobby())) {
                ImGui::SameLine();
                if (ImGui::Button("Teleport Everyone To"))
                {
                    Vector2 target = { State.xCoordinate, State.yCoordinate };
                    std::queue<RPCInterface*>* queue = nullptr;
                    if (IsInGame())
                        queue = &State.rpcQueue;
                    else if (IsInLobby())
                        queue = &State.lobbyRpcQueue;
                    for (auto player : GetAllPlayerControl()) {
                        queue->push(new RpcForceSnapTo(player, target));
                    }
                }
            }

            if (State.InMeeting && ImGui::Button("Move in Meeting"))
            {
                State.rpcQueue.push(new EndMeeting());
                State.InMeeting = false;
            }

            if (CustomListBoxInt("Select Role", &State.FakeRole, FAKEROLES, 100.0f * State.dpiScale))
                State.Save();
            ImGui::SameLine();
            if ((IsHost() || !State.SafeMode) && (IsInGame() || IsInLobby()) && ImGui::Button("Set Role")) {
                auto fakeRole = RoleTypes__Enum::Crewmate;
                if (State.FakeRole == 0)
                    fakeRole = RoleTypes__Enum::Crewmate;
                else if (State.FakeRole == 1)
                    fakeRole = RoleTypes__Enum::Scientist;
                else if (State.FakeRole == 2)
                    fakeRole = RoleTypes__Enum::Engineer;
                else if (State.FakeRole == 3)
                    fakeRole = RoleTypes__Enum::Impostor;
                else if (State.FakeRole == 4)
                    fakeRole = RoleTypes__Enum::Shapeshifter;
                else if (State.FakeRole == 5)
                    fakeRole = RoleTypes__Enum::CrewmateGhost;
                else if (State.FakeRole == 6)
                    fakeRole = RoleTypes__Enum::GuardianAngel;
                else if (State.FakeRole == 7)
                    fakeRole = RoleTypes__Enum::ImpostorGhost;
                if (IsInGame())
                    State.rpcQueue.push(new RpcSetRole(*Game::pLocalPlayer, fakeRole));
                else if (IsInLobby())
                    State.lobbyRpcQueue.push(new RpcSetRole(*Game::pLocalPlayer, fakeRole));                    
            }
            ImGui::SameLine();
            if (!State.SafeMode && (IsInGame() || IsInLobby()) && ImGui::Button("Set for Everyone")) {
                auto fakeRole = RoleTypes__Enum::Crewmate;
                if (State.FakeRole == 0)
                    fakeRole = RoleTypes__Enum::Crewmate;
                else if (State.FakeRole == 1)
                    fakeRole = RoleTypes__Enum::Scientist;
                else if (State.FakeRole == 2)
                    fakeRole = RoleTypes__Enum::Engineer;
                else if (State.FakeRole == 3)
                    fakeRole = RoleTypes__Enum::Impostor;
                else if (State.FakeRole == 4)
                    fakeRole = RoleTypes__Enum::Shapeshifter;
                else if (State.FakeRole == 5)
                    fakeRole = RoleTypes__Enum::CrewmateGhost;
                else if (State.FakeRole == 6)
                    fakeRole = RoleTypes__Enum::GuardianAngel;
                else if (State.FakeRole == 7)
                    fakeRole = RoleTypes__Enum::ImpostorGhost;
                if (IsInGame()) {
                    for (auto player : GetAllPlayerControl())
                        State.rpcQueue.push(new RpcSetRole(player, fakeRole));
                }
                else if (IsInLobby()) {
                    for (auto player : GetAllPlayerControl())
                        State.lobbyRpcQueue.push(new RpcSetRole(player, fakeRole));
                }
            }
            if ((IsInGame() || IsInLobby()) && ImGui::Button("Set Fake Role")) {
                auto localData = GetPlayerData(*Game::pLocalPlayer);
                if (State.FakeRole == 0) {
                    localData->fields.RoleType = RoleTypes__Enum::Crewmate;
                    localData->fields.Role->fields.TeamType = RoleTeamTypes__Enum::Crewmate;
                    localData->fields.Role->fields.Role = RoleTypes__Enum::Crewmate;
                    localData->fields.Role->fields.CanUseKillButton = false;
                }
                else if (State.FakeRole == 1) {
                    localData->fields.RoleType = RoleTypes__Enum::Scientist;
                    localData->fields.Role->fields.TeamType = RoleTeamTypes__Enum::Crewmate;
                    localData->fields.Role->fields.Role = RoleTypes__Enum::Scientist;
                    localData->fields.Role->fields.CanUseKillButton = false;
                }
                else if (State.FakeRole == 2) {
                    localData->fields.RoleType = RoleTypes__Enum::Engineer;
                    localData->fields.Role->fields.TeamType = RoleTeamTypes__Enum::Crewmate;
                    localData->fields.Role->fields.Role = RoleTypes__Enum::Engineer;
                    localData->fields.Role->fields.CanUseKillButton = false;
                }
                else if (State.FakeRole == 3) {
                    localData->fields.RoleType = RoleTypes__Enum::Impostor;
                    localData->fields.Role->fields.TeamType = RoleTeamTypes__Enum::Impostor;
                    localData->fields.Role->fields.Role = RoleTypes__Enum::Impostor;
                    localData->fields.Role->fields.CanUseKillButton = true;
                }
                else if (State.FakeRole == 4) {
                    localData->fields.RoleType = RoleTypes__Enum::Shapeshifter;
                    localData->fields.Role->fields.TeamType = RoleTeamTypes__Enum::Impostor;
                    localData->fields.Role->fields.Role = RoleTypes__Enum::Shapeshifter;
                    localData->fields.Role->fields.CanUseKillButton = true;
                }
                else if (State.FakeRole == 5) {
                    localData->fields.RoleType = RoleTypes__Enum::CrewmateGhost;
                    localData->fields.Role->fields.TeamType = RoleTeamTypes__Enum::Crewmate;
                    localData->fields.Role->fields.Role = RoleTypes__Enum::CrewmateGhost;
                    localData->fields.Role->fields.TasksCountTowardProgress = (GameOptions().GetGameMode() != GameModes__Enum::HideNSeek);
                    localData->fields.Role->fields.CanUseKillButton = false;
                }
                else if (State.FakeRole == 6) {
                    localData->fields.RoleType = RoleTypes__Enum::CrewmateGhost;
                    localData->fields.Role->fields.TeamType = RoleTeamTypes__Enum::Crewmate;
                    localData->fields.Role->fields.Role = RoleTypes__Enum::CrewmateGhost;
                    localData->fields.Role->fields.TasksCountTowardProgress = (GameOptions().GetGameMode() != GameModes__Enum::HideNSeek);
                    localData->fields.Role->fields.CanUseKillButton = false;
                }
                else if (State.FakeRole == 7) {
                    localData->fields.RoleType = RoleTypes__Enum::ImpostorGhost;
                    localData->fields.Role->fields.TeamType = RoleTeamTypes__Enum::Impostor;
                    localData->fields.Role->fields.Role = RoleTypes__Enum::ImpostorGhost;
                    localData->fields.Role->fields.CanUseKillButton = true;
                }
                auto fakeRole = RoleTypes__Enum::Crewmate;
                if (State.FakeRole == 0)
                    fakeRole = RoleTypes__Enum::Crewmate;
                else if (State.FakeRole == 1)
                    fakeRole = RoleTypes__Enum::Scientist;
                else if (State.FakeRole == 2)
                    fakeRole = RoleTypes__Enum::Engineer;
                else if (State.FakeRole == 3)
                    fakeRole = RoleTypes__Enum::Impostor;
                else if (State.FakeRole == 4)
                    fakeRole = RoleTypes__Enum::Shapeshifter;
                else if (State.FakeRole == 5)
                    fakeRole = RoleTypes__Enum::CrewmateGhost;
                else if (State.FakeRole == 6)
                    fakeRole = RoleTypes__Enum::GuardianAngel;
                else if (State.FakeRole == 7)
                    fakeRole = RoleTypes__Enum::ImpostorGhost;
                if (IsInGame())
                    State.rpcQueue.push(new SetRole(fakeRole));
                else if (IsInLobby())
                    State.lobbyRpcQueue.push(new SetRole(fakeRole));
            }

            ImGui::EndTabItem();
        }
    }
}