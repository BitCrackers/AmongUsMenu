#pragma once
#include "DestroyableSingleton.h"

using namespace app;

namespace Game {
	constexpr size_t MAX_PLAYERS = 15;

	using PlayerId = uint8_t;
	using ClientId = int32_t;
	using ColorId = int32_t;

	using Voter = PlayerId;
	using VotedFor = PlayerId;

	constexpr ColorId NoColorId = -1;
	constexpr PlayerId NoPlayerId = -1;
	constexpr ClientId NoClientId = -1;
	constexpr ClientId HostInherit = -2;
	constexpr ClientId CurrentClient = -3;

	constexpr VotedFor HasNotVoted = 255, MissedVote = 254, SkippedVote = 253, DeadVote = 252;

	extern AmongUsClient** pAmongUsClient;
	extern GameData** pGameData;
	extern List_1_PlayerControl_** pAllPlayerControls;
	extern PlayerControl** pLocalPlayer;
	extern ShipStatus** pShipStatus;
	extern LobbyBehaviour** pLobbyBehaviour;

	extern DestroyableSingleton<app::RoleManager*> RoleManager;

	//typedef bool STEAMUSERSTATS_SETACHIEVEMENT(String* pchName);
	//typedef bool STEAMUSERSTATS_STORESTATS();
	
	//extern STEAMUSERSTATS_SETACHIEVEMENT* SteamUserStats_SetAchievement;
	//extern STEAMUSERSTATS_STORESTATS* SteamUserStats_StoreStats;

	extern void scanGameFunctions();
}