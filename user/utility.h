#pragma once
#include <vector>
#include <imgui/imgui.h>
#include "_events.h"
#include <filesystem>
#include "game.h"

#define UNIQUE_NAME(prefix)	_CONCAT(prefix ## _, __COUNTER__) ## _CONCAT(at, __LINE__)

#define _synchronized(lock, name, mtx)	if (lock name(mtx); true)
#define synchronized_read(smtx)	_synchronized(std::shared_lock<decltype(smtx)>, UNIQUE_NAME(rdLock), smtx)
#define synchronized_write(mtx)	_synchronized(std::unique_lock<decltype(mtx)>, UNIQUE_NAME(lock), mtx)
/*
	it mimics the behaviour of the Java construct
	"synchronized(this) { }"
*/
#define synchronized(mtx)	synchronized_write(mtx)
/*
	to secure a code-block, use the following syntax:
	"{ SYNCHRONIZED(mutex); <commands> }"
*/
#define SYNCHRONIZED(mtx)	std::scoped_lock UNIQUE_NAME(lock)(mtx)

enum class MapType {
	MAP_SKELD = 0,
	MAP_MIRAHQ = 1,
	MAP_POLUS = 2,
	MAP_AIRSHIP = 3
};

enum class RoleType
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
	int GuardianAngelCount = 0;
	int GuardianAngelChance = 0;
	int MaxCrewmates = Game::MAX_PLAYERS;
	RoleRates(const class GameOptions& gameOptions, int playerAmount);
	int GetRoleCount(RoleTypes__Enum role);
	void SubtractRole(RoleTypes__Enum role);
};

class PlayerSelection {
	Game::ClientId clientId;
	Game::PlayerId playerId;

	struct [[nodiscard]] Result {
		constexpr _Ret_notnull_ auto get_PlayerControl() const {
#if _CONTAINER_DEBUG_LEVEL > 0
			assert(has_value() && "Cannot access value of empty result");
#endif
			return _playerControl;
		}
		constexpr _Ret_notnull_ auto get_PlayerData() const {
#if _CONTAINER_DEBUG_LEVEL > 0
			assert(has_value() && "get_PlayerData() called on empty result");
#endif
			return _playerData;
		}
		constexpr bool is_LocalPlayer() const {
#if _CONTAINER_DEBUG_LEVEL > 0
			assert(has_value() && "is_LocalPlayer() called on empty result");
#endif
			return _playerControl->fields._.OwnerId == (*Game::pAmongUsClient)->fields._.ClientId;
		}
		constexpr bool is_Disconnected() const {
#if _CONTAINER_DEBUG_LEVEL > 0
			assert(has_value() && "is_Disconnected() called on empty result");
#endif
			return _playerData->fields.Disconnected;
		}
		constexpr bool equals(_Maybenull_ const PlayerControl* playerControl) const {
			return _playerControl == playerControl;
		}
		constexpr bool equals(_Maybenull_ const GameData_PlayerInfo* playerData) const {
			return _playerData == playerData;
		}
		constexpr bool has_value() const {
			return _has_value;
		}
	private:
		friend class PlayerSelection;
		PlayerControl* _playerControl;
		GameData_PlayerInfo* _playerData;
		bool _has_value;

		constexpr Result() noexcept {
			_playerControl = nullptr;
			_playerData = nullptr;
			_has_value = false;
		}

		constexpr Result(_Notnull_ PlayerControl* pc, _Notnull_ GameData_PlayerInfo* data) {
			_playerControl = pc;
			_playerData = data;
			_has_value = true;
		}
		constexpr Result(const Result&) = delete;
	};
public:
	PlayerSelection() noexcept;
	explicit PlayerSelection(const  PlayerControl* playerControl);
	explicit PlayerSelection(GameData_PlayerInfo* playerData);

	PlayerSelection::Result validate();

	bool equals(const PlayerSelection& selectedPlayer) const;
	Game::PlayerId get_PlayerId() const noexcept;
	Game::ClientId get_ClientId() const noexcept;
	bool is_LocalPlayer() const noexcept;
	bool has_value() const noexcept {
		return (this->clientId != Game::NoClientId || this->playerId != Game::NoPlayerId);
	}
	/*[[deprecated]]*/ bool has_value() {
		return validate().has_value();
	}
	/*[[deprecated]]*/ std::optional<PlayerControl*> get_PlayerControl() const;
	/*[[deprecated]]*/ std::optional<GameData_PlayerInfo*> get_PlayerData() const;
};

int randi(int lo, int hi);
ImVec4 AmongUsColorToImVec4(const Color& color);
ImVec4 AmongUsColorToImVec4(const Color32& color);
bool IsInLobby();
bool IsHost();
bool IsInGame();
bool IsInMultiplayerGame();
bool IsColorBlindMode();
int GetMaxImposterAmount(int playerAmount);
int GenerateRandomNumber(int min, int max);
GameData_PlayerInfo* GetPlayerData(PlayerControl* player);
Vector2 GetTrueAdjustedPosition(PlayerControl* player);
GameData_PlayerInfo* GetPlayerDataById(Game::PlayerId id);
PlayerControl* GetPlayerControlById(Game::PlayerId id);
PlainDoor* GetPlainDoorByRoom(SystemTypes__Enum room);
il2cpp::Array<PlainDoor__Array> GetAllPlainDoors();
il2cpp::List<List_1_PlayerControl_> GetAllPlayerControl();
il2cpp::List<List_1_GameData_PlayerInfo_> GetAllPlayerData();
il2cpp::Array<DeadBody__Array> GetAllDeadBodies();
il2cpp::List<List_1_PlayerTask_> GetPlayerTasks(PlayerControl* player);
std::vector<NormalPlayerTask*> GetNormalPlayerTasks(PlayerControl* player);
SabotageTask* GetSabotageTask(PlayerControl* player);
void RepairSabotage(PlayerControl* player);
void CompleteTask(NormalPlayerTask* playerTask);
const char* TranslateTaskTypes(TaskTypes__Enum taskType);
const char* TranslateSystemTypes(SystemTypes__Enum systemType);
Color32 GetPlayerColor(Game::ColorId colorId);
std::filesystem::path getModulePath(HMODULE hModule);
std::string getGameVersion();
SystemTypes__Enum GetSystemTypes(const Vector2& vector);
// TO-DO:
// some C++ wizardry to allow overloading on pointer types w/ different base type (then we can rename both to just GetEventPlayer)
std::optional<EVENT_PLAYER> GetEventPlayer(GameData_PlayerInfo* playerInfo);
std::optional<EVENT_PLAYER> GetEventPlayerControl(PlayerControl* player);
std::optional<Vector2> GetTargetPosition(GameData_PlayerInfo* playerInfo);
il2cpp::Array<Camera__Array> GetAllCameras();
il2cpp::List<List_1_InnerNet_ClientData_> GetAllClients();
Vector2 GetSpawnLocation(Game::PlayerId playerId, int numPlayer, bool initialSpawn);
bool IsAirshipSpawnLocation(const Vector2& vec);
Vector2 Rotate(const Vector2& vec, float degrees);
bool Equals(const Vector2& vec1, const Vector2& vec2);
std::string ToString(Object* object);
std::string ToString(Game::PlayerId id);
std::string ToString(__maybenull PlayerControl* player);
std::string ToString(__maybenull GameData_PlayerInfo* data);
std::string GetGitCommit();
std::string GetGitBranch();
void ImpersonateName(PlayerSelection& player);
Game::ColorId GetRandomColorId();
void SaveOriginalAppearance();
void ResetOriginalAppearance();
bool PlayerIsImpostor(GameData_PlayerInfo* player);
GameData_PlayerOutfit* GetPlayerOutfit(GameData_PlayerInfo* player, bool includeShapeshifted = false);
Color GetRoleColor(RoleBehaviour* roleBehaviour);
std::string GetRoleName(RoleBehaviour* roleBehaviour, bool abbreviated = false);
RoleTypes__Enum GetRoleTypesEnum(RoleType role);
float GetDistanceBetweenPoints_Unity(const Vector2& p1, const Vector2& p2);
float GetDistanceBetweenPoints_ImGui(const ImVec2& p1, const ImVec2& p2);

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

bool Object_1_IsNotNull(app::Object_1* unity_object);
bool Object_1_IsNull(app::Object_1* unity_object);

std::string GetPlayerName();
void SetPlayerName(std::string_view name);

void SaveGameOptions();
void SaveGameOptions(const class GameOptions& gameOptions);

class RoleOptions {
public:
	RoleOptions(app::IRoleOptionsCollection* options)
		: _options(options) {
	}

	RoleOptions& SetRoleRate(app::RoleTypes__Enum role, int32_t maxCount, int32_t chance);
	RoleOptions& SetRoleRecommended(app::RoleTypes__Enum role);

	int32_t GetNumPerGame(app::RoleTypes__Enum role) const;
	int32_t GetChancePerGame(app::RoleTypes__Enum role) const;
private:
	app::IRoleOptionsCollection* _options;
};

class GameOptions {
public:
	GameOptions();
	GameOptions(app::IGameOptions* options) : _options(options){};

	constexpr bool HasOptions() const {
		return _options != nullptr;
	}

	GameOptions& SetByte(app::ByteOptionNames__Enum option, uint8_t value);
	GameOptions& SetFloat(app::FloatOptionNames__Enum option, float value);
	GameOptions& SetBool(app::BoolOptionNames__Enum option, bool value);
	GameOptions& SetInt(app::Int32OptionNames__Enum option, int32_t value);
	GameOptions& SetUInt(app::UInt32OptionNames__Enum option, uint32_t value);

	uint8_t GetByte(app::ByteOptionNames__Enum option, uint8_t defaultValue = 0) const;
	float GetFloat(app::FloatOptionNames__Enum option, float defaultValue = 0.0) const;
	bool GetBool(app::BoolOptionNames__Enum option, bool defaultValue = false) const;
	int32_t GetInt(app::Int32OptionNames__Enum option, int32_t defaultValue = 0) const;

	app::GameModes__Enum GetGameMode() const;
	int32_t GetMaxPlayers() const;
	uint8_t GetMapId() const;
	int32_t GetNumImpostors() const;
	int32_t GetTotalTaskCount() const;
	RoleOptions GetRoleOptions() const;

	float GetPlayerSpeedMod() const;
	float GetKillCooldown() const;
protected:
	app::IGameOptions* _options;
};

class GameLogicOptions : public GameOptions {
public:
	GameLogicOptions();
};
