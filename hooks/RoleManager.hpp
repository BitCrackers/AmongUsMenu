#pragma once
#include "utility.h"

void AssignPreChosenRoles(RoleRates& roleRates, std::vector<uint8_t>& assignedPlayers);
void AssignRoles(int& roleCount, int roleChance, RoleTypes__Enum role, std::vector<app::PlayerControl*>& allPlayers, std::vector<uint8_t>& assignedPlayers);