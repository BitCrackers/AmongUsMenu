#include "pch-il2cpp.h"
#include "DirectX.h"
#include "Renderer.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "keybinds.h"
#include "menu.hpp"
#include "radar.hpp"
#include "replay.hpp"
#include "esp.hpp"
#include "state.hpp"
#include "theme.hpp"
#include <mutex>
#include "logger.h"
#include "resource_data.h"
#include "game.h"
#include "console.hpp"
#include "profiler.h"

#include <future>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND window;
ID3D11Device* pDevice;
ID3D11DeviceContext* pContext;
ID3D11RenderTargetView* pRenderTargetView;
D3D_PRESENT_FUNCTION oPresent;
WNDPROC oWndProc;

HANDLE DirectX::hRenderSemaphore;
constexpr DWORD MAX_RENDER_THREAD_COUNT = 5; //Should be overkill for our purposes

std::vector<MapTexture> maps = std::vector<MapTexture>();
std::unordered_map<ICON_TYPES, IconTexture> icons;

typedef struct Cache
{
	ImGuiWindow* Window;  //Window instance
	ImVec2       Winsize; //Size of the window
} cache_t;

static cache_t s_Cache;

ImVec2 DirectX::GetWindowSize()
{
    if (Screen_get_fullScreen(nullptr))
    {
        RECT rect;
        GetWindowRect(window, &rect);

        return { (float)(rect.right - rect.left),  (float)(rect.bottom - rect.top) };
    }

    return { (float)Screen_get_width(nullptr), (float)Screen_get_height(nullptr) };

}

static bool CanDrawEsp()
{
	return IsInGame() && State.ShowEsp && (!State.InMeeting || !State.HideEsp_During_Meetings);
}

static bool CanDrawRadar()
{
	return IsInGame() && State.ShowRadar && (!State.InMeeting || !State.HideRadar_During_Meetings);
}

static bool CanDrawReplay()
{
    return IsInGame() && State.ShowReplay;
}

LRESULT __stdcall dWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DPICHANGED) {
        float dpi = HIWORD(wParam);
        State.dpiScale = dpi / 96.0f;
        ImGui::GetStyle().ScaleAllSizes(State.dpiScale);
        LPCRECT rc = (LPCRECT)lParam;
        ::SetWindowPos(hWnd, nullptr,
            rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top, 
            SWP_NOZORDER | SWP_NOACTIVATE);
        STREAM_DEBUG("DPI Scale: " << State.dpiScale);
    }

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
    if (KeyBinds::IsKeyPressed(State.KeyBinds.Toggle_Replay)) State.ShowReplay = !State.ShowReplay;

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
        State.dpiScale = ImGui_ImplWin32_GetDpiScaleForHwnd(window);

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->Clear();
        ImFontConfig config;
        io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14, &config, io.Fonts->GetGlyphRangesCyrillic());
        io.Fonts->Build();
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(pDevice, pContext);

        maps.push_back({ D3D11Image(Resource(IDB_PNG1), pDevice), 277.F, 77.F, 11.5F });
        maps.push_back({ D3D11Image(Resource(IDB_PNG2), pDevice), 115.F, 240.F, 9.25F });
        maps.push_back({ D3D11Image(Resource(IDB_PNG3), pDevice), 8.F, 21.F, 10.F });
        maps.push_back({ D3D11Image(Resource(IDB_PNG4), pDevice), 162.F, 107.F, 6.F });

        icons.insert({ ICON_TYPES::VENT_IN, { D3D11Image(Resource(IDB_PNG5), pDevice), 0.02f }});
        icons.insert({ ICON_TYPES::VENT_OUT, { D3D11Image(Resource(IDB_PNG6), pDevice), 0.02f }});
        icons.insert({ ICON_TYPES::KILL, { D3D11Image(Resource(IDB_PNG7), pDevice), 0.02f } });
        icons.insert({ ICON_TYPES::REPORT, { D3D11Image(Resource(IDB_PNG8), pDevice), 0.02f } });
        icons.insert({ ICON_TYPES::TASK, { D3D11Image(Resource(IDB_PNG9), pDevice), 0.02f } });
        icons.insert({ ICON_TYPES::PLAYER, { D3D11Image(Resource(IDB_PNG10), pDevice), 0.02f } });
        icons.insert({ ICON_TYPES::CROSS, { D3D11Image(Resource(IDB_PNG11), pDevice), 0.02f } });
        icons.insert({ ICON_TYPES::DEAD, { D3D11Image(Resource(IDB_PNG12), pDevice), 0.02f } });
        icons.insert({ ICON_TYPES::PLAY, { D3D11Image(Resource(IDB_PNG13), pDevice), 0.55f } });
        icons.insert({ ICON_TYPES::PAUSE, { D3D11Image(Resource(IDB_PNG14), pDevice), 0.55f } });

        DirectX::hRenderSemaphore = CreateSemaphore(
            NULL,                                 // default security attributes
            MAX_RENDER_THREAD_COUNT,              // initial count
            MAX_RENDER_THREAD_COUNT,              // maximum count
            NULL);                                // unnamed semaphore);
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
            ImVec2 size = DirectX::GetWindowSize();
            State.ImGuiInitialized = true;
            STREAM_DEBUG("ImGui Initialized successfully!");
            STREAM_DEBUG("Fullscreen: " << Screen_get_fullScreen(nullptr));
            STREAM_DEBUG("Unity Window Resolution: " << +Screen_get_width(nullptr) << "x" << +Screen_get_height(nullptr));
            STREAM_DEBUG("DirectX Window Size: " << +size.x << "x" << +size.y);
        } else {
            ReleaseSemaphore(DirectX::hRenderSemaphore, 1, NULL);
            return oPresent(__this, SyncInterval, Flags);
        }
    }

    if (!Profiler::HasInitialized)
    {
        Profiler::InitProfiling();
    }

    WaitForSingleObject(DirectX::hRenderSemaphore, INFINITE);

    il2cpp_gc_disable();

    ApplyTheme();
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

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
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f * State.dpiScale);
			ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });

			//Setup BackBuffer
			ImGui::Begin("BackBuffer", reinterpret_cast<bool*>(true),
				ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoScrollbar);
            ImGui::SetWindowFontScale(State.dpiScale);

			s_Cache.Winsize = DirectX::GetWindowSize();
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

    if (CanDrawReplay())
    {
        ImGuiRenderer::Submit([]() { Replay::Render(); });
    }

    // Render in a separate thread
	std::async(std::launch::async, ImGuiRenderer::ExecuteQueue);

    ImGui::EndFrame();
    ImGui::Render();

    pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    il2cpp_gc_enable();

    HRESULT result = oPresent(__this, SyncInterval, Flags);

    ReleaseSemaphore(DirectX::hRenderSemaphore, 1, NULL);

    return result;
}

void DirectX::Shutdown() {
    assert(hRenderSemaphore != NULL); //Initialization is now in a hook, so we might as well guard against this
    for (uint8_t i = 0; i < MAX_RENDER_THREAD_COUNT; i++) //This ugly little hack means we use up all the render queues so we can end everything
    {
        assert(WaitForSingleObject(hRenderSemaphore, INFINITE) == WAIT_OBJECT_0); //Since this is only used on debug builds, we'll leave this for now
    }
    oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CloseHandle(hRenderSemaphore);
}
