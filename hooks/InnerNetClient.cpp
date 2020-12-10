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

    if (State.DisableLights)
    {
        SwitchSystem* switchSystem = nullptr;
        std::vector<std::pair<SystemTypes__Enum, ISystemType*>> systems = GetEntriesFromDictionary<Dictionary_2_SystemTypes_ISystemType_*, SystemTypes__Enum, ISystemType*>((*Game::pShipStatus)->fields.Systems);

        for (auto system : systems)
        {
            if (system.first == SystemTypes__Enum_Electrical)
            {
                switchSystem = (SwitchSystem*)system.second;
            }
        }

        if (switchSystem != nullptr)
        {
            auto actualSwitches = switchSystem->fields.ActualSwitches;
            auto expectedSwitches = switchSystem->fields.ExpectedSwitches;

            if (actualSwitches == expectedSwitches) {
                auto switchMask = 1 << (0 & 0x1F);

                if ((actualSwitches & switchMask) != (~expectedSwitches & switchMask))
                    State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Electrical, randi(0, 4)));
            }
        }
    }

	InnerNetClient_Update(__this, method);
}