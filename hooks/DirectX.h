#pragma once
#include "resources.h"
#include "directx11.h"
#include <vector>

struct MapTexture {
	D3D11Image mapImage;
	float x_offset;
	float y_offset;
	float scale;
};

extern std::vector<MapTexture> maps;

extern D3D_PRESENT_FUNCTION oPresent;
HRESULT __stdcall dPresent(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags);

namespace DirectX {
	void Shutdown();
}