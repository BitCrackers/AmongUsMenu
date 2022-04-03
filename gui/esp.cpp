#include "pch-il2cpp.h"
#include "esp.hpp"
#include "DirectX.h"
#include "utility.h"
#include "game.h"

#include <imgui/imgui_internal.h>

drawing_t* Esp::s_Instance = new drawing_t();
ImGuiWindow* CurrentWindow = nullptr;

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
		CurrentWindow->DrawList->AddText(nullptr, 0.f,
		{ ImScreen.x - 1.f, ImScreen.y + 1.f },
		ImGui::GetColorU32(IM_COL32_BLACK), text);
	}

	CurrentWindow->DrawList->AddText(nullptr, 0.f, ImScreen, ImGui::GetColorU32(color), text);
}

static void RenderLine(const ImVec2& start, const ImVec2& end, const ImVec4& color, bool shadow = false) noexcept
{
	if (shadow)
	{
		CurrentWindow->DrawList->AddLine(
		{ start.x + 1.0f, start.y + 1.0f },
		{ end.x + 1.0f, end.y + 1.0f },
		ImGui::GetColorU32(color) & IM_COL32_A_MASK);
	}

	CurrentWindow->DrawList->AddLine(start, end, ImGui::GetColorU32(color));
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
	CurrentWindow = ImGui::GetCurrentWindow();

	drawing_t& instance = Esp::GetDrawing();

	// Lock our mutex when we render (this will unlock when it goes out of scope)
	std::lock_guard<std::mutex> lock(instance.m_DrawingMutex);

	for (auto& it : instance.m_Players)
	{
		if (it.playerData.has_value()				//Verify PlayerControl hasn't been destroyed (happens when disconnected)
			&& !it.playerData.is_Disconnected()		//Sanity check, shouldn't ever be true
			&& !it.playerData.is_LocalPlayer()		//Don't highlight yourself, you're ugly
			&& (!it.playerData.get_PlayerData()->fields.IsDead || State.ShowEsp_Ghosts)
			&& it.OnScreen)
		{
			/////////////////////////////////
			//// Box ////////////////////////
			/////////////////////////////////
			if (State.ShowEsp_Box)
			{
				float width = GetScaleFromValue(35.0f * State.dpiScale);
				float height = GetScaleFromValue(120.0f * State.dpiScale);

				ImVec2 top{ it.Position.x + width, it.Position.y };
				ImVec2 bottom{ it.Position.x - width, it.Position.y - height };

				RenderBox(top, bottom, height, width, it.Color);
			}
			/////////////////////////////////
			//// Distance ///////////////////
			/////////////////////////////////
			if (State.ShowEsp_Distance)
			{
				const ImVec2 position{ it.Position.x, it.Position.y + 15.0f * State.dpiScale };

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
	}
}
