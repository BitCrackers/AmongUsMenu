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
	if (auto player = GetEventPlayerControl(__this)) {
		std::optional<TaskTypes__Enum> taskType = std::nullopt;
		auto normalPlayerTasks = GetNormalPlayerTasks(__this);
		for (auto normalPlayerTask : normalPlayerTasks)
			if (normalPlayerTask->fields._._Id_k__BackingField == idx) taskType = normalPlayerTask->fields._.TaskType;

		synchronized(Replay::replayEventMutex) {
			State.liveReplayEvents.emplace_back(std::make_unique<TaskCompletedEvent>(player.value(), taskType, PlayerControl_GetTruePosition(__this, NULL)));
		}
	}
	PlayerControl_CompleteTask(__this, idx, method);
}

static Color32 GetKillCooldownColor(float killTimer) {
	if (killTimer < 2.0) {
		return app::Color32_op_Implicit(Palette__TypeInfo->static_fields->ImpostorRed, NULL);
	}
	else if (killTimer < 5.0) {
		return app::Color32_op_Implicit(Palette__TypeInfo->static_fields->Orange, NULL);
	}
	else {
		return app::Color32_op_Implicit(Palette__TypeInfo->static_fields->White_75Alpha, NULL);
	}
}

float dPlayerControl_fixedUpdateTimer = 50;
float dPlayerControl_fixedUpdateCount = 0;
void dPlayerControl_FixedUpdate(PlayerControl* __this, MethodInfo* method) {
	dPlayerControl_fixedUpdateTimer = round(1.f / Time_get_fixedDeltaTime(nullptr));
	if (__this == *Game::pLocalPlayer) {
		if (State.rpcCooldown == 0) {
			MessageWriter* rpcMessage = InnerNetClient_StartRpc((InnerNetClient*)(*Game::pAmongUsClient), __this->fields._.NetId, (uint8_t)42069, (SendOption__Enum)1, NULL);
			MessageWriter_WriteByte(rpcMessage, __this->fields.PlayerId, NULL);
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
		assert(Object_1_IsNotNull((Object_1*)__this->fields.cosmetics));
		auto nameTextTMP = __this->fields.cosmetics->fields.nameText;

		if (!playerData || !localData)
			return;

		app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData, true);
		std::string playerName = "<Unknown>";
		if (outfit != NULL)
			playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
		if (State.ShowKillCD
			&& __this != *Game::pLocalPlayer
			&& !playerData->fields.IsDead
			&& playerData->fields.Role
			&& playerData->fields.Role->fields.CanUseKillButton
			) {
			float killTimer = __this->fields.killTimer;
			Color32&& color = GetKillCooldownColor(killTimer);
			playerName += std::format("\n<size=70%><color=#{:02x}{:02x}{:02x}{:02x}>Cooldown: {:.1f}s",
									  color.r, color.g, color.b, color.a,
									  killTimer);
		}
		if (State.RevealRoles)
		{
			std::string roleName = GetRoleName(playerData->fields.Role, State.AbbreviatedRoleNames);
			playerName += "\n<size=50%>(" + roleName + ")";
			Color32&& roleColor = app::Color32_op_Implicit(GetRoleColor(playerData->fields.Role), NULL);

			playerName = std::format("<color=#{:02x}{:02x}{:02x}{:02x}>{}",
									 roleColor.r, roleColor.g, roleColor.b,
									 roleColor.a, playerName);
		}

		String* playerNameStr = convert_to_string(playerName);
		app::TMP_Text_set_text((app::TMP_Text*)nameTextTMP, playerNameStr, NULL);

		if (IsColorBlindMode()) {
			// TODO: Adjust the position of nameTextTMP
		}

		// SeeProtect
		do {
			if (__this->fields.protectedByGuardianId <= -1)
				break;
			if (localData->fields.IsDead)
				break;
			GameOptions options;
			if (PlayerIsImpostor(localData)
				&& options.GetBool(app::BoolOptionNames__Enum::ImpostorsCanSeeProtect))
				break;
			bool isPlaying = false;
			for (auto anim : il2cpp::List(__this->fields.currentRoleAnimations))
				if (anim->fields.effectType == RoleEffectAnimation_EffectType__Enum::ProtectLoop) {
					isPlaying = true;
					break;
				}
			if (isPlaying == State.ShowProtections)
				break;
			if (!State.ShowProtections)
				app::PlayerControl_RemoveProtection(__this, nullptr);
			std::pair<int32_t/*ColorId*/, float/*Time*/> pair;
			synchronized(State.protectMutex) {
				pair = State.protectMonitor[__this->fields.PlayerId];
			}
			const float ProtectionDurationSeconds = options.GetFloat(app::FloatOptionNames__Enum::ProtectionDurationSeconds, 1.0F);
			float _Duration = ProtectionDurationSeconds - (app::Time_get_time(nullptr) - pair.second);
			options.SetFloat(app::FloatOptionNames__Enum::ProtectionDurationSeconds, _Duration);
			if (_Duration > 0.f)
				app::PlayerControl_TurnOnProtection(__this, State.ShowProtections, pair.first, __this->fields.protectedByGuardianId, nullptr);
			options.SetFloat(app::FloatOptionNames__Enum::ProtectionDurationSeconds, ProtectionDurationSeconds);
		} while (0);

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
		else if (auto role = playerData->fields.Role) {
			// ESP: Calculate Kill Cooldown
			if (role->fields.CanUseKillButton && !playerData->fields.IsDead) {
				if (__this->fields.ForceKillTimerContinue
					|| app::PlayerControl_get_IsKillTimerEnabled(__this, nullptr)) {
					__this->fields.killTimer = (std::max)(__this->fields.killTimer - app::Time_get_fixedDeltaTime(nullptr), 0.f);
				}
			}
		}

		if ((__this == *Game::pLocalPlayer) && (State.originalColor == Game::NoColorId)) {
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

			Vector2 prevPlayerPos;
			synchronized(Replay::replayEventMutex) {
				auto& lastPos = State.lastWalkEventPosPerPlayer[__this->fields.PlayerId];
				prevPlayerPos = { lastPos.x, lastPos.y };
				lastPos.x = playerPos.x;
				lastPos.y = playerPos.y;
			}

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
				float dist = GetDistanceBetweenPoints_Unity(playerPos, prevPlayerPos);
				// NOTE:
				// the localplayer moves even while standing still, by the tiniest amount.
				// hopefully 0.01 will be big enough to filter that out but small enough to catch every real movement
				if (dist > 0.01f)
				{
					synchronized(Replay::replayEventMutex) {
						// NOTE:
						// we do not add walkevents to liveReplayEvents. linedata contains everything we need for live visualization.
						const auto outfit = GetPlayerOutfit(playerData);
						const auto& map = maps[(size_t)State.mapType];
						ImVec2 mapPos_pre = { map.x_offset + (playerPos.x * map.scale), map.y_offset - (playerPos.y * map.scale) };
						if (State.replayWalkPolylineByPlayer.find(__this->fields.PlayerId) == State.replayWalkPolylineByPlayer.end())
						{
							// first-time init
							State.replayWalkPolylineByPlayer[__this->fields.PlayerId] = {};
							State.replayWalkPolylineByPlayer[__this->fields.PlayerId].pendingPoints.reserve(100);
							State.replayWalkPolylineByPlayer[__this->fields.PlayerId].pendingTimeStamps.reserve(100);
						}
						auto& plrLineData = State.replayWalkPolylineByPlayer[__this->fields.PlayerId];
						plrLineData.playerId = __this->fields.PlayerId; 
						plrLineData.colorId = outfit ? outfit->fields.ColorId : Game::NoColorId;
						plrLineData.pendingPoints.push_back(mapPos_pre);
						plrLineData.pendingTimeStamps.emplace_back(std::chrono::system_clock::now());
						if (plrLineData.pendingPoints.size() >= 100) {
							DoPolylineSimplification(plrLineData.pendingPoints, plrLineData.pendingTimeStamps,
								plrLineData.simplifiedPoints, plrLineData.simplifiedTimeStamps, 50.f, true);
						}
					}
				}
				Profiler::EndSample("WalkEventCreation");
			}
			app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);
			EspPlayerData espPlayerData;
			espPlayerData.Position = WorldToScreen(playerPos);
			if (outfit != NULL)
			{
				espPlayerData.Color = State.ShowEsp_RoleBased == false ? AmongUsColorToImVec4(GetPlayerColor(outfit->fields.ColorId))
					: AmongUsColorToImVec4(GetRoleColor(playerData->fields.Role));
				espPlayerData.Name = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
			}
			else
			{
				espPlayerData.Color = State.ShowEsp_RoleBased == false ? ImVec4(0.f, 0.f, 0.f, 1.f)
					: AmongUsColorToImVec4(GetRoleColor(playerData->fields.Role));
				espPlayerData.Name = "<Unknown>";
			}
			espPlayerData.OnScreen = IsWithinScreenBounds(playerPos);
			espPlayerData.Distance = Vector2_Distance(localPos, playerPos, nullptr);
			espPlayerData.playerData = PlayerSelection(__this);

			drawing_t& instance = Esp::GetDrawing();
			synchronized(instance.m_DrawingMutex) {
				instance.LocalPosition = localScreenPosition;
				instance.m_Players[playerData->fields.PlayerId] = espPlayerData;
			}
		}
	}
	app::PlayerControl_FixedUpdate(__this, method);
}

void dPlayerControl_RpcSyncSettings(PlayerControl* __this, Byte__Array* optionsByteArray, MethodInfo* method) {
	SaveGameOptions();

	PlayerControl_RpcSyncSettings(__this, optionsByteArray, method);
}

void dPlayerControl_MurderPlayer(PlayerControl* __this, PlayerControl* target, MurderResultFlags__Enum resultFlags, MethodInfo* method)
{
	if (static_cast<int32_t>(resultFlags) & static_cast<int32_t>(MurderResultFlags__Enum::FailedError)) {
		app::PlayerControl_MurderPlayer(__this, target, resultFlags, method);
		return;
	}

	auto killer = GetEventPlayerControl(__this);
	auto victim = GetEventPlayerControl(target);
	if (killer && victim) {
		if(PlayerIsImpostor(GetPlayerData(__this)) && PlayerIsImpostor(GetPlayerData(target))) {
			synchronized(Replay::replayEventMutex) {
				State.liveReplayEvents.emplace_back(std::make_unique<CheatDetectedEvent>(killer.value(), CHEAT_ACTIONS::CHEAT_KILL_IMPOSTOR));
			}
		}
		synchronized(Replay::replayEventMutex) {
			State.liveReplayEvents.emplace_back(std::make_unique<KillEvent>(killer.value(), victim.value(), PlayerControl_GetTruePosition(__this, NULL), PlayerControl_GetTruePosition(target, NULL)));
			State.replayDeathTimePerPlayer[target->fields.PlayerId] = std::chrono::system_clock::now();
		}
	}

	// ESP: Reset Kill Cooldown
	if (__this->fields._.OwnerId != (*Game::pAmongUsClient)->fields._.ClientId) {
		if (!target || target->fields.protectedByGuardianId <= -1)
			__this->fields.killTimer = (std::max)(GameOptions().GetKillCooldown(), 0.f);
		else
			__this->fields.killTimer = (std::max)(GameOptions().GetKillCooldown() * 0.5f, 0.f);
		//STREAM_DEBUG("Player " << ToString(__this) << " KillTimer " << __this->fields.killTimer);
	}

	do {
		if (!State.ShowProtections) break;
		if (!target || target->fields.protectedByGuardianId <= -1)
			break;
		if (__this->fields._.OwnerId == (*Game::pAmongUsClient)->fields._.ClientId)
			break; // AmKiller
		if (auto localData = GetPlayerData(*Game::pLocalPlayer);
			!localData || !localData->fields.Role
			|| localData->fields.Role->fields.Role == RoleTypes__Enum::GuardianAngel)
			break; // AmAngel
		int prev = target->fields.protectedByGuardianId;
		PlayerControl_ShowFailedMurder(target, nullptr);
		target->fields.protectedByGuardianId = prev;
	} while (false);
	PlayerControl_MurderPlayer(__this, target, resultFlags, method);
}

void dPlayerControl_StartMeeting(PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method)
{
	if (auto player = GetEventPlayerControl(__this);
		player && target) {
		synchronized(Replay::replayEventMutex) {
			State.liveReplayEvents.emplace_back(std::make_unique<ReportDeadBodyEvent>(player.value(), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL), GetTargetPosition(target)));
		}
	}
	app::PlayerControl_StartMeeting(__this, target, method);
}

void dPlayerControl_HandleRpc(PlayerControl* __this, uint8_t callId, MessageReader* reader, MethodInfo* method) {
	HandleRpc(callId, reader);
	PlayerControl_HandleRpc(__this, callId, reader, NULL);
}

void dRenderer_set_enabled(Renderer* __this, bool value, MethodInfo* method)
{
	//If we're already rendering it, lets skip checking if we should
	if (IsInGame() && !value && State.ShowGhosts)
	{
		Transform* rendererTrans = app::Component_get_transform(reinterpret_cast<app::Component_1*>(__this), NULL);
		if (rendererTrans != NULL)
		{
			Transform* root = app::Transform_GetRoot(rendererTrans, NULL); // docs say GetRoot never returns NULL, so no need to check it
			for (auto player : GetAllPlayerControl())
			{
				auto playerInfo = GetPlayerData(player);
				if (!playerInfo) break; //This happens sometimes during loading

				if (playerInfo->fields.IsDead)
				{
					// TO-DO:
					// figure out if a reference to the Renderer component can be gotten, otherwise just use UnityEngine's GetComponentInChildren<T> function
					// was: player->fields.MyPhysics->fields.rend
					Transform* playerTrans = app::Component_get_transform(reinterpret_cast<app::Component_1*>(player), NULL);
					if (playerTrans == NULL) continue;
					Transform* playerRoot = app::Transform_GetRoot(playerTrans, NULL); // docs say GetRoot never returns NULL, so no need to check it
					if (root == playerRoot)
					{
						value = true;
					}
				}
			}
		}
	}
	Renderer_set_enabled(__this, value, method);
}

void dGameObject_SetActive(GameObject* __this, bool value, MethodInfo* method)
{
	if (IsInGame() && !value && State.ShowGhosts) { //If we're already rendering it, lets skip checking if we should
		for (auto player : GetAllPlayerControl()) {
			auto playerInfo = GetPlayerData(player);
			if (!playerInfo || !player->fields.cosmetics) break; //This happens sometimes during loading
			if (playerInfo->fields.IsDead)
			{
				auto nameObject = Component_get_gameObject((Component_1*)player->fields.cosmetics->fields.nameText, NULL);
				if (nameObject == __this) {
					value = true;
					break;
				}
			}
		}
	}
	GameObject_SetActive(__this, value, method);
}

void dPlayerControl_Shapeshift(PlayerControl* __this, PlayerControl* target, bool animate, MethodInfo* method) {
	auto source_player = GetEventPlayerControl(__this);
	auto target_player = GetEventPlayerControl(target);
	if (source_player && target_player) {
		synchronized(Replay::replayEventMutex) {
			State.liveReplayEvents.emplace_back(std::make_unique<ShapeShiftEvent>(source_player.value(), target_player.value()));
		}
	}
	PlayerControl_Shapeshift(__this, target, animate, method);
}

void dPlayerControl_ProtectPlayer(PlayerControl* __this, PlayerControl* target, int32_t colorId, MethodInfo* method) {
	auto source_player = GetEventPlayerControl(__this);
	auto target_player = GetEventPlayerControl(target);
	if (source_player && target_player) {
		synchronized(Replay::replayEventMutex) {
			State.liveReplayEvents.emplace_back(std::make_unique<ProtectPlayerEvent>(source_player.value(), target_player.value()));
		}
	}
	PlayerControl_ProtectPlayer(__this, target, colorId, method);
}

void dPlayerControl_TurnOnProtection(PlayerControl* __this, bool visible, int32_t colorId, int32_t guardianPlayerId, MethodInfo* method) {
	app::PlayerControl_TurnOnProtection(__this, visible || State.ShowProtections, colorId, guardianPlayerId, method);
	std::pair pair { colorId, app::Time_get_time(nullptr) };
	synchronized(State.protectMutex) {
		State.protectMonitor[__this->fields.PlayerId] = pair;
	}
}