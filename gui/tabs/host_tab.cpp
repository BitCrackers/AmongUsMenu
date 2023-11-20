#include "pch-il2cpp.h"
#include "host_tab.h"
#include "utility.h"
#include "game.h"
#include "state.hpp"
#include "gui-helpers.hpp"

namespace HostTab {
	static void SetRoleAmount(RoleTypes__Enum type, int amount) {
		auto&& options = GameOptions().GetRoleOptions();
		auto maxCount = options.GetNumPerGame(type);
		if (amount > maxCount)
			options.SetRoleRate(type, amount, 100);
		else if (amount > 0)
			options.SetRoleRate(type, maxCount, 100);
	}

	void Render() {
		if (IsHost()) {
			if (ImGui::BeginTabItem("Host")) {
				GameOptions options;
				if (IsInLobby())
					ImGui::Text("Select Roles:");
				if (IsInLobby()) {
					ImGui::BeginChild("host#list", ImVec2(200, 0) * State.dpiScale, true, ImGuiWindowFlags_NoBackground);
					bool shouldEndListBox = ImGui::ListBoxHeader("Choose Roles", ImVec2(200, 150) * State.dpiScale);
					auto allPlayers = GetAllPlayerData();
					auto playerAmount = allPlayers.size();
					auto maxImpostorAmount = GetMaxImpostorAmount((int)playerAmount);
					for (size_t index = 0; index < playerAmount; index++) {
						auto playerData = allPlayers[index];
						PlayerControl* playerCtrl = GetPlayerControlById(playerData->fields.PlayerId);

						State.assignedRolesPlayer[index] = playerCtrl;
						if (State.assignedRolesPlayer[index] == nullptr)
							continue;

						app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);
						if (outfit == NULL) continue;
						const std::string& playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
						if (CustomListBoxInt(playerName.c_str(), reinterpret_cast<int*>(&State.assignedRoles[index]), ROLE_NAMES, 80 * State.dpiScale))
						{
							State.engineers_amount = (int)GetRoleCount(RoleType::Engineer);
							State.scientists_amount = (int)GetRoleCount(RoleType::Scientist);
							State.shapeshifters_amount = (int)GetRoleCount(RoleType::Shapeshifter);
							State.impostors_amount = (int)GetRoleCount(RoleType::Impostor);
							if (State.impostors_amount + State.shapeshifters_amount > maxImpostorAmount)
							{
								if (State.assignedRoles[index] == RoleType::Shapeshifter)
									State.assignedRoles[index] = RoleType::Random;
								else if (State.assignedRoles[index] == RoleType::Impostor)
									State.assignedRoles[index] = RoleType::Random;
								State.shapeshifters_amount = (int)GetRoleCount(RoleType::Shapeshifter);
								State.impostors_amount = (int)GetRoleCount(RoleType::Impostor);
								State.crewmates_amount = (int)GetRoleCount(RoleType::Crewmate);
							}

							if (State.assignedRoles[index] == RoleType::Engineer || State.assignedRoles[index] == RoleType::Scientist || State.assignedRoles[index] == RoleType::Crewmate) {
								if (State.engineers_amount + State.scientists_amount + State.crewmates_amount >= (int)playerAmount)
									State.assignedRoles[index] = RoleType::Random;
							} //Some may set all players to non imps. This hangs the game on beginning. Leave space to Random so we have imps.

							if (!IsInGame()) {
								if (options.GetGameMode() == GameModes__Enum::HideNSeek)
									SetRoleAmount(RoleTypes__Enum::Engineer, 15);
								else
									SetRoleAmount(RoleTypes__Enum::Engineer, State.engineers_amount);
								SetRoleAmount(RoleTypes__Enum::Scientist, State.scientists_amount);
								SetRoleAmount(RoleTypes__Enum::Shapeshifter, State.shapeshifters_amount);
								if (options.GetNumImpostors() <= State.impostors_amount + State.shapeshifters_amount)
									options.SetInt(app::Int32OptionNames__Enum::NumImpostors, State.impostors_amount + State.shapeshifters_amount);
							}
						}
					}
					if (shouldEndListBox)
						ImGui::ListBoxFooter();
					ImGui::EndChild();
					ImGui::SameLine();
				}
				ImGui::BeginChild("host#actions", ImVec2(300, 0) * State.dpiScale, true, ImGuiWindowFlags_NoBackground);

				// AU v2022.8.24 has been able to change maps in lobby.
				State.mapHostChoice = options.GetByte(app::ByteOptionNames__Enum::MapId);
				if (State.mapHostChoice > 3)
					State.mapHostChoice--;
				State.mapHostChoice = std::clamp(State.mapHostChoice, 0, (int)MAP_NAMES.size() - 1);
				if (IsInLobby() && CustomListBoxInt("Map", &State.mapHostChoice, MAP_NAMES, 75 * State.dpiScale)) {
					if (!IsInGame()) {
						// disable flip
						/*if (State.mapHostChoice == 3) {
							options.SetByte(app::ByteOptionNames__Enum::MapId, 0);
							State.FlipSkeld = true;
						}
						else {
							options.SetByte(app::ByteOptionNames__Enum::MapId, State.mapHostChoice);
							State.FlipSkeld = false;
						}*/
						auto id = State.mapHostChoice;
						if (id >= 3) id++;
						options.SetByte(app::ByteOptionNames__Enum::MapId, id);
					}
				}
				if (IsInLobby() && ImGui::Checkbox("Custom Impostor Amount", &State.CustomImpostorAmount))
					State.Save();
				State.ImpostorCount = std::clamp(State.ImpostorCount, 0, int(Game::MAX_PLAYERS));
				if (IsInLobby() && ImGui::InputInt("Impostor Count", &State.ImpostorCount))
					State.Save();
				/*int32_t maxPlayers = options.GetMaxPlayers();
				maxPlayers = std::clamp(maxPlayers, 0, int(Game::MAX_PLAYERS));
				if (IsInLobby() && ImGui::InputInt("Max Players", &maxPlayers))
					GameOptions().SetInt(app::Int32OptionNames__Enum::MaxPlayers, maxPlayers);*/ //support for more than 15 players

				/*if (IsInLobby() && ImGui::Checkbox("Flip Skeld", &State.FlipSkeld))
					State.Save();*/ //to be fixed later
				ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
				if (IsInLobby() && ImGui::Button("Force Start of Game"))
				{
					app::InnerNetClient_SendStartGame((InnerNetClient*)(*Game::pAmongUsClient), NULL);
				}
				if (ImGui::Checkbox("Disable Meetings", &State.DisableMeetings))
					State.Save();
				if (ImGui::Checkbox("Disable Sabotages", &State.DisableSabotages))
					State.Save();

				/*if (ImGui::Checkbox("Disable Specific RPC Call ID", &State.DisableCallId))
					State.Save();
				int callId = State.ToDisableCallId;
				if (ImGui::InputInt("ID to Disable", &callId)) {
					State.ToDisableCallId = (uint8_t)callId;
					State.Save();
				}*/

				if ((State.mapType == Settings::MapType::Airship) && IsInGame() && ImGui::Button("Switch Moving Platform Side"))
				{
					State.rpcQueue.push(new RpcUsePlatform());
				}

				if (State.InMeeting && ImGui::Button("End Meeting")) {
					State.rpcQueue.push(new RpcEndMeeting());
					State.InMeeting = false;
				}

				if (IsInMultiplayerGame() || IsInLobby()) { //lobby isn't possible in freeplay
					if (ImGui::Checkbox("Disable Game Ending", &State.NoGameEnd)) {
						State.Save();
					}

					if (IsInGame()) {
						CustomListBoxInt("Reason", &State.SelectedGameEndReasonId, GAMEENDREASON, 120.0f * State.dpiScale);

						ImGui::SameLine();

						if (ImGui::Button("End Game")) {
								State.rpcQueue.push(new RpcEndGame(GameOverReason__Enum(std::clamp(State.SelectedGameEndReasonId, 0, 8))));
						}
					}
				}

				CustomListBoxInt(" ­", &State.HostSelectedColorId, HOSTCOLORS, 85.0f * State.dpiScale);

				if (ImGui::Checkbox("Force Color for Everyone", &State.ForceColorForEveryone)) {
					State.Save();
				}


				static int framesPassed = -1;

				if (IsHost() && IsInGame() && GetPlayerData(*Game::pLocalPlayer)->fields.IsDead && ImGui::Button("Revive Yourself"))
				{
					app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer));
					State.rpcQueue.push(new RpcRevive(*Game::pLocalPlayer));
					State.rpcQueue.push(new RpcForceColor(*Game::pLocalPlayer, outfit->fields.ColorId, true));
					framesPassed = 40;
				}

				if (framesPassed == 20)
				{
					State.rpcQueue.push(new RpcVent(*Game::pLocalPlayer, 1, false));
					framesPassed--;
				}
				else if (framesPassed <= 0 && (*Game::pLocalPlayer)->fields.inVent) {
					State.rpcQueue.push(new RpcVent(*Game::pLocalPlayer, 1, true)); //for showing you as alive to ALL players
					framesPassed = -1;
				}
				else framesPassed--;

				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
	const ptrdiff_t GetRoleCount(RoleType role)
	{
		return std::count_if(State.assignedRoles.cbegin(), State.assignedRoles.cend(), [role](RoleType i) {return i == role; });
	}
}