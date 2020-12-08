#include "DirectX.h"
#include "console.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "imhotkeys.h"
#include "menu.hpp"
#include "radar.hpp"
#include "state.hpp"
#include "theme.hpp"
#include <iostream>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND window;
ID3D11Device* pDevice;
ID3D11DeviceContext* pContext;
ID3D11RenderTargetView* pRenderTargetView;
D3D_PRESENT_FUNCTION oPresent;
WNDPROC oWndProc;

std::vector<MapTexture> maps = std::vector<MapTexture>();

LRESULT __stdcall dWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (!State.ImGuiInitialized)
        return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);

    ImHotkeys::WndProc(uMsg, wParam);

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    if (!ImGui::IsPopupOpen("", ImGuiPopupFlags_AnyPopup)) {
        auto shortcut = ImHotkeys::GetShortcut(&State.Shortcuts);
        if (shortcut != -1) {
            if (shortcut == 0) State.ShowMenu = !State.ShowMenu;
            if (shortcut == 1) State.ShowRadar = !State.ShowRadar;
            if (shortcut == 2) State.ShowConsole = !State.ShowConsole;
            if (shortcut == 3 && IsInGame()) RepairSabotage(*Game::pLocalPlayer);
        }
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall dPresent(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags) {
    if (!State.ImGuiInitialized) {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)dWndProc);

            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
            ImGui_ImplWin32_Init(window);
            ImGui_ImplDX11_Init(pDevice, pContext);

            maps.push_back({ D3D11Image(Resource(IDB_PNG1), pDevice), 277.F, 77.F, 11.5F });
            maps.push_back({ D3D11Image(Resource(IDB_PNG2), pDevice), 115.F, 240.F, 9.25F });
            maps.push_back({ D3D11Image(Resource(IDB_PNG3), pDevice), 8.F, 21.F, 10.F });

            State.ImGuiInitialized = true;
        } else {
            return oPresent(pSwapChain, syncInterval, flags);
        }
    }

    il2cpp_gc_disable();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ApplyTheme();

    if (!IsInGame()) {
        State.selectedPlayer = PlayerSelection();
        State.playerToFollow = PlayerSelection();
        State.NoClip = false;
        State.FreeCam = false;
        State.InMeeting = false;
        State.FollowerCam = nullptr;
        State.EnableZoom = false;

        if (!IsInLobby()) {
            State.FlipSkeld = false;
        }
    }

    if (State.ShowMenu) {
        Menu::Render();
    }

    if (IsInGame() && State.ShowRadar && (!State.InMeeting || !State.HideRadar_During_Meetings)) {
        Radar::Render();
    }

    if (State.ShowConsole) {
        ConsoleGui::Render();
    }

    ImGui::EndFrame();
    ImGui::Render();

    pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    il2cpp_gc_enable();

    return oPresent(pSwapChain, syncInterval, flags);
}

void DirectX::Initialize()
{
    ID3D11Device* pDevice = NULL;
    IDXGISwapChain* pSwapchain = NULL;

    D3D_FEATURE_LEVEL featureLevel;
    DXGI_SWAP_CHAIN_DESC swapChainDesc{ 0 };

    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.Height = 800;
    swapChainDesc.BufferDesc.Width = 600;
    swapChainDesc.BufferDesc.RefreshRate = { 60, 1 };
    swapChainDesc.OutputWindow = GetForegroundWindow();
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_REFERENCE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &swapChainDesc, &pSwapchain, &pDevice, &featureLevel, nullptr);
    if (FAILED(result)) return;

    void** pVMT = *(void***)pSwapchain;
    oPresent = (D3D_PRESENT_FUNCTION)pVMT[8];

    if (pDevice) {
        pDevice->Release();
        pDevice = NULL;
    }

    if (pSwapchain) {
        pSwapchain->Release();
        pSwapchain = NULL;
    }
}

void DirectX::Shutdown() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
}