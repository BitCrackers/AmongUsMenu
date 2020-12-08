#pragma once
#include "resources.h"
#include <vector>

struct MapTexture {
	D3D11Image mapImage;
	float x_offset;
	float y_offset;
	float scale;
};

typedef HRESULT(__stdcall* D3D_PRESENT_FUNCTION)(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);

extern D3D_PRESENT_FUNCTION oPresent;
extern std::vector<MapTexture> maps;

HRESULT __stdcall dPresent(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags);

namespace DirectX {
	void Initialize();
	void Shutdown();
}