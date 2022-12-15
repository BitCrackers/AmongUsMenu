#pragma once

#include <vector>
#include <mutex>

#include "state.hpp"
#include "game.h"
#include "DirectX.h"
#include <imgui/imgui.h>

static bool IsWithinScreenBounds(const Vector2& pos)
{
	return pos.x < (float)Screen_get_width(nullptr) && pos.y < (float)Screen_get_height(nullptr);
}

static float GetScaleFromValue(float value)
{
	// NOTE : The res of the game can not be lower than the desktop res if the game is in fullscreen.
	// We always need to divide the camera height by 3
	// since 3 is the default zoom in the menu for some reason.
	// We offset from 1080 since the w2s scale is defaulted to that.
	float scale = DirectX::GetWindowSize().y / 1080.0f;

	// If we enable zoom then we scale but otherwise don't
	float cameraHeight = State.EnableZoom ? State.CameraHeight / 3.0f : 1.0f;
	return (value * scale) / cameraHeight;
}

static ImVec2 WorldToScreen(const Vector2& pos)
{
	auto mainCamera = Camera_get_main(nullptr);
	Transform* cameraTransform = Component_get_transform(reinterpret_cast<Component_1*>(mainCamera), nullptr);
	Vector3 cameraPosition = Transform_get_position(cameraTransform, nullptr);
	const Vector2& localPos = PlayerControl_GetTruePosition(*Game::pLocalPlayer, nullptr);

	// Calculation to compensate for Camera movement
	cameraPosition.x = localPos.x - (localPos.x - cameraPosition.x);
	cameraPosition.y = localPos.y - (localPos.y - cameraPosition.y);

	// The value 180 is specific for 1920x1080 so we need to scale it for other resolutions.
	// Scaling from the x axis would probably also work but now we scale from the y axis.
	float view = GetScaleFromValue(180.0f);
	const ImVec2 winsize = DirectX::GetWindowSize();

	// Here we transform the world position to the screen position
	ImVec2 value;
	value.x = (pos.x - cameraPosition.x) * view + winsize.x * 0.5f;
	value.y = (cameraPosition.y - pos.y) * view + winsize.y * 0.5f;

	return value;
}

static Vector2 ScreenToWorld(Vector2 pos)
{
	auto mainCamera = Camera_get_main(nullptr);
	Vector3 vec3 = Camera_ScreenToWorldPoint(mainCamera, { pos.x, pos.y, 0 }, nullptr);
	return { vec3.x, vec3.y };
}

struct EspPlayerData
{
	ImVec2 Position = { 0.0f, 0.0f };
	ImVec4 Color{ 0.0f, 0.0f, 0.0f, 0.0f };

	std::string Name = std::string();

	float Distance = 0.0f;
	bool OnScreen = false;

	PlayerSelection playerData;
};

typedef struct Drawing
{
	std::mutex m_DrawingMutex;

	std::array<EspPlayerData, Game::MAX_PLAYERS> m_Players;

	ImVec2 LocalPosition{ 0.0f, 0.0f };
} drawing_t;

class Esp
{
public:
	static void Render();

	static drawing_t& GetDrawing() { return *s_Instance; }
private:
	static drawing_t* s_Instance;
};