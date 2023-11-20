#include "pch-il2cpp.h"
#include "theme.hpp"
#include "state.hpp"
#include <imgui/imgui.h>

ImVec4 HI(float v) {
	static ImVec4 vec = State.MenuThemeColor;
	if (State.RgbMenuTheme)
		vec = State.RgbColor;
	else
		vec = State.MenuThemeColor;
	return ImVec4(vec.x, vec.y, vec.z, v * State.MenuThemeColor.w);
}

ImVec4 MED(float v) {
	static ImVec4 vec = State.MenuThemeColor;
	if (State.RgbMenuTheme)
		vec = State.RgbColor;
	else
		vec = State.MenuThemeColor;
	return ImVec4((float)(vec.x / 1.25), (float)(vec.y / 1.25), (float)(vec.z / 1.25), v * State.MenuThemeColor.w);
}

ImVec4 LOW(float v) {
	static ImVec4 vec = State.MenuThemeColor;
	if (State.RgbMenuTheme)
		vec = State.RgbColor;
	else
		vec = State.MenuThemeColor;
	return ImVec4((float)(vec.x / 1.5625), (float)(vec.y / 1.5625), (float)(vec.z / 1.5625), v * State.MenuThemeColor.w);
}

#define BG(v)   ImVec4(0.230f, 0.230f, 0.230f, v * State.MenuThemeColor.w)
#define IMGUI_TEXT(v) ImVec4(1.f, 1.f, 1.f, v * State.MenuThemeColor.w)

void ApplyTheme()
{
	static const ImGuiStyle defaultStyle;

	auto& style = ImGui::GetStyle();
	style = defaultStyle;
	style.Colors[ImGuiCol_Text] = IMGUI_TEXT(0.78f);
	style.Colors[ImGuiCol_TextDisabled] = IMGUI_TEXT(0.28f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = BG(1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
	style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
	style.Colors[ImGuiCol_Tab] = MED(0.76f);
	style.Colors[ImGuiCol_TabHovered] = MED(0.86f);
	style.Colors[ImGuiCol_TabActive] = HI(1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
	style.Colors[ImGuiCol_CheckMark] = HI(1.00f);
	style.Colors[ImGuiCol_SliderGrab] = MED(0.78f);
	style.Colors[ImGuiCol_SliderGrabActive] = MED(1.00f);
	style.Colors[ImGuiCol_Button] = BG(1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
	style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
	style.Colors[ImGuiCol_Header] = MED(0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
	style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = BG(0.04f);
	style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
	style.Colors[ImGuiCol_PlotLines] = IMGUI_TEXT(0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = IMGUI_TEXT(0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

	style.WindowPadding = ImVec2(6, 4);
	style.WindowRounding = 4.0f;
	style.FramePadding = ImVec2(5, 2);
	style.FrameRounding = 3.0f;
	style.ItemSpacing = ImVec2(7, 1);
	style.ItemInnerSpacing = ImVec2(1, 1);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 6.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f;
	style.GrabMinSize = 20.0f;
	style.GrabRounding = 2.0f;

	style.WindowTitleAlign.x = 0.50f;

	style.Colors[ImGuiCol_Border] = ImVec4(0.f, 0.f, 0.f, 0.f);
	style.FrameBorderSize = 0.0f;
	style.WindowBorderSize = 0.0f;

	style.ChildBorderSize = 0.0f;

	// scale by dpi
	style.ScaleAllSizes(State.dpiScale);
}