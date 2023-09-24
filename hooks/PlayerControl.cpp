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
#include "logger.h"

void dPlayerControl_CompleteTask(PlayerControl* __this, uint32_t idx, MethodInfo* method) {
	std::optional<TaskTypes__Enum> taskType = std::nullopt;

	auto normalPlayerTasks = GetNormalPlayerTasks(__this);
	for (auto normalPlayerTask : normalPlayerTasks)
		if (normalPlayerTask->fields._._Id_k__BackingField == idx) taskType = normalPlayerTask->fields._.TaskType;

	synchronized(Replay::replayEventMutex) {
		State.liveReplayEvents.emplace_back(std::make_unique<TaskCompletedEvent>(GetEventPlayerControl(__this).value(), taskType, PlayerControl_GetTruePosition(__this, NULL)));
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
		return app::Color32_op_Implicit(Palette__TypeInfo->static_fields->White, NULL);
	}
}

float dPlayerControl_fixedUpdateTimer = 50;
float dPlayerControl_fixedUpdateCount = 0;
void dPlayerControl_FixedUpdate(PlayerControl* __this, MethodInfo* method) {
	dPlayerControl_fixedUpdateTimer = round(1.f / Time_get_fixedDeltaTime(nullptr));

	if ((IsInGame() || IsInLobby())) {
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

		static int nameDelay = 0;

		if (__this == *Game::pLocalPlayer && !State.userName.empty() && !((State.RevealRoles && GameOptions().GetGameMode() == GameModes__Enum::HideNSeek && GameOptions().GetBool(app::BoolOptionNames__Enum::ShowCrewmateNames) == false) && __this->fields.inVent)) {
			if (State.CustomName) {
				std::string opener = "";
				std::string closer = "";
				if (State.ColoredName && !State.RgbName) {
					std::string colorCode = std::format("<#{:02x}{:02x}{:02x}{:02x}>", int(State.NameColor.x * 255), int(State.NameColor.y * 255), int(State.NameColor.z * 255), int(State.NameColor.w * 255));
					playerName = colorCode + "" + playerName + "</color>";
					opener += colorCode;
					closer += "</color>";
				}
				if (State.RgbName) {
					const auto calculate = [](float value) {return std::sin(value) * .5f + .5f; };
					auto color_r = calculate(State.RgbNameColor + 0.f);
					auto color_g = calculate(State.RgbNameColor + 4.f);
					auto color_b = calculate(State.RgbNameColor + 2.f);
					std::string rgbCode = std::format("<#{:02x}{:02x}{:02x}{:02x}>", int(color_r * 255), int(color_g * 255), int(color_b * 255), int(State.NameColor.w * 255));
					opener += rgbCode;
					closer += "</color>";
				}
				if (State.BoldName) {
					opener += "<b>";
					closer += "</b>";
				}
				if (State.ItalicName) {
					opener += "<i>";
					closer += "</i>";
				}
				if (State.UnderlineName) {
					opener += "<u>";
					closer += "</u>";
				}
				if (State.StrikethroughName) {
					opener += "<s>";
					closer += "</s>";
				}

				playerName = opener + playerName + closer;

				if (nameDelay <= 0 && State.ServerSideCustomName && convert_from_string(GameData_PlayerOutfit_get_PlayerName(GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer)), nullptr)) != playerName) {
					if (IsInGame()) {
						State.rpcQueue.push(new RpcSetName(opener + State.userName + closer));
						nameDelay = 10;
					}
					else if (IsInLobby()) {
						State.lobbyRpcQueue.push(new RpcSetName(opener + State.userName + closer));
						nameDelay = 10;
					}
				}
				else nameDelay--;
			}
		}

		if (State.ShowPlayerInfo && IsInLobby() && !((State.RevealRoles && GameOptions().GetGameMode() == GameModes__Enum::HideNSeek && GameOptions().GetBool(app::BoolOptionNames__Enum::ShowCrewmateNames) == false) && __this->fields.inVent))
		{
			uint32_t playerLevel = playerData->fields.PlayerLevel + 1;
			uint8_t playerId = GetPlayerControlById(playerData->fields.PlayerId)->fields._.OwnerId;
			uint8_t hostId = InnerNetClient_GetHost((InnerNetClient*)(*Game::pAmongUsClient), NULL)->fields.Id;
			std::string levelText = std::format("Level <#0f0>{}</color>", playerLevel);
			std::string friendCode = convert_from_string(playerData->fields.FriendCode);
			if (IsStreamerMode() && friendCode != "")
				friendCode = (convert_from_string(playerData->fields.FriendCode)).substr(0,1) + "...";
			std::string hostFriendCode = convert_from_string(InnerNetClient_GetHost((InnerNetClient*)(*Game::pAmongUsClient), NULL)->fields.FriendCode);
			if (playerId == hostId) {
				if (friendCode == "goatfated#8066")
					playerName = "<size=1.4><#0f0>[HOST]</color> " + State.rgbCode + "[SickoModeAU_Dev] </color><#fff>" + levelText + "</size></color>\n" + playerName + "</color>\n<size=1.4><#0000>0</color><#9ef>" + friendCode + "</color><#0000>0</color>\n<#0000>0";
				else if (friendCode == "" && !IsStreamerMode())
					playerName = "<size=1.4><#0f0>[HOST]</color> " + levelText + "</size></color>\n" + playerName + "</color>\n<size=1.4><#0000>0</color><#9ef>No Friend Code</color><#0000>0</color>\n<#0000>0";
				else
					playerName = "<size=1.4><#0f0>[HOST]</color> " + levelText + "</size></color>\n" + playerName + "</color>\n<size=1.4><#0000>0</color><#9ef>" + friendCode + "</color><#0000>0</color>\n<#0000>0";
			}
			else {
				if (friendCode == "goatfated#8066")
					playerName = "<size=1.4>" + State.rgbCode + "[SickoModeAU_Dev] </color><#fff>" + levelText + "</size></color>\n" + playerName + "</color>\n<size=1.4><#0000>0</color><#9ef>" + friendCode + "</color><#0000>0</color>\n<#0000>0";
				else if (friendCode == "" && !IsStreamerMode())
					playerName = "<size=1.4>" + levelText + "</size></color>\n" + playerName + "</color>\n<size=1.4><#0000>0</color><#9ef>No Friend Code</color><#0000>0</color>\n<#0000>0";
				else
					playerName = "<size=1.4>" + levelText + "</size></color>\n" + playerName + "</color>\n<size=1.4><#0000>0</color><#9ef>" + friendCode + "</color><#0000>0</color>\n<#0000>0";
			}
		}

		if (State.PlayerColoredNames && !((State.RevealRoles && GameOptions().GetGameMode() == GameModes__Enum::HideNSeek && GameOptions().GetBool(app::BoolOptionNames__Enum::ShowCrewmateNames) == false) && __this->fields.inVent))
		{
			playerName = playerName + "</color>";
			Color32&& nameColor = GetPlayerColor(outfit->fields.ColorId);

			playerName = std::format("<#{:02x}{:02x}{:02x}{:02x}>{}",
				nameColor.r, nameColor.g, nameColor.b,
				nameColor.a, playerName);
		}
		if ((IsHost() || !State.SafeMode) && State.TeleportEveryone && (IsInGame() && !State.InMeeting) && State.ShiftRightClickTP && (ImGui::IsKeyPressed(VK_SHIFT) || ImGui::IsKeyDown(VK_SHIFT)) && (ImGui::IsKeyPressed(0x12) || ImGui::IsKeyDown(0x12)) && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
			ImVec2 mouse = ImGui::GetMousePos();
			Vector2 target = {
				(mouse.x - DirectX::GetWindowSize().x / 2) + DirectX::GetWindowSize().x / 2,
				((mouse.y - DirectX::GetWindowSize().y / 2) - DirectX::GetWindowSize().y / 2) * -1.0f
			};
			for (auto player : GetAllPlayerControl())
				State.rpcQueue.push(new RpcForceSnapTo(player, ScreenToWorld(target)));
		}
		else if ((IsHost() || !State.SafeMode) && State.TeleportEveryone && IsInLobby() && State.ShiftRightClickTP && (ImGui::IsKeyPressed(VK_SHIFT) || ImGui::IsKeyDown(VK_SHIFT)) && (ImGui::IsKeyPressed(0x12) || ImGui::IsKeyDown(0x12)) && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
			ImVec2 mouse = ImGui::GetMousePos();
			Vector2 target = {
				(mouse.x - DirectX::GetWindowSize().x / 2) + DirectX::GetWindowSize().x / 2,
				((mouse.y - DirectX::GetWindowSize().y / 2) - DirectX::GetWindowSize().y / 2) * -1.0f
			};
			for (auto player : GetAllPlayerControl())
				State.lobbyRpcQueue.push(new RpcForceSnapTo(player, ScreenToWorld(target)));
		}

		if ((IsHost() || !State.SafeMode) && State.RotateEveryone && !State.TeleportEveryone && __this != *Game::pLocalPlayer) {
			static float f = 0.f;
			static float rotateDelay = 0;
			if (rotateDelay <= 0) {
				Vector2 position = GetTrueAdjustedPosition(*Game::pLocalPlayer);
				float num = (State.RotateRadius * cos(f)) + position.x;
				float num2 = (State.RotateRadius * sin(f)) + position.y;
				Vector2 target = {num, num2};
				if (IsInGame()) {
					for (auto player : GetAllPlayerControl()) {
						if (player != *Game::pLocalPlayer)
							State.rpcQueue.push(new RpcForceSnapTo(player, target));
					}
				}
				else if (IsInLobby()) {
					for (auto player : GetAllPlayerControl()) {
						if (player != *Game::pLocalPlayer)
							State.lobbyRpcQueue.push(new RpcForceSnapTo(player, target));
					}
				}
				rotateDelay = 25 * float(GetAllPlayerControl().size());
				f += 36 * 0.017453292f;
			}
			else {
				rotateDelay--;
			}
		}
		if (!State.SafeMode && State.ChatSpam && (IsInGame() || IsInLobby())) {
			static float spamDelay = 0;
			if (spamDelay <= 0 && (__this == ((!State.SafeMode && State.playerToChatAs.has_value()) ? GetPlayerControlById(State.playerToChatAs.get_PlayerId()) : *Game::pLocalPlayer) || State.ChatSpamEveryone)) {
				if (IsInGame()) {
					for (auto player : GetAllPlayerControl())
						State.rpcQueue.push(new RpcChatMessage(player, State.chatMessage));
				}
				else if (IsInLobby()) {
					for (auto player : GetAllPlayerControl())
						State.lobbyRpcQueue.push(new RpcChatMessage(player, State.chatMessage));
				}
				spamDelay = 25 * float(GetAllPlayerControl().size());
			}
			else spamDelay--;
		}

		if (IsInGame() && State.RevealRoles && !((State.RevealRoles && GameOptions().GetGameMode() == GameModes__Enum::HideNSeek && GameOptions().GetBool(app::BoolOptionNames__Enum::ShowCrewmateNames) == false) && __this->fields.inVent))
		{
			std::string roleName = GetRoleName(playerData->fields.Role, State.AbbreviatedRoleNames);
			int completedTasks = 0;
			int totalTasks = 0;
			auto tasks = GetNormalPlayerTasks(__this);
			for (auto task : tasks)
			{
				if (task->fields.taskStep == task->fields.MaxStep) {
					completedTasks++;
					totalTasks++;
				}
				else
					totalTasks++;
			}
			Color32&& roleColor = app::Color32_op_Implicit(GetRoleColor(playerData->fields.Role), NULL);
			if (totalTasks == 0 || PlayerIsImpostor(playerData)) {
				playerName = "<size=1.4>" + roleName + "\n</size>" + playerName + "\n<size=1.4><#0000>0</color>";
				playerName = std::format("<#{:02x}{:02x}{:02x}{:02x}>{}",
					roleColor.r, roleColor.g, roleColor.b,
					roleColor.a, playerName);
			}
			else {
				playerName = "\n</size>" + playerName + "\n<size=1.4><#0000>0</color>";
				playerName = std::format("<#{:02x}{:02x}{:02x}{:02x}><size=1.4>{} ({:d}/{:d}) {}",
					roleColor.r, roleColor.g, roleColor.b,
					roleColor.a, roleName, completedTasks, totalTasks, playerName);
			}
		}
		if (IsInGame() && State.ShowKillCD
			&& !playerData->fields.IsDead
			&& playerData->fields.Role
			&& playerData->fields.Role->fields.CanUseKillButton
			&& !((State.RevealRoles && GameOptions().GetGameMode() == GameModes__Enum::HideNSeek && GameOptions().GetBool(app::BoolOptionNames__Enum::ShowCrewmateNames) == false) && __this->fields.inVent)) {
			if (State.RevealRoles) {
				float killTimer = __this->fields.killTimer;
				Color32&& color = GetKillCooldownColor(killTimer);
				playerName += std::format("<size=1.4><#{:02x}{:02x}{:02x}{:02x}>Cooldown: {:.2f}s<#0000>0",
					color.r, color.g, color.b, color.a,
					killTimer);
			}
			else {
				float killTimer = __this->fields.killTimer;
				Color32&& color = GetKillCooldownColor(killTimer);
				playerName = "<size=1.4><#0000>0\n</color></size>" + playerName;
				playerName += std::format("\n<size=1.4><#{:02x}{:02x}{:02x}{:02x}>Cooldown: {:.2f}s",
					color.r, color.g, color.b, color.a,
					killTimer);
			}
		}

		if (IsInGame() && (State.RevealRoles && GameOptions().GetGameMode() == GameModes__Enum::HideNSeek && !(GameOptions().GetBool(app::BoolOptionNames__Enum::ShowCrewmateNames))) && __this->fields.inVent) {
			playerName = "<#0000>" +playerName + "</color>";
		}
		else {
			playerName = playerName; //failsafe
		}

		if (IsHost() && State.ForceColorForEveryone)
		{
			static float forceColorDelay = 0;
			for (auto player : GetAllPlayerControl()) {
				if (forceColorDelay <= 0) {				
						app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(player));
						auto colorId = outfit->fields.ColorId;
						if (IsInGame() && colorId != State.HostSelectedColorId)
							State.rpcQueue.push(new RpcForceColor(player, State.HostSelectedColorId, true));
						else if (IsInLobby() && colorId != State.HostSelectedColorId)
							State.lobbyRpcQueue.push(new RpcForceColor(player, State.HostSelectedColorId, true));
						forceColorDelay = State.CycleDuration * GetAllPlayerControl().size();
				}
				else {
					forceColorDelay--;
				}
			}
		}

		if ((IsHost() || !State.SafeMode) && State.Cycler && State.CycleForEveryone && State.RandomColor)
		{
			static float cycleColorDelay = 0;
				if (cycleColorDelay <= 0) {
					for (auto player : GetAllPlayerControl()) {
						if (IsInGame())
							State.rpcQueue.push(new RpcForceColor(player, randi(0, 17)));
						else if (IsInLobby())
							State.lobbyRpcQueue.push(new RpcForceColor(player, randi(0, 17)));
					}
					cycleColorDelay = State.CycleDuration * GetAllPlayerControl().size();
				}
				else {
					cycleColorDelay--;
				}
		}

		if ((IsHost() || !State.SafeMode) && State.ForceNameForEveryone) {
			static float forceNameDelay = 0;
			if (forceNameDelay <= 0) {
				for (auto player : GetAllPlayerControl()) {
					app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(player));
					std::string playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
					std::string playerId = std::format("{}", player->fields.PlayerId);
					std::string newName = State.hostUserName + "<size=0>" + playerId + "</size>";
					if (IsInGame() && playerName != newName)
						State.rpcQueue.push(new RpcForceName(player, State.hostUserName + "<size=0>" + playerId + "</size>"));
					else if (IsInLobby() && (playerName.find(State.hostUserName) == std::string::npos))
						State.lobbyRpcQueue.push(new RpcForceName(player, State.hostUserName + "<size=0>" + playerId + "</size>"));
				}
				forceNameDelay = State.CycleDuration * GetAllPlayerControl().size();
			}
			else {
				forceNameDelay--;
			}
		}


		if ((IsHost() || !State.SafeMode) && State.Cycler && State.CycleForEveryone && State.CycleName)
		{
			static int nameCtr = 1;
			static float cycleNameDelay = 0;
			if (cycleNameDelay <= 0 && !State.userName1.empty() && !State.userName2.empty()) {
				if (nameCtr == 2) {
					if (IsInGame()) {
						for (auto player : GetAllPlayerControl())
							State.rpcQueue.push(new RpcForceName(player, State.userName1));
					}
					else if (IsInLobby()) {
						for (auto player : GetAllPlayerControl())
							State.lobbyRpcQueue.push(new RpcForceName(player, State.userName1));
					}
					cycleNameDelay = State.CycleDuration * GetAllPlayerControl().size();
					nameCtr = 1;
				}
				else if (nameCtr == 1) {
					if (IsInGame()) {
						for (auto player : GetAllPlayerControl())
							State.rpcQueue.push(new RpcForceName(player, State.userName2));
					}
					else if (IsInLobby()) {
						for (auto player : GetAllPlayerControl())
							State.lobbyRpcQueue.push(new RpcForceName(player, State.userName2));
					}
					cycleNameDelay = State.CycleDuration * GetAllPlayerControl().size();
					nameCtr = 2;
				}
			}
			else {
				cycleNameDelay--;
			}
		}
		
		String* playerNameStr = convert_to_string(playerName);
		app::TMP_Text_set_text((app::TMP_Text*)nameTextTMP, playerNameStr, NULL);

		if (IsColorBlindMode()) {
			// TODO: Adjust the position of nameTextTMP
		}

		// SeeProtect
		do {
			if (!__this->fields.protectedByGuardian)
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
				app::PlayerControl_TurnOnProtection(__this, State.ShowProtections, pair.first, nullptr);
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
				if(State.EnableZoom && !State.InMeeting && (IsInGame() || IsInLobby())) //chat button disappears after meeting
					Camera_set_orthographicSize(State.FollowerCam, State.CameraHeight * 3, NULL);
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
			if (GetKeyboardState(arr) && !State.ChatFocused)
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

			Transform_set_position(cameraTransform, { State.camPos.x, State.camPos.y }, NULL);
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

			if (IsInGame() && !State.InMeeting)
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
				espPlayerData.Color = (State.ShowEsp_RoleBased == true && IsInGame()) ? AmongUsColorToImVec4(GetRoleColor(playerData->fields.Role))
					: AmongUsColorToImVec4(GetPlayerColor(outfit->fields.ColorId));
				espPlayerData.Name = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
			}
			else
			{
				espPlayerData.Color = (State.ShowEsp_RoleBased == true && IsInGame()) ? AmongUsColorToImVec4(GetRoleColor(playerData->fields.Role))
					: ImVec4(0.f, 0.f, 0.f, 1.f);
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

bool dPlayerControl_get_CanMove(PlayerControl* __this, MethodInfo* method) {
	if (((State.AlwaysMove) || (State.MoveInVent && (((*Game::pLocalPlayer)->fields.inVent) || ((*Game::pLocalPlayer)->fields.shapeshifting)))) && !State.ChatFocused && !((*Game::pLocalPlayer)->fields.petting))
		return true;
	return PlayerControl_get_CanMove(__this, method);
}

void dPlayerControl_OnGameStart(PlayerControl* __this,  MethodInfo* method) {
	SaveGameOptions();
	if (__this == *Game::pLocalPlayer && State.confuser && State.confuseOnStart)
		ControlAppearance(true);
	PlayerControl_OnGameStart(__this, method);
}

void dPlayerControl_MurderPlayer(PlayerControl* __this, PlayerControl* target, MethodInfo* method)
{
	if (!PlayerIsImpostor(GetPlayerData(__this)) || PlayerIsImpostor(GetPlayerData(target))) {
		synchronized(Replay::replayEventMutex) {
			State.liveReplayEvents.emplace_back(std::make_unique<CheatDetectedEvent>(GetEventPlayerControl(__this).value(), CHEAT_ACTIONS::CHEAT_KILL_IMPOSTOR));
		}
	}
	synchronized(Replay::replayEventMutex) {
		State.liveReplayEvents.emplace_back(std::make_unique<KillEvent>(GetEventPlayerControl(__this).value(), GetEventPlayerControl(target).value(), PlayerControl_GetTruePosition(__this, NULL), PlayerControl_GetTruePosition(target, NULL)));
		State.replayDeathTimePerPlayer[target->fields.PlayerId] = std::chrono::system_clock::now();
	}

	// ESP: Reset Kill Cooldown
	if (__this->fields._.OwnerId != (*Game::pAmongUsClient)->fields._.ClientId) {
		if (!target || target->fields.protectedByGuardian == false)
			__this->fields.killTimer = (std::max)(GameOptions().GetKillCooldown(), 0.f);
		else
			__this->fields.killTimer = (std::max)(GameOptions().GetKillCooldown() * 0.5f, 0.f);
		//STREAM_DEBUG("Player " << ToString(__this) << " KillTimer " << __this->fields.killTimer);
	}

	do {
		if (!State.ShowProtections) break;
		if (!target || target->fields.protectedByGuardian == false)
			break;
		if (__this->fields._.OwnerId == (*Game::pAmongUsClient)->fields._.ClientId)
			break; // AmKiller
		if (auto localData = GetPlayerData(*Game::pLocalPlayer);
			!localData || !localData->fields.Role
			|| localData->fields.Role->fields.Role == RoleTypes__Enum::GuardianAngel)
			break; // AmAngel
		PlayerControl_ShowFailedMurder(target, nullptr);
		target->fields.protectedByGuardian = true;
	} while (false);
	PlayerControl_MurderPlayer(__this, target, method);
	if (__this == *Game::pLocalPlayer && State.confuser && State.confuseOnKill)
		ControlAppearance(true);
}

void dPlayerControl_CmdCheckMurder(PlayerControl* __this, PlayerControl* target, MethodInfo* method)
{
	PlayerControl_RpcMurderPlayer(__this, target, method);
}

void dPlayerControl_RpcShapeshift(PlayerControl* __this, PlayerControl* target, bool animate, MethodInfo* method)
{
	PlayerControl_RpcShapeshift(__this, target, !State.AnimationlessShapeshift, method);
}

void dPlayerControl_RpcRevertShapeshift(PlayerControl* __this, bool animate, MethodInfo* method)
{
	if (__this == *Game::pLocalPlayer && GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer)) == GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer), true))
		return;
	if (!animate)
		PlayerControl_RpcRevertShapeshift(__this, false, method);
	if (animate)
		PlayerControl_RpcRevertShapeshift(__this, !State.AnimationlessShapeshift, method);
}

void dPlayerControl_StartMeeting(PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method)
{
	if (State.DisableMeetings) {
		return;
	}
	else {
		synchronized(Replay::replayEventMutex) {
			State.liveReplayEvents.emplace_back(std::make_unique<ReportDeadBodyEvent>(GetEventPlayerControl(__this).value(), GetEventPlayer(target), PlayerControl_GetTruePosition(__this, NULL), GetTargetPosition(target)));
		}
		app::PlayerControl_StartMeeting(__this, target, method);
	}
}

void dPlayerControl_HandleRpc(PlayerControl* __this, uint8_t callId, MessageReader* reader, MethodInfo* method) {
	HandleRpc(callId, reader);
	PlayerControl_HandleRpc(__this, callId, reader, NULL);
}

void dRenderer_set_enabled(Renderer* __this, bool value, MethodInfo* method)
{
	//If we're already rendering it, lets skip checking if we should
	if ((IsInGame() || IsInLobby()) && !value && State.ShowGhosts)
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
	if ((IsInGame() || IsInLobby()) && !value) { //If we're already rendering it, lets skip checking if we should
		for (auto player : GetAllPlayerControl()) {
			auto playerInfo = GetPlayerData(player);
			if (!playerInfo || !player->fields.cosmetics) break; //This happens sometimes during loading
			if ((playerInfo->fields.IsDead && State.ShowGhosts) || (State.RevealRoles && GameOptions().GetGameMode() == GameModes__Enum::HideNSeek && GameOptions().GetBool(app::BoolOptionNames__Enum::ShowCrewmateNames) == false))
			{
				auto nameObject = Component_get_gameObject((Component_1*)player->fields.cosmetics->fields.nameText, NULL);
				if (nameObject == __this) {
					value = true;
					break;
				}
			}
			else if (!State.RevealRoles && GameOptions().GetGameMode() == GameModes__Enum::HideNSeek && GameOptions().GetBool(app::BoolOptionNames__Enum::ShowCrewmateNames) == false) {
				auto nameObject = Component_get_gameObject((Component_1*)player->fields.cosmetics->fields.nameText, NULL);
				if (nameObject == __this) {
					value = false;
					break;
				}
			}
		}
	}
	GameObject_SetActive(__this, value, method);
}

void dPlayerControl_CmdReportDeadBody(PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method) {
	if (State.DisableMeetings) {
		return;
	}
	else {
		PlayerControl_CmdReportDeadBody(__this, target, method);
	}
}

void dPlayerControl_RpcStartMeeting(PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method) {
	if (State.DisableMeetings) {
		return;
	}
	else {
		PlayerControl_RpcStartMeeting(__this, target, method);
	}
}

void dPlayerControl_Shapeshift(PlayerControl* __this, PlayerControl* target, bool animate, MethodInfo* method) {
	synchronized(Replay::replayEventMutex) {
		State.liveReplayEvents.emplace_back(std::make_unique<ShapeShiftEvent>(GetEventPlayerControl(__this).value(), GetEventPlayerControl(target).value()));
	}
	PlayerControl_Shapeshift(__this, target, animate, method);
}

void dPlayerControl_ProtectPlayer(PlayerControl* __this, PlayerControl* target, int32_t colorId, MethodInfo* method) {
	if (SYNCHRONIZED(Replay::replayEventMutex); target != nullptr) {
		State.liveReplayEvents.emplace_back(std::make_unique<ProtectPlayerEvent>(GetEventPlayerControl(__this).value(), GetEventPlayerControl(target).value()));
	}
	else {
		LOG_ERROR("target is null"); // TownOfHost
	}
	PlayerControl_ProtectPlayer(__this, target, colorId, method);
}

void dPlayerControl_TurnOnProtection(PlayerControl* __this, bool visible, int32_t colorId, MethodInfo* method) {
	app::PlayerControl_TurnOnProtection(__this, visible || State.ShowProtections, colorId, method);
	std::pair pair { colorId, app::Time_get_time(nullptr) };
	synchronized(State.protectMutex) {
		State.protectMonitor[__this->fields.PlayerId] = pair;
	}
}