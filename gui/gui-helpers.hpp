#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <imgui/imgui.h>
#include "imgui/imgui_internal.h"
#include "utility.h"

bool CustomListBoxInt(const char* label, int* value, const std::vector<const char*> list, float width = 225.f, ImGuiComboFlags flags = ImGuiComboFlags_None);
bool SteppedSliderFloat(const char* label, float* v, float v_min, float v_max, float v_step, const char* format, ImGuiSliderFlags flags);