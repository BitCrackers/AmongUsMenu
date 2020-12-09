#pragma once
#include <stdint.h>
#include <dxgi.h>
#include <d3d11.h>

typedef HRESULT(__stdcall* D3D_PRESENT_FUNCTION)(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags);

class directx11 {
public:
    D3D_PRESENT_FUNCTION presentFunction;
    directx11();
};