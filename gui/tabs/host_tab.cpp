#include "pch-il2cpp.h"
#include "host_tab.h"
#include "utility.h"
#include "game.h"
#include "state.hpp"
#include "gui-helpers.hpp"

namespace HostTab {
	static void SetRoleAmount(RoleTypes__Enum type, int amount) {
		il2cpp::Dictionary roleRates = (*Game::pGameOptionsData)->fields.RoleOptions->fields.roleRates;
		if (auto value = roleRates[type]) {
			if (amount > 0)
				value->Chance = 100;
			if (amount > value->MaxCount)
				value->MaxCount = amount;
		}
	}

	void Render() {
		if (IsHost() && IsInLobby()) {
			if (ImGui::BeginTabItem("Host")) {
				ImGui::Text("Select Roles:");
				ImGui::BeginChild("host#list", ImVec2(200, 0) * State.dpiScale, true);
				bool shouldEndListBox = ImGui::ListBoxHeader("Choose Roles", ImVec2(200, 150) * State.dpiScale);
				auto allPlayers = GetAllPlayerData();
				auto playerAmount = allPlayers.size();
				auto maxImposterAmount = GetMaxImposterAmount((int)playerAmount);
				for (size_t index = 0; index < playerAmount; index++) {
					auto playerData = allPlayers[index];
					PlayerControl* playerCtrl = GetPlayerControlById(playerData->fields.PlayerId);

					State.assignedRolesPlayer[index] = playerCtrl;
					if (State.assignedRolesPlayer[index] == nullptr)
						continue;

					app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);
					if (outfit == NULL) continue;
					std::string playerName = convert_from_string(outfit->fields._playerName);
					if (CustomListBoxInt(playerName.c_str(), reinterpret_cast<int*>(&State.assignedRoles[index]), ROLE_NAMES, 80 * State.dpiScale))
					{
						State.engineers_amount = (int)GetRoleCount(RoleType::Engineer);
						State.scientists_amount = (int)GetRoleCount(RoleType::Scientist);
						State.shapeshifters_amount = (int)GetRoleCount(RoleType::Shapeshifter);
						State.impostors_amount = (int)GetRoleCount(RoleType::Impostor);
						if (State.impostors_amount + State.shapeshifters_amount > maxImposterAmount)
						{
							if(State.assignedRoles[index] == RoleType::Shapeshifter)
								State.assignedRoles[index] = RoleType::Engineer;
							else if(State.assignedRoles[index] == RoleType::Impostor)
								State.assignedRoles[index] = RoleType::Random;
							State.shapeshifters_amount = (int)GetRoleCount(RoleType::Shapeshifter);
							State.impostors_amount = (int)GetRoleCount(RoleType::Impostor);
						}

						if (!IsInGame()) {
							SetRoleAmount(RoleTypes__Enum::Engineer, State.engineers_amount);
							SetRoleAmount(RoleTypes__Enum::Scientist, State.scientists_amount);
							SetRoleAmount(RoleTypes__Enum::Shapeshifter, State.shapeshifters_amount);
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
	const ptrdiff_t GetRoleCount(RoleType role)
	{
		return std::count_if(State.assignedRoles.cbegin(), State.assignedRoles.cend(), [role](RoleType i) {return i == role; });
	}
}