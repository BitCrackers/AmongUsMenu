#include "pch-il2cpp.h"
#include "host_tab.h"
#include "utility.h"
#include "game.h"
#include "state.hpp"
#include "gui-helpers.hpp"

namespace HostTab {
	void Render() {
		if (IsHost() && IsInLobby()) {
			if (ImGui::BeginTabItem("Host")) {
				ImGui::Text("Select Roles:");
				ImGui::BeginChild("host#list", ImVec2(200, 0) * State.dpiScale, true);
				bool shouldEndListBox = ImGui::ListBoxHeader("Choose Roles", ImVec2(200, 150) * State.dpiScale);
				auto allPlayers = GetAllPlayerData();
				auto playerAmount = allPlayers.size();
				auto maxImposterAmount = GetMaxImposterAmount(playerAmount);
				for (size_t index = 0; index < playerAmount; index++) {
					auto playerData = allPlayers[index];
					PlayerControl* playerCtrl = GetPlayerControlById(playerData->fields.PlayerId);

					State.assignedRolesPlayer[index] = playerCtrl;
					if (State.assignedRolesPlayer[index] == nullptr)
						continue;

					app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);
					if (outfit == NULL) continue;
					std::string playerName = convert_from_string(outfit->fields._playerName);
					if (CustomListBoxInt(playerName.c_str(), &State.assignedRoles[index], ROLE_NAMES, 80 * State.dpiScale))
					{
						State.engineers_amount = GetRoleCount((int)RoleType::Engineer);
						State.scientists_amount = GetRoleCount((int)RoleType::Scientist);
						State.shapeshifters_amount = GetRoleCount((int)RoleType::Shapeshifter);
						State.impostors_amount = GetRoleCount((int)RoleType::Impostor);
						if (State.impostors_amount + State.shapeshifters_amount > maxImposterAmount)
						{
							if(State.assignedRoles[index] == (int)RoleType::Shapeshifter)
								State.assignedRoles[index] = (int)RoleType::Engineer;
							else if(State.assignedRoles[index] == (int)RoleType::Impostor)
								State.assignedRoles[index] = (int)RoleType::Random;
						}
						State.shapeshifters_amount = GetRoleCount((int)RoleType::Shapeshifter);
						State.impostors_amount = GetRoleCount((int)RoleType::Impostor);

						if (!IsInGame())
						{
							auto roleRates = (*Game::pGameOptionsData)->fields.RoleOptions->fields.roleRates;
							if(roleRates->fields.count != 0)
							{
								auto vectors = roleRates->fields.entries[0].vector;
								for (auto iVector = 0; iVector < 32; iVector++)
								{
									if (vectors[iVector].key == RoleTypes__Enum::Engineer)
									{
										if(State.engineers_amount > 0)
											vectors[iVector].value.Chance = 100;
										if(State.engineers_amount > vectors[iVector].value.MaxCount)
											vectors[iVector].value.MaxCount = State.engineers_amount;
									}
									else if (vectors[iVector].key == RoleTypes__Enum::Scientist)
									{
										if(State.scientists_amount > 0)
											vectors[iVector].value.Chance = 100;
										if(State.scientists_amount > vectors[iVector].value.MaxCount)
											vectors[iVector].value.MaxCount = State.scientists_amount;
									}
									else if (vectors[iVector].key == RoleTypes__Enum::Shapeshifter)
									{
										if(State.shapeshifters_amount > 0)
											vectors[iVector].value.Chance = 100;
										if(State.shapeshifters_amount > vectors[iVector].value.MaxCount)
											vectors[iVector].value.MaxCount = State.shapeshifters_amount;
									}
								}
							}

							if((*Game::pGameOptionsData)->fields._.numImpostors <= State.impostors_amount + State.shapeshifters_amount)
								(*Game::pGameOptionsData)->fields._.numImpostors = State.impostors_amount + State.shapeshifters_amount;
						}
					}
				}
				if (shouldEndListBox)
					ImGui::ListBoxFooter();
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("host#actions", ImVec2(200, 0) * State.dpiScale, true);

				State.mapHostChoice = std::clamp(State.mapHostChoice, 0, 4);
				if (CustomListBoxInt("Map", &State.mapHostChoice, MAP_NAMES, 75 * State.dpiScale)) {
					if (!IsInGame()) {
						if (State.mapHostChoice == 3) {
							(*Game::pGameOptionsData)->fields.MapId = 0;
							State.FlipSkeld = true;
						}
						else {
							(*Game::pGameOptionsData)->fields.MapId = State.mapHostChoice;
							State.FlipSkeld = false;
						}
					}
				}
				ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
				if (IsInLobby() && ImGui::Button("Force Start of Game"))
				{
					app::InnerNetClient_SendStartGame((InnerNetClient*)(*Game::pAmongUsClient), NULL);
				}
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
		}
	}
	const ptrdiff_t& GetRoleCount(int role)
	{
		return std::count_if(State.assignedRoles.cbegin(), State.assignedRoles.cend(), [role](int i) {return i == role; });
	}
}