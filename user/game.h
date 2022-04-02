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
	
	extern STEAMUSERSTATS_SETACHIEVEMENT* SteamUserStats_SetAchievement;
	extern STEAMUSERSTATS_STORESTATS* SteamUserStats_StoreStats;

	extern void scanGameFunctions();
}