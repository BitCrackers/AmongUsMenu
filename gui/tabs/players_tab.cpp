#include "pch-il2cpp.h"
#include "players_tab.h"
#include "game.h"
#include "state.hpp"
#include "utility.h"
#include "gui-helpers.hpp"

namespace PlayersTab {

	int framesPassed = -1;
	Vector2 previousPlayerPosition;

	void Render() {
		if (IsInGame() || IsInLobby()) {
			if (ImGui::BeginTabItem("Players")) {
				ImGui::BeginChild("players#list", ImVec2(200, 0) * State.dpiScale, true);
				auto selectedPlayer = State.selectedPlayer.validate();
				bool shouldEndListBox = ImGui::ListBoxHeader("###players#list", ImVec2(200, 150) * State.dpiScale);
				auto localData = GetPlayerData(*Game::pLocalPlayer);
				for (auto playerData : GetAllPlayerData()) {
					if (playerData->fields.Disconnected)
						continue;

					app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);
					if (outfit == NULL) continue;
					std::string playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0) * State.dpiScale);
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0) * State.dpiScale);
					if (ImGui::Selectable(std::string("##" + playerName).c_str(), selectedPlayer.equals(playerData))) {
						State.selectedPlayer = PlayerSelection(playerData);
						selectedPlayer = State.selectedPlayer.validate();
					}
					ImGui::SameLine();
					ImGui::ColorButton(std::string("##" + playerName + "_ColorButton").c_str(), AmongUsColorToImVec4(GetPlayerColor(outfit->fields.ColorId)), ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
					ImGui::SameLine();
					ImGui::PopStyleVar(2);
					ImGui::Dummy(ImVec2(0, 0) * State.dpiScale);
					ImGui::SameLine();

					ImVec4 nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->White);
					if (State.RevealRoles && IsInGame())
					{
						std::string roleName = GetRoleName(playerData->fields.Role);
						playerName = playerName + " (" + roleName + ")";
						nameColor = AmongUsColorToImVec4(GetRoleColor(playerData->fields.Role));
					}
					else if (PlayerIsImpostor(localData) && PlayerIsImpostor(playerData))
						nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->ImpostorRed);
					//else if (std::count(State.aumUsers.begin(), State.aumUsers.end(), playerData->fields.PlayerId))
						//nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->Orange);

					if (playerData->fields.IsDead)
						nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->DisabledGrey);

					ImGui::TextColored(nameColor, playerName.c_str());
				}
				if (shouldEndListBox)
					ImGui::ListBoxFooter();

				if (selectedPlayer.has_value()) //Upon first startup no player is selected.  Also rare case where the playerdata is deleted before the next gui cycle
				{
					//ImGui::Text("Is using AUM: %s", std::count(State.aumUsers.begin(), State.aumUsers.end(), selectedPlayer.get_PlayerData()->fields.PlayerId) ? "Yes" : "No");
					std::uint8_t playerId = selectedPlayer.get_PlayerData()->fields.PlayerId;
					std::string playerIdText = std::format("Player ID: {}", playerId);
					ImGui::Text(const_cast<char*>(playerIdText.c_str()));
					std::string friendCode = convert_from_string(selectedPlayer.get_PlayerData()->fields.FriendCode);
					std::string friendCodeText = std::format("Friend Code: {}", (!IsStreamerMode()) ? friendCode : ((friendCode != "") ? friendCode.substr(0,1) + "..." : ""));
					if (friendCode != "") {
						ImGui::Text(const_cast<char*>(friendCodeText.c_str()));
					}
					uint32_t playerLevel = selectedPlayer.get_PlayerData()->fields.PlayerLevel + 1;
					std::string levelText = std::format("Level: {}", playerLevel);
					ImGui::Text(const_cast<char*>(levelText.c_str()));
					std::string platform = "";
					for (auto client : GetAllClients()) {
						if (GetPlayerControlById(selectedPlayer.get_PlayerData()->fields.PlayerId)->fields._.OwnerId == client->fields.Id) {
							platform = convert_from_string(client->fields.PlatformData->fields.PlatformName);
							break;
						}
					}
					std::string platformText = std::format("Platform:{}", platform);
					ImGui::Text(const_cast<char*>(platformText.c_str()));
					if (!IsStreamerMode()) {
						std::string puidText = std::format("Product User ID:\n{}", convert_from_string(selectedPlayer.get_PlayerData()->fields.Puid));
						ImGui::Text(const_cast<char*>(puidText.c_str()));
					}
				}

				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("players#actions", ImVec2(200, 0) * State.dpiScale, true);
				if (State.DisableSabotages)
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Meetings have been disabled.");
				GameOptions options;
				if (IsInGame() && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) { //Player selection doesn't matter
					if (!State.InMeeting) {
						if (ImGui::Button("Call Meeting")) {
							State.rpcQueue.push(new RpcReportPlayer(PlayerSelection()));
						}
					}
					else {
						if (ImGui::Button("Call Meeting")) {
							State.rpcQueue.push(new RpcForceMeeting(*Game::pLocalPlayer, PlayerSelection()));
						}
					}
				}
				if (selectedPlayer.has_value() && IsInGame() && !GetPlayerData(selectedPlayer.get_PlayerControl())->fields.IsDead && (IsHost() || !State.SafeMode)) { //Player selection doesn't matter
					ImGui::SameLine();
					if (!State.InMeeting) {
						if (ImGui::Button("Force Meeting By")) {
							State.rpcQueue.push(new RpcForceReportPlayer(selectedPlayer.get_PlayerControl(), PlayerSelection()));
						}
					}
					else {
						if (ImGui::Button("Force Meeting By")) {
							State.rpcQueue.push(new RpcForceMeeting(selectedPlayer.get_PlayerControl(), PlayerSelection()));
						}
					}
				}
				if (State.activeImpersonation)
				{
					if (ImGui::Button("Reset Impersonation"))
					{
						std::queue<RPCInterface*>* queue = nullptr;

						if (IsInGame())
							queue = &State.rpcQueue;
						else if (IsInLobby())
							queue = &State.lobbyRpcQueue;
						if (queue != nullptr) {
							if (IsHost() || !State.SafeMode)
								queue->push(new RpcForceColor(*Game::pLocalPlayer, State.originalColor, true));
							else
								queue->push(new RpcSetColor(State.originalColor));
							queue->push(new RpcSetPet(State.originalPet));
							queue->push(new RpcSetSkin(State.originalSkin));
							queue->push(new RpcSetHat(State.originalHat));
							queue->push(new RpcSetVisor(State.originalVisor));
							queue->push(new RpcSetNamePlate(State.originalNamePlate));
							queue->push(new RpcSetName(State.originalName));
							State.activeImpersonation = false;
						}
					}
				}
				if (selectedPlayer.has_value())
				{
					if (IsInGame()) {
						ImGui::NewLine();
						if (!State.InMeeting) {
							if (ImGui::Button("Report Body") && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) {
								State.rpcQueue.push(new RpcReportPlayer(State.selectedPlayer));
							}
						}
						else {
							if (ImGui::Button("Report Body") && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) {
								State.rpcQueue.push(new RpcForceMeeting(*Game::pLocalPlayer, State.selectedPlayer));
							}
						}
					}
					if (selectedPlayer.has_value() && IsInGame() && (IsHost() || !State.SafeMode)) {
						ImGui::SameLine();
						if (!State.InMeeting) {
							if (ImGui::Button("Self-Report") && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) {
								State.rpcQueue.push(new RpcForceReportPlayer(selectedPlayer.get_PlayerControl(), State.selectedPlayer));
							}
						}
						else {
							if (ImGui::Button("Self-Report") && !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead) {
								State.rpcQueue.push(new RpcForceMeeting(selectedPlayer.get_PlayerControl(), State.selectedPlayer));
							}
						}
					}
					ImGui::NewLine();

					if (!selectedPlayer.is_Disconnected())
					{
						if (State.playerToFollow.equals(State.selectedPlayer) || selectedPlayer.is_LocalPlayer()) {
							if (ImGui::Button("Stop Spectating")) {
								State.playerToFollow = PlayerSelection();
							}
						}
						else {
							if (!selectedPlayer.is_LocalPlayer() && ImGui::Button("Spectate")) {
								State.FreeCam = false;
								State.playerToFollow = State.selectedPlayer;
							}
						}
					}

					if (selectedPlayer.is_LocalPlayer() && State.originalName != "-") {
						if (ImGui::Button("Reset Name")) {
							if (IsInGame())
								State.rpcQueue.push(new RpcSetName(State.originalName));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new RpcSetName(State.originalName));
						}
					}
					else if (!selectedPlayer.is_LocalPlayer()) {
						if ((IsInMultiplayerGame() || IsInLobby()) && ImGui::Button("Steal Name")) {
							ImpersonateName(State.selectedPlayer);
						}
					}
					if ((IsInGame() || IsInLobby())) {
						if (!selectedPlayer.is_LocalPlayer()) {
							app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(selectedPlayer.get_PlayerData());
							if (outfit != NULL) {
								if (ImGui::Button("Impersonate")) {

									auto petId = outfit->fields.PetId;
									auto skinId = outfit->fields.SkinId;
									auto hatId = outfit->fields.HatId;
									auto visorId = outfit->fields.VisorId;
									auto colorId = outfit->fields.ColorId;
									auto namePlateId = outfit->fields.NamePlateId;
									std::queue<RPCInterface*>* queue = nullptr;

									if (IsInGame())
										queue = &State.rpcQueue;
									else if (IsInLobby())
										queue = &State.lobbyRpcQueue;

									if (queue != nullptr) {
										if (IsHost() || !State.SafeMode)
											queue->push(new RpcForceColor(*Game::pLocalPlayer, colorId, true));
										else
											queue->push(new RpcSetColor(GetRandomColorId()));
										queue->push(new RpcSetPet(petId));
										queue->push(new RpcSetSkin(skinId));
										queue->push(new RpcSetVisor(visorId));
										queue->push(new RpcSetHat(hatId));
										queue->push(new RpcSetNamePlate(namePlateId));
										ImpersonateName(State.selectedPlayer);
										State.activeImpersonation = true;
									}
								}
							}
						}
					}

					if (IsInGame() && PlayerIsImpostor(GetPlayerData(*Game::pLocalPlayer))
						&& !selectedPlayer.get_PlayerData()->fields.IsDead
						&& !selectedPlayer.get_PlayerControl()->fields.inVent
						&& !selectedPlayer.get_PlayerControl()->fields.inMovingPlat
						&& !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead && ((*Game::pLocalPlayer)->fields.killTimer <= 0.0f)
						&& selectedPlayer.get_PlayerControl()->fields.protectedByGuardianId < 0
						&& !State.InMeeting)
					{
						if (ImGui::Button("Kill"))
						{
							State.rpcQueue.push(new CmdCheckMurder(State.selectedPlayer));
						}
					}
					else {// if (!State.SafeMode)
						if (ImGui::Button("Kill"))
						{
							if (IsInGame()) {
								State.rpcQueue.push(new RpcMurderPlayer((*Game::pLocalPlayer), selectedPlayer.get_PlayerControl()));
							}
							else if (IsInLobby()) {
								State.lobbyRpcQueue.push(new RpcMurderPlayer((*Game::pLocalPlayer), selectedPlayer.get_PlayerControl()));
							}
						}
					}
					if (IsInGame() && PlayerIsImpostor(GetPlayerData(*Game::pLocalPlayer))
						&& !selectedPlayer.get_PlayerData()->fields.IsDead
						&& !selectedPlayer.get_PlayerControl()->fields.inVent
						&& !selectedPlayer.get_PlayerControl()->fields.inMovingPlat
						&& !GetPlayerData(*Game::pLocalPlayer)->fields.IsDead && ((*Game::pLocalPlayer)->fields.killTimer <= 0.0f)
						&& selectedPlayer.get_PlayerControl()->fields.protectedByGuardianId < 0
						&& !State.InMeeting)
					{
						ImGui::SameLine();
						if (ImGui::Button("Telekill"))
						{
							previousPlayerPosition = GetTrueAdjustedPosition(*Game::pLocalPlayer);
							State.rpcQueue.push(new CmdCheckMurder(State.selectedPlayer));
							framesPassed = 40;
						}
					}
					else {// if (!State.SafeMode)
						ImGui::SameLine();
						if (ImGui::Button("Telekill"))
						{
							previousPlayerPosition = GetTrueAdjustedPosition(*Game::pLocalPlayer);
							if (IsInGame()) {
								State.rpcQueue.push(new RpcMurderPlayer((*Game::pLocalPlayer), selectedPlayer.get_PlayerControl()));
							}
							else if (IsInLobby()) {
								State.lobbyRpcQueue.push(new RpcMurderPlayer((*Game::pLocalPlayer), selectedPlayer.get_PlayerControl()));
							}
							framesPassed = 40;
						}
					}
					if (!State.SafeMode) {
						ImGui::SameLine();
						if (ImGui::Button("Suicide")) {
							if (IsInGame()) {
								State.rpcQueue.push(new RpcMurderPlayer(selectedPlayer.get_PlayerControl(), selectedPlayer.get_PlayerControl()));
							}
							else if (IsInLobby()) {
								State.lobbyRpcQueue.push(new RpcMurderPlayer(selectedPlayer.get_PlayerControl(), selectedPlayer.get_PlayerControl()));
							}
						}
					}

					static int murderCount = 0;
					static bool murderLoop = false;
					static int murderDelay = 0;
					if (ImGui::Button("Murder Loop")) {
						murderLoop = true;
						murderCount = 20; //controls how many times the player is to be murdered
					}

					if (murderDelay <= 0) {
						if (murderCount > 0 && selectedPlayer.has_value()) {
							if (IsInGame()) {
								State.rpcQueue.push(new RpcMurderPlayer(*Game::pLocalPlayer, selectedPlayer.get_PlayerControl()));
								murderDelay = 15;
							}
							else if (IsInLobby()) {
								State.lobbyRpcQueue.push(new RpcMurderPlayer(*Game::pLocalPlayer, selectedPlayer.get_PlayerControl()));
								murderDelay = 15;
							}
							murderCount--;
						}
						else {
							murderLoop = false;
							murderCount = 0;
						}
					}
					else murderDelay--;

					static int suicideCount = 0;
					static bool suicideLoop = false;
					static int suicideDelay = 0;
					if (IsHost() || !State.SafeMode) {
						ImGui::SameLine();
						if (ImGui::Button("Suicide Loop")) {
							suicideLoop = true;
							suicideCount = 20; //controls how many times the player is to be suicided
						}

						if (suicideDelay <= 0) {
							if (suicideCount > 0 && selectedPlayer.has_value()) {
								if (IsInGame()) {
									State.rpcQueue.push(new RpcMurderPlayer(selectedPlayer.get_PlayerControl(), selectedPlayer.get_PlayerControl()));
									suicideDelay = 15;
								}
								else if (IsInLobby()) {
									State.lobbyRpcQueue.push(new RpcMurderPlayer(selectedPlayer.get_PlayerControl(), selectedPlayer.get_PlayerControl()));
									suicideDelay = 15;
								}
								suicideCount--;
							}
							else {
								suicideLoop = false;
								suicideCount = 0;
							}
						}
						else suicideDelay--;
					}

					if ((IsHost() || !State.SafeMode) || selectedPlayer.is_LocalPlayer()) {
						if (ImGui::Button("Kill Crewmates By")) {
							for (auto player : GetAllPlayerControl()) {
								if (!PlayerIsImpostor(GetPlayerData(player))) {
									if (IsInGame())
										State.rpcQueue.push(new RpcMurderPlayer(selectedPlayer.get_PlayerControl(), player));
									else if (IsInLobby())
										State.lobbyRpcQueue.push(new RpcMurderPlayer(selectedPlayer.get_PlayerControl(), player));
								}
							}
						}
						ImGui::SameLine();
						if (ImGui::Button("Kill Impostors By")) {
							for (auto player : GetAllPlayerControl()) {
								if (PlayerIsImpostor(GetPlayerData(player))) {
									if (IsInGame())
										State.rpcQueue.push(new RpcMurderPlayer(selectedPlayer.get_PlayerControl(), player));
									else if (IsInLobby())
										State.lobbyRpcQueue.push(new RpcMurderPlayer(selectedPlayer.get_PlayerControl(), player));
								}
							}
						}
					}

					if ((IsHost() || !State.SafeMode) && State.InMeeting) {
						if (ImGui::Button("Vote Off")) {
							for (auto player : GetAllPlayerControl()) {
								if (player != selectedPlayer.get_PlayerControl()) {
									State.rpcQueue.push(new RpcClearVote(player));
								}
								State.rpcQueue.push(new RpcVotePlayer(player, selectedPlayer.get_PlayerControl()));
							}
							State.rpcQueue.push(new RpcEndMeeting());
							State.InMeeting = false;
						}
						ImGui::SameLine();
						if (ImGui::Button("Skip Vote by All")) {
							for (auto player : GetAllPlayerControl()) {
								if (player != selectedPlayer.get_PlayerControl()) {
									State.rpcQueue.push(new RpcClearVote(player));
								}
								State.rpcQueue.push(new RpcVotePlayer(player, player, true));
							}
							State.rpcQueue.push(new RpcEndMeeting());
							State.InMeeting = false;
						}
					}

					if (IsHost() && ImGui::Button("Kick")) {
						app::InnerNetClient_KickPlayer((InnerNetClient*)(*Game::pAmongUsClient), selectedPlayer.get_PlayerControl()->fields._.OwnerId, false, NULL);
					}
					if (ImGui::Button("Votekick")) {
						if (IsInGame()) {
							for (auto player : GetAllPlayerControl())
								State.rpcQueue.push(new RpcVoteKick(selectedPlayer.get_PlayerControl()));
						}
						else if (IsInLobby()) {
							for (auto player : GetAllPlayerControl())
								State.rpcQueue.push(new RpcVoteKick(selectedPlayer.get_PlayerControl()));
						}
					}
					ImGui::SameLine();
					if (ImGui::Button("Ban")) {
						app::InnerNetClient_KickPlayer((InnerNetClient*)(*Game::pAmongUsClient), selectedPlayer.get_PlayerControl()->fields._.OwnerId, true, NULL);
					}

					if (framesPassed == 0)
					{
						if (IsInGame())
							State.rpcQueue.push(new RpcSnapTo(previousPlayerPosition));
						else if (IsInLobby())
							State.lobbyRpcQueue.push(new RpcSnapTo(previousPlayerPosition));
						framesPassed--;
					}
					else framesPassed--;

					app::RoleBehaviour* playerRole = localData->fields.Role;
					app::RoleTypes__Enum role = playerRole != nullptr ? playerRole->fields.Role : app::RoleTypes__Enum::Crewmate;

					if (role == RoleTypes__Enum::Shapeshifter || !State.SafeMode)
					{
						if (ImGui::Button("Shift"))
						{
							if (IsInGame())
								State.rpcQueue.push(new RpcShapeshift(*Game::pLocalPlayer, State.selectedPlayer, !State.AnimationlessShapeshift));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new RpcShapeshift(*Game::pLocalPlayer, State.selectedPlayer, !State.AnimationlessShapeshift));
						}
					}

					if (!State.SafeMode)
					{
						if (ImGui::Button("Shift Everyone To"))
						{
							for (auto player : GetAllPlayerControl()) {
								if (IsInGame()) {
									State.rpcQueue.push(new RpcShapeshift(player, State.selectedPlayer, !State.AnimationlessShapeshift));
								}
								else if (IsInLobby()) {
									State.lobbyRpcQueue.push(new RpcShapeshift(player, State.selectedPlayer, !State.AnimationlessShapeshift));
								}
							}
						}
						ImGui::SameLine();
						if (ImGui::Button("Unshift Everyone"))
						{
							for (auto player : GetAllPlayerControl()) {
								if (IsInGame()) {
									State.rpcQueue.push(new RpcShapeshift(player, PlayerSelection(player), !State.AnimationlessShapeshift));
								}
								else if (IsInLobby()) {
									State.lobbyRpcQueue.push(new RpcShapeshift(player, PlayerSelection(player), !State.AnimationlessShapeshift));
								}
							}
						}
					}

					if ((role == RoleTypes__Enum::GuardianAngel || (IsHost() || !State.SafeMode)) && ImGui::Button("Protect Player"))
					{
						if (IsHost() || !State.SafeMode) {
							app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer));
							auto colorId = outfit->fields.ColorId;
							if (IsInGame())
								State.rpcQueue.push(new RpcProtectPlayer(*Game::pLocalPlayer, State.selectedPlayer, colorId));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new RpcProtectPlayer(*Game::pLocalPlayer, State.selectedPlayer, colorId));
						}
						else {
							if (IsInGame())
								State.rpcQueue.push(new CmdCheckProtect(*Game::pLocalPlayer, State.selectedPlayer));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new CmdCheckProtect(*Game::pLocalPlayer, State.selectedPlayer));
						}
					}

					if (!selectedPlayer.is_LocalPlayer()) {
						if (ImGui::Button("Teleport To")) {
							if (IsInGame())
								State.rpcQueue.push(new RpcSnapTo(GetTrueAdjustedPosition(selectedPlayer.get_PlayerControl())));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new RpcSnapTo(GetTrueAdjustedPosition(selectedPlayer.get_PlayerControl())));
						}
					}
					ImGui::SameLine();
					if (!selectedPlayer.is_LocalPlayer() && !State.SafeMode) {
						if (ImGui::Button("Teleport To You")) {
							if (IsInGame())
								State.rpcQueue.push(new RpcForceSnapTo(selectedPlayer.get_PlayerControl(), GetTrueAdjustedPosition(*Game::pLocalPlayer)));
							else if (IsInLobby())
								State.lobbyRpcQueue.push(new RpcForceSnapTo(selectedPlayer.get_PlayerControl(), GetTrueAdjustedPosition(*Game::pLocalPlayer)));
						}
					}

					if ((IsInGame() || IsInLobby()) && !selectedPlayer.is_Disconnected() && !selectedPlayer.is_LocalPlayer())
					{
						if (State.playerToAttach.equals(State.selectedPlayer) && State.ActiveAttach) {
							if (ImGui::Button("Stop Attaching")) {
								State.playerToAttach = PlayerSelection();
								State.ActiveAttach = false;
							}
						}
						else {
							if (ImGui::Button("Attach To")) {
								State.playerToAttach = State.selectedPlayer;
								State.ActiveAttach = true;
							}
						}
					}

					if ((IsHost() || !State.SafeMode) && (IsInGame() || IsInLobby()) && !selectedPlayer.get_PlayerData()->fields.IsDead) {
						if (ImGui::Button("Turn into Ghost"))
						{
							if (PlayerIsImpostor(selectedPlayer.get_PlayerData())) {
								if (IsInGame())
									State.rpcQueue.push(new RpcSetRole(selectedPlayer.get_PlayerControl(), RoleTypes__Enum::ImpostorGhost));
								else if (IsInLobby())
									State.lobbyRpcQueue.push(new RpcSetRole(selectedPlayer.get_PlayerControl(), RoleTypes__Enum::ImpostorGhost));
							}
							else {
								if (IsInGame())
									State.rpcQueue.push(new RpcSetRole(selectedPlayer.get_PlayerControl(), RoleTypes__Enum::CrewmateGhost));
								else if (IsInLobby())
									State.lobbyRpcQueue.push(new RpcSetRole(selectedPlayer.get_PlayerControl(), RoleTypes__Enum::CrewmateGhost));
							}
						}
					}

					if (IsHost() && (IsInGame() || IsInLobby()) && selectedPlayer.get_PlayerData()->fields.IsDead) {
						if (ImGui::Button("Revive"))
						{
							if (IsInGame()) {
								app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(selectedPlayer.get_PlayerData());
								State.rpcQueue.push(new RpcRevive(selectedPlayer.get_PlayerControl()));
								State.rpcQueue.push(new RpcForceColor(selectedPlayer.get_PlayerControl(), outfit->fields.ColorId, true));
							}
							else if (IsInLobby()) {
								app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(selectedPlayer.get_PlayerData());
								State.lobbyRpcQueue.push(new RpcRevive(selectedPlayer.get_PlayerControl()));
								State.lobbyRpcQueue.push(new RpcForceColor(selectedPlayer.get_PlayerControl(), outfit->fields.ColorId, true));
							}
						}
					}

					if ((IsHost() || !State.SafeMode) && (IsInGame() || IsInLobby())) {
						if (ImGui::Button("Turn into Fake Impostor"))
						{
							if (!PlayerIsImpostor(selectedPlayer.get_PlayerData())) {
								if (IsInGame())
									State.rpcQueue.push(new RpcSetRole(selectedPlayer.get_PlayerControl(), RoleTypes__Enum::Shapeshifter));
								else if (IsInLobby())
									State.lobbyRpcQueue.push(new RpcSetRole(selectedPlayer.get_PlayerControl(), RoleTypes__Enum::Shapeshifter));
							}
						}
					}

					if (!State.SafeMode && ImGui::Button("Set Scanner")) {
						if (IsInGame())
							State.rpcQueue.push(new RpcForceScanner(selectedPlayer.get_PlayerControl(), true));
						else if (IsInLobby())
							State.lobbyRpcQueue.push(new RpcForceScanner(selectedPlayer.get_PlayerControl(), true));
					}

					if ((IsHost() || !State.SafeMode) && (IsInGame() || IsInLobby())) {
						char* nameBufferHost[255]{ const_cast<char*>(State.hostUserName.c_str()) };
						if (ImGui::InputText("Username", *nameBufferHost, IM_ARRAYSIZE(nameBufferHost))) {
							State.hostUserName = std::string(*nameBufferHost);
						}
						if (ImGui::Button("Force Name"))
						{
							if (IsInGame() && !State.hostUserName.empty())
								State.rpcQueue.push(new RpcForceName(selectedPlayer.get_PlayerControl(), State.hostUserName));
							else if (IsInLobby() && !State.hostUserName.empty())
								State.lobbyRpcQueue.push(new RpcForceName(selectedPlayer.get_PlayerControl(), State.hostUserName));
						}
					}

					if ((IsHost() || !State.SafeMode) && (IsInGame() || IsInLobby())) {
						CustomListBoxInt(" ", &State.HostSelectedColorId, COLORS, 85.0f * State.dpiScale);
						ImGui::SameLine();
						if (ImGui::Button("Force Color"))
						{
							if (IsInGame()) {
								if (IsHost())
									State.rpcQueue.push(new RpcForceColor(selectedPlayer.get_PlayerControl(), State.HostSelectedColorId, true));
								else
									State.rpcQueue.push(new RpcForceColor(selectedPlayer.get_PlayerControl(), State.HostSelectedColorId));
							}
							else if (IsInLobby()) {
								if (IsHost())
									State.lobbyRpcQueue.push(new RpcForceColor(selectedPlayer.get_PlayerControl(), State.HostSelectedColorId, true));
								else
									State.lobbyRpcQueue.push(new RpcForceColor(selectedPlayer.get_PlayerControl(), State.HostSelectedColorId));
							}
						}
					}

					if (!State.SafeMode && (IsInGame() || IsInLobby()) && !selectedPlayer.is_Disconnected() && !selectedPlayer.is_LocalPlayer())
					{
						if (State.playerToChatAs.equals(State.selectedPlayer) && State.activeChatSpoof) {
							if (ImGui::Button("Stop Chatting As")) {
								State.playerToChatAs = PlayerSelection();
								State.activeChatSpoof = false;
							}
						}
						else {
							if (ImGui::Button("Chat As")) {
								State.playerToChatAs = State.selectedPlayer;
								State.activeChatSpoof = true;
							}
						}
					}

					ImGui::NewLine();

					if (IsInGame() && !selectedPlayer.is_Disconnected() && IsInMultiplayerGame())
					{
						auto tasks = GetNormalPlayerTasks(selectedPlayer.get_PlayerControl());

						if (State.RevealRoles && PlayerIsImpostor(selectedPlayer.get_PlayerData()))
						{
							ImGui::TextColored(ImVec4(0.8F, 0.2F, 0.0F, 1.0F), "Fake Tasks:");
						}
						else
						{
							ImGui::Text("Tasks:");
						}

						bool shouldEndListBox = ImGui::ListBoxHeader("###tasks#list", ImVec2(181, 94) * State.dpiScale);

						if (selectedPlayer.get_PlayerControl()->fields.myTasks == nullptr)
						{
							ImGui::Text("ERROR: Could not load tasks.");
						}
						else
						{
							for (auto task : tasks)
							{
								if (task->fields.taskStep == task->fields.MaxStep)
									ImGui::TextColored(ImVec4(0.0F, 1.0F, 0.0F, 1.0F), (std::string(TranslateTaskTypes(task->fields._.TaskType))).c_str());
								else
									ImGui::Text((std::string(TranslateTaskTypes(task->fields._.TaskType))).c_str());
							}
						}
						if (shouldEndListBox)
							ImGui::ListBoxFooter();
					}
				}

				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
}