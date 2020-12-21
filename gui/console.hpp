#pragma once
#include <vector>

namespace ConsoleGui {
	const std::vector<const char*> BY_TYPE = { "", "Kill", "Vent", "Task", "Report", "Meeting", "Vote" };
	extern int selectedType;

	void Init();
	void Render();
};