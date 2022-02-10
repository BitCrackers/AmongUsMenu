#include "pch-il2cpp.h"
#include "gui-helpers.hpp"
#include "keybinds.h"
#include "imgui/imgui_internal.h"
#include "state.hpp"
#include "game.h"

bool CustomListBoxInt(const char* label, int* value, const std::vector<const char*> list, float width, ImGuiComboFlags flags) {
	auto comboLabel = "##" + std::string(label);
	auto leftArrow = "##" + std::string(label) + "Left";
	auto rightArrow = "##" + std::string(label) + "Right";

	ImGuiStyle& style = ImGui::GetStyle();
	float spacing = style.ItemInnerSpacing.x;
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
	ImGui::SameLine(0, spacing);
	ImGui::Text(label);

	return response;
}

bool CustomListBoxIntMultiple(const char* label, std::vector<std::pair<const char*, bool>>* list, float width, bool resetButton, ImGuiComboFlags flags) {
	auto comboLabel = "##" + std::string(label);
	auto buttonLabel = "Reset##" + std::string(label);
	ImGuiStyle& style = ImGui::GetStyle();
	float spacing = style.ItemInnerSpacing.x;
	ImGui::PushItemWidth(width);
	const bool response = ImGui::BeginCombo(comboLabel.c_str(), label, flags);
	if (response) {
		for (size_t i = 0; i < list->size(); i++) {
			if (ImGui::Selectable(list->at(i).first, list->at(i).second))
				list->at(i).second ^= 1;
			if (list->at(i).second)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::PopItemWidth();

	if (resetButton)
	{
		ImGui::SameLine(0, spacing);
		const bool resetResponse = ImGui::Button(buttonLabel.c_str());
		if (resetResponse) {
			for (int i = 0; i < list->size(); i++)
				list->at(i).second = false;
			return resetResponse;
		}
	}
	
	return response;
}

bool CustomListBoxPlayerSelectionMultiple(const char* label, std::vector<std::pair<PlayerSelection, bool>>* list, float width, bool resetButton, ImGuiComboFlags flags) {
	if (!IsInGame()) return false; // works only ingame

	auto comboLabel = "##" + std::string(label);
	auto buttonLabel = "Reset##" + std::string(label);
	ImGuiStyle& style = ImGui::GetStyle();
	float spacing = style.ItemInnerSpacing.x;
	ImGui::PushItemWidth(width);
	const bool response = ImGui::BeginCombo(comboLabel.c_str(), label, flags);
	if (response) {
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		for (auto playerData : GetAllPlayerData()) {
			if (playerData->fields.Disconnected) // maybe make that an option for replays ? (parameter based on "state.showDisconnected" related data)
				continue;

			std::string playerName = convert_from_string(GetPlayerOutfit(playerData)->fields._playerName);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			if (ImGui::Selectable(std::string("##" + playerName + "_ConsoleName").c_str(), list->at(playerData->fields.PlayerId).second))
			{
				list->at(playerData->fields.PlayerId).second ^= 1;
				if (list->at(playerData->fields.PlayerId).second
					&& (!list->at(playerData->fields.PlayerId).first.has_value()
						|| (list->at(playerData->fields.PlayerId).first.has_value()
							&& list->at(playerData->fields.PlayerId).first.is_Disconnected())))
				{
					list->at(playerData->fields.PlayerId).first = PlayerSelection(playerData);
				}
			}
			if (list->at(playerData->fields.PlayerId).second)
				ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			ImGui::ColorButton(std::string("##" + playerName + "_ConsoleColorButton").c_str(), AmongUsColorToImVec4(GetPlayerColor(GetPlayerOutfit(playerData)->fields.ColorId)), ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
			ImGui::SameLine();
			ImGui::PopStyleVar(2);
			ImGui::Dummy(ImVec2(0, 0));
			ImGui::SameLine();

			ImVec4 nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->White);
			if (State.RevealRoles)
			{
				std::string roleName = GetRoleName(playerData->fields.Role);
				playerName = playerName + " (" + roleName + ")";
				nameColor = AmongUsColorToImVec4(GetRoleColor(playerData->fields.Role));
			}
			else if (PlayerIsImpostor(localData) && PlayerIsImpostor(playerData))
				nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->ImpostorRed);
			else if (PlayerSelection(playerData).is_LocalPlayer() || std::count(State.aumUsers.begin(), State.aumUsers.end(), playerData->fields.PlayerId))
				nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->Orange);

			if (playerData->fields.IsDead)
				nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->DisabledGrey);

			ImGui::TextColored(nameColor, playerName.c_str());
		}
		ImGui::EndCombo();
	}

	ImGui::PopItemWidth();

	if (resetButton)
	{
		ImGui::SameLine(0, spacing);
		const bool resetResponse = ImGui::Button(buttonLabel.c_str());
		if (resetResponse) {
			for (int i = 0; i < list->size(); i++)
				list->at(i).second = false;
			return resetResponse;
		}
	}
	
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
	ImGui::Text("[ %s ]", KeyBinds::ToString(key));

	if (!ImGui::IsItemHovered())
		return false;

	ImGui::SetTooltip("Press any key to change the keybind, ESC to reset");
	for (uint8_t vKey : KeyBinds::GetValidKeys()) {
		if (KeyBinds::IsKeyDown(vKey)) {
			key = (vKey != VK_ESCAPE ? vKey : 0x00);
			return true;
		}
	}

	return false;
}