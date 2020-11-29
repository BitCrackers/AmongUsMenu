#pragma once
#include "il2cpp-appdata.h"
#define _USE_MATH_DEFINES
#include <imgui/imgui.h>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "state.hpp"
#include "game.hpp"
#include "utility.h"
#include "_hooks.hpp"

namespace Radar
{
	void Init();
	void Render();
}