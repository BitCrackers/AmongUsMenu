#include "pch-il2cpp.h"
#include "gui-helpers.hpp"
#include "keyBindsConfig.h"
#include "imgui/imgui_internal.h"

bool CustomListBoxInt(const char* label, int* value, const std::vector<const char*> list, float width, ImGuiComboFlags flags) {
	auto comboLabel = "##" + std::string(label);
	auto leftArrow = "##" + std::string(label) + "Left";
	auto rightArrow = "##" + std::string(label) + "Right";

	ImGuiStyle& style = ImGui::GetStyle();
	float w = ImGui::CalcItemWidth();
	float spacing = style.ItemInnerSpacing.x;
	float button_sz = ImGui::GetFrameHeight();
	ImGui::PushItemWidth(width);
	const bool response = ImGui::BeginCombo(comboLabel.c_str(), list.at(*value), ImGuiComboFlags_NoArrowButton | flags);
	if (response) {
		for (size_t i = 0; i < list.size(); i++) {
			bool is_selected = (*value == i);
			if (ImGui::Selectable(list.at(i), is_selected))
				*value = i;
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::PopItemWidth();
	ImGui::SameLine(0, spacing);

	const bool LeftResponse = ImGui::ArrowButton(leftArrow.c_str(), ImGuiDir_Left);
	if (LeftResponse) {
		*value -= 1;
		if (*value < 0) *value = (list.size() - 1);
		return LeftResponse;
	}
	ImGui::SameLine(0, spacing);
	const bool RightResponse = ImGui::ArrowButton(rightArrow.c_str(), ImGuiDir_Right);
	if (RightResponse) {
		*value += 1;
		if (*value > (int)(list.size() - 1)) *value = 0;
		return RightResponse;
	}
	ImGui::SameLine(0, style.ItemInnerSpacing.x);
	ImGui::Text(label);

	return response;
}

bool SteppedSliderFloat(const char* label, float* v, float v_min, float v_max, float v_step, const char* format = "%.3f", ImGuiSliderFlags flags = 0) {
	char text_buf[64] = {};
	ImFormatString(text_buf, IM_ARRAYSIZE(text_buf), format, *v);

	const int stepCount = int((v_max - v_min) / v_step);
	int v_i = int((*v - v_min) / v_step);
	const bool valueChanged = ImGui::SliderInt(label, &v_i, 0, stepCount, text_buf);

	*v = v_min + float(v_i) * v_step;
	return valueChanged;
}

bool HotKey(uint8_t& key)
{
	ImGui::Text("[ %s ]", KeyBindsConfig::toString(key));

	if (!ImGui::IsItemHovered())
		return false;

	ImGui::SetTooltip("Press any key to change the keybind, ESC to reset");
	for (uint8_t vKey : KeyBindsConfig::getValidKeys()) {
		if (ImGui::IsKeyReleased(vKey)) {
			key = (vKey != VK_ESCAPE ? vKey : 0x00);
			return true;
		} else if (ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
			key = 0x02;
			return true;
		} else if (ImGui::IsMouseReleased(ImGuiMouseButton_Middle)) {
			key = 0x04;
			return true;
		} else if (ImGui::IsMouseReleased(3)) {
			key = 0x05;
			return true;
		} else if (ImGui::IsMouseReleased(4)) {
			key = 0x06;
			return true;
		}
	}

	return false;
}