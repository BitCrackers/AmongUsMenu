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

    if (((IsInGame() && IsInMultiplayerGame()) || IsInLobby()) && State.AntiBan) {
        PlayerControl_SetColor(*Game::pLocalPlayer, 0, NULL);
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

    if (((IsInGame() && IsInMultiplayerGame()) || IsInLobby()) && State.AntiBan) {
        PlayerControl_SetColor(*Game::pLocalPlayer, 0, NULL);
    }

    InnerNetClient_Update(__this, method);
}