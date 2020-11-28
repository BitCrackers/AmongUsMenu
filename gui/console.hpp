#pragma once
#include <imgui/imgui.h>
#include "imgui/imgui_internal.h"
#include "state.hpp"
#include "utility.h"
#include "gui-helpers.hpp"

namespace ConsoleGui {
	const std::vector<const char*> BY_TYPE = { "", "Kill", "Vent", "Task", "Report", "Meeting", "Vote" };
	extern int selectedType;

	void Init();
	void Render();
};