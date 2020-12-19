#pragma once
#include <vector>
#include "il2cpp-appdata.h"
#include <imgui/imgui.h>
#include "imgui/imgui_internal.h"
#include "state.hpp"
#include "game.hpp"
#include "utility.h"
#include "gui-helpers.hpp"

namespace GameTab {
	const std::vector<const char*> KILL_DISTANCE = { "Short", "Medium", "Long" };
	const std::vector<const char*> TASKBARUPDATES = { "Always", "Meetings", "Never" };
	const std::vector<const char*> COLORS = { "Red", "Blue", "Dark Green", "Pink", "Orange", "Yellow", "Black", "White", "Purple", "Brown", "Cyan", "Lime"};
	void Render();
}