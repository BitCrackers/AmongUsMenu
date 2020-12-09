#include "DirectX.h"
#include "console.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "keyBindsConfig.h"
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

HANDLE hPresentMutex;

std::vector<MapTexture> maps = std::vector<MapTexture>();

LRESULT __stdcall dWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (!State.ImGuiInitialized)
        return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    if (ImGui::IsKeyReleased(State.KeyBinds.Toggle_Menu)) State.ShowMenu = !State.ShowMenu;
    if (ImGui::IsKeyReleased(State.KeyBinds.Toggle_Radar)) State.ShowRadar = !State.ShowRadar;
    if (ImGui::IsKeyReleased(State.KeyBinds.Toggle_Console)) State.ShowConsole = !State.ShowConsole;
    if (ImGui::IsKeyReleased(State.KeyBinds.Repair_Sabotage) && IsInGame()) RepairSabotage(*Game::pLocalPlayer);

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool ImGuiInitialization(IDXGISwapChain* pSwapChain) {
    if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
        pDevice->GetImmediateContext(&pContext);
        DXGI_SWAP_CHAIN_DESC sd;
        pSwapChain->GetDesc(&sd);
        window = sd.OutputWindow;
        ID3D11Texture2D* pBackBuffer = NULL;
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

        return true;
    }
    
    return false;
}

HRESULT __stdcall dPresent(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags) {
    WaitForSingleObject(hPresentMutex, 0); //We're claiming ownership, but we'll be damned if we're going to wait
    if (!State.ImGuiInitialized) {
        if (ImGuiInitialization(__this)) {
            State.ImGuiInitialized = true;
        } else {
            ReleaseMutex(hPresentMutex);
            return oPresent(__this, SyncInterval, Flags);
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
        State.DisableLights = false;

        if (!IsInLobby()) {
            State.FlipSkeld = false;
        }
    }

    if (!IsInGame() || State.InMeeting)
    {
        if (State.PlayMedbayScan)
        {
            State.PlayMedbayScan = false;
            State.rpcQueue.push(new RpcSetScanner(false));
        }
    }

    if (State.DisableLights)
    {
        SwitchSystem* switchSystem = nullptr;
        std::vector<std::pair<SystemTypes__Enum, ISystemType*>> systems = GetEntriesFromDictionary<Dictionary_2_SystemTypes_ISystemType_*, SystemTypes__Enum, ISystemType*>((*Game::pShipStatus)->fields.Systems);

        for (auto system : systems)
        {
            if (system.first == SystemTypes__Enum_Electrical)
            {
                switchSystem = (SwitchSystem*)system.second;
            }
        }

        if (switchSystem != nullptr)
        {
            auto actualSwitches = switchSystem->fields.ActualSwitches;
            auto expectedSwitches = switchSystem->fields.ExpectedSwitches;

            if (actualSwitches == expectedSwitches) {
                auto switchMask = 1 << (0 & 0x1F);

                if ((actualSwitches & switchMask) != (~expectedSwitches & switchMask))
                    State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Electrical, randi(0, 4)));
            }
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

    ReleaseMutex(hPresentMutex);

    return oPresent(__this, SyncInterval, Flags);
}

void DirectX::Shutdown() {
    assert(WaitForSingleObject(hPresentMutex, INFINITE) == WAIT_OBJECT_0); //Since this is only used on debug builds, we'll leave this for now
    oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    ReleaseMutex(hPresentMutex);
    CloseHandle(hPresentMutex);
}