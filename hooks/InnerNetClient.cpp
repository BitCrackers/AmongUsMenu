#include "_hooks.hpp"

using namespace app;

void dInnerNetClient_Update(InnerNetClient* __this, MethodInfo* method)
{
    if (!IsInGame()) {
        State.selectedPlayer = PlayerSelection();
        State.playerToFollow = PlayerSelection();
        State.NoClip = false;
        State.FreeCam = false;
        State.InMeeting = false;
        State.FollowerCam = nullptr;
        State.EnableZoom = false;
        State.DisableLights = false;
        State.CloseAllDoors = false;
        State.HotkeyNoClip = false;

        if (!IsInLobby()) {
            State.FlipSkeld = false;
        }
    }

    if (!IsInGame() || State.InMeeting)
    {
        if (State.PlayMedbayScan)
        {
            State.PlayMedbayScan = false;
            State.rpcQueue.push(new RpcSetScanner(false));
        }
    }

    if (IsInGame() && State.CloseAllDoors)
    {
        for (auto door : State.mapDoors)
        {
            State.rpcQueue.push(new RpcCloseDoorsOfType(door, false));
        }
        State.CloseAllDoors = false;
    }

    if (IsInGame() && State.HotkeyNoClip)
    {
        if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
            if (State.NoClip)
                app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
            else
                app::GameObject_set_layer(app::Component_get_gameObject((Component*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
        }
        State.HotkeyNoClip = false;
    }

	InnerNetClient_Update(__this, method);
}