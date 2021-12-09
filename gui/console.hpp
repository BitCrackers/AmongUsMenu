#pragma once
#include <vector>

namespace ConsoleGui {
	const std::vector<const char*> BY_TYPE = { "All", "Kill", "Vent", "Task", "Report", "Meeting", "Vote", "Cheat", "Disconnect", "Shapeshift", "Protect" };
	extern int selectedType;

	void Init();
	void Render();
};