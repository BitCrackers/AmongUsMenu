#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"

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

    InnerNetClient_Update(__this, method);
}

void dAmongUsClient_OnPlayerLeft(AmongUsClient* __this, ClientData* data, DisconnectReasons__Enum reason, MethodInfo* method) {
    auto it = std::find(State.aumUsers.begin(), State.aumUsers.end(), data->fields.Character->fields.PlayerId);

    if (it != State.aumUsers.end())
        State.aumUsers.erase(it);
    AmongUsClient_OnPlayerLeft(__this, data, reason, method);
}

bool bogusTransformSnap(PlayerSelection player, Vector2 newPosition)
{
#ifdef _DEBUG
    assert(player.has_value());
#endif
    if (!player.has_value()) return false; //Error getting playercontroller
    if (player.is_LocalPlayer()) return false; //We are not going to log ourselves
    if (player.get_PlayerControl()->fields.inVent) return false; //Vent buttons are warps
    if (player.get_PlayerData()->fields.IsDead) return false; //The dead do as they please
    if (Equals(GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (*Game::pGameData)->fields.AllPlayers->fields._size, true), newPosition) ||
        Equals(GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (*Game::pGameData)->fields.AllPlayers->fields._size, false), newPosition))
        return false;  //You are warped to your spawn at meetings and start of games
    if (player.get_PlayerData()->fields.IsImpostor &&
        Vector2_Distance(PlayerControl_GetTruePosition(player.get_PlayerControl(), NULL), newPosition, NULL) > (*Game::pGameOptionsData)->fields.KillDistance) return false;
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
        }
    }
    InnerNetObject_Despawn(__this, method);
}