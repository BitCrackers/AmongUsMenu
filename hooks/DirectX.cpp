#include "pch-il2cpp.h"
#include "DirectX.h"
#include "Renderer.hpp"
#include "console.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "keybinds.h"
#include "menu.hpp"
#include "radar.hpp"
#include "esp.hpp"
#include "state.hpp"
#include "theme.hpp"
#include <iostream>
#include <mutex>

#include "resource_data.h"
#include "game.h"

#include <future>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND window;
ID3D11Device* pDevice;
ID3D11DeviceContext* pContext;
ID3D11RenderTargetView* pRenderTargetView;
D3D_PRESENT_FUNCTION oPresent;
WNDPROC oWndProc;

HANDLE hPresentMutex;

std::vector<MapTexture> maps = std::vector<MapTexture>();

typedef struct Cache
{
	ImGuiWindow* Window;  //Window instance
	ImVec2       Winsize; //Size of the window
} cache_t;

static cache_t s_Cache;

static bool CanDrawEsp()
{
	return IsInGame() && State.ShowEsp && (!State.InMeeting || !State.HideEsp_During_Meetings);
}

static bool CanDrawRadar()
{
	return IsInGame() && State.ShowRadar && (!State.InMeeting || !State.HideRadar_During_Meetings);
}

LRESULT __stdcall dWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (!State.ImGuiInitialized)
        return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    KeyBinds::WndProc(uMsg, wParam, lParam);

    if (KeyBinds::IsKeyPressed(State.KeyBinds.Toggle_Menu)) State.ShowMenu = !State.ShowMenu;
    if (KeyBinds::IsKeyPressed(State.KeyBinds.Toggle_Radar)) State.ShowRadar = !State.ShowRadar;
    if (KeyBinds::IsKeyPressed(State.KeyBinds.Toggle_Console)) State.ShowConsole = !State.ShowConsole;
    if (KeyBinds::IsKeyPressed(State.KeyBinds.Repair_Sabotage) && IsInGame()) RepairSabotage(*Game::pLocalPlayer);
    if (KeyBinds::IsKeyPressed(State.KeyBinds.Toggle_Noclip) && (IsInGame() || IsInLobby())) { State.NoClip = !State.NoClip; State.HotkeyNoClip = true; }
    if (KeyBinds::IsKeyPressed(State.KeyBinds.Close_All_Doors) && IsInGame()) State.CloseAllDoors = true;
    if (KeyBinds::IsKeyPressed(State.KeyBinds.Toggle_Zoom) && IsInGame()) State.EnableZoom = !State.EnableZoom;
    if (KeyBinds::IsKeyPressed(State.KeyBinds.Toggle_Freecam) && IsInGame()) State.FreeCam = !State.FreeCam;
    if (KeyBinds::IsKeyPressed(State.KeyBinds.Close_Current_Room_Door) && IsInGame()) State.rpcQueue.push(new RpcCloseDoorsOfType(GetSystemTypes(GetTrueAdjustedPosition(*Game::pLocalPlayer)), false));

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

        hPresentMutex = CreateMutex(NULL, false, NULL);

        return true;
    }
    
    return false;
}

std::once_flag init_d3d;
HRESULT __stdcall dPresent(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags) {
    std::call_once(init_d3d, [&] {
        __this->GetDevice(__uuidof(pDevice), reinterpret_cast<void**>(&pDevice));
        pDevice->GetImmediateContext(&pContext);
    });
	if (!State.ImGuiInitialized) {
        if (ImGuiInitialization(__this)) {
            State.ImGuiInitialized = true;
        } else {
            ReleaseMutex(hPresentMutex);
            return oPresent(__this, SyncInterval, Flags);
        }
    }

    WaitForSingleObject(hPresentMutex, 0); //We're claiming ownership, but we'll be damned if we're going to wait

    il2cpp_gc_disable();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ApplyTheme();

    if (State.ShowMenu)
    {
        ImGuiRenderer::Submit([]() { Menu::Render(); });
    }

    if (State.ShowConsole)
    {
        ImGuiRenderer::Submit([]() { ConsoleGui::Render(); });
    }

	if (CanDrawEsp())
	{
		ImGuiRenderer::Submit([&]()
		{
			//Push ImGui flags
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
			ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });

			//Setup BackBuffer
			ImGui::Begin("BackBuffer", reinterpret_cast<bool*>(true),
				ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoScrollbar);

			s_Cache.Winsize = { (float)app::Screen_get_width(nullptr), (float)app::Screen_get_height(nullptr) };
			s_Cache.Window = ImGui::GetCurrentWindow();

			//Set window properties
			ImGui::SetWindowPos({ 0, 0 }, ImGuiCond_Always);
			ImGui::SetWindowSize(s_Cache.Winsize, ImGuiCond_Always);

			Esp::Render();

			s_Cache.Window->DrawList->PushClipRectFullScreen();

			ImGui::PopStyleColor();
			ImGui::PopStyleVar();
			ImGui::End();
		});
	}

	if (CanDrawRadar())
	{
		ImGuiRenderer::Submit([]() { Radar::Render(); });
	}

    // Render in a separate thread
	std::async(std::launch::async, ImGuiRenderer::ExecuteQueue);

    ImGui::EndFrame();
    ImGui::Render();

    pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    il2cpp_gc_enable();

    HRESULT result = oPresent(__this, SyncInterval, Flags);

    ReleaseMutex(hPresentMutex);

    return result;
}

void DirectX::Shutdown() {
    assert(hPresentMutex != NULL); //Initialization is now in a hook, so we might as well guard against this
    assert(WaitForSingleObject(hPresentMutex, INFINITE) == WAIT_OBJECT_0); //Since this is only used on debug builds, we'll leave this for now
    oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    ReleaseMutex(hPresentMutex);
    CloseHandle(hPresentMutex);
}
