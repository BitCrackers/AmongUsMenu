#pragma once
#include "il2cpp-appdata.h"
#define _USE_MATH_DEFINES
#include <imgui/imgui.h>
#include "imgui/imgui_internal.h"
#include <math.h>
#include <algorithm>
#include <cmath>
#include "state.hpp"
#include "game.hpp"
#include "tabs/game_tab.h"
#include "tabs/radar_tab.h"
#include "tabs/players_tab.h"
#include "tabs/tasks_tab.h"
#include "tabs/sabotage_tab.h"
#include "tabs/doors_tab.h"
#include "tabs/host_tab.h"
#include "tabs/self_tab.h"

namespace Menu {
	void Init();
	void Render();
}