#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"
#include "utility.h"
#include "game.h"
#include <random>
#include <algorithm>

void dRoleManager_AssignRolesForTeam(List_1_GameData_PlayerInfo_* players, RoleOptionsData* opts, RoleTeamTypes__Enum team, int32_t teamMax, Nullable_1_RoleTypes_ defaultRole, MethodInfo* method) {
	return RoleManager_AssignRolesForTeam(players, opts, team, teamMax, defaultRole, method);

	//if (team == RoleTeamTypes__Enum::Crewmate || State.impostors[0] == nullptr) {
	//	return RoleManager_AssignRolesForTeam(players, opts, team, teamMax, defaultRole, method);
	//}
	///*auto allRoles = (*Game::pRoleManager)->fields.AllRoles;
	//RoleBehaviour* impostorRole = nullptr;

	//for (int i = 0; i < (int)allRoles->bounds->length; i++) {
	//	RoleBehaviour* role = allRoles->vector[i];
	//	if (role->fields.TeamType == RoleTeamTypes__Enum::Impostor) {
	//		impostorRole = role;
	//	}
	//}*/
	//int remainingImpostors = teamMax;
	//for (auto player : State.impostors) {
	//	if (player == nullptr) {
	//		break;
	//	}
	//	PlayerControl_RpcSetRole(player, RoleTypes__Enum::Impostor, NULL);
	//	remainingImpostors--;
	//}
	//if (remainingImpostors == 0) {
	//	return;
	//}
	//auto allPlayers = GetAllPlayerControl();
	//std::vector<PlayerControl*> randomImpostors;
	//std::sample(allPlayers.begin(), allPlayers.end(), std::back_inserter(randomImpostors), remainingImpostors, std::mt19937{ std::random_device{}() });
	//for (auto player : randomImpostors) {
	//	if (player == nullptr) {
	//		break;
	//	}
	//	// can't use queue here because it is between lobby and game state
	//	PlayerControl_RpcSetRole(player, RoleTypes__Enum::Impostor, NULL);
	//	remainingImpostors--;
	//}
}

void dRoleManager_AssignRolesFromList(List_1_GameData_PlayerInfo_* players, int32_t teamMax, List_1_RoleTypes_* roleList, int32_t* rolesAssigned, MethodInfo* method) {
	int amountImpostors = 0;
	for (int i = 0; i < roleList->fields._size; i++) {
		if (roleList->fields._items->vector[i] == RoleTypes__Enum::Impostor) {
			amountImpostors++;
		}
	}
	std::vector<uint8_t> assignedPlayers;
	auto allPlayers = GetAllPlayerControl();

	for (auto player : State.impostors) {
		if (player == nullptr || amountImpostors == 0) {
			break;
		}
		// can't use queue here because it is between lobby and game state
		PlayerControl_RpcSetRole(player, RoleTypes__Enum::Impostor, NULL);
		rolesAssigned++;
		assignedPlayers.push_back(player->fields.PlayerId);

		amountImpostors--;
	}
	if (amountImpostors > 0) {
		std::vector<PlayerControl*> randomImpostors;
		std::sample(allPlayers.begin(), allPlayers.end(), std::back_inserter(randomImpostors), amountImpostors + *rolesAssigned, std::mt19937{ std::random_device{}() });
		for (auto player : randomImpostors) {
			if (player == nullptr) {
				break;
			}
			if (std::find(assignedPlayers.begin(), assignedPlayers.end(), player->fields.PlayerId) != assignedPlayers.end()) {
				continue;
			}
			// same here
			PlayerControl_RpcSetRole(player, RoleTypes__Enum::Impostor, NULL);
			(*rolesAssigned)++;
			assignedPlayers.push_back(player->fields.PlayerId);

			amountImpostors--;
		}
	}
	if (*rolesAssigned >= roleList->fields._size) {
		return;
	}
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(allPlayers), std::end(allPlayers), rng);
	int j = 0;
	for (int i = 0; i < roleList->fields._size; i++) {
		if (roleList->fields._items->vector[i] == RoleTypes__Enum::Impostor) {
			continue;
		}
		if (allPlayers.size() <= j) break;
		auto player = allPlayers[j];
		PlayerControl_RpcSetRole(player, roleList->fields._items->vector[i], NULL);
		(*rolesAssigned)++;
		j++;
		assignedPlayers.push_back(player->fields.PlayerId);
	}
}
