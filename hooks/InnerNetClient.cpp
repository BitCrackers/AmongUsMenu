#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"
#include "logger.h"
#include "utility.h"
#include "replay.hpp"
#include "profiler.h"
#include <sstream>
#include "esp.hpp"

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
                app::GameObject_set_layer(app::Component_get_gameObject((Component_1*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
            else
                app::GameObject_set_layer(app::Component_get_gameObject((Component_1*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
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
            State.NoClip = false;
            State.HotkeyNoClip = false;
            State.originalName = "-";
        }
    }
    else {
        if (!State.rpcQueue.empty()) {
            auto rpc = State.rpcQueue.front();
            //Looks like there is a check on Task completion when u are dead.
            //The maximum amount of Tasks that can be completed per Update is at 6.
            auto maxProcessedTasks = 6;
			auto processedTaskCompletes = 0;
			if (dynamic_cast<RpcCompleteTask*>(rpc))
			{
				if (processedTaskCompletes < maxProcessedTasks)
				{
					State.rpcQueue.pop();
					rpc->Process();
					processedTaskCompletes++;
				}
			}
			else
			{
				State.rpcQueue.pop();
				rpc->Process();
			}
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
            app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer));
            if (outfit != NULL)
                State.originalName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
        }

        if (!State.lobbyRpcQueue.empty()) {
            auto rpc = State.lobbyRpcQueue.front();
            State.lobbyRpcQueue.pop();

            rpc->Process();
            delete rpc;
        }
    }

    static int nameChangeCycleDelay = 0; //If we spam too many name changes, we're banned

    if (nameChangeCycleDelay <= 0 && !State.activeImpersonation) {
        if ((GetPlayerName() != State.userName) && !State.userName.empty()) {
            SetPlayerName(State.userName);
            LOG_INFO("Name mismatch, setting name to \"" + State.userName + "\"");
            if (IsInGame())
                State.rpcQueue.push(new RpcSetName(State.userName));
            else if (IsInLobby())
                State.lobbyRpcQueue.push(new RpcSetName(State.userName));
            nameChangeCycleDelay = 100; //Should be approximately two second
        }
    }
    else {
        nameChangeCycleDelay--;
    }
    // Right-click Teleport
    if (IsInGame() && State.RightClickTeleport && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
        ImVec2 mouse = ImGui::GetMousePos();
        Vector2 target = {
            (mouse.x - DirectX::GetWindowSize().x / 2) + DirectX::GetWindowSize().x / 2,
            ((mouse.y - DirectX::GetWindowSize().y / 2) - DirectX::GetWindowSize().y / 2) * -1.0f
        };
        State.rpcQueue.push(new RpcSnapTo(ScreenToWorld(target)));
    }
    InnerNetClient_Update(__this, method);
}

void dAmongUsClient_OnPlayerLeft(AmongUsClient* __this, ClientData* data, DisconnectReasons__Enum reason, MethodInfo* method) {
    if (data->fields.Character) { // Don't use Object_1_IsNotNull().
        auto playerInfo = GetPlayerData(data->fields.Character);
        Log.Debug(ToString(data->fields.Character) + " has left the game.");

        auto it = std::find(State.aumUsers.begin(), State.aumUsers.end(), data->fields.Character->fields.PlayerId);
        if (it != State.aumUsers.end())
            State.aumUsers.erase(it);

        if (auto evtPlayer = GetEventPlayer(playerInfo); evtPlayer) {
            synchronized(Replay::replayEventMutex) {
        	    State.liveReplayEvents.emplace_back(std::make_unique<DisconnectEvent>(evtPlayer.value()));
            }
        }
    }
    else {
        //Found this happens on game ending occasionally
        //Log.Info(std::format("Client {} has left the game.", data->fields.Id));
    }

    AmongUsClient_OnPlayerLeft(__this, data, reason, method);
}

bool bogusTransformSnap(PlayerSelection& _player, Vector2 newPosition)
{
    const auto& player = _player.validate();
    if (!player.has_value())
        Log.Debug("bogusTransformSnap received invalid player!");
    if (!player.has_value()) return false; //Error getting playercontroller
    if (player.is_LocalPlayer()) return false; //We are not going to log ourselves
    if (player.get_PlayerControl()->fields.inVent) return false; //Vent buttons are warps
    if (GameObject_get_layer(app::Component_get_gameObject((Component_1*)player.get_PlayerControl(), NULL), NULL) == LayerMask_NameToLayer(convert_to_string("Ghost"), NULL))
        return false; //For some reason the playercontroller is not marked dead at this point, so we check what layer the player is on
    auto currentPosition = PlayerControl_GetTruePosition(player.get_PlayerControl(), NULL);
    auto distanceToTarget = (int32_t)Vector2_Distance(currentPosition, newPosition, NULL); //rounding off as the smallest kill distance is zero
    auto killDistance = std::clamp(GameOptions().GetInt(app::Int32OptionNames__Enum::KillDistance), 0, 2);
    auto initialSpawnLocation = GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (int)il2cpp::List((*Game::pGameData)->fields.AllPlayers).size(), true);
    auto meetingSpawnLocation = GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (int)il2cpp::List((*Game::pGameData)->fields.AllPlayers).size(), false);
    if (Equals(initialSpawnLocation, newPosition)) return false;
    if (Equals(meetingSpawnLocation, newPosition)) return false;  //You are warped to your spawn at meetings and start of games
    if (IsAirshipSpawnLocation(newPosition)) return false;
    if (PlayerIsImpostor(player.get_PlayerData()) && distanceToTarget <= killDistance) 
        return false;
    std::ostringstream ss;

    ss << "From " << +currentPosition.x << "," << +currentPosition.y << " to " << +newPosition.x << "," << +newPosition.y << std::endl;
    ss << "Range to target " << +distanceToTarget << ", KillDistance: " << +killDistance << std::endl;
    ss << "Initial Spawn Location " << +initialSpawnLocation.x << "," << +initialSpawnLocation.y << std::endl;
    ss << "Meeting Spawn Location " << +meetingSpawnLocation.x << "," << +meetingSpawnLocation.y << std::endl;
    ss << "-------";
    Log.Debug(ss.str());
    return true; //We have ruled out all possible scenarios.  Off with his head!
}

void dCustomNetworkTransform_SnapTo(CustomNetworkTransform* __this, Vector2 position, uint16_t minSid, MethodInfo* method) {
    //Leave this out until we fix it.
    /*
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
    */

    CustomNetworkTransform_SnapTo(__this, position, minSid, method);
}

static void onGameEnd() {
    LOG_DEBUG("Reset All");
    Replay::Reset();
    State.aumUsers.clear();
    State.chatMessages.clear();
    State.MatchEnd = std::chrono::system_clock::now();

    drawing_t& instance = Esp::GetDrawing();
    synchronized(instance.m_DrawingMutex) {
        instance.m_Players = {};
    }
}

void dAmongUsClient_OnGameEnd(AmongUsClient* __this, Object* endGameResult, MethodInfo* method) {
    onGameEnd();
    AmongUsClient_OnGameEnd(__this, endGameResult, method);
}

void dInnerNetClient_DisconnectInternal(InnerNetClient* __this, DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method) {
    // IsInGame() || IsInLobby()
    if (__this->fields.GameState == InnerNetClient_GameStates__Enum::Started
        || __this->fields.GameState == InnerNetClient_GameStates__Enum::Joined
        || __this->fields.NetworkMode == NetworkModes__Enum::FreePlay) {
        onGameEnd();
    }
    InnerNetClient_DisconnectInternal(__this, reason, stringReason, method);
}

void dInnerNetClient_EnqueueDisconnect(InnerNetClient* __this, DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method) {
    if (!IsHost() || reason != DisconnectReasons__Enum::Banned) {
        return InnerNetClient_EnqueueDisconnect(__this, reason, stringReason, method);
    }
    if (reason == DisconnectReasons__Enum::Banned) {
        LOG_INFO("Blocked ban");
    }
}