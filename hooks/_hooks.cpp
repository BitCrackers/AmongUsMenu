#include "_hooks.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <fcntl.h>
#include "theme.hpp"
#include "imhotkeys.h"

using namespace app;

ID3D11Device* pDevice;
ID3D11DeviceContext* pContext;
ID3D11RenderTargetView* pRenderTargetView;
D3D_PRESENT_FUNCTION oPresent;
HWND window;
WNDPROC oWndProc;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::vector<MapTexture> maps = std::vector<MapTexture>();

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!State.ImGuiInitialized)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(pDevice, pContext);

			maps.push_back({ D3D11Image(Resource(IDB_PNG1), pDevice), 277.F, 77.F, 11.5F });
			maps.push_back({ D3D11Image(Resource(IDB_PNG2), pDevice), 115.F, 240.F, 9.25F });
			maps.push_back({ D3D11Image(Resource(IDB_PNG3), pDevice), 8.F, 21.F, 10.F });

			State.ImGuiInitialized = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	il2cpp_gc_disable();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ApplyTheme();

	if (!IsInGame())
	{
		State.selectedPlayer = PlayerSelection();
		State.playerToFollow = PlayerSelection();
		State.NoClip = false;
		State.FreeCam = false;
		State.InMeeting = false;
		State.FollowerCam = nullptr;
		State.EnableZoom = false;

		if (!IsInLobby())
		{
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

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void DetourInitilization() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	if (DetourAttach(&(PVOID&)SceneManager_Internal_ActiveSceneChanged, dSceneManager_Internal_ActiveSceneChanged) != 0) return;
	if (DetourAttach(&(PVOID&)HatManager_GetUnlockedHats, dHatManager_GetUnlockedHats) != 0) return;
	if (DetourAttach(&(PVOID&)HatManager_GetUnlockedPets, dHatManager_GetUnlockedPets) != 0) return;
	if (DetourAttach(&(PVOID&)HatManager_GetUnlockedSkins, dHatManager_GetUnlockedSkins) != 0) return;
	if (DetourAttach(&(PVOID&)PlayerControl_FixedUpdate, dPlayerControl_FixedUpdate) != 0) return;
	if (DetourAttach(&(PVOID&)PlayerControl_RpcSyncSettings, dPlayerControl_RpcSyncSettings) != 0) return;
	if (DetourAttach(&(PVOID&)MeetingHud_Update, dMeetingHud_Update) != 0) return;
	if (DetourAttach(&(PVOID&)ShipStatus_CalculateLightRadius, dShipStatus_CalculateLightRadius) != 0) return;
	if (DetourAttach(&(PVOID&)ShipStatus_OnEnable, dShipStatus_OnEnable) != 0) return;
	if (DetourAttach(&(PVOID&)Vent_CanUse, dVent_CanUse) != 0) return;
	if (DetourAttach(&(PVOID&)Vent_EnterVent, dVent_EnterVent) != 0) return;
	if (DetourAttach(&(PVOID&)Vent_ExitVent, dVent_ExitVent) != 0) return;
	if (DetourAttach(&(PVOID&)StatsManager_get_AmBanned, dStatsManager_get_AmBanned) != 0) return;
	if (DetourAttach(&(PVOID&)StatsManager_get_BanMinutesLeft, dStatsManager_get_BanMinutesLeft) != 0) return;
	if (DetourAttach(&(PVOID&)StatsManager_get_BanPoints, dStatsManager_get_BanPoints) != 0) return;
	if (DetourAttach(&(PVOID&)AutoOpenDoor_DoUpdate, dAutoOpenDoor_DoUpdate) != 0) return;
	if (DetourAttach(&(PVOID&)ChatBubble_SetName, dChatBubble_SetName) != 0) return;
	if (DetourAttach(&(PVOID&)ChatController_AddChat, dChatController_AddChat) != 0) return;
	if (DetourAttach(&(PVOID&)ChatController_SetVisible, dChatController_SetVisible) != 0) return;
	if (DetourAttach(&(PVOID&)HudManager_ShowMap, dHudManager_ShowMap) != 0) return;
	if (DetourAttach(&(PVOID&)HudManager_Update, dHudManager_Update) != 0) return;
	if (DetourAttach(&(PVOID&)KeyboardJoystick_Update, dKeyboardJoystick_Update) != 0) return;
	if (DetourAttach(&(PVOID&)PlainDoor_SetDoorway, dPlainDoor_SetDoorway) != 0) return;
	if (DetourAttach(&(PVOID&)GameOptionsData_Deserialize, dGameOptionsData_Deserialize) != 0) return;
	if (DetourAttach(&(PVOID&)GameOptionsData_Deserialize_1, dGameOptionsData_Deserialize_1) != 0) return;
	if (DetourAttach(&(PVOID&)PlayerControl_MurderPlayer, dPlayerControl_MurderPlayer) != 0) return;
	if (DetourAttach(&(PVOID&)PlayerControl_CompleteTask, dPlayerControl_CompleteTask) != 0) return;
	if (DetourAttach(&(PVOID&)PlayerControl_ReportDeadBody, dPlayerControl_ReportDeadBody) != 0) return;
	if (DetourAttach(&(PVOID&)PlayerControl_RpcSetInfected, dPlayerControl_RpcSetInfected) != 0) return;
	if (DetourAttach(&(PVOID&)MeetingHud_Awake, dMeetingHud_Awake) != 0) return;
	if (DetourAttach(&(PVOID&)MeetingHud_Close, dMeetingHud_Close) != 0) return;
	if (DetourAttach(&(PVOID&)Constants_ShouldFlipSkeld, dConstants_ShouldFlipSkeld) != 0) return;

	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
		oPresent = (D3D_PRESENT_FUNCTION)kiero::getMethodsTable()[8];
		if (DetourAttach(&(PVOID&)oPresent, hkPresent) != 0)
			return;
	}
	DetourTransactionCommit();
}

void DetourUninitialization()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	if (DetourDetach(&(PVOID&)SceneManager_Internal_ActiveSceneChanged, dSceneManager_Internal_ActiveSceneChanged) != 0) return;
	if (DetourDetach(&(PVOID&)HatManager_GetUnlockedHats, dHatManager_GetUnlockedHats) != 0) return;
	if (DetourDetach(&(PVOID&)HatManager_GetUnlockedPets, dHatManager_GetUnlockedPets) != 0) return;
	if (DetourDetach(&(PVOID&)HatManager_GetUnlockedSkins, dHatManager_GetUnlockedSkins) != 0) return;
	if (DetourDetach(&(PVOID&)PlayerControl_FixedUpdate, dPlayerControl_FixedUpdate) != 0) return;
	if (DetourDetach(&(PVOID&)PlayerControl_RpcSyncSettings, dPlayerControl_RpcSyncSettings) != 0) return;
	if (DetourDetach(&(PVOID&)MeetingHud_Update, dMeetingHud_Update) != 0) return;
	if (DetourDetach(&(PVOID&)ShipStatus_CalculateLightRadius, dShipStatus_CalculateLightRadius) != 0) return;
	if (DetourDetach(&(PVOID&)ShipStatus_OnEnable, dShipStatus_OnEnable) != 0) return;
	if (DetourDetach(&(PVOID&)Vent_CanUse, dVent_CanUse) != 0) return;
	if (DetourDetach(&(PVOID&)Vent_EnterVent, dVent_EnterVent) != 0) return;
	if (DetourDetach(&(PVOID&)Vent_ExitVent, dVent_ExitVent) != 0) return;
	if (DetourDetach(&(PVOID&)StatsManager_get_AmBanned, dStatsManager_get_AmBanned) != 0) return;
	if (DetourDetach(&(PVOID&)StatsManager_get_BanMinutesLeft, dStatsManager_get_BanMinutesLeft) != 0) return;
	if (DetourDetach(&(PVOID&)StatsManager_get_BanPoints, dStatsManager_get_BanPoints) != 0) return;
	if (DetourDetach(&(PVOID&)AutoOpenDoor_DoUpdate, dAutoOpenDoor_DoUpdate) != 0) return;
	if (DetourDetach(&(PVOID&)ChatBubble_SetName, dChatBubble_SetName) != 0) return;
	if (DetourDetach(&(PVOID&)ChatController_AddChat, dChatController_AddChat) != 0) return;
	if (DetourDetach(&(PVOID&)ChatController_SetVisible, dChatController_SetVisible) != 0) return;
	if (DetourDetach(&(PVOID&)HudManager_ShowMap, dHudManager_ShowMap) != 0) return;
	if (DetourDetach(&(PVOID&)HudManager_Update, dHudManager_Update) != 0) return;
	if (DetourDetach(&(PVOID&)KeyboardJoystick_Update, dKeyboardJoystick_Update) != 0) return;
	if (DetourDetach(&(PVOID&)PlainDoor_SetDoorway, dPlainDoor_SetDoorway) != 0) return;
	if (DetourDetach(&(PVOID&)GameOptionsData_Deserialize, dGameOptionsData_Deserialize) != 0) return;
	if (DetourDetach(&(PVOID&)GameOptionsData_Deserialize_1, dGameOptionsData_Deserialize_1) != 0) return;
	if (DetourDetach(&(PVOID&)PlayerControl_MurderPlayer, dPlayerControl_MurderPlayer) != 0) return;
	if (DetourDetach(&(PVOID&)PlayerControl_CompleteTask, dPlayerControl_CompleteTask) != 0) return;
	if (DetourDetach(&(PVOID&)PlayerControl_ReportDeadBody, dPlayerControl_ReportDeadBody) != 0) return;
	if (DetourDetach(&(PVOID&)PlayerControl_RpcSetInfected, dPlayerControl_RpcSetInfected) != 0) return;
	if (DetourDetach(&(PVOID&)MeetingHud_Awake, dMeetingHud_Awake) != 0) return;
	if (DetourDetach(&(PVOID&)MeetingHud_Close, dMeetingHud_Close) != 0) return;
	if (DetourDetach(&(PVOID&)Constants_ShouldFlipSkeld, dConstants_ShouldFlipSkeld) != 0) return;
	if (DetourDetach(&(PVOID&)oPresent, hkPresent) != 0)
		return;

	DetourTransactionCommit();

	kiero::shutdown();
	pDevice->Release();
	pContext->Release();
	pRenderTargetView->Release();
	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
}