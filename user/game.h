#ifndef GAME_H
#define GAME_H
#define RESOLVE_FUNC(r, n, p) extern r (*n) p

using namespace app;

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
	extern STEAMUSERSTATS_SETACHIEVEMENT* SteamUserStats_SetAchievement;

	extern void scanGameFunctions();
}
#endif