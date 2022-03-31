#pragma once

using namespace app;

#define MAX_PLAYERS 15

namespace Game {
	extern AmongUsClient** pAmongUsClient;
	extern GameData** pGameData;
	extern GameOptionsData** pGameOptionsData;
	extern List_1_PlayerControl_** pAllPlayerControls;
	extern PlayerControl** pLocalPlayer;
	extern ShipStatus** pShipStatus;
	extern LobbyBehaviour** pLobbyBehaviour;
	extern RoleManager** pRoleManager;

	typedef bool STEAMUSERSTATS_SETACHIEVEMENT(String* pchName);
	typedef bool STEAMUSERSTATS_STORESTATS();
	typedef bool HATMANAGER_C_GETUNLOCKEDHATS(HatManager_c* __this, HatData* h, MethodInfo* method);
	typedef bool HATMANAGER_C_GETUNLOCKEDSKINS(HatManager_c* __this, SkinData* s, MethodInfo* method);
	typedef bool HATMANAGER_C_GETUNLOCKEDPETS(HatManager_c* __this, PetData* h, MethodInfo* method);
	typedef bool HATMANAGER_C_GETUNLOCKEDVISORS(HatManager_c* __this, VisorData* s, MethodInfo* method);
	typedef bool HATMANAGER_C_GETUNLOCKEDNAMEPLATES(HatManager_c* __this, NamePlateData* s, MethodInfo* method);
	
	extern STEAMUSERSTATS_SETACHIEVEMENT* SteamUserStats_SetAchievement;
	extern STEAMUSERSTATS_STORESTATS* SteamUserStats_StoreStats;
	extern HATMANAGER_C_GETUNLOCKEDHATS* HatManager_c__GetUnlockedHats_b__11_0;
	extern HATMANAGER_C_GETUNLOCKEDSKINS* HatManager_c__GetUnlockedSkins_b__12_0;
	extern HATMANAGER_C_GETUNLOCKEDPETS* HatManager_c__GetUnlockedPets_b__9_0;
	extern HATMANAGER_C_GETUNLOCKEDVISORS* HatManager_c__GetUnlockedVisors_b__15_0;
	extern HATMANAGER_C_GETUNLOCKEDNAMEPLATES* HatManager_c__GetUnlockedNamePlates_b__17_0;

	extern void scanGameFunctions();
}