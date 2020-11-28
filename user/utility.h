#pragma once
#include "il2cpp-appdata.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "game.hpp"
#include <imgui/imgui.h>
#include "state.hpp"
#include "_events.h"

struct CorrectedColor32 {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

int randi(int lo, int hi);
ImVec4 AmongUsColorToImVec4(Color color);
ImVec4 AmongUsColorToImVec4(CorrectedColor32 color);
bool IsInLobby();
bool IsHost();
bool IsInGame();
bool IsInMultiplayerGame();
GameData_PlayerInfo* GetPlayerData(PlayerControl* player);
GameData_PlayerInfo* GetPlayerDataById(uint8_t id);
PlayerControl* GetPlayerControlById(uint8_t id);
std::vector<PlayerControl*> GetAllPlayerControl();
std::vector<GameData_PlayerInfo*> GetAllPlayerData();
std::vector<DeadBody*> GetAllDeadBodies();
std::vector<PlayerTask*> GetPlayerTasks(PlayerControl* player);
std::vector<NormalPlayerTask*> GetNormalPlayerTasks(PlayerControl* player);
SabotageTask* GetSabotageTask(PlayerControl* player);
void RepairSabotage(PlayerControl* player);
void CompleteTask(NormalPlayerTask* playerTask);
const char* TranslateTaskTypes(TaskTypes__Enum taskType);
const char* TranslateSystemTypes(SystemTypes__Enum systemType);
CorrectedColor32 GetPlayerColor(uint8_t colorId);
std::string getModulePath();
std::string getGameVersion();
SystemTypes__Enum GetSystemTypes(Vector2 vector);
std::optional<EVENT_PLAYER> GetEventPlayer(GameData_PlayerInfo* playerInfo);
EVENT_PLAYER GetEventPlayer(PlayerControl* player);
std::optional<Vector2> GetLastWalkEventPosition(uint8_t playerId);
std::vector<Camera*> GetAllCameras();