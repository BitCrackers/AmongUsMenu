#pragma once
#include <vector>

namespace HostTab {
	const std::vector<const char*> MAP_NAMES = { "The Skeld", "Mira HQ", "Polus", "Dleks", "Airship" };
	const std::vector<const char*> IMPOSTOR_AMOUNTS = { "1", "2", "3" };
	const std::vector<const char*> ROLE_NAMES = { "Random", "Crewmate", "Scientist", "Engineer", "Imposter", "Shapeshifter" };
	void Render();
	const ptrdiff_t GetRoleCount(int role);
}