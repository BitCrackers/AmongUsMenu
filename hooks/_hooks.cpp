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

std::vector<MapTexture> maps{
	{ "the_skald.png", NULL, NULL, NULL, 277.F, 77.F, 11.5F },
	{ "mira_hq.png", NULL, NULL, NULL, 115.F, 240.F, 9.25F },
	{ "polus.png", NULL, NULL, NULL, 8.F, 21.F, 10.F }
};

bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height) {
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
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
	pDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}

bool LoadTextures() {
	HMODULE hModule = GetModuleHandle(NULL);
	for (size_t i = 0; i < maps.size(); i++)
		if (!LoadTextureFromFile(getModulePath().append("resources\\").append(maps[i].name).c_str(), &maps[i].buffer, &maps[i].width, &maps[i].height))
			return false;
	return true;
}

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

			LoadTextures();

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

	if (State.ShowMenu) {
		Menu::Render();
	}

	if (IsInGame() && State.ShowRadar) {
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

	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
		oPresent = (D3D_PRESENT_FUNCTION)kiero::getMethodsTable()[8];
		if (DetourAttach(&(PVOID&)oPresent, hkPresent) != 0)
			return;
	}

	DetourTransactionCommit();
}