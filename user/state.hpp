#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "il2cpp-appdata.h"
#include <queue>
#include <optional>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "_events.h"
#include "_rpc.h"
#include "json.hpp"
#include "imhotkeys.h"
#include "utility.h"

using namespace app;
using json = nlohmann::ordered_json;

class Settings {
private:
	inline bool Exists(const std::string& name);

public:

	std::vector<ImHotkeys::HotKey> Shortcuts = {
		{"Toggle Menu", { 0xFF, 0xFF, 0xFF, VK_DELETE } },
		{"Toggle Radar", { 0xFF, 0xFF, 0xFF, VK_INSERT } },
		{"Toggle Console", { 0xFF, 0xFF, 0xFF, VK_HOME } },
		{"Repair Sabotage", { 0xFF, 0xFF, 0xFF, VK_END } }
	};

	bool ImGuiInitialized = false;
	bool ShowMenu = false;

	std::string CurrentScene;

	bool MaxVision = false;
	float PrevPlayerSpeed = 1.f;
	float PlayerSpeed = 1.f;
	bool UnlockVents = false;

	bool RevealImpostors = false;
	int PrevKillDistance = 0;
	int KillDistance = 0;
	int PrevTaskBarUpdates = 0;
	int TaskBarUpdates = 0;

	bool NoClip = false;

	int selectedPlayerId = -1;
	PlayerControl* selectedPlayer = NULL;
	std::queue<RPCInterface*> rpcQueue;

	bool ShowRadar = false;
	bool ShowRadar_DeadBodies = false;
	bool ShowRadar_Ghosts = false;
	bool ShowRadar_RightClick_Teleport = false;

	bool ChatAlwaysActive = false;
	bool ReadGhostMessages = false;

	SystemTypes__Enum selectedDoor;
	std::vector<SystemTypes__Enum> mapDoors;
	std::vector<SystemTypes__Enum> pinnedDoors;

	bool ShowConsole = false;
	std::vector<EventInterface*> events;

	std::map<uint8_t, bool> voteMonitor;

	std::vector<PlayerControl*> impostors = { nullptr, nullptr, nullptr };
	int map = -1;
	int impostors_amount = 0;

	bool Wallhack = false;
	bool FreeCam = false;
	float FreeCamSpeed = 1.f;

	bool FollowPlayer = false;
	PlayerControl PlayerToFollow;

	Vector3 camPos = { NULL, NULL, NULL };
	Vector3 prevCamPos = { NULL, NULL, NULL };

	void Load();
	void Save();
};

extern Settings State;