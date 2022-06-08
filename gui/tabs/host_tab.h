#pragma once
#include <vector>
#include "utility.h"

namespace HostTab {
	const std::vector<const char*> MAP_NAMES = { "The Skeld", "Mira HQ", "Polus", "Dleks", "Airship" };
	const std::vector<const char*> IMPOSTOR_AMOUNTS = { "1", "2", "3" };
	const std::vector<const char*> ROLE_NAMES = { "Random", "Crewmate", "Scientist", "Engineer", "Imposter", "Shapeshifter" };
	void Render();
	const ptrdiff_t GetRoleCount(RoleType role);
}