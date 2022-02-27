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

enum RoleType
{
	Random = 0,
	Crewmate = 1,
	Scientist = 2,
	Engineer = 3,
	Impostor = 4,
	Shapeshifter = 5,
};

class RoleRates {
public:
	int ImposterCount = 0;
	int ShapeshifterCount = 0;
	int ShapeshifterChance = 0;
	int ScientistCount = 0;
	int ScientistChance = 0;
	int EngineerCount = 0;
	int EngineerChance = 0;
	int MaxCrewmates = 15;
	RoleRates(RoleOptionsData* roleOptions);
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
// TO-DO:
// some C++ wizardry to allow overloading on pointer types w/ different base type (then we can rename both to just GetEventPlayer)
std::optional<EVENT_PLAYER> GetEventPlayer(GameData_PlayerInfo* playerInfo);
std::optional<EVENT_PLAYER> GetEventPlayerControl(PlayerControl* player);
std::optional<Vector2> GetTargetPosition(GameData_PlayerInfo* playerInfo);
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
bool PlayerIsImpostor(GameData_PlayerInfo* player);
GameData_PlayerOutfit* GetPlayerOutfit(GameData_PlayerInfo* player, bool includeShapeshifted = false);
Color GetRoleColor(RoleBehaviour* roleBehaviour);
std::string GetRoleName(RoleBehaviour* roleBehaviour, bool abbreviated = false);
RoleTypes__Enum GetRoleTypesEnum(RoleType role);
float GetDistanceBetweenPoints_Unity(Vector2 p1, Vector2 p2);
float GetDistanceBetweenPoints_ImGui(ImVec2 p1, ImVec2 p2);

/// <summary>
/// Simplifies a list of points by ensuring the distance between consecutive points is greater than the squared distance threshold; all other points are discarded.
/// </summary>
/// <param name="inPoints">Collection of points pending simplification</param>
/// <param name="inTimeStamps">Collection of timestamps associated with each point pending simplification</param>
/// <param name="outPoints">Contains only the points that meet the distance filter</param>
/// <param name="outTimeStamps">The original timestamp associated with each point</param>
/// <param name="sqDistanceThreshold">The squared distance between two consecutive points. We use squared distance to avoid a costly sqrtf operation in the distance calculation</param>
/// <param name="clearInputs">Whether both input collections should be cleared after processing. If no work is done they will not be cleared.</param>
void DoPolylineSimplification(std::vector<ImVec2>& inPoints, std::vector<std::chrono::system_clock::time_point>& inTimeStamps, std::vector<ImVec2>& outPoints, std::vector<std::chrono::system_clock::time_point>& outTimeStamps, float sqDistanceThreshold, bool clearInputs);

float getMapXOffsetSkeld(float x);