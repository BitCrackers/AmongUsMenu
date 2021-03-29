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

void dCustomNetworkTransform_SnapTo(CustomNetworkTransform* __this, Vector2 position, uint16_t minSid, MethodInfo* method) {
    if (!IsInGame()) {
        CustomNetworkTransform_SnapTo(__this, position, minSid, method);
        return;
    }

    PlayerControl* player = nullptr;
    for (auto p : GetAllPlayerControl()) {
        if (p->fields.NetTransform == __this) {
            player = p;
            break;
        }
    }

    if (!player->fields.inVent && 
        player != *Game::pLocalPlayer &&
        !(GameObject_get_layer(app::Component_get_gameObject((Component*)player, NULL), NULL) == LayerMask_NameToLayer(convert_to_string("Ghost"), NULL)) &&
        !(GetPlayerData(player)->fields.IsImpostor && player->fields.killTimer == (*Game::pGameOptionsData)->fields.KillCooldown) &&
        !Equals(GetSpawnLocation(player->fields.PlayerId, (*Game::pGameData)->fields.AllPlayers->fields._size, true), position) &&
        !Equals(GetSpawnLocation(player->fields.PlayerId, (*Game::pGameData)->fields.AllPlayers->fields._size, false), position)
        ) {
        State.events.push_back(new CheatDetectedEvent(GetEventPlayer(player), CHEAT_TELEPORT));
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