#include "pch-il2cpp.h"
#include "game.h"
#include "SignatureScan.hpp"

namespace Game {
	AmongUsClient** pAmongUsClient;
	GameData** pGameData;
	GameOptionsData** pGameOptionsData;
	List_1_PlayerControl_** pAllPlayerControls;
	PlayerControl** pLocalPlayer;
	ShipStatus** pShipStatus;
	LobbyBehaviour** pLobbyBehaviour;
	RoleManager** pRoleManager;

	STEAMUSERSTATS_SETACHIEVEMENT* SteamUserStats_SetAchievement = nullptr;

	void scanGameFunctions()
	{
		Game::SteamUserStats_SetAchievement = SignatureScan<STEAMUSERSTATS_SETACHIEVEMENT*>("E8 ? ? ? ? 6A 00 E8 ? ? ? ? 83 C4 0C 5D C3 A1 ? ? ? ? F6 80 ? ? ? ? ? 74 0F 83 78 74 00 75 09 50 E8 ? ? ? ? 83 C4 04 6A 00 FF 35 ? ? ? ? E8 ? ? ? ? 83 C4 08 5D C3 CC", GetModuleHandleA("GameAssembly.dll")).ResolveCall();
	}
}