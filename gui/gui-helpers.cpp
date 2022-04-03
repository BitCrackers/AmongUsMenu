#include "pch-il2cpp.h"
#include "gui-helpers.hpp"
#include "keybinds.h"
#include "state.hpp"
#include "game.h"
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
	const bool response = BeginCombo(comboLabel.c_str(), list.at(*value), ImGuiComboFlags_NoArrowButton | flags);
	if (response) {
		for (size_t i = 0; i < list.size(); i++) {
			bool is_selected = (*value == i);
			if (Selectable(list.at(i), is_selected))
				*value = i;
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
		if (*value < 0) *value = (list.size() - 1);
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
	const bool response = BeginCombo(comboLabel.c_str(), label, flags);
	if (response) {
		for (size_t i = 0; i < list->size(); i++) {
			if (strcmp(list->at(i).first, "") == 0) // ignore all entries with empty labels so we can create padding
				continue;
			if (Selectable(list->at(i).first, list->at(i).second))
				list->at(i).second ^= 1;
			if (list->at(i).second)
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
			for (size_t i = 0; i < list->size(); i++)
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
	ImGuiStyle& style = GetStyle();
	float spacing = style.ItemInnerSpacing.x;
	PushItemWidth(width);
	const bool response = BeginCombo(comboLabel.c_str(), label, flags);
	if (response) {
		auto localData = GetPlayerData(*Game::pLocalPlayer);
		for (auto playerData : GetAllPlayerData()) {
			if (playerData->fields.Disconnected) // maybe make that an option for replays ? (parameter based on "state.showDisconnected" related data)
				continue;

			std::string playerName = convert_from_string(GetPlayerOutfit(playerData)->fields._playerName);
			PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0) * State.dpiScale);
			PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0) * State.dpiScale);
			if (Selectable(std::string("##" + playerName + "_ConsoleName").c_str(), list->at(playerData->fields.PlayerId).second))
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
				SetItemDefaultFocus();
			SameLine();
			ColorButton(std::string("##" + playerName + "_ConsoleColorButton").c_str(), AmongUsColorToImVec4(GetPlayerColor(GetPlayerOutfit(playerData)->fields.ColorId)), ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip);
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
			else if (PlayerSelection(playerData).is_LocalPlayer() || std::count(State.aumUsers.begin(), State.aumUsers.end(), playerData->fields.PlayerId))
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

bool SliderChrono(const char* label, void* p_data, const void* p_min, const void* p_max, std::string format, ImGuiSliderFlags flags)
{
	flags |= ImGuiSliderFlags_NoInput; // disable manual inputs by default

	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	if (ImGui::ImageButton((void*)icons.at(ICON_TYPES::PLAY).iconImage.shaderResourceView,
		ImVec2(icons.at(ICON_TYPES::PLAY).iconImage.imageWidth * icons.at(ICON_TYPES::PLAY).scale,
			icons.at(ICON_TYPES::PLAY).iconImage.imageHeight * icons.at(ICON_TYPES::PLAY).scale)))
	{
		State.Replay_IsPlaying = true;
	}

	ImGui::SameLine(0.0f * State.dpiScale, 1.0f * State.dpiScale);

	if (ImGui::ImageButton((void*)icons.at(ICON_TYPES::PAUSE).iconImage.shaderResourceView,
		ImVec2(icons.at(ICON_TYPES::PAUSE).iconImage.imageWidth * icons.at(ICON_TYPES::PAUSE).scale,
			icons.at(ICON_TYPES::PAUSE).iconImage.imageHeight * icons.at(ICON_TYPES::PAUSE).scale)))
	{
		State.Replay_IsPlaying = State.Replay_IsLive = false;
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
	if (value_changed)
		MarkItemEdited(id);

	// check if new current timestamp is matching the live timestamp
	// this logic makes sure that we can switch between live and replay mode
	auto newMatchCurrent = std::chrono::time_point_cast<std::chrono::seconds>(State.MatchCurrent).time_since_epoch().count();
	auto matchLiveMs = std::chrono::time_point_cast<std::chrono::seconds>(State.MatchLive).time_since_epoch().count();
	if (newMatchCurrent == matchLiveMs)
	{
		State.Replay_IsLive = true;
		State.Replay_IsPlaying = false;
	}
	else
	{
		State.Replay_IsLive = false;
	}

	// Render grab
	if (grab_bb.Max.x > grab_bb.Min.x)
		window->DrawList->AddRectFilled(grab_bb.Min, grab_bb.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	RenderTextClipped(frame_bb.Min, frame_bb.Max, &format[0], &format[format.size()], NULL, ImVec2(0.5f, 0.5f));

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

void drawPlayerDot(PlayerControl* player, ImVec2 winPos, ImU32 color, ImU32 statusColor)
{
	ImDrawList* drawList = GetWindowDrawList();

	Vector2 playerPos = app::PlayerControl_GetTruePosition(player, NULL);

	float xOffset = maps[State.mapType].x_offset;
	float yOffset = maps[State.mapType].y_offset;

	if (State.mapType == Settings::MapType::Ship && State.FlipSkeld) {
		xOffset -= 50;
	}

	float radX = xOffset + (playerPos.x * maps[State.mapType].scale);
	float radY = yOffset - (playerPos.y * maps[State.mapType].scale);
	const ImVec2& center = ImVec2(radX, radY) * State.dpiScale + winPos;

	drawList->AddCircleFilled(center, 4.5F * State.dpiScale, color);
	drawList->AddCircle(center, (4.5F + 0.5F) * State.dpiScale, statusColor, 0, 2.0F);
}

void drawPlayerIcon(PlayerControl* player, ImVec2 winPos, ImU32 color)
{
	ImDrawList* drawList = GetWindowDrawList();

	Vector2 playerPos = app::PlayerControl_GetTruePosition(player, NULL);

	float xOffset = maps[State.mapType].x_offset;
	float yOffset = maps[State.mapType].y_offset;

	if (State.mapType == Settings::MapType::Ship && State.FlipSkeld) {
		xOffset -= 50;
	}

	IconTexture icon = icons.at(ICON_TYPES::PLAYER);
	float radX = xOffset + (playerPos.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[State.mapType].scale;
	float radY = yOffset - (playerPos.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[State.mapType].scale;
	float radXMax = xOffset + (playerPos.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[State.mapType].scale;
	float radYMax = yOffset - (playerPos.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[State.mapType].scale;

	const ImVec2& p_min = ImVec2(radX, radY) * State.dpiScale + winPos;
	const ImVec2& p_max = ImVec2(radXMax, radYMax) * State.dpiScale + winPos;

	drawList->AddImage((void*)icon.iconImage.shaderResourceView, 
		p_min, p_max,
		ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f), color);

	if (GetPlayerData(player)->fields.IsDead)
		drawList->AddImage((void*)icons.at(ICON_TYPES::CROSS).iconImage.shaderResourceView, 
			p_min, p_max,
			ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
}

void drawDeadPlayerDot(DeadBody* deadBody, ImVec2 winPos, ImU32 color)
{
	ImDrawList* drawList = GetWindowDrawList();

	Vector2 bodyPos = app::DeadBody_get_TruePosition(deadBody, NULL);

	float xOffset = maps[State.mapType].x_offset;
	float yOffset = maps[State.mapType].y_offset;

	if (State.mapType == Settings::MapType::Ship && State.FlipSkeld) {
		xOffset -= 50;
	}

	float radX = xOffset + (bodyPos.x * maps[State.mapType].scale);
	float radY = yOffset - (bodyPos.y * maps[State.mapType].scale);

	drawList->AddText(GetFont(), 16 * State.dpiScale, 
		ImVec2(radX - 5.F, radY - 6.75F) * State.dpiScale + winPos, color, "X");
}

void drawDeadPlayerIcon(DeadBody* deadBody, ImVec2 winPos, ImU32 color)
{
	ImDrawList* drawList = GetWindowDrawList();

	Vector2 bodyPos = app::DeadBody_get_TruePosition(deadBody, NULL);

	float xOffset = maps[State.mapType].x_offset;
	float yOffset = maps[State.mapType].y_offset;

	if (State.mapType == Settings::MapType::Ship && State.FlipSkeld) {
		xOffset -= 50;
	}

	IconTexture icon = icons.at(ICON_TYPES::DEAD);
	float radX = xOffset + (bodyPos.x - (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[State.mapType].scale;
	float radY = yOffset - (bodyPos.y - (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[State.mapType].scale;
	float radXMax = xOffset + (bodyPos.x + (icon.iconImage.imageWidth * icon.scale * 0.5f)) * maps[State.mapType].scale;
	float radYMax = yOffset - (bodyPos.y + (icon.iconImage.imageHeight * icon.scale * 0.5f)) * maps[State.mapType].scale;

	drawList->AddImage((void*)icon.iconImage.shaderResourceView, 
		ImVec2(radX, radY) * State.dpiScale + winPos,
		ImVec2(radXMax, radYMax) * State.dpiScale + winPos,
		ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f), color);
}