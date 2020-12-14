#pragma once
#include <imgui/imgui.h>
#include "state.hpp"
#include "debugtabs/main_debug_tab.h"
#include "debugtabs/class_debug_tab.h"
#include "debugtabs/translations_debug_tab.h"

namespace DebugGui
{

	void Init();
	void Render();

}