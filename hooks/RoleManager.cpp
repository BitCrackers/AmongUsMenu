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
}

void dRoleManager_AssignRolesFromList(List_1_GameData_PlayerInfo_* players, int32_t teamMax, List_1_RoleTypes_* roleList, int32_t* rolesAssigned, MethodInfo* method) {
	return RoleManager_AssignRolesFromList(players, teamMax, roleList, rolesAssigned, method);
}
