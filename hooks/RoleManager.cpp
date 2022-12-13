#include "pch-il2cpp.h"
#include "RoleManager.hpp"
#include "_hooks.h"
#include "state.hpp"
#include "logger.h"
#include "utility.h"
#include "game.h"

void dRoleManager_SelectRoles(RoleManager* __this, MethodInfo* method) {
	std::vector<uint8_t> assignedPlayers;
	GameOptions options;
	auto allPlayers = GetAllPlayerControl();
	auto roleRates = RoleRates(options, (int)allPlayers.size());

	AssignPreChosenRoles(roleRates, assignedPlayers);
	AssignRoles(roleRates, roleRates.ShapeshifterChance, RoleTypes__Enum::Shapeshifter, allPlayers, assignedPlayers);
	AssignRoles(roleRates, 100, RoleTypes__Enum::Impostor, allPlayers, assignedPlayers);
	AssignRoles(roleRates, roleRates.ScientistChance, RoleTypes__Enum::Scientist, allPlayers, assignedPlayers);
	AssignRoles(roleRates, roleRates.EngineerChance, RoleTypes__Enum::Engineer, allPlayers, assignedPlayers);
	AssignRoles(roleRates, 100, RoleTypes__Enum::Crewmate, allPlayers, assignedPlayers);
}

/*void dRoleManager_AssignRolesForTeam(List_1_GameData_PlayerInfo_* players, RoleOptionsData* opts, RoleTeamTypes__Enum team, int32_t teamMax, Nullable_1_RoleTypes_ defaultRole, MethodInfo* method) {
	return RoleManager_AssignRolesForTeam(players, opts, team, teamMax, defaultRole, method);
}

void dRoleManager_AssignRolesFromList(List_1_GameData_PlayerInfo_* players, int32_t teamMax, List_1_RoleTypes_* roleList, int32_t* rolesAssigned, MethodInfo* method) {
	return RoleManager_AssignRolesFromList(players, teamMax, roleList, rolesAssigned, method);
}*/

void AssignPreChosenRoles(RoleRates& roleRates, std::vector<uint8_t>& assignedPlayers)
{
	for (size_t i = 0; i < State.assignedRolesPlayer.size(); i++)
	{
		auto role = State.assignedRoles[i];
		auto player = State.assignedRolesPlayer[i];
		if (!CanPlayerBeAssignedToRole(player, assignedPlayers) || role == RoleType::Random)
			continue;

		auto trueRole = GetRoleTypesEnum(role);
		roleRates.SubtractRole(trueRole);

		PlayerControl_RpcSetRole(player, trueRole, NULL);
		assignedPlayers.push_back(player->fields.PlayerId);
	}
}

void AssignRoles(RoleRates& roleRates, int roleChance, RoleTypes__Enum role, il2cpp::List<List_1_PlayerControl_>& allPlayers, std::vector<uint8_t>& assignedPlayers)
{
	auto roleCount = roleRates.GetRoleCount(role);
	if (roleCount < 1)
		return;

	auto playerAmount = allPlayers.size();

	for (auto i = 0; i < roleCount; i++)
	{
		if(assignedPlayers.size() >= playerAmount)
			break;

		if (!ShouldRoleBeAssigned(roleChance))
			continue;

		int sanityCheck = 1000;
		while (sanityCheck > 0)
		{
			sanityCheck--;
			auto playerIndex = GenerateRandomNumber(0, (int)playerAmount - 1);
			auto player = allPlayers[playerIndex];
			if (CanPlayerBeAssignedToRole(player, assignedPlayers))
			{
				roleRates.SubtractRole(role);
				PlayerControl_RpcSetRole(player, role, NULL);
				assignedPlayers.push_back(player->fields.PlayerId);
				break;
			}
		}
		if (sanityCheck == 0)
			STREAM_ERROR("Sanity check failed, could not assign roles to all players (roleCount " << roleCount << ", playerAmount " << playerAmount << ")");
	}
}

bool ShouldRoleBeAssigned(int roleChance)
{
	if (roleChance == 100)
		return true;

	return roleChance >= GenerateRandomNumber(1, 100);
}

bool CanPlayerBeAssignedToRole(app::PlayerControl* player, std::vector<uint8_t>& assignedPlayers)
{
	if (player == nullptr || std::find(assignedPlayers.begin(), assignedPlayers.end(), player->fields.PlayerId) != assignedPlayers.end())
		return false;
	return true;
}