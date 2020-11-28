#pragma once
#include "il2cpp-appdata.h"
#include <imgui/imgui.h>
#include "imgui/imgui_internal.h"
#include "state.hpp"
#include "game.hpp"
#include "utility.h"
#include <algorithm>
#include "gui-helpers.hpp"

namespace HostTab {
	const std::vector<const char*> MAP_NAMES = { "The Skeld", "Mira HQ", "Polus" };
	const std::vector<const char*> IMPOSTOR_AMOUNTS = { "One", "Two", "Three" };
	void Render();
}