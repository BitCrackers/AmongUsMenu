#include "pch-il2cpp.h"
#include "gui-helpers.hpp"
#include "keybinds.h"
#include "imgui/imgui_internal.h"
#include "state.hpp"
#include "game.h"
#include "DirectX.h"
#include <DirectX.h>

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
			if (strcmp(list->at(i).first, "") == 0) // ignore all entries with empty labels so we can create padding
				continue;
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

void drawPlayerDot(PlayerControl* player, ImVec2 winPos, ImU32 color, ImU32 statusColor)
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	Vector2 playerPos = app::PlayerControl_GetTruePosition(player, NULL);

	float xOffset = maps[State.mapType].x_offset;
	float yOffset = maps[State.mapType].y_offset;

	if (State.mapType == Settings::MapType::Ship && State.FlipSkeld) {
		xOffset -= 50;
	}

	float radX = xOffset + (playerPos.x * maps[State.mapType].scale) + winPos.x;
	float radY = yOffset - (playerPos.y * maps[State.mapType].scale) + winPos.y;

	drawList->AddCircleFilled(ImVec2(radX, radY), 4.5F, color);
	drawList->AddCircle(ImVec2(radX, radY), 4.5F + 0.5F, statusColor, 0, 2.0F);
}

void drawPlayerIcon(PlayerControl* player, ImVec2 winPos, ImU32 color)
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	Vector2 playerPos = app::PlayerControl_GetTruePosition(player, NULL);

	float xOffset = maps[State.mapType].x_offset;
	float yOffset = maps[State.mapType].y_offset;

	if (State.mapType == Settings::MapType::Ship && State.FlipSkeld) {
		xOffset -= 50;
	}

	IconTexture icon = icons.at(ICON_TYPES::PLAYER);
	float radX = xOffset + (playerPos.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[State.mapType].scale + winPos.x;
	float radY = yOffset - (playerPos.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[State.mapType].scale + winPos.y;
	float radXMax = xOffset + (playerPos.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[State.mapType].scale + winPos.x;
	float radYMax = yOffset - (playerPos.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[State.mapType].scale + winPos.y;

	drawList->AddImage((void*)icon.iconImage.shaderResourceView, ImVec2(radX, radY), ImVec2(radXMax, radYMax), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f), color);

	if (GetPlayerData(player)->fields.IsDead)
		drawList->AddImage((void*)icons.at(ICON_TYPES::CROSS).iconImage.shaderResourceView, ImVec2(radX, radY), ImVec2(radXMax, radYMax), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
}

void drawDeadPlayerDot(DeadBody* deadBody, ImVec2 winPos, ImU32 color)
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	Vector2 bodyPos = app::DeadBody_get_TruePosition(deadBody, NULL);

	float xOffset = maps[State.mapType].x_offset;
	float yOffset = maps[State.mapType].y_offset;

	if (State.mapType == Settings::MapType::Ship && State.FlipSkeld) {
		xOffset -= 50;
	}

	float radX = xOffset + (bodyPos.x * maps[State.mapType].scale) + winPos.x;
	float radY = yOffset - (bodyPos.y * maps[State.mapType].scale) + winPos.y;

	drawList->AddText(ImGui::GetFont(), 16, ImVec2(radX - 5.F, radY - 6.75F), color, "X");
}

void drawDeadPlayerIcon(DeadBody* deadBody, ImVec2 winPos, ImU32 color)
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	Vector2 bodyPos = app::DeadBody_get_TruePosition(deadBody, NULL);

	float xOffset = maps[State.mapType].x_offset;
	float yOffset = maps[State.mapType].y_offset;

	if (State.mapType == Settings::MapType::Ship && State.FlipSkeld) {
		xOffset -= 50;
	}

	IconTexture icon = icons.at(ICON_TYPES::DEAD);
	float radX = xOffset + (bodyPos.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[State.mapType].scale + winPos.x;
	float radY = yOffset - (bodyPos.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[State.mapType].scale + winPos.y;
	float radXMax = xOffset + (bodyPos.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[State.mapType].scale + winPos.x;
	float radYMax = yOffset - (bodyPos.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[State.mapType].scale + winPos.y;

	drawList->AddImage((void*)icon.iconImage.shaderResourceView, ImVec2(radX, radY), ImVec2(radXMax, radYMax), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f), color);
}