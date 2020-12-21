#include "pch-il2cpp.h"
#include "resources.h"
#include "main.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Resource::Resource(int32_t id)
{
    hResInfo = FindResource(hModule, MAKEINTRESOURCE(id), L"PNG");
    if (hResInfo) {
        hResData = LoadResource(hModule, hResInfo);
        if (hResData) {
            pointerToResource = LockResource(hResData);
            sizeOfResource = SizeofResource(hModule, hResInfo);
        }
    }
}

D3D11Image::D3D11Image(Resource resource, ID3D11Device* pDevice)
{
    if (resource.pointerToResource) {
        auto image_data = stbi_load_from_memory((stbi_uc*)resource.pointerToResource, resource.sizeOfResource, &imageWidth, &imageHeight, NULL, 4);
        if (image_data == NULL)
            return;

        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = imageWidth;
        desc.Height = imageHeight;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;

        ID3D11Texture2D* pTexture = NULL;
        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = image_data;
        subResource.SysMemPitch = desc.Width * 4;
        subResource.SysMemSlicePitch = 0;
        pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        pDevice->CreateShaderResourceView(pTexture, &srvDesc, &shaderResourceView);
        pTexture->Release();

        stbi_image_free(image_data);
    }
}