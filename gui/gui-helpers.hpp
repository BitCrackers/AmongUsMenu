#pragma once
#include <vector>
#include <imgui/imgui.h>
#include "utility.h"

bool CustomListBoxInt(const char* label, int* value, const std::vector<const char*> list, float width = 225.f, ImGuiComboFlags flags = ImGuiComboFlags_None);
bool CustomListBoxIntMultiple(const char* label, std::vector<std::pair<const char*, bool>>* list, float width, bool resetButton = true, ImGuiComboFlags flags = ImGuiComboFlags_None);
bool CustomListBoxPlayerSelectionMultiple(const char* label, std::vector<std::pair<PlayerSelection, bool>>* list, float width, bool resetButton = true, ImGuiComboFlags flags = ImGuiComboFlags_None);
bool SteppedSliderFloat(const char* label, float* v, float v_min, float v_max, float v_step, const char* format, ImGuiSliderFlags flags);
bool SliderChrono(const char* label, void* p_data, const void* p_min, const void* p_max, std::string format, ImGuiSliderFlags flags = ImGuiSliderFlags_None);
bool HotKey(uint8_t& key);
void drawPlayerDot(PlayerControl* player, ImVec2 winPos, ImU32 color, ImU32 statusColor);
void drawPlayerIcon(PlayerControl* player, ImVec2 winPos, ImU32 color);
void drawDeadPlayerDot(DeadBody* deadBody, ImVec2 winPos, ImU32 color);
void drawDeadPlayerIcon(DeadBody* deadBody, ImVec2 winPos, ImU32 color);