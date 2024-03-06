#include "pch-il2cpp.h"
#include "_hooks.h"
#include "detours/detours.h"
#include "DirectX.h"
#include <iostream>
#include "main.h"
#include "SignatureScan.hpp"
#include "game.h"
#include "logger.h"

using namespace Game;

bool HookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourAttach(ppPointer, pDetour); error != NO_ERROR) {
		STREAM_ERROR("Failed to hook " << functionName << ", error " << error);
		return false;
	}
	//std::cout << "Hooked " << functionName << std::endl;
	return true;
}

#define HOOKFUNC(n) if (!HookFunction(&(PVOID&)n, d ## n, #n)) return;

bool UnhookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourDetach(ppPointer, pDetour); error != NO_ERROR) {
		STREAM_ERROR("Failed to unhook " << functionName << ", error " << error);
		return false;
	}
	//std::cout << "Unhooked " << functionName << std::endl;
	return true;
}

#define UNHOOKFUNC(n) if (!UnhookFunction(&(PVOID&)n, d ## n, #n)) return;

void DetourInitilization() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	directx11 d3d11 = directx11();
	if (!d3d11.presentFunction) {
		LOG_ERROR("Unable to retrieve IDXGISwapChain::Present method");
		return;
	} else {
		// Attempting to hook the Steam overlay
		do {
			if (oPresent)
				break;
			HMODULE hModule = GetModuleHandleA("GameOverlayRenderer.dll");
			if (!hModule)
				break;
			oPresent = SignatureScan<D3D_PRESENT_FUNCTION>("55 8B EC 53 8B 5D ? F6 C3 01 74 ? 53 FF 75 ? FF 75 ? FF 15 ? ? ? ? 5B 5D C2", hModule);
			if (oPresent)
				break;
			if (MessageBox(NULL,
				L"Failed to hook the Steam overlay D3DPresent function.\nThis may cause the menu to be visible to streaming applications.  Do you wish to continue?",
				L"Error",
				MB_YESNO | MB_ICONWARNING) == IDNO)
			{
#ifndef _VERSION
				SetEvent(hUnloadEvent); //Might as well unload the DLL if we're not going to render anything
#endif
				return;
			}
			oPresent = d3d11.presentFunction;
		} while (0);
		// Attempting to hook the Epic overlay
		do {
			if (oPresent)
				break;
			HMODULE hModule = GetModuleHandleA("EOSOVH-Win32-Shipping.dll");
			if (!hModule)
				break;
			oPresent = SignatureScan<D3D_PRESENT_FUNCTION>("56 8B 74 24 08 8D 44 24 08 6A 01 56 50 E8 ? ? ? ? 83 C4 0C 83 7C 24 ? ? 74 1C 8D 44 24 08 56 50 E8 ? ? ? ? 8B 44 24 10 83 C4 08 85 C0 74 06 8B 08 50 FF 51 08 FF 74 24 10 A1 ? ? ? ? FF 74 24 10 56 FF D0 5E C2 0C 00", hModule);
			if (oPresent)
				break;
			if (MessageBox(NULL,
				L"Failed to hook the Epic overlay D3DPresent function.\nThis may cause the menu to be visible to streaming applications.  Do you wish to continue?",
				L"Error",
				MB_YESNO | MB_ICONWARNING) == IDNO)
			{
#ifndef _VERSION
				SetEvent(hUnloadEvent); //Might as well unload the DLL if we're not going to render anything
#endif
				return;
			}
			oPresent = d3d11.presentFunction;
		} while (0);
		if (!oPresent)
			oPresent = d3d11.presentFunction;
	}

	HOOKFUNC(SceneManager_Internal_ActiveSceneChanged);
	HOOKFUNC(PlayerControl_FixedUpdate);
	HOOKFUNC(PlayerControl_RpcSyncSettings);
	HOOKFUNC(PlayerControl_Shapeshift);
	HOOKFUNC(PlayerControl_ProtectPlayer);
	HOOKFUNC(MeetingHud_Update);
	HOOKFUNC(MeetingHud_PopulateResults);
	HOOKFUNC(ShipStatus_CalculateLightRadius);
	HOOKFUNC(AirshipStatus_CalculateLightRadius);
	HOOKFUNC(ShipStatus_OnEnable);
	HOOKFUNC(PolusShipStatus_OnEnable);
	HOOKFUNC(AirshipStatus_OnEnable);
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
	HOOKFUNC(HudManager_Update);
	HOOKFUNC(Camera_ScreenToWorldPoint);
	HOOKFUNC(KeyboardJoystick_Update);
	HOOKFUNC(ScreenJoystick_FixedUpdate);
	HOOKFUNC(PlainDoor_SetDoorway);
	HOOKFUNC(PlayerControl_MurderPlayer);
	HOOKFUNC(PlayerControl_CompleteTask);
	HOOKFUNC(PlayerControl_StartMeeting);
	HOOKFUNC(RoleManager_SelectRoles);
	//HOOKFUNC(RoleManager_AssignRolesForTeam);
	//HOOKFUNC(RoleManager_AssignRolesFromList);
	HOOKFUNC(PlayerControl_HandleRpc);
	HOOKFUNC(Renderer_set_enabled);
	HOOKFUNC(MeetingHud_Awake);
	HOOKFUNC(MeetingHud_Close);
	HOOKFUNC(InnerNetClient_Update);
	HOOKFUNC(AmongUsClient_OnPlayerLeft);
	HOOKFUNC(CustomNetworkTransform_SnapTo);
	//HOOKFUNC(Constants_ShouldFlipSkeld);
	HOOKFUNC(LobbyBehaviour_Start);
	HOOKFUNC(GameObject_SetActive);
	//HOOKFUNC(NoShadowBehaviour_LateUpdate);
	HOOKFUNC(FollowerCamera_Update);
	HOOKFUNC(DoorBreakerGame_Start);
	HOOKFUNC(DoorCardSwipeGame_Begin);
	HOOKFUNC(Debug_Log);
	HOOKFUNC(Debug_LogError);
	HOOKFUNC(Debug_LogException);
	HOOKFUNC(Debug_LogWarning);
	HOOKFUNC(VersionShower_Start);
	HOOKFUNC(EOSManager_LoginFromAccountTab);
	HOOKFUNC(EOSManager_InitializePlatformInterface);
	HOOKFUNC(EOSManager_IsFreechatAllowed);
	HOOKFUNC(ChatController_Update);
	HOOKFUNC(InnerNetClient_EnqueueDisconnect);
	HOOKFUNC(PlayerPhysics_FixedUpdate);
	HOOKFUNC(PlayerPurchasesData_GetPurchase);
	HOOKFUNC(PlayerControl_TurnOnProtection);
	HOOKFUNC(AmongUsClient_OnGameEnd);
	HOOKFUNC(InnerNetClient_DisconnectInternal);
	HOOKFUNC(AccountManager_UpdateKidAccountDisplay);
	HOOKFUNC(PlayerStorageManager_OnReadPlayerPrefsComplete);
	HOOKFUNC(EOSManager_UpdatePermissionKeys);
	HOOKFUNC(GameOptionsManager_set_CurrentGameOptions);
	HOOKFUNC(ExileController_ReEnableGameplay);
	HOOKFUNC(SabotageSystemType_SetInitialSabotageCooldown);
	HOOKFUNC(FungleShipStatus_OnEnable);
	HOOKFUNC(MushroomWallDoor_SetDoorway);
	HOOKFUNC(MushroomDoorSabotageMinigame_Begin);


	if (!HookFunction(&(PVOID&)oPresent, dPresent, "D3D_PRESENT_FUNCTION")) return;

	DetourTransactionCommit();
}

void DetourUninitialization()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());


	UNHOOKFUNC(PlayerPurchasesData_GetPurchase);
	UNHOOKFUNC(PlayerPhysics_FixedUpdate);
	UNHOOKFUNC(GameObject_SetActive);
	UNHOOKFUNC(SceneManager_Internal_ActiveSceneChanged);
	UNHOOKFUNC(PlayerControl_FixedUpdate);
	UNHOOKFUNC(PlayerControl_RpcSyncSettings);
	UNHOOKFUNC(PlayerControl_Shapeshift);
	UNHOOKFUNC(PlayerControl_ProtectPlayer);
	UNHOOKFUNC(MeetingHud_Update);
	UNHOOKFUNC(MeetingHud_PopulateResults);
	UNHOOKFUNC(AirshipStatus_CalculateLightRadius);
	UNHOOKFUNC(ShipStatus_CalculateLightRadius);
	UNHOOKFUNC(ShipStatus_OnEnable);
	UNHOOKFUNC(PolusShipStatus_OnEnable);
	UNHOOKFUNC(AirshipStatus_OnEnable);
	UNHOOKFUNC(Vent_CanUse);
	UNHOOKFUNC(Vent_EnterVent);
	UNHOOKFUNC(Vent_ExitVent);
	UNHOOKFUNC(StatsManager_get_AmBanned);
	UNHOOKFUNC(StatsManager_get_BanMinutesLeft);
	UNHOOKFUNC(StatsManager_get_BanPoints);
	UNHOOKFUNC(AutoOpenDoor_DoUpdate);
	UNHOOKFUNC(ChatBubble_SetName);
	UNHOOKFUNC(ChatController_AddChat);
	UNHOOKFUNC(ChatController_SetVisible);
	UNHOOKFUNC(HudManager_Update);
	UNHOOKFUNC(ScreenJoystick_FixedUpdate);
	UNHOOKFUNC(KeyboardJoystick_Update);
	UNHOOKFUNC(Camera_ScreenToWorldPoint);
	UNHOOKFUNC(PlainDoor_SetDoorway);
	UNHOOKFUNC(PlayerControl_MurderPlayer);
	UNHOOKFUNC(PlayerControl_CompleteTask);
	UNHOOKFUNC(PlayerControl_StartMeeting);
	UNHOOKFUNC(RoleManager_SelectRoles);
	//UNHOOKFUNC(RoleManager_AssignRolesForTeam);
	//UNHOOKFUNC(RoleManager_AssignRolesFromList);
	UNHOOKFUNC(PlayerControl_HandleRpc);
	UNHOOKFUNC(Renderer_set_enabled);
	UNHOOKFUNC(MeetingHud_Awake);
	UNHOOKFUNC(MeetingHud_Close);
	UNHOOKFUNC(InnerNetClient_Update);
	UNHOOKFUNC(AmongUsClient_OnPlayerLeft);
	UNHOOKFUNC(CustomNetworkTransform_SnapTo);
	//UNHOOKFUNC(Constants_ShouldFlipSkeld);
	UNHOOKFUNC(LobbyBehaviour_Start);
	//UNHOOKFUNC(NoShadowBehaviour_LateUpdate);
	UNHOOKFUNC(FollowerCamera_Update);
	UNHOOKFUNC(DoorBreakerGame_Start);
	UNHOOKFUNC(DoorCardSwipeGame_Begin);
	UNHOOKFUNC(Debug_Log);
	UNHOOKFUNC(Debug_LogError);
	UNHOOKFUNC(Debug_LogException);
	UNHOOKFUNC(Debug_LogWarning);
	UNHOOKFUNC(VersionShower_Start);
	UNHOOKFUNC(EOSManager_LoginFromAccountTab);
	UNHOOKFUNC(EOSManager_InitializePlatformInterface);
	UNHOOKFUNC(EOSManager_IsFreechatAllowed);
	UNHOOKFUNC(ChatController_Update);
	UNHOOKFUNC(InnerNetClient_EnqueueDisconnect);
	UNHOOKFUNC(PlayerControl_TurnOnProtection);
	UNHOOKFUNC(AmongUsClient_OnGameEnd);
	UNHOOKFUNC(InnerNetClient_DisconnectInternal);
	UNHOOKFUNC(AccountManager_UpdateKidAccountDisplay);
	UNHOOKFUNC(PlayerStorageManager_OnReadPlayerPrefsComplete);
	UNHOOKFUNC(EOSManager_UpdatePermissionKeys);
	UNHOOKFUNC(GameOptionsManager_set_CurrentGameOptions);
	UNHOOKFUNC(ExileController_ReEnableGameplay);
	UNHOOKFUNC(SabotageSystemType_SetInitialSabotageCooldown);
	UNHOOKFUNC(FungleShipStatus_OnEnable);
	UNHOOKFUNC(MushroomWallDoor_SetDoorway);
	UNHOOKFUNC(MushroomDoorSabotageMinigame_Begin);

	if (DetourDetach(&(PVOID&)oPresent, dPresent) != 0) return;

	DetourTransactionCommit();
	DirectX::Shutdown();
}