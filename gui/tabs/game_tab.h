#pragma once
#include <vector>

namespace GameTab {
	const std::vector<const char*> KILL_DISTANCE = { "Short", "Medium", "Long" };
	const std::vector<const char*> TASKBARUPDATES = { "Always", "Meetings", "Never" };
	void Render();
}