#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "_hooks.hpp"
#include "detours/detours.h"
#include "DirectX.h"
#include <iostream>

using namespace app;

bool HookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (DetourAttach(ppPointer, pDetour) != 0) {
		std::cout << "Failed to hook " << functionName << std::endl;
		return false;
	}
	//std::cout << "Hooked " << functionName << std::endl;
	return true;
}

#define HOOKFUNC(n) if (!HookFunction(&(PVOID&)n, d ## n, #n)) return;

void DetourInitilization() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	directx11 d3d11 = directx11();
	if (!d3d11.presentFunction) {
		std::cout << "Unable to retrieve IDXGISwapChain::Present method" << std::endl;
		return;
	} else {
		oPresent = d3d11.presentFunction;
	}

	HOOKFUNC(SceneManager_Internal_ActiveSceneChanged);
	HOOKFUNC(HatManager_GetUnlockedHats);
	HOOKFUNC(HatManager_GetUnlockedPets);
	HOOKFUNC(HatManager_GetUnlockedSkins);
	HOOKFUNC(PlayerControl_FixedUpdate);
	HOOKFUNC(PlayerControl_RpcSyncSettings);
	HOOKFUNC(MeetingHud_Update);
	HOOKFUNC(ShipStatus_CalculateLightRadius);
	HOOKFUNC(ShipStatus_OnEnable);
	HOOKFUNC(Vent_CanUse);
	HOOKFUNC(Vent_EnterVent);
	HOOKFUNC(Vent_ExitVent);
	HOOKFUNC(StatsManager_get_AmBanned);
	HOOKFUNC(StatsManager_get_BanMinutesLeft);
	HOOKFUNC(StatsManager_get_BanPoints);
	HOOKFUNC(AutoOpenDoor_DoUpdate);
	HOOKFUNC(ChatBubble_SetName);
	HOOKFUNC(ChatController_AddChat);
	HOOKFUNC(ChatController_SetVisible);
	HOOKFUNC(HudManager_ShowMap);
	HOOKFUNC(HudManager_Update);
	HOOKFUNC(KeyboardJoystick_Update);
	HOOKFUNC(PlainDoor_SetDoorway);
	HOOKFUNC(GameOptionsData_Deserialize);
	HOOKFUNC(GameOptionsData_Deserialize_1);
	HOOKFUNC(PlayerControl_MurderPlayer);
	HOOKFUNC(PlayerControl_CompleteTask);
	HOOKFUNC(PlayerControl_ReportDeadBody);
	HOOKFUNC(PlayerControl_RpcSetInfected);
	HOOKFUNC(Renderer_set_enabled);
	HOOKFUNC(MeetingHud_Awake);
	HOOKFUNC(MeetingHud_Close);
	HOOKFUNC(InnerNetClient_Update);
	HOOKFUNC(Constants_ShouldFlipSkeld);
	if (!HookFunction(&(PVOID&)oPresent, dPresent, "D3D_PRESENT_FUNCTION")) return;

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
	if (DetourDetach(&(PVOID&)Renderer_set_enabled, dRenderer_set_enabled) != 0) return;
	if (DetourDetach(&(PVOID&)MeetingHud_Awake, dMeetingHud_Awake) != 0) return;
	if (DetourDetach(&(PVOID&)MeetingHud_Close, dMeetingHud_Close) != 0) return;
	if (DetourDetach(&(PVOID&)Constants_ShouldFlipSkeld, dConstants_ShouldFlipSkeld) != 0) return;
	if (DetourDetach(&(PVOID&)oPresent, dPresent) != 0) return;

	DetourTransactionCommit();
	DirectX::Shutdown();
}