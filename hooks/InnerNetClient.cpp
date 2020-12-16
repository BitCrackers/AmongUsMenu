#include "_hooks.hpp"

using namespace app;

void dInnerNetClient_Update(InnerNetClient* __this, MethodInfo* method)
{
    if (!IsInLobby())
    {
        State.LobbyTimer = 0;
    }

    if (IsInLobby() && State.LobbyTimer > 0)
    {
        State.LobbyTimer--;
    }

    if (!IsInGame() || State.InMeeting)
    {
        if (State.PlayMedbayScan)
        {
            State.PlayMedbayScan = false;
            State.rpcQueue.push(new RpcSetScanner(false));
        }
    }

    if ((IsInGame() || IsInLobby()) && State.HotkeyNoClip)
    {
        if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
            if (State.NoClip)
                app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
            else
                app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
        }
        State.HotkeyNoClip = false;
    }

    if (((IsInGame() && IsInMultiplayerGame()) || IsInLobby()) && State.AntiBan)
    {
        PlayerControl_SetColor(*Game::pLocalPlayer, 0, NULL);
    }

    if (!IsInGame()) {
        State.selectedPlayer = PlayerSelection();
        State.playerToFollow = PlayerSelection();
        State.FreeCam = false;
        State.InMeeting = false;
        State.FollowerCam = nullptr;
        State.EnableZoom = false;
        State.DisableLights = false;
        State.CloseAllDoors = false;

        if (!IsInLobby()) {
            State.FlipSkeld = false;
            State.NoClip = false;
            State.HotkeyNoClip = false;
        }
    }
    else
    {
        if (!State.rpcQueue.empty()) {
            auto rpc = State.rpcQueue.front();
            State.rpcQueue.pop();

            rpc->Process();
            delete rpc;
        }

        if (State.CloseAllDoors)
        {
            for (auto door : State.mapDoors)
            {
                State.rpcQueue.push(new RpcCloseDoorsOfType(door, false));
            }
            State.CloseAllDoors = false;
        }

        if (State.MoveInVent && (*Game::pLocalPlayer)->fields.inVent)
        {
            (*Game::pLocalPlayer)->fields.moveable = true;
        }
    }

	InnerNetClient_Update(__this, method);
}