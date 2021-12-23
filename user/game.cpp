#include "pch-il2cpp.h"
#include "game.h"
#include "SignatureScan.hpp"

namespace Game {
	AmongUsClient** pAmongUsClient = nullptr;
	GameData** pGameData = nullptr;
	GameOptionsData** pGameOptionsData = nullptr;
	List_1_PlayerControl_** pAllPlayerControls = nullptr;
	PlayerControl** pLocalPlayer = nullptr;
	ShipStatus** pShipStatus = nullptr;
	LobbyBehaviour** pLobbyBehaviour = nullptr;
	RoleManager** pRoleManager = nullptr;

	STEAMUSERSTATS_SETACHIEVEMENT* SteamUserStats_SetAchievement = nullptr;
	STEAMUSERSTATS_STORESTATS* SteamUserStats_StoreStats = nullptr;
	HATMANAGER_C_GETUNLOCKEDHATS* HatManager_c__GetUnlockedHats_b__11_0 = nullptr;
	HATMANAGER_C_GETUNLOCKEDSKINS* HatManager_c__GetUnlockedSkins_b__12_0 = nullptr;
	HATMANAGER_C_GETUNLOCKEDPETS* HatManager_c__GetUnlockedPets_b__9_0 = nullptr;
	HATMANAGER_C_GETUNLOCKEDVISORS* HatManager_c__GetUnlockedVisors_b__15_0 = nullptr;
	HATMANAGER_C_GETUNLOCKEDNAMEPLATES* HatManager_c__GetUnlockedNamePlates_b__17_0 = nullptr;

	void scanGameFunctions()
	{
		SteamUserStats_SetAchievement = SignatureScan<STEAMUSERSTATS_SETACHIEVEMENT*>("E8 ? ? ? ? 6A 00 E8 ? ? ? ? 83 C4 0C 5D C3 A1 ? ? ? ? F6 80 ? ? ? ? ? 74 0F 83 78 74 00 75 09 50 E8 ? ? ? ? 83 C4 04 6A 00 FF 35 ? ? ? ? E8 ? ? ? ? 83 C4 08 5D C3 CC", GetModuleHandleA("GameAssembly.dll")).ResolveCall();
		SteamUserStats_StoreStats = SignatureScan<STEAMUSERSTATS_STORESTATS*>("E8 ? ? ? ? 83 C4 0C 5D C3 A1 ? ? ? ? F6 80 ? ? ? ? ? 74 0F 83 78 74 00 75 09 50 E8 ? ? ? ? 83 C4 04 6A 00 FF 35 ? ? ? ? E8 ? ? ? ? 83 C4 08 5D C3 CC", GetModuleHandleA("GameAssembly.dll")).ResolveCall();
		HatManager_c__GetUnlockedHats_b__11_0 = SignatureScan<HATMANAGER_C_GETUNLOCKEDHATS*>("55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 3F 80 78 50 00", GetModuleHandleA("GameAssembly.dll"));
		HatManager_c__GetUnlockedSkins_b__12_0 = SignatureScan<HATMANAGER_C_GETUNLOCKEDSKINS*>("55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 42 80 B8 ? ? ? ? ?", GetModuleHandleA("GameAssembly.dll"));
		HatManager_c__GetUnlockedPets_b__9_0 = SignatureScan<HATMANAGER_C_GETUNLOCKEDPETS*>("55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 3F 80 78 2C 00", GetModuleHandleA("GameAssembly.dll"));
		HatManager_c__GetUnlockedVisors_b__15_0 = SignatureScan<HATMANAGER_C_GETUNLOCKEDVISORS*>("55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 3F 80 78 40 00", GetModuleHandleA("GameAssembly.dll"));
		HatManager_c__GetUnlockedNamePlates_b__17_0 = SignatureScan<HATMANAGER_C_GETUNLOCKEDNAMEPLATES*>("55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 3F 80 78 30 00", GetModuleHandleA("GameAssembly.dll"));
	}
}