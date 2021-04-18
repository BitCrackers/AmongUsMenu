#pragma once
#include <vector>
#include <imgui/imgui.h>
#include "_events.h"
#include <filesystem>

struct CorrectedColor32 {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

enum MapType {
	MAP_SKELD = 0,
	MAP_MIRAHQ = 1,
	MAP_POLUS = 2,
	MAP_AIRSHIP = 3
};

class PlayerSelection {
	bool hasValue;
	int32_t clientId;
	uint8_t playerId;

public:
	PlayerSelection();
	PlayerSelection(PlayerControl* playerControl);
	PlayerSelection(GameData_PlayerInfo* playerData);
	bool equals(PlayerControl* playerControl);
	bool equals(GameData_PlayerInfo* playerDate);
	bool equals(PlayerSelection selectedPlayer);
	PlayerControl* get_PlayerControl();
	GameData_PlayerInfo* get_PlayerData();
	bool has_value();
	uint8_t get_PlayerId();
	int32_t get_ClientId();
	bool is_LocalPlayer();
	bool is_Disconnected();
};

template < typename T, typename K, typename V >
std::vector<std::pair<K, V>> GetEntriesFromDictionary(T d) {
	auto entries = d->fields.entries;
	int length = d->fields.count;

	std::vector<std::pair<K, V>> vec(length);
	for (int i = 0; i < length; i++) {
		K key = entries->vector[i].key;
		V value = entries->vector[i].value;
		vec[i] = { key, value };
	}
	return vec;
}

template < typename T, typename E >
std::vector<E> GetElementsFromList(T l) {
	auto elements = l->fields._items;
	int length = l->fields._size;

	std::vector<E> vec(length);
	for (int i = 0; i < length; i++) {
		vec[i] = elements->vector[i];
	}
	return vec;
}

template < typename T, typename E >
std::vector<E> GetElementsFromArray(T a) {
	auto elements = a;
	int length = a->max_length;

	std::vector<E> vec(length);
	for (int i = 0; i < length; i++) {
		vec[i] = elements->vector[i];
	}
	return vec;
}

int randi(int lo, int hi);
ImVec4 AmongUsColorToImVec4(Color color);
ImVec4 AmongUsColorToImVec4(CorrectedColor32 color);
bool IsInLobby();
bool IsHost();
bool IsInGame();
bool IsInMultiplayerGame();
GameData_PlayerInfo* GetPlayerData(PlayerControl* player);
Vector2 GetTrueAdjustedPosition(PlayerControl* player);
GameData_PlayerInfo* GetPlayerDataById(uint8_t id);
PlayerControl* GetPlayerControlById(uint8_t id);
PlainDoor* GetPlainDoorByRoom(SystemTypes__Enum room);
std::vector<PlainDoor*> GetAllPlainDoors();
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
std::filesystem::path getModulePath(HMODULE hModule);
std::string getGameVersion();
SystemTypes__Enum GetSystemTypes(Vector2 vector);
std::optional<EVENT_PLAYER> GetEventPlayer(GameData_PlayerInfo* playerInfo);
EVENT_PLAYER GetEventPlayer(PlayerControl* player);
std::vector<Camera*> GetAllCameras();
std::vector<ClientData*> GetAllClients();
Vector2 GetSpawnLocation(int playerId, int numPlayer, bool initialSpawn);
bool IsAirshipSpawnLocation(Vector2 vec);
Vector2 Rotate(Vector2 vec, float degrees);
bool Equals(Vector2 vec1, Vector2 vec2);
std::string ToString(Object* object);
std::string GetGitCommit();
std::string GetGitBranch();
void ImpersonateName(PlayerSelection player);
int GetRandomColorId();
void SaveOriginalAppearance();
void ResetOriginalAppearance();