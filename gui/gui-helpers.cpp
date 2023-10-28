#include "pch-il2cpp.h"
#include "gui-helpers.hpp"
#include "keybinds.h"
#include "state.hpp"
#include "game.h"
#include "logger.h"
#include "DirectX.h"
#include <DirectX.h>

using namespace ImGui;

bool CustomListBoxInt(const char* label, int* value, const std::vector<const char*> list, float width, ImGuiComboFlags flags) {
	auto comboLabel = "##" + std::string(label);
	auto leftArrow = "##" + std::string(label) + "Left";
	auto rightArrow = "##" + std::string(label) + "Right";

	ImGuiStyle& style = GetStyle();
	float spacing = style.ItemInnerSpacing.x;
	PushItemWidth(width);
	bool response = BeginCombo(comboLabel.c_str(), (*value >= 0 ? list.at(*value) : nullptr), ImGuiComboFlags_NoArrowButton | flags);
	if (response) {
		response = false;
		for (size_t i = 0; i < list.size(); i++) {
			bool is_selected = (*value == i);
			if (Selectable(list.at(i), is_selected)) {
				*value = (int)i;
				response = true;
			}
			if (is_selected)
				SetItemDefaultFocus();
		}
		EndCombo();
	}

	PopItemWidth();
	SameLine(0, spacing);

	const bool LeftResponse = ArrowButton(leftArrow.c_str(), ImGuiDir_Left);
	if (LeftResponse) {
		*value -= 1;
		if (*value < 0) *value = int(list.size() - 1);
		return LeftResponse;
	}
	SameLine(0, spacing);
	const bool RightResponse = ArrowButton(rightArrow.c_str(), ImGuiDir_Right);
	if (RightResponse) {
		*value += 1;
		if (*value > (int)(list.size() - 1)) *value = 0;
		return RightResponse;
	}
	SameLine(0, spacing);
	Text(label);

	return response;
}

bool CustomListBoxIntMultiple(const char* label, std::vector<std::pair<const char*, bool>>* list, float width, bool resetButton, ImGuiComboFlags flags) {
	auto comboLabel = "##" + std::string(label);
	auto buttonLabel = "Reset##" + std::string(label);
	ImGuiStyle& style = GetStyle();
	float spacing = style.ItemInnerSpacing.x;
	PushItemWidth(width);
	size_t countSelected = 0;
	for (auto& pair : *list) {
		if (pair.second) {
			countSelected++;
		}
	}
	std::string preview;
	if (countSelected > 0) {
		char buf[32] = { 0 };
		sprintf_s(buf, "%zu item(s) selected", countSelected);
		preview = buf;
	}
	else
		preview = label;
	bool response = BeginCombo(comboLabel.c_str(), preview.c_str(), flags);
	if (response) {
		response = false;
		for (auto& pair : *list) {
			if (strcmp(pair.first, "") == 0) // ignore all entries with empty labels so we can create padding
				continue;
			if (Selectable(pair.first, pair.second)) {
				pair.second ^= 1;
				response = true;
			}
			if (pair.second)
				SetItemDefaultFocus();
		}
		EndCombo();
	}

	PopItemWidth();

	if (resetButton)
	{
		SameLine(0, spacing);
		const bool resetResponse = Button(buttonLabel.c_str());
		if (resetResponse) {
			for (auto& pair : *list)
				pair.second = false;
			return resetResponse;
		}
	}
	
	return response;
}

bool CustomListBoxPlayerSelectionMultiple(const char* label, std::array<std::pair<PlayerSelection, bool>, Game::MAX_PLAYERS>* list, float width, bool resetButton, ImGuiComboFlags flags) {
	if (!IsInGame()) return false; // works only ingame

	auto comboLabel = "##" + std::string(label);
	auto buttonLabel = "Reset##" + std::string(label);
	ImGuiStyle& style = GetStyle();
	float spacing = style.ItemInnerSpacing.x;
	PushItemWidth(width);
	size_t countSelected = 0;
	for (auto& pair : *list) {
		if (pair.second) {
			countSelected++;
		}
	}
	std::string preview;
	if (countSelected > 0) {
		char buf[32] = { 0 };
		sprintf_s(buf, "%zu player(s) selected", countSelected);
		preview = buf;
	}
	else
		preview = label;
	bool response = BeginCombo(comboLabel.c_str(), preview.c_str(), flags);
	if (response) {
		response = false;
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		for (auto playerData : GetAllPlayerData()) {
			auto playerSelection = PlayerSelection(playerData);
			const auto& player = playerSelection.validate();
			if (!player.has_value())
				continue;
			if (player.is_Disconnected()) // maybe make that an option for replays ? (parameter based on "state.showDisconnected" related data)
				continue;

			app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(playerData);
			if (outfit == NULL) return false;
			auto& item = list->at(playerData->fields.PlayerId);
			std::string playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
			PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0) * State.dpiScale);
			PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0) * State.dpiScale);
			if (Selectable(std::string("##" + playerName + "_ConsoleName").c_str(), item.second))
			{
				item.second ^= 1;
				if (item.second)
				{
					if (const auto& result = item.first.validate();
						!result.has_value() || result.is_Disconnected())
						item.first = playerSelection;
				}
				response = true;
			}
			if (item.second)
				SetItemDefaultFocus();
			SameLine();
			ColorButton(std::string("##" + playerName + "_ConsoleColorButton").c_str(), AmongUsColorToImVec4(GetPlayerColor(outfit->fields.ColorId)), ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
			SameLine();
			PopStyleVar(2);
			Dummy(ImVec2(0, 0) * State.dpiScale);
			SameLine();

			ImVec4 nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->White);
			if (State.RevealRoles)
			{
				std::string roleName = GetRoleName(playerData->fields.Role);
				playerName = playerName + " (" + roleName + ")";
				nameColor = AmongUsColorToImVec4(GetRoleColor(playerData->fields.Role));
			}
			else if (PlayerIsImpostor(localData) && PlayerIsImpostor(playerData))
				nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->ImpostorRed);
			else if (player.is_LocalPlayer() || std::count(State.aumUsers.begin(), State.aumUsers.end(), playerData->fields.PlayerId))
				nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->Orange);

			if (playerData->fields.IsDead)
				nameColor = AmongUsColorToImVec4(Palette__TypeInfo->static_fields->DisabledGrey);

			TextColored(nameColor, playerName.c_str());
		}
		EndCombo();
	}

	PopItemWidth();

	if (resetButton)
	{
		SameLine(0, spacing);
		const bool resetResponse = Button(buttonLabel.c_str());
		if (resetResponse) {
			for (size_t i = 0; i < list->size(); i++)
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
	const bool valueChanged = SliderInt(label, &v_i, 0, stepCount, text_buf);

	*v = v_min + float(v_i) * v_step;
	return valueChanged;
}

bool SliderChrono(const char* label, void* p_data, const void* p_min, const void* p_max, std::string_view format, ImGuiSliderFlags flags)
{
	flags |= ImGuiSliderFlags_NoInput; // disable manual inputs by default

	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	if (!State.Replay_IsLive && !State.Replay_IsPlaying) {
		const auto& playIcon = icons.at(ICON_TYPES::PLAY);
		const auto& iconSize = ImVec2((float)playIcon.iconImage.imageWidth, (float)playIcon.iconImage.imageHeight) * playIcon.scale;
		if (ImGui::ImageButton((ImTextureID)playIcon.iconImage.shaderResourceView, iconSize))
		{
			State.Replay_IsPlaying = true;
		}
	}
	else {
		// Live or Playing
		const auto& pauseIcon = icons.at(ICON_TYPES::PAUSE);
		const auto& iconSize = ImVec2((float)pauseIcon.iconImage.imageWidth, (float)pauseIcon.iconImage.imageHeight) * pauseIcon.scale;
		if (ImGui::ImageButton((ImTextureID)pauseIcon.iconImage.shaderResourceView, iconSize))
		{
			State.Replay_IsPlaying = State.Replay_IsLive = false;
		}
	}

	ImGui::SameLine(0.0f * State.dpiScale, 1.0f * State.dpiScale);

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w = CalcItemWidth();

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, id, &frame_bb))
		return false;

	// Tabbing or CTRL-clicking on Slider turns it into an input box
	const bool hovered = ItemHoverable(frame_bb, id);
	bool clicked = false;;
	const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
	bool temp_input_is_active = temp_input_allowed && TempInputIsActive(id);
	if (!temp_input_is_active)
	{
		const bool focus_requested = temp_input_allowed && FocusableItemRegister(window, id);
		clicked = (hovered && g.IO.MouseClicked[0]);
		if (focus_requested || clicked || g.NavActivateId == id || g.NavInputId == id)
		{
			SetActiveID(id, window);
			SetFocusID(id, window);
			FocusWindow(window);
			g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
			if (temp_input_allowed && (focus_requested || (clicked && g.IO.KeyCtrl) || g.NavInputId == id))
			{
				temp_input_is_active = true;
				FocusableItemUnregister(window);
			}
		}
	}

	// Draw frame
	const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	RenderNavHighlight(frame_bb, id);
	RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, g.Style.FrameRounding);

	// Slider behavior
	ImRect grab_bb;
	const bool value_changed = SliderBehavior(frame_bb, id, ImGuiDataType_S64, p_data, p_min, p_max, nullptr, flags | ImGuiSliderFlags_NoRoundToFormat, &grab_bb);
	if (value_changed) {
		MarkItemEdited(id);

		// check if new current timestamp is matching the live timestamp
		// this logic makes sure that we can switch between live and replay mode
		auto newMatchCurrent = std::chrono::time_point_cast<std::chrono::seconds>(State.MatchCurrent);
		auto matchLiveMs = std::chrono::time_point_cast<std::chrono::seconds>(State.MatchLive);
		if (newMatchCurrent == matchLiveMs)
		{
			State.Replay_IsLive = true;
			State.Replay_IsPlaying = false;
		}
		else
		{
			State.Replay_IsLive = false;
		}
	}

	// Render grab
	if (grab_bb.Max.x > grab_bb.Min.x)
		window->DrawList->AddRectFilled(grab_bb.Min, grab_bb.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	RenderTextClipped(frame_bb.Min, frame_bb.Max, format.data(), format.data() + format.length(), NULL, ImVec2(0.5f, 0.5f));

	if (label_size.x > 0.0f)
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	ImGui::SameLine(0.0f * State.dpiScale, 10.0f * State.dpiScale);

	ImU32 liveColor = (State.Replay_IsLive) ? ImGui::ColorConvertFloat4ToU32(ImVec4(255.0f, 0.f, 0.f, 255.0f)) : ImGui::ColorConvertFloat4ToU32(ImVec4(128.f, 128.f, 128.f, 255.0f));
	const ImVec2 circlePos(window->DC.CursorPos.x, window->DC.CursorPos.y + 9.5f * State.dpiScale);
	window->DrawList->AddCircleFilled(circlePos, 5.0f * State.dpiScale, liveColor);
	ImGui::SameLine(0.0f * State.dpiScale, 18.f * State.dpiScale);
	ImGui::Text("Live");


	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);

	return value_changed;
}

bool HotKey(uint8_t& key)
{
	Text("[ %s ]", KeyBinds::ToString(key));

	if (!IsItemHovered())
		return false;

	SetTooltip("Press any key to change the keybind, ESC to reset");
	for (uint8_t vKey : KeyBinds::GetValidKeys()) {
		if (KeyBinds::IsKeyDown(vKey)) {
			key = (vKey != VK_ESCAPE ? vKey : 0x00);
			return true;
		}
	}

	return false;
}

void drawPlayerDot(PlayerControl* player, const ImVec2& winPos, ImU32 color, ImU32 statusColor)
{
	ImDrawList* drawList = GetWindowDrawList();

	Vector2 playerPos = app::PlayerControl_GetTruePosition(player, NULL);

	const auto& map = maps[(size_t)State.mapType];
	float xOffset = getMapXOffsetSkeld(map.x_offset);
	float yOffset = map.y_offset;

	float radX = xOffset + (playerPos.x * map.scale);
	float radY = yOffset - (playerPos.y * map.scale);
	const ImVec2& center = ImVec2(radX, radY) * State.dpiScale + winPos;

	drawList->AddCircleFilled(center, 4.5F * State.dpiScale, color);
	drawList->AddCircle(center, (4.5F + 0.5F) * State.dpiScale, statusColor, 0, 2.0F);
}

void drawPlayerIcon(PlayerControl* player, const ImVec2& winPos, ImU32 color)
{
	ImDrawList* drawList = GetWindowDrawList();

	Vector2 playerPos = app::PlayerControl_GetTruePosition(player, NULL);

	const auto& map = maps[(size_t)State.mapType];
	float xOffset = getMapXOffsetSkeld(map.x_offset);
	float yOffset = map.y_offset;

	IconTexture icon = icons.at(ICON_TYPES::PLAYER);
	float halfImageWidth = icon.iconImage.imageWidth * icon.scale * 0.5f, halfImageHeight = icon.iconImage.imageHeight * icon.scale * 0.5f;
	float radX = xOffset + (playerPos.x - halfImageWidth) * map.scale;
	float radY = yOffset - (playerPos.y - halfImageHeight) * map.scale;
	float radXMax = xOffset + (playerPos.x + halfImageWidth) * map.scale;
	float radYMax = yOffset - (playerPos.y + halfImageHeight) * map.scale;

	const ImVec2& p_min = ImVec2(radX, radY) * State.dpiScale + winPos;
	const ImVec2& p_max = ImVec2(radXMax, radYMax) * State.dpiScale + winPos;

	drawList->AddImage((void*)icon.iconImage.shaderResourceView, 
		p_min, p_max,
		ImVec2(0.0f, 1.0f),
		ImVec2(1.0f, 0.0f),
		color);

	if (GetPlayerData(player)->fields.IsDead)
		drawList->AddImage((void*)icons.at(ICON_TYPES::CROSS).iconImage.shaderResourceView, 
			p_min, p_max,
			ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
}

void drawDeadPlayerDot(DeadBody* deadBody, const ImVec2& winPos, ImU32 color)
{
	ImDrawList* drawList = GetWindowDrawList();

	Vector2 bodyPos = app::DeadBody_get_TruePosition(deadBody, NULL);

	const auto& map = maps[(size_t)State.mapType];
	float xOffset = getMapXOffsetSkeld(map.x_offset);
	float yOffset = map.y_offset;

	float radX = xOffset + (bodyPos.x * map.scale);
	float radY = yOffset - (bodyPos.y * map.scale);

	drawList->AddText(GetFont(), 16 * State.dpiScale, 
		ImVec2(radX - 5.F, radY - 6.75F) * State.dpiScale + winPos, color, "X");
}

void drawDeadPlayerIcon(DeadBody* deadBody, const ImVec2& winPos, ImU32 color)
{
	ImDrawList* drawList = GetWindowDrawList();

	Vector2 bodyPos = app::DeadBody_get_TruePosition(deadBody, NULL);

	const auto& map = maps[(size_t)State.mapType];
	float xOffset = getMapXOffsetSkeld(map.x_offset);
	float yOffset = map.y_offset;

	IconTexture icon = icons.at(ICON_TYPES::DEAD);
	float radX = xOffset + (bodyPos.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
	float radY = yOffset - (bodyPos.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;
	float radXMax = xOffset + (bodyPos.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * map.scale;
	float radYMax = yOffset - (bodyPos.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * map.scale;

	drawList->AddImage((void*)icon.iconImage.shaderResourceView, 
		ImVec2(radX, radY) * State.dpiScale + winPos,
		ImVec2(radXMax, radYMax) * State.dpiScale + winPos,
		ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f), color);
}