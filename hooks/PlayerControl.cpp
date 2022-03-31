#include "pch-il2cpp.h"
#include "_hooks.h"
#include "game.h"
#include "state.hpp"
#include "esp.hpp"
#include "_rpc.h"
#include "replay.hpp"
#include "profiler.h"
#include <iostream>
#include <optional>

void dPlayerControl_CompleteTask(PlayerControl* __this, uint32_t idx, MethodInfo* method) {
	std::optional<TaskTypes__Enum> taskType = std::nullopt;

	auto normalPlayerTasks = GetNormalPlayerTasks(__this);
	for (auto normalPlayerTask : normalPlayerTasks)
		if (normalPlayerTask->fields._._Id_k__BackingField == idx) taskType = normalPlayerTask->fields._.TaskType;

	State.rawEvents.push_back(std::make_unique<TaskCompletedEvent>(GetEventPlayerControl(__this).value(), taskType, PlayerControl_GetTruePosition(__this, NULL)));
	State.liveReplayEvents.push_back(std::make_unique<TaskCompletedEvent>(GetEventPlayerControl(__this).value(), taskType, PlayerControl_GetTruePosition(__this, NULL)));

	PlayerControl_CompleteTask(__this, idx, method);
}

float dPlayerControl_fixedUpdateTimer = 50;
float dPlayerControl_fixedUpdateCount = 0;
void dPlayerControl_FixedUpdate(PlayerControl* __this, MethodInfo* method) {
	dPlayerControl_fixedUpdateTimer = round(1.f / Time_get_fixedDeltaTime(nullptr));
	if (__this == *Game::pLocalPlayer) {
		if (State.rpcCooldown == 0) {
			MessageWriter* rpcMessage = InnerNetClient_StartRpc((InnerNetClient*)(*Game::pAmongUsClient), __this->fields._.NetId, (uint8_t)42069, (SendOption__Enum)1, NULL);
			MessageWriter_WriteInt32(rpcMessage, __this->fields.PlayerId, NULL);
			MessageWriter_EndMessage(rpcMessage, NULL);
			State.rpcCooldown = 15;
		}
		else {
			State.rpcCooldown--;
		}
	}

	if (IsInGame()) {
		auto playerData = GetPlayerData(__this);
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		auto nameTextTMP = __this->fields.nameText;

		if (!playerData || !localData)
			return;

		Color32 faceColor = app::Color32_op_Implicit(Palette__TypeInfo->static_fields->Black, NULL);
		Color32 roleColor = app::Color32_op_Implicit(Palette__TypeInfo->static_fields->White, NULL);
		std::string playerName = convert_from_string(GetPlayerOutfit(playerData, true)->fields._playerName);
		if (State.RevealRoles)
		{
			std::string roleName = GetRoleName(playerData->fields.Role, State.AbbreviatedRoleNames);
			playerName += "\n<size=50%>(" + roleName + ")";
			roleColor = app::Color32_op_Implicit(GetRoleColor(playerData->fields.Role), NULL);
		}
		else if (PlayerIsImpostor(localData) && PlayerIsImpostor(playerData))
		{
			roleColor = app::Color32_op_Implicit(Palette__TypeInfo->static_fields->ImpostorRed, NULL);
		}

		String* playerNameStr = convert_to_string(playerName);
		app::TMP_Text_set_text((app::TMP_Text*)nameTextTMP, playerNameStr, NULL);
		app::TextMeshPro_SetFaceColor(nameTextTMP, roleColor, NULL);
		app::TextMeshPro_SetOutlineColor(nameTextTMP, faceColor, NULL);

		if (State.Wallhack && __this == *Game::pLocalPlayer && !State.FreeCam && !State.playerToFollow.has_value()) {
			auto mainCamera = Camera_get_main(NULL);

			Transform* cameraTransform = Component_get_transform((Component_1*)mainCamera, NULL);
			Vector3 cameraVector3 = Transform_get_position(cameraTransform, NULL);
			Transform_set_position(cameraTransform, { cameraVector3.x, cameraVector3.y, 1000}, NULL);
		}

		if (__this == *Game::pLocalPlayer) {
			if (State.FollowerCam == nullptr) {
				for (auto cam : GetAllCameras()) {
					if (Camera_get_orthographicSize(cam, NULL) == 3.0f) {
						State.FollowerCam = cam;
						break;
					}
				};
			}
			if (State.FollowerCam != nullptr) {
				if(State.EnableZoom && !State.InMeeting)
					Camera_set_orthographicSize(State.FollowerCam, State.CameraHeight, NULL);
				else
					Camera_set_orthographicSize(State.FollowerCam, 3.0f, NULL);

				Transform* cameraTransform = Component_get_transform((Component_1*)State.FollowerCam, NULL);
				Vector3 cameraVector3 = Transform_get_position(cameraTransform, NULL);
				if(State.EnableZoom && !State.InMeeting && State.CameraHeight > 3.0f)
				Transform_set_position(cameraTransform, { cameraVector3.x, cameraVector3.y, 100 }, NULL);
			}
		}

		if ((__this == *Game::pLocalPlayer) && (State.originalColor == 0xFF)) {
			SaveOriginalAppearance();
		}

		if (!State.FreeCam && __this == *Game::pLocalPlayer && State.prevCamPos.x != NULL) {
			auto mainCamera = Camera_get_main(NULL);

			Transform* cameraTransform = Component_get_transform((Component_1*)mainCamera, NULL);
			Vector3 cameraVector3 = Transform_get_position(cameraTransform, NULL);
			Transform_set_position(cameraTransform, State.prevCamPos, NULL);

			State.camPos = { NULL, NULL, NULL };
			State.prevCamPos = { NULL, NULL, NULL };
		}

		if (State.FreeCam  && __this == *Game::pLocalPlayer) {
			auto mainCamera = Camera_get_main(NULL);

			Transform* cameraTransform = Component_get_transform((Component_1*)mainCamera, NULL);
			Vector3 cameraVector3 = Transform_get_position(cameraTransform, NULL);

			if (State.camPos.x == NULL) {
				State.camPos = cameraVector3;
			}
			if (State.prevCamPos.x == NULL) {
				State.prevCamPos = cameraVector3;
			}

			BYTE arr[256];
			if (GetKeyboardState(arr))
			{
				if ((arr[0x57] & 0x80) != 0) {
					State.camPos.y = State.camPos.y + (0.1f * State.FreeCamSpeed);
				}
				if ((arr[0x41] & 0x80) != 0) {
					State.camPos.x = State.camPos.x - (0.1f * State.FreeCamSpeed);
				}
				if ((arr[0x53] & 0x80) != 0) {
					State.camPos.y = State.camPos.y - (0.1f * State.FreeCamSpeed);
				}
				if ((arr[0x44] & 0x80) != 0)
				{
					State.camPos.x = State.camPos.x + (0.1f * State.FreeCamSpeed);
				}
			}

			Transform_set_position(cameraTransform, { State.camPos.x, State.camPos.y, 100 }, NULL);
		}

		// We should have this in a scope so that the lock guard only locks the right things
		{
			Vector2 localPos = PlayerControl_GetTruePosition(*Game::pLocalPlayer, nullptr);
			ImVec2 localScreenPosition = WorldToScreen(localPos);

			Vector2 playerPos = PlayerControl_GetTruePosition(__this, nullptr);
			Vector2 prevPlayerPos = {State.lastWalkEventPosPerPlayer[__this->fields.PlayerId].x, State.lastWalkEventPosPerPlayer[__this->fields.PlayerId].y};

			State.lastWalkEventPosPerPlayer[__this->fields.PlayerId].x = playerPos.x;
			State.lastWalkEventPosPerPlayer[__this->fields.PlayerId].y = playerPos.y;

			// only update our counter if fixedUpdate is executed on local player
			if (__this == *Game::pLocalPlayer)
				dPlayerControl_fixedUpdateCount++;

			if (State.Replay_IsPlaying
				&& !State.Replay_IsLive
				&& dPlayerControl_fixedUpdateCount >= dPlayerControl_fixedUpdateTimer)
			{
				dPlayerControl_fixedUpdateCount = 0;
				State.MatchCurrent += std::chrono::seconds(1);
			}

			if (!State.InMeeting)
			{
				Profiler::BeginSample("WalkEventCreation");
				std::lock_guard<std::mutex> replayLock(Replay::replayEventMutex);
				float dist = GetDistanceBetweenPoints_Unity(playerPos, prevPlayerPos);
				// NOTE:
				// the localplayer moves even while standing still, by the tiniest amount.
				// hopefully 0.01 will be big enough to filter that out but small enough to catch every real movement
				if (dist > 0.01f)
				{
					// NOTE:
					// we do not add walkevents to liveReplayEvents. linedata contains everything we need for live visualization.
					State.rawEvents.push_back(std::make_unique<WalkEvent>(GetEventPlayerControl(__this).value(), playerPos));
					ImVec2 mapPos_pre = {maps[State.mapType].x_offset + (playerPos.x * maps[State.mapType].scale), maps[State.mapType].y_offset - (playerPos.y * maps[State.mapType].scale)};
					if (State.replayWalkPolylineByPlayer.find(__this->fields.PlayerId) == State.replayWalkPolylineByPlayer.end())
					{
						// first-time init
						State.replayWalkPolylineByPlayer[__this->fields.PlayerId] = {};
						State.replayWalkPolylineByPlayer[__this->fields.PlayerId].pendingPoints = {};
						State.replayWalkPolylineByPlayer[__this->fields.PlayerId].pendingTimeStamps = {};
						State.replayWalkPolylineByPlayer[__this->fields.PlayerId].simplifiedPoints = {};
						State.replayWalkPolylineByPlayer[__this->fields.PlayerId].simplifiedTimeStamps = {};
					}
					State.replayWalkPolylineByPlayer[__this->fields.PlayerId].playerId = __this->fields.PlayerId;
					State.replayWalkPolylineByPlayer[__this->fields.PlayerId].colorId = State.rawEvents.back().get()->getSource().colorId;

					State.replayWalkPolylineByPlayer[__this->fields.PlayerId].pendingPoints.push_back(mapPos_pre);
					State.replayWalkPolylineByPlayer[__this->fields.PlayerId].pendingTimeStamps.push_back(State.rawEvents.back().get()->GetTimeStamp());
				}
				Profiler::EndSample("WalkEventCreation");
			}

			PlayerData espPlayerData;
			espPlayerData.Position = WorldToScreen(playerPos);
			espPlayerData.Color = AmongUsColorToImVec4(GetPlayerColor(GetPlayerOutfit(playerData)->fields.ColorId));
			espPlayerData.Name = convert_from_string(GetPlayerOutfit(playerData)->fields._playerName);
			espPlayerData.OnScreen = IsWithinScreenBounds(playerPos);
			espPlayerData.Distance = Vector2_Distance(localPos, playerPos, nullptr);
			espPlayerData.playerData = PlayerSelection(__this);

			drawing_t& instance = Esp::GetDrawing();
			std::lock_guard<std::mutex> lock(instance.m_DrawingMutex);
			instance.LocalPosition = localScreenPosition;
			instance.m_Players[playerData->fields.PlayerId] = espPlayerData;
		}
	}
	app::PlayerControl_FixedUpdate(__this, method);
}

void dPlayerControl_RpcSyncSettings(PlayerControl* __this, GameOptionsData* gameOptions, MethodInfo* method)
{
	State.PrevPlayerSpeed = gameOptions->fields._.playerSpeedMod;
	State.PlayerSpeed = gameOptions->fields._.playerSpeedMod;
	State.PrevKillDistance = gameOptions->fields._.killDistance;
	State.KillDistance = gameOptions->fields._.killDistance;
	State.PrevTaskBarUpdates = (int)gameOptions->fields.TaskBarMode;
	State.TaskBarUpdates = (int)gameOptions->fields.TaskBarMode;

	PlayerControl_RpcSyncSettings(__this, gameOptions, method);
}

void dPlayerControl_MurderPlayer(PlayerControl* __this, PlayerControl* target, MethodInfo* method)
{
	if (PlayerIsImpostor(GetPlayerData(__this)) && PlayerIsImpostor(GetPlayerData(target)))
	{
		State.rawEvents.push_back(std::make_unique<CheatDetectedEvent>(GetEventPlayerControl(__this).value(), CHEAT_KILL_IMPOSTOR));
		State.liveReplayEvents.push_back(std::make_unique<CheatDetectedEvent>(GetEventPlayerControl(__this).value(), CHEAT_KILL_IMPOSTOR));
	}

	State.rawEvents.push_back(std::make_unique<KillEvent>(GetEventPlayerControl(__this).value(), GetEventPlayerControl(target).value(), PlayerControl_GetTruePosition(__this, NULL), PlayerControl_GetTruePosition(target, NULL)));
	State.liveReplayEvents.push_back(std::make_unique<KillEvent>(GetEventPlayerControl(__this).value(), GetEventPlayerControl(target).value(), PlayerControl_GetTruePosition(__this, NULL), PlayerControl_GetTruePosition(target, NULL)));

	PlayerControl_MurderPlayer(__this, target, method);
}

void dPlayerControl_CmdReportDeadBody(PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method)
{
	State.rawEvents.push_back(std::make_unique<ReportDeadBodyEvent>(GetEventPlayerControl(__this).value(), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL), GetTargetPosition(target)));
	State.liveReplayEvents.push_back(std::make_unique<ReportDeadBodyEvent>(GetEventPlayerControl(__this).value(), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL), GetTargetPosition(target)));
	PlayerControl_CmdReportDeadBody(__this, target, method);
}

void dPlayerControl_ReportDeadBody(PlayerControl*__this, GameData_PlayerInfo* target, MethodInfo *method)
{
	if (!IsHost())
	{
		State.rawEvents.push_back(std::make_unique<ReportDeadBodyEvent>(GetEventPlayerControl(__this).value(), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL), GetTargetPosition(target)));
		State.liveReplayEvents.push_back(std::make_unique<ReportDeadBodyEvent>(GetEventPlayerControl(__this).value(), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL), GetTargetPosition(target)));
	}
	PlayerControl_ReportDeadBody(__this, target, method);
}

void dPlayerControl_HandleRpc(PlayerControl* __this, uint8_t callId, MessageReader* reader, MethodInfo* method) {
	HandleRpc(callId, reader);
	PlayerControl_HandleRpc(__this, callId, reader, NULL);
}

void dRenderer_set_enabled(Renderer * __this, bool value, MethodInfo * method) {
	if (IsInGame() && !value) { //If we're already rendering it, lets skip checking if we should
		for (auto player : GetAllPlayerControl()) {
			if (GetPlayerData(player) == NULL) break; //This happens sometimes during loading
			if (GetPlayerData(player)->fields.IsDead && State.ShowGhosts)
			{
				// TO-DO:
				// figure out if a reference to the Renderer component can be gotten, otherwise just use UnityEngine's GetComponentInChildren<T> function
				// was: player->fields.MyPhysics->fields.rend
				if (((Renderer*)player->fields.MyPhysics->fields.Skin->fields.layer) == __this) {
					value = true;
				}
			}
		}
	}
	Renderer_set_enabled(__this, value, method);
}

void dGameObject_SetActive(GameObject* __this, bool value, MethodInfo* method)
{
	if (IsInGame() && !value) { //If we're already rendering it, lets skip checking if we should
		for (auto player : GetAllPlayerControl()) {
			if (GetPlayerData(player) == NULL) break; //This happens sometimes during loading
			if (GetPlayerData(player)->fields.IsDead && State.ShowGhosts)
			{
				auto nameObject = Component_get_gameObject((Component_1*)player->fields.nameText, NULL);
				if (nameObject == __this) {
					value = true;
				}
			}
		}
	}
	GameObject_SetActive(__this, value, method);
}

void dPlayerControl_Shapeshift(PlayerControl* __this, PlayerControl* target, bool animate, MethodInfo* method) {
	State.rawEvents.push_back(std::make_unique<ShapeShiftEvent>(GetEventPlayerControl(__this).value(), GetEventPlayerControl(target).value()));
	State.liveReplayEvents.push_back(std::make_unique<ShapeShiftEvent>(GetEventPlayerControl(__this).value(), GetEventPlayerControl(target).value()));
	PlayerControl_Shapeshift(__this, target, animate, method);
}

void dPlayerControl_ProtectPlayer(PlayerControl* __this, PlayerControl* target, int32_t colorId, MethodInfo* method) {
	State.rawEvents.push_back(std::make_unique<ProtectPlayerEvent>(GetEventPlayerControl(__this).value(), GetEventPlayerControl(target).value()));
	State.liveReplayEvents.push_back(std::make_unique<ProtectPlayerEvent>(GetEventPlayerControl(__this).value(), GetEventPlayerControl(target).value()));
	PlayerControl_ProtectPlayer(__this, target, colorId, method);
}