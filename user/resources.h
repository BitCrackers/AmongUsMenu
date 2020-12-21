#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d11.h>

struct Resource {
    HRSRC hResInfo;
    HGLOBAL hResData;
    LPVOID pointerToResource;
    DWORD sizeOfResource;

    Resource(int32_t id);
};

struct D3D11Image {
    ID3D11ShaderResourceView* shaderResourceView;
    int32_t imageWidth;
    int32_t imageHeight;

    D3D11Image(Resource resource, ID3D11Device* pDevice);
};