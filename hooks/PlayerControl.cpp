#include "pch-il2cpp.h"
#include "_hooks.h"
#include "game.h"
#include "state.hpp"
#include "esp.hpp"
#include "_rpc.h"
#include <iostream>

void dPlayerControl_CompleteTask(PlayerControl* __this, uint32_t idx, MethodInfo* method) {
	std::optional<TaskTypes__Enum> taskType = std::nullopt;

	auto normalPlayerTasks = GetNormalPlayerTasks(__this);
	for (auto normalPlayerTask : normalPlayerTasks)
		if (normalPlayerTask->fields._._Id_k__BackingField == idx) taskType = normalPlayerTask->fields._.TaskType;

	State.events.push_back(new TaskCompletedEvent(GetEventPlayer(__this), taskType, PlayerControl_GetTruePosition(__this, NULL)));
	PlayerControl_CompleteTask(__this, idx, method);
}

void dPlayerControl_FixedUpdate(PlayerControl* __this, MethodInfo* method) {
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
		TextRenderer* nameText = (TextRenderer*)(__this->fields.nameText);

		if (!playerData || !localData)
			return;

		if (State.RevealImpostors || localData->fields.IsImpostor)
			nameText->fields.Color = playerData->fields.IsImpostor
			? Palette__TypeInfo->static_fields->ImpostorRed
			: Palette__TypeInfo->static_fields->White;
		else
			nameText->fields.Color = Palette__TypeInfo->static_fields->White;

		if (State.Wallhack && __this == *Game::pLocalPlayer && !State.FreeCam && !State.playerToFollow.has_value()) {
			auto mainCamera = Camera_get_main(NULL);

			Transform* cameraTransform = Component_get_transform((Component*)mainCamera, NULL);
			Vector3 cameraVector3 = Transform_get_position(cameraTransform, NULL);
			Transform_set_position(cameraTransform, { cameraVector3.x, cameraVector3.y, 1000}, NULL);
		}

		if (State.shadowLayer.has_value()) {
			GameObject* shadowLayerObject = Component_get_gameObject((Component*)State.shadowLayer.value()->fields.ShadowQuad, NULL);
			GameObject_SetActive(shadowLayerObject, !(State.FreeCam || State.EnableZoom || State.playerToFollow.has_value() || State.Wallhack), NULL);
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

				Transform* cameraTransform = Component_get_transform((Component*)State.FollowerCam, NULL);
				Vector3 cameraVector3 = Transform_get_position(cameraTransform, NULL);
				if(State.EnableZoom && !State.InMeeting && State.CameraHeight > 3.0f)
				Transform_set_position(cameraTransform, { cameraVector3.x, cameraVector3.y, 100 }, NULL);
			}
		}

		if (!State.FreeCam && __this == *Game::pLocalPlayer && State.prevCamPos.x != NULL) {
			auto mainCamera = Camera_get_main(NULL);

			Transform* cameraTransform = Component_get_transform((Component*)mainCamera, NULL);
			Vector3 cameraVector3 = Transform_get_position(cameraTransform, NULL);
			Transform_set_position(cameraTransform, State.prevCamPos, NULL);

			State.camPos = { NULL, NULL, NULL };
			State.prevCamPos = { NULL, NULL, NULL };
		}

		if (State.FreeCam  && __this == *Game::pLocalPlayer) {
			auto mainCamera = Camera_get_main(NULL);

			Transform* cameraTransform = Component_get_transform((Component*)mainCamera, NULL);
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

		
		Transform* skinTransform = Component_get_transform((Component*)__this->fields.MyPhysics->fields.Skin, NULL);
		Vector3 skinLocation = Transform_get_position(skinTransform, NULL);
		std::map<uint8_t, float>::iterator it = State.playerSkinLocations.find(__this->fields.PlayerId);
		float location = NULL;

		if (it != State.playerSkinLocations.end()) location = it->second;

		if ((State.Wallhack || State.FreeCam || State.EnableZoom) && location == NULL) {
			State.playerSkinLocations.insert({ __this->fields.PlayerId, skinLocation.z });
			Transform_set_position(skinTransform, { skinLocation.x, skinLocation.y, -6.f }, NULL);
		}
		else if(!(State.Wallhack || State.FreeCam || State.EnableZoom) && location != NULL) {
			Transform_set_position(skinTransform, { skinLocation.x, skinLocation.y, location }, NULL);
			State.playerSkinLocations.erase(__this->fields.PlayerId);
		}
    
		// We should have this in a scope so that the lock guard only locks the right things
		{
			Vector2 localPos = PlayerControl_GetTruePosition(*Game::pLocalPlayer, nullptr);
			ImVec2 localScreenPosition = WorldToScreen(localPos);

			Vector2 playerPos = PlayerControl_GetTruePosition(__this, nullptr);

			PlayerData espPlayerData;
			espPlayerData.Position = WorldToScreen(playerPos);
			espPlayerData.Color = AmongUsColorToImVec4(GetPlayerColor(playerData->fields.ColorId));
			espPlayerData.Name = convert_from_string(playerData->fields.PlayerName);
			espPlayerData.OnScreen = IsWithinScreenBounds(playerPos);
			espPlayerData.Distance = Vector2_Distance(localPos, playerPos, nullptr);
			espPlayerData.playerData = PlayerSelection(__this);

			drawing_t& instance = Esp::GetDrawing();
			std::lock_guard<std::mutex> lock(instance.m_DrawingMutex);
			instance.LocalPosition = localScreenPosition;
			instance.m_Players[playerData->fields.PlayerId] = espPlayerData;
		}

		// TODO: Improve performance
		/*Vector2 position = PlayerControl_GetTruePosition(__this, NULL);
		std::optional<Vector2> lastPosition = GetLastWalkEventPosition(__this->fields.PlayerId);
		if (!lastPosition.has_value() ||(lastPosition.has_value() && position.x != lastPosition->x && position.y != lastPosition->y))
			State.events.push_back(new WalkEvent(GetEventPlayer(__this), position));*/
	}
	app::PlayerControl_FixedUpdate(__this, method);
}

void dPlayerControl_RpcSyncSettings(PlayerControl* __this, GameOptionsData* gameOptions, MethodInfo* method) {
	State.PrevPlayerSpeed = gameOptions->fields.PlayerSpeedMod;
	State.PlayerSpeed = gameOptions->fields.PlayerSpeedMod;
	State.PrevKillDistance = gameOptions->fields.KillDistance;
	State.KillDistance = gameOptions->fields.KillDistance;
	State.PrevTaskBarUpdates = gameOptions->fields.TaskBarUpdates;
	State.TaskBarUpdates = gameOptions->fields.TaskBarUpdates;

	PlayerControl_RpcSyncSettings(__this, gameOptions, method);
}

void dPlayerControl_MurderPlayer(PlayerControl* __this, PlayerControl* target, MethodInfo* method) {
	if (GetPlayerData(__this)->fields.IsImpostor && GetPlayerData(target)->fields.IsImpostor) {
		State.events.push_back(new CheatDetectedEvent(GetEventPlayer(__this), CHEAT_KILL_IMPOSTOR));
	}

	State.events.push_back(new KillEvent(GetEventPlayer(__this), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL)));
	PlayerControl_MurderPlayer(__this, target, method);
}

void dPlayerControl_ReportDeadBody(PlayerControl*__this, GameData_PlayerInfo* target, MethodInfo *method) {
	State.events.push_back(new ReportDeadBodyEvent(GetEventPlayer(__this), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL)));
	PlayerControl_ReportDeadBody(__this, target, method);
}

void dPlayerControl_RpcSetInfected(PlayerControl* __this, GameData_PlayerInfo__Array* infected, MethodInfo* method) {
	for (int i = 0; i < (*Game::pGameOptionsData)->fields.NumImpostors; i++) {
		if (State.impostors[i] != nullptr) {
			infected->vector[i] = GetPlayerData(State.impostors[i]);
		}
	}
	PlayerControl_RpcSetInfected(__this, infected, method);
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
				if (((Renderer*)player->fields.MyPhysics->fields.rend) == __this) {
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
				auto nameObject = Component_get_gameObject((Component*)player->fields.nameText, NULL);
				if (nameObject == __this) {
					value = true;
				}
			}
		}
	}
	GameObject_SetActive(__this, value, method);
}