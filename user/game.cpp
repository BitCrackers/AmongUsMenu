#include "pch-il2cpp.h"
#include "game.h"
#include "SignatureScan.hpp"

namespace Game {
	AmongUsClient** pAmongUsClient = nullptr;
	GameData** pGameData = nullptr;
	List_1_PlayerControl_** pAllPlayerControls = nullptr;
	PlayerControl** pLocalPlayer = nullptr;
	ShipStatus** pShipStatus = nullptr;
	LobbyBehaviour** pLobbyBehaviour = nullptr;
	DestroyableSingleton<app::RoleManager*> RoleManager { "Assembly-CSharp, RoleManager" };

	//STEAMUSERSTATS_SETACHIEVEMENT* SteamUserStats_SetAchievement = nullptr;
	//STEAMUSERSTATS_STORESTATS* SteamUserStats_StoreStats = nullptr;

	void scanGameFunctions()
	{
		//SteamUserStats_SetAchievement = SignatureScan<STEAMUSERSTATS_SETACHIEVEMENT*>("E8 ? ? ? ? 6A 00 E8 ? ? ? ? 83 C4 0C 5D C3 A1 ? ? ? ? F6 80 ? ? ? ? ? 74 0F 83 78 74 00 75 09 50 E8 ? ? ? ? 83 C4 04 6A 00 FF 35 ? ? ? ? E8 ? ? ? ? 83 C4 08 5D C3 CC", GetModuleHandleA("GameAssembly.dll")).ResolveCall();
		//SteamUserStats_StoreStats = SignatureScan<STEAMUSERSTATS_STORESTATS*>("E8 ? ? ? ? 83 C4 0C 5D C3 A1 ? ? ? ? F6 80 ? ? ? ? ? 74 0F 83 78 74 00 75 09 50 E8 ? ? ? ? 83 C4 04 6A 00 FF 35 ? ? ? ? E8 ? ? ? ? 83 C4 08 5D C3 CC", GetModuleHandleA("GameAssembly.dll")).ResolveCall();
	}
}