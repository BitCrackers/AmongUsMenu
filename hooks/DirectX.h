#pragma once
#include "resources.h"
#include "directx11.h"
#include <vector>
#include <unordered_map>
#include <imgui/imgui.h>

enum ICON_TYPES {
	VENT_IN,
	VENT_OUT,
	KILL,
	REPORT,
	TASK,
	PLAYER,
	CROSS
};

struct MapTexture {
	D3D11Image mapImage;
	float x_offset;
	float y_offset;
	float scale;
};

struct IconTexture {
	D3D11Image iconImage;
	float scale;
};

extern std::vector<MapTexture> maps;
extern std::unordered_map<ICON_TYPES, IconTexture> icons;

extern D3D_PRESENT_FUNCTION oPresent;
HRESULT __stdcall dPresent(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags);

namespace DirectX {
	extern HANDLE hRenderSemaphore;
	void Shutdown();
	ImVec2 GetWindowSize();
}