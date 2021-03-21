#include "pch-il2cpp.h"
#include "_hooks.h"
#include "game.h"
#include "state.hpp"
#include "esp.hpp"

void dPlayerControl_CompleteTask(PlayerControl* __this, uint32_t idx, MethodInfo* method) {
	std::optional<TaskTypes__Enum> taskType = std::nullopt;

	auto normalPlayerTasks = GetNormalPlayerTasks(__this);
	for (auto normalPlayerTask : normalPlayerTasks)
		if (normalPlayerTask->fields._._Id_k__BackingField == idx) taskType = normalPlayerTask->fields._.TaskType;

	State.events.push_back(new TaskCompletedEvent(GetEventPlayer(__this), taskType, PlayerControl_GetTruePosition(__this, NULL)));
	PlayerControl_CompleteTask(__this, idx, method);
}

void dPlayerControl_FixedUpdate(PlayerControl* __this, MethodInfo* method) {
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
			Transform_set_position(cameraTransform, { cameraVector3.x, cameraVector3.y, 100}, NULL);
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

		if (State.playerToFollow.has_value() && __this == *Game::pLocalPlayer)
		{
			auto mainCamera = Camera_get_main(NULL);

			Transform* cameraTransform = Component_get_transform((Component*)mainCamera, NULL);
			Vector3 cameraVector3 = Transform_get_position(cameraTransform, NULL);
			Vector2 playerVector2 = GetTrueAdjustedPosition(State.playerToFollow.get_PlayerControl());

			Transform_set_position(cameraTransform, { playerVector2.x, playerVector2.y, 100 }, NULL);
		}

		Vector2 localPos = PlayerControl_GetTruePosition(*Game::pLocalPlayer, nullptr);
		ImVec2 localScreenPosition = WorldToScreen(localPos);

		size_t playerIndex = 0;
		for (auto& player : GetAllPlayerControl())
		{
			auto data = GetPlayerData(player);
			if (!data || (!State.ShowEsp_Ghosts && data->fields.IsDead)) continue;
			if (player == *Game::pLocalPlayer) continue;

			Vector2 playerPos = PlayerControl_GetTruePosition(player, nullptr);

			PlayerData playerData;
			playerData.Position = WorldToScreen(playerPos);
			playerData.Color = AmongUsColorToImVec4(GetPlayerColor(data->fields.ColorId));
			playerData.Name = convert_from_string(data->fields.PlayerName);
			playerData.OnScreen = IsWithinScreenBounds(playerPos);
			playerData.Distance = Vector2_Distance(localPos, playerPos, nullptr);

			drawing_t& instance = Esp::GetDrawing();
			std::lock_guard<std::mutex> lock(instance.m_DrawingMutex);
			instance.LocalPosition = localScreenPosition;
			instance.m_Players[playerIndex] = playerData;
			playerIndex++;
		}

		if (State.RainbowName && __this == *Game::pLocalPlayer) {
			// update rainbow colour
			State.RainbowNameColor += State.RainbowSpeed;
			constexpr auto d_pi = 2.f * 3.14159265358979323846f;
			while (State.RainbowNameColor > d_pi) State.RainbowNameColor -= d_pi;
			// apply rainbow colour
			const auto calculate = [](float value) {return std::sin(value) * .5f + .5f; };
			__this->fields.nameText->fields.Color.r = calculate(State.RainbowNameColor + 0.f);
			__this->fields.nameText->fields.Color.g = calculate(State.RainbowNameColor + 2.f);
			__this->fields.nameText->fields.Color.b = calculate(State.RainbowNameColor + 4.f);
			// TODO: add speed slider to State.RainbowSpeed;
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