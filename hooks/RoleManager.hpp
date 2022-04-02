#pragma once
#include "utility.h"

void AssignPreChosenRoles(RoleRates& roleRates, std::vector<uint8_t>& assignedPlayers);
void AssignRoles(RoleRates& roleRates, int roleChance, RoleTypes__Enum role, std::vector<app::PlayerControl*>& allPlayers, std::vector<uint8_t>& assignedPlayers);
bool ShouldRoleBeAssigned(int roleChance);
bool CanPlayerBeAssignedToRole(app::PlayerControl* player, std::vector<uint8_t>& assignedPlayers);