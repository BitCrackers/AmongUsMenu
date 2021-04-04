#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"
#include <iostream>

void dInnerNetClient_Update(InnerNetClient* __this, MethodInfo* method)
{
    if (!IsInLobby()) {
        State.LobbyTimer = -1;
    }

    if (IsInLobby() && State.LobbyTimer > 0) {
        State.LobbyTimer--;
    }

    if (!IsInGame() || State.InMeeting) {
        if (State.PlayMedbayScan) {
            State.PlayMedbayScan = false;
            State.rpcQueue.push(new RpcSetScanner(false));
        }
    }

    if ((IsInGame() || IsInLobby()) && State.HotkeyNoClip) {
        if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
            if (State.NoClip)
                app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
            else
                app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
        }
        State.HotkeyNoClip = false;
    }

    if (!IsInGame()) {

        State.FreeCam = false;
        State.InMeeting = false;
        State.EnableZoom = false;
        State.DisableLights = false;
        State.CloseAllDoors = false;
        State.playerToFollow = PlayerSelection();
        State.FollowerCam = nullptr;

        if (!IsInLobby()) {
            State.selectedPlayer = PlayerSelection();
            State.FlipSkeld = false;
            State.NoClip = false;
            State.HotkeyNoClip = false;
            State.originalName = "-";
        }
    } else {
        if (!State.rpcQueue.empty()) {
            auto rpc = State.rpcQueue.front();
            State.rpcQueue.pop();

            rpc->Process();
            delete rpc;
        }

        if (State.CloseAllDoors) {
            for (auto door : State.mapDoors) {
                State.rpcQueue.push(new RpcCloseDoorsOfType(door, false));
            }
            State.CloseAllDoors = false;
        }

        if (State.MoveInVent && (*Game::pLocalPlayer)->fields.inVent) {
            (*Game::pLocalPlayer)->fields.moveable = true;
        }
    }

    if (IsInLobby()) {
        if (State.originalName == "-") {
            State.originalName = convert_from_string(GetPlayerData(*Game::pLocalPlayer)->fields.PlayerName);
        }

        if (!State.lobbyRpcQueue.empty()) {
            auto rpc = State.lobbyRpcQueue.front();
            State.lobbyRpcQueue.pop();

            rpc->Process();
            delete rpc;
        }
    }

    if (convert_from_string(SaveManager__TypeInfo->static_fields->lastPlayerName) != State.userName) {
        SaveManager__TypeInfo->static_fields->lastPlayerName = convert_to_string(State.userName);
        if (IsInGame())
            State.rpcQueue.push(new RpcSetName(State.userName));
        else if (IsInLobby())
            State.lobbyRpcQueue.push(new RpcSetName(State.userName));
    }

    InnerNetClient_Update(__this, method);
}

void dAmongUsClient_OnPlayerLeft(AmongUsClient* __this, ClientData* data, DisconnectReasons__Enum reason, MethodInfo* method) {
    std::cout << data->fields.Character->fields.nameText->fields.Text << " has left the game.\n";

    auto it = std::find(State.aumUsers.begin(), State.aumUsers.end(), data->fields.Character->fields.PlayerId);
    if (it != State.aumUsers.end())
        State.aumUsers.erase(it);

    AmongUsClient_OnPlayerLeft(__this, data, reason, method);
}

bool bogusTransformSnap(PlayerSelection player, Vector2 newPosition)
{
#ifdef _DEBUG
    if (!player.has_value())
        std::cout << __func__ << " received invalid player!" << std::endl;
#endif
    if (!player.has_value()) return false; //Error getting playercontroller
    if (player.is_LocalPlayer()) return false; //We are not going to log ourselves
    if (player.get_PlayerControl()->fields.inVent) return false; //Vent buttons are warps
    if (GameObject_get_layer(app::Component_get_gameObject((Component*)player.get_PlayerControl(), NULL), NULL) == LayerMask_NameToLayer(convert_to_string("Ghost"), NULL))
        return false; //For some reason the playercontroller is not marked dead at this point, so we check what layer the player is on
    auto currentPosition = PlayerControl_GetTruePosition(player.get_PlayerControl(), NULL);
    int32_t distanceToTarget = Vector2_Distance(currentPosition, newPosition, NULL); //rounding off as the smallest kill distance is zero
    auto killDistance = std::clamp((*Game::pGameOptionsData)->fields.KillDistance, 0, 2);
    auto initialSpawnLocation = GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (*Game::pGameData)->fields.AllPlayers->fields._size, true);
    auto meetingSpawnLocation = GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (*Game::pGameData)->fields.AllPlayers->fields._size, false);
    if (Equals(initialSpawnLocation, newPosition)) return false;
    if (Equals(meetingSpawnLocation, newPosition)) return false;  //You are warped to your spawn at meetings and start of games
    if (IsAirshipSpawnLocation(newPosition)) return false;
    if (player.get_PlayerData()->fields.IsImpostor && distanceToTarget <= killDistance) 
        return false;
#ifdef _DEBUG
    std::cout << "From " << +currentPosition.x << "," << +currentPosition.y << " to " << +newPosition.x << "," << +newPosition.y << std::endl;
    std::cout << "Range to target " << +distanceToTarget << ", KillDistance: " << +killDistance << std::endl;
    std::cout << "Initial Spawn Location " << +initialSpawnLocation.x << "," << +initialSpawnLocation.y << std::endl;
    std::cout << "Meeting Spawn Location " << +meetingSpawnLocation.x << "," << +meetingSpawnLocation.y << std::endl;
    std::cout << "-------" << std::endl;
#endif
    return true; //We have ruled out all possible scenarios.  Off with his head!
}

void dCustomNetworkTransform_SnapTo(CustomNetworkTransform* __this, Vector2 position, uint16_t minSid, MethodInfo* method) {
    if (!IsInGame()) {
        CustomNetworkTransform_SnapTo(__this, position, minSid, method);
        return;
    }

    PlayerSelection player;
    for (auto p : GetAllPlayerControl()) {
        if (p->fields.NetTransform == __this) {
            player = PlayerSelection(p);
            break;
        }
    }

    if (bogusTransformSnap(player, position))
    {
        State.events.push_back(new CheatDetectedEvent(GetEventPlayer(player.get_PlayerControl()), CHEAT_TELEPORT));
    }

    CustomNetworkTransform_SnapTo(__this, position, minSid, method);
}

void dInnerNetObject_Despawn(InnerNetObject* __this, MethodInfo* method) {
    if ((*Game::pLobbyBehaviour)) {
        if ((InnerNetObject*)(*Game::pLobbyBehaviour) == __this) {
            State.events.clear();

            State.mapDoors.clear();
            State.pinnedDoors.clear();

            auto allDoors = (*Game::pShipStatus)->fields.AllDoors;

            for (il2cpp_array_size_t i = 0; i < allDoors->max_length; i++) {
                if (std::find(State.mapDoors.begin(), State.mapDoors.end(), allDoors->vector[i]->fields.Room) == State.mapDoors.end())
                    State.mapDoors.push_back(allDoors->vector[i]->fields.Room);
            }

            std::sort(State.mapDoors.begin(), State.mapDoors.end());
            State.selectedDoor = State.mapDoors[0];
        }
    }
    InnerNetObject_Despawn(__this, method);
}

void dInnerNetClient_StartEndGame(InnerNetClient* __this, MethodInfo* method) {
    State.shadowLayer.reset();
    State.spawnInGame.reset();
    State.aumUsers.clear();
    State.events.clear();

    InnerNetClient_StartEndGame(__this, method);
}