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
		if (IsHost() && IsInLobby()) {
			if (ImGui::BeginTabItem("Host")) {
				GameOptions options;
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
					const std::string& playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
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
							if(options.GetNumImpostors() <= State.impostors_amount + State.shapeshifters_amount)
								options.SetInt(app::Int32OptionNames__Enum::NumImpostors, State.impostors_amount + State.shapeshifters_amount);
						}
					}
				}
				if (shouldEndListBox)
					ImGui::ListBoxFooter();
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("host#actions", ImVec2(200, 0) * State.dpiScale, true);

				// AU v2022.8.24 has been able to change maps in lobby.
				State.mapHostChoice = options.GetByte(app::ByteOptionNames__Enum::MapId);
				State.mapHostChoice = std::clamp(State.mapHostChoice, 0, 4);
				if (CustomListBoxInt("Map", &State.mapHostChoice, MAP_NAMES, 75 * State.dpiScale)) {
					if (!IsInGame()) {
						if (State.mapHostChoice == 3) {
							options.SetByte(app::ByteOptionNames__Enum::MapId, 0);
							State.FlipSkeld = true;
						}
						else {
							options.SetByte(app::ByteOptionNames__Enum::MapId, State.mapHostChoice);
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