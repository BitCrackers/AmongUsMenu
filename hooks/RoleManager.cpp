#include "pch-il2cpp.h"
#include "RoleManager.hpp"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"
#include "utility.h"
#include "game.h"
#include <random>
#include <algorithm>

void dRoleManager_SelectRoles(RoleManager* __this, MethodInfo* method) {
	std::vector<uint8_t> assignedPlayers;
	auto allPlayers = GetAllPlayerControl();
	auto roleRates = RoleRates((*Game::pGameOptionsData)->fields);

	AssignPreChosenRoles(roleRates, assignedPlayers);
	AssignRoles(roleRates.ShapeshifterCount, roleRates.ShapeshifterChance, RoleTypes__Enum::Shapeshifter, allPlayers, assignedPlayers);
	AssignRoles(roleRates.ImposterCount, 100, RoleTypes__Enum::Impostor, allPlayers, assignedPlayers);
	AssignRoles(roleRates.ScientistCount, roleRates.ScientistChance, RoleTypes__Enum::Scientist, allPlayers, assignedPlayers);
	AssignRoles(roleRates.EngineerCount, roleRates.EngineerChance, RoleTypes__Enum::Engineer, allPlayers, assignedPlayers);
	AssignRoles(roleRates.MaxCrewmates, 100, RoleTypes__Enum::Crewmate, allPlayers, assignedPlayers);
}

void dRoleManager_AssignRolesForTeam(List_1_GameData_PlayerInfo_* players, RoleOptionsData* opts, RoleTeamTypes__Enum team, int32_t teamMax, Nullable_1_RoleTypes_ defaultRole, MethodInfo* method) {
	return RoleManager_AssignRolesForTeam(players, opts, team, teamMax, defaultRole, method);
}

void dRoleManager_AssignRolesFromList(List_1_GameData_PlayerInfo_* players, int32_t teamMax, List_1_RoleTypes_* roleList, int32_t* rolesAssigned, MethodInfo* method) {
	return RoleManager_AssignRolesFromList(players, teamMax, roleList, rolesAssigned, method);
}

void AssignPreChosenRoles(RoleRates& roleRates, std::vector<uint8_t>& assignedPlayers)
{
	for (int i = 0; i < State.assignedRolesPlayer.size(); i++) {
		auto role = State.assignedRoles[i];
		auto player = State.assignedRolesPlayer[i];
		if (player == nullptr)
			break;
		if (role == (int)RoleType::Random)
			continue;

		auto trueRole = GetRoleTypesEnum((RoleType)role);
		if (trueRole == RoleTypes__Enum::Shapeshifter)
		{
			if (roleRates.ShapeshifterCount < 1)
				continue;
			roleRates.ShapeshifterCount--;
			roleRates.ImposterCount--;
		}
		else if (trueRole == RoleTypes__Enum::Impostor)
		{
			if (roleRates.ImposterCount < 1)
				continue;
			roleRates.ImposterCount--;
			roleRates.ShapeshifterCount--;
		}
		else if (trueRole == RoleTypes__Enum::Scientist)
		{
			if (roleRates.ScientistCount < 1)
				continue;
			roleRates.ScientistCount--;
		}
		else if (trueRole == RoleTypes__Enum::Engineer)
		{
			if (roleRates.EngineerCount < 1)
				continue;
			roleRates.EngineerCount--;
		}

		PlayerControl_RpcSetRole(player, trueRole, NULL);
		assignedPlayers.push_back(player->fields.PlayerId);
	}
}

void AssignRoles(int& roleCount, int roleChance, RoleTypes__Enum role, std::vector<app::PlayerControl*>& allPlayers, std::vector<uint8_t>& assignedPlayers)
{
	if (roleCount < 1)
		return;

	std::vector<PlayerControl*> randomEngineers;
	std::sample(allPlayers.begin(), allPlayers.end(), std::back_inserter(randomEngineers), roleCount, std::mt19937{ std::random_device{}() });
	for (auto player : randomEngineers) {
		if (player == nullptr) {
			break;
		}
		if (std::find(assignedPlayers.begin(), assignedPlayers.end(), player->fields.PlayerId) != assignedPlayers.end()) {
			continue;
		}

		if (roleChance < 100)
		{
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist100(1, 100);
			auto chance = 100 - dist100(rng);

			if (chance <= roleChance)
				continue;
		}

		PlayerControl_RpcSetRole(player, role, NULL);
		assignedPlayers.push_back(player->fields.PlayerId);
	}
}