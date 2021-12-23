#ifndef GUI_HELPERS_H
#define GUI_HELPERS_H
#include <vector>
#include <imgui/imgui.h>

bool CustomListBoxInt(const char* label, int* value, const std::vector<const char*> list, float width = 225.f, ImGuiComboFlags flags = ImGuiComboFlags_None);
bool SteppedSliderFloat(const char* label, float* v, float v_min, float v_max, float v_step, const char* format, ImGuiSliderFlags flags);
bool HotKey(uint8_t& key);
#endif