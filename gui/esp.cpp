#include "pch-il2cpp.h"
#include "esp.hpp"
#include "DirectX.h"
#include "utility.h"
#include "game.h"

#include <../includes/imgui/imgui_internal.h> // TODO : Fix this dir mess

#include <iostream>

drawing_t* Esp::s_Instance = new drawing_t();
ImGuiWindow* Window = nullptr;

static void RenderText(const char* text, const ImVec2& pos, const ImVec4& color, const bool outlined = true, const bool centered = true)
{
	if (!text) return;
	ImVec2& ImScreen = *(ImVec2*)&pos; // Type punning is safe here
	if (centered)
	{
		auto size = ImGui::CalcTextSize(text);
		ImScreen.x -= size.x * 0.5f;
		ImScreen.y -= size.y;
	}

	if (outlined)
	{
		Window->DrawList->AddText(nullptr, 0.f,
		{ ImScreen.x - 1.f, ImScreen.y + 1.f },
		ImGui::GetColorU32(IM_COL32_BLACK), text);
	}

	Window->DrawList->AddText(nullptr, 0.f, ImScreen, ImGui::GetColorU32(color), text);
}

static void RenderLine(const ImVec2& start, const ImVec2& end, const ImVec4& color, bool shadow = false) noexcept
{
	if (shadow)
	{
		Window->DrawList->AddLine(
		{ start.x + 1.0f, start.y + 1.0f },
		{ end.x + 1.0f, end.y + 1.0f },
		ImGui::GetColorU32(color) & IM_COL32_A_MASK);
	}

	Window->DrawList->AddLine(start, end, ImGui::GetColorU32(color));
}

static void RenderBox(const ImVec2 top, const ImVec2 bottom, const float height, const float width, const ImVec4& color, const bool wantsShadow = true)
{
	RenderLine(bottom, { bottom.x, ((float)(int)(bottom.y * 0.75f + top.y * 0.25f)) }, color, wantsShadow);
	RenderLine(bottom, { ((float)(int)(bottom.x * 0.75f + top.x * 0.25f)), bottom.y }, color, wantsShadow);

	RenderLine({ top.x, bottom.y }, { ((float)(int)(top.x * 0.75f + bottom.x * 0.25f)), bottom.y }, color, wantsShadow);
	RenderLine({ top.x - 1.0f, bottom.y }, { top.x - 1.0f, ((float)(int)(bottom.y * 0.75f + top.y * 0.25f)) }, color, wantsShadow);

	RenderLine({ bottom.x, top.y }, { bottom.x, ((float)(int)(top.y * 0.75f + bottom.y * 0.25f)) }, color, wantsShadow);
	RenderLine({ bottom.x, top.y - 1.0f }, { ((float)(int)(bottom.x * 0.75f + top.x * 0.25f)), top.y - 1.0f }, color, wantsShadow);

	RenderLine({ top.x - 0.5f, top.y - 1.0f }, { ((float)(int)(top.x * 0.75f + bottom.x * 0.25f)), top.y - 1.0f }, color, wantsShadow);
	RenderLine({ top.x - 1.0f, top.y }, { top.x - 1.0f, ((float)(int)(top.y * 0.75f + bottom.y * 0.25f)) }, color, wantsShadow);
}

void Esp::Render()
{
	Window = ImGui::GetCurrentWindow();

	drawing_t& instance = Esp::GetDrawing();

	// Lock our mutex when we render (this will unlock when it goes out of scope)
	std::lock_guard<std::mutex> lock(instance.m_DrawingMutex);

	for (auto& it : instance.m_Players)
	{
		if (!it.Name.empty() && it.OnScreen)
		{
			/////////////////////////////////
			//// Box ////////////////////////
			/////////////////////////////////
			if (State.ShowEsp_Box)
			{
				// NOTE : The res of the game can not be lower than the desktop res if the game is in fullscreen
				const ImVec2 winsize{ (float)app::Screen_get_width(nullptr), (float)app::Screen_get_height(nullptr) };
				float scale = winsize.y / 1080.0f; // We offset from 1080 since the w2s scale is defaulted to that

				// NOTE : We always need to divide the camera height by 3
				// since 3 is the default zoom in the menu for some reason
				float width = (35.0f * scale) / (State.CameraHeight / 3);
				float height = (120.0f * scale) / (State.CameraHeight / 3);

				ImVec2 top{ it.Position.x + width, it.Position.y };
				ImVec2 bottom{ it.Position.x - width, it.Position.y - height };

				RenderBox(top, bottom, height, width, it.Color);
			}
			/////////////////////////////////
			//// Distance ///////////////////
			/////////////////////////////////
			if (State.ShowEsp_Distance)
			{
				const ImVec2 position{ it.Position.x, it.Position.y + 15.0f };

				char distance[32];
				sprintf_s(distance, "[%.0fm]", it.Distance);

				RenderText(distance, position, it.Color);
			}
			/////////////////////////////////
			//// Tracers ////////////////////
			/////////////////////////////////
			if (State.ShowEsp_Tracers)
			{
				RenderLine(instance.LocalPosition, it.Position, it.Color, true);
			}
		}

		instance.m_Players.empty();
	}
}