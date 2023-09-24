#include "pch-il2cpp.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"
#include "gitparams.h"
#include "logger.h"
#include "profiler.h"
#include <random>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

int randi(int lo, int hi) {
	int n = hi - lo + 1;
	int i = rand() % n;
	if (i < 0) i = -i;
	return lo + i;
}

RoleRates::RoleRates(const class GameOptions& gameOptions, int playerAmount) {
	this->ImposterCount = gameOptions.GetNumImpostors();
	auto maxImpostors = GetMaxImposterAmount(playerAmount);
	if(this->ImposterCount > maxImpostors)
		this->ImposterCount = maxImpostors;

	const auto& roleOptions = gameOptions.GetRoleOptions();
#define GET_ROLE_RATE(type) \
	this->type##Chance = roleOptions.GetChancePerGame(RoleTypes__Enum::##type); \
	this->type##Count = roleOptions.GetNumPerGame(RoleTypes__Enum::##type);

	GET_ROLE_RATE(Engineer);
	GET_ROLE_RATE(Scientist);
	GET_ROLE_RATE(Shapeshifter);
	GET_ROLE_RATE(GuardianAngel);
#undef GET_ROLE_RATE
}

int RoleRates::GetRoleCount(RoleTypes__Enum role) {
	switch (role)
	{
		case RoleTypes__Enum::Shapeshifter:
			return this->ShapeshifterCount;
		case RoleTypes__Enum::Impostor:
			return this->ImposterCount;
		case RoleTypes__Enum::Scientist:
			return this->ScientistCount;
		case RoleTypes__Enum::Engineer:
			return this->EngineerCount;
		case RoleTypes__Enum::GuardianAngel:
			return this->GuardianAngelCount;
		case RoleTypes__Enum::Crewmate:
			return this->MaxCrewmates;
		default:
#ifdef _DEBUG
			assert(false);
#endif
			return 0;
	}
}

void RoleRates::SubtractRole(RoleTypes__Enum role) {
	if (role == RoleTypes__Enum::Shapeshifter)
	{
		if (this->ShapeshifterCount < 1)
			return;
		this->ShapeshifterCount--;
		this->ImposterCount--;
	}
	else if (role == RoleTypes__Enum::Impostor)
	{
		if (this->ImposterCount < 1)
			return;
		this->ImposterCount--;
		this->ShapeshifterCount--;
	}
	else if (role == RoleTypes__Enum::Scientist)
	{
		if (this->ScientistCount < 1)
			return;
		this->ScientistCount--;
	}
	else if (role == RoleTypes__Enum::Engineer)
	{
		if (this->EngineerCount < 1)
			return;
		this->EngineerCount--;
	}
	else if (role == RoleTypes__Enum::GuardianAngel)
	{
		if (this->GuardianAngelCount < 1)
			return;
		this->GuardianAngelCount--;
	}
}

int GetMaxImposterAmount(int playerAmount)
{
	if(playerAmount >= 9)
		return 3;
	if(playerAmount >= 7)
		return 2;
	return 1;
}

int GenerateRandomNumber(int min, int max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}

Vector2 GetTrueAdjustedPosition(PlayerControl* playerControl)
{
	Vector2 playerVector2 = PlayerControl_GetTruePosition(playerControl, NULL);
	playerVector2.y += 0.36f;
	return playerVector2;
}

#pragma region PlayerSelection
PlayerSelection::PlayerSelection() noexcept
{
	this->clientId = Game::NoClientId;
	this->playerId = Game::NoPlayerId;
}

PlayerSelection::PlayerSelection(const PlayerControl* playerControl) {
	if (Object_1_IsNotNull((Object_1*)playerControl)) {
		this->clientId = playerControl->fields._.OwnerId;
		this->playerId = playerControl->fields.PlayerId;
	}
	else {
		new (this)PlayerSelection();
	}
}

PlayerSelection::PlayerSelection(GameData_PlayerInfo* playerData) {
	new (this)PlayerSelection(app::GameData_PlayerInfo_get_Object(playerData, nullptr));
}

PlayerSelection::Result PlayerSelection::validate() {
	auto playerControl = this->get_PlayerControl();
	if (playerControl) {
		auto playerData = app::PlayerControl_get_Data((*playerControl), nullptr);
		if (playerData) {
			return { (*playerControl), playerData };
		}
	}
	this->clientId = Game::NoClientId;
	this->playerId = Game::NoPlayerId;
	return {};
}

bool PlayerSelection::equals(const PlayerSelection& selectedPlayer) const
{
	if (!this->has_value() || !selectedPlayer.has_value()) return false;
	return std::tie(clientId,  playerId) == std::tie(selectedPlayer.clientId, selectedPlayer.playerId);
}

std::optional<PlayerControl*> PlayerSelection::get_PlayerControl() const {
	if (!this->has_value()) 
		return std::nullopt;

	if (clientId == Game::HostInherit) {
		auto playerControl = GetPlayerControlById(this->playerId);
		if (Object_1_IsNotNull((Object_1*)playerControl))
			return playerControl;
#if _DEBUG
		if (playerControl) {
			// oops: game bug
			STREAM_ERROR(ToString(playerControl) << " playerControl is invalid");
		}
#endif
	}

	for (auto client : GetAllClients()) {
		if (client->fields.Id == this->clientId) {
			if (auto playerControl = client->fields.Character;
				Object_1_IsNotNull((Object_1*)playerControl)) {
				return playerControl;
			}
#if _DEBUG
			if (client->fields.Character) {
				// oops: game bug
				STREAM_ERROR(ToString(client->fields.Character) << " Character is invalid");
			}
#endif
			return std::nullopt;
		}
	}

	return std::nullopt;
}

std::optional<GameData_PlayerInfo*> PlayerSelection::get_PlayerData() const
{
	if (auto data = GetPlayerData(this->get_PlayerControl().value_or(nullptr));
		data != nullptr) {
		return data;
	}
	return std::nullopt;
}

Game::PlayerId PlayerSelection::get_PlayerId() const noexcept {
#if 0//_DEBUG
	LOG_ASSERT(this->has_value());
#endif
	return this->playerId;
}

Game::ClientId PlayerSelection::get_ClientId() const noexcept {
#if 0//_DEBUG
	LOG_ASSERT(this->has_value());
#endif
	return this->clientId;
}

bool PlayerSelection::is_LocalPlayer() const noexcept {
#if 0//_DEBUG
<<<<<<< HEAD
	//assert(this->has_value());
=======
	LOG_ASSERT(this->has_value());
>>>>>>> e5f1c6f3dbd1732fa54ae7e021bbea9492767f81
#endif
	return this->clientId == (*Game::pAmongUsClient)->fields._.ClientId;
}
#pragma endregion

ImVec4 AmongUsColorToImVec4(const Color& color) {
	return ImVec4(color.r, color.g, color.b, color.a);
}

ImVec4 AmongUsColorToImVec4(const Color32& color) {
	static_assert(offsetof(Color32, a) + sizeof(Color32::a) == sizeof(Color32::rgba), "Color32 must be defined as union");
	return ImVec4(color.r / 255.0F, color.g / 255.0F, color.b / 255.0F, color.a / 255.0F);
}

#define LocalInGame (((*Game::pAmongUsClient)->fields._.NetworkMode == NetworkModes__Enum::LocalGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Started))
#define LocalInLobby (((*Game::pAmongUsClient)->fields._.NetworkMode == NetworkModes__Enum::LocalGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Joined))
#define OnlineInGame (((*Game::pAmongUsClient)->fields._.NetworkMode == NetworkModes__Enum::OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Started))
#define OnlineInLobby (((*Game::pAmongUsClient)->fields._.NetworkMode == NetworkModes__Enum::OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Joined))
#define TutorialScene (State.CurrentScene.compare("Tutorial") == 0)

bool IsInLobby() {
	if (Object_1_IsNull((Object_1*)*Game::pAmongUsClient)) return false;
	if (!app::GameManager_get_Instance(nullptr)) return false;
	return (LocalInLobby || OnlineInLobby) && Object_1_IsNotNull((Object_1*)*Game::pLocalPlayer);
}

bool IsHost() {
	if (Object_1_IsNull((Object_1*)*Game::pAmongUsClient)) return false;
	return app::InnerNetClient_get_AmHost((InnerNetClient*)(*Game::pAmongUsClient), NULL);
}

bool IsInGame() {
	if (Object_1_IsNull((Object_1*)*Game::pAmongUsClient)) return false;
	if (!app::GameManager_get_Instance(nullptr)) return false;
	return (LocalInGame || OnlineInGame || TutorialScene) && Object_1_IsNotNull((Object_1*)*Game::pShipStatus) && Object_1_IsNotNull((Object_1*)*Game::pLocalPlayer);
}

bool IsInMultiplayerGame() {
	if (Object_1_IsNull((Object_1*)*Game::pAmongUsClient)) return false;
	if (!app::GameManager_get_Instance(nullptr)) return false;
	return (LocalInGame || OnlineInGame) && Object_1_IsNotNull((Object_1*)*Game::pShipStatus) && Object_1_IsNotNull((Object_1*)*Game::pLocalPlayer);
}

bool IsColorBlindMode() {
	if (auto settings = DataManager_get_Settings(nullptr)) {
		if (auto accessibility = SettingsData_get_Accessibility(settings, nullptr)) {
			return AccessibilitySettingsData_get_ColorBlindMode(accessibility, nullptr);
		}
	}
	return false;
}

bool IsStreamerMode() {
	if (auto settings = DataManager_get_Settings(nullptr)) {
		if (auto gameplay = SettingsData_get_Gameplay(settings, nullptr)) {
			return GameplaySettingsData_get_StreamerMode(gameplay, nullptr);
		}
	}
	return false;
}

std::string GetHostUsername() {
	return convert_from_string(InnerNetClient_GetHost((InnerNetClient*)(*Game::pAmongUsClient), NULL)->fields.PlayerName);
}

std::string RemoveHtmlTags(std::string html_str) {
	size_t a = 0, b = 0;
	for (size_t a = b; a < html_str.length(); a++) {
		if (html_str[a] == '<') {
			for (size_t b = a; b < html_str.length(); b++) {
				if (html_str[b] == '>') {
					html_str.erase(a, (b - a + 1));
					break;
				}
			}
		}
	}
	return html_str;
}


GameData_PlayerInfo* GetPlayerData(PlayerControl* player) {
	if (player) return app::PlayerControl_get_Data(player, NULL);
	return NULL;
}

GameData_PlayerInfo* GetPlayerDataById(Game::PlayerId id) {
	return app::GameData_GetPlayerById((*Game::pGameData), id, NULL);
}

PlayerControl* GetPlayerControlById(Game::PlayerId id) {
	for (auto player : GetAllPlayerControl()) {
		if (player->fields.PlayerId == id) return player;
	}

	return NULL;
}

bool IsColorAvailable(int colorId) {
	for (auto player : GetAllPlayerData()) {
		if (GetPlayerOutfit(player)->fields.ColorId = colorId) {
			return false;
			break;
		}
	}
	return true;
}

std::string GenerateRandomString() {
	std::string allowedChars = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int outputLength = randi(0,9) % 10 + 1;

	int randomIndex;
	std::string outputString = "";

	for (int i = 0; i < outputLength; ++i) {
		randomIndex = rand() % (allowedChars.length()-1);
		outputString += allowedChars[randomIndex];
	}
	//std::string outputString = convert_from_string(AccountManager_GetRandomName(AccountManager__TypeInfo->static_fields->Instance, NULL));
	return outputString;
}

PlainDoor* GetPlainDoorByRoom(SystemTypes__Enum room) {
	for (auto door : il2cpp::Array((*Game::pShipStatus)->fields.AllDoors))
	{
		if (door->fields.Room == room)
		{
			return door;
		}
	}

	return nullptr;
}

il2cpp::Array<PlainDoor__Array> GetAllPlainDoors() {
	return (*Game::pShipStatus)->fields.AllDoors;
}

il2cpp::List<List_1_PlayerControl_> GetAllPlayerControl() {
	return *Game::pAllPlayerControls;
}

il2cpp::List<List_1_GameData_PlayerInfo_> GetAllPlayerData() {
	return (*Game::pGameData)->fields.AllPlayers;
}

il2cpp::Array<DeadBody__Array> GetAllDeadBodies() {
	static std::string deadBodyType = translate_type_name("DeadBody, Assembly-CSharp");

	Type* deadBody_Type = app::Type_GetType(convert_to_string(deadBodyType), NULL);
	return (DeadBody__Array*)app::Object_1_FindObjectsOfType(deadBody_Type, NULL);
}

il2cpp::List<List_1_PlayerTask_> GetPlayerTasks(PlayerControl* player) {
	return player->fields.myTasks;
}

std::vector<NormalPlayerTask*> GetNormalPlayerTasks(PlayerControl* player) {
	static std::string normalPlayerTaskType = translate_type_name("NormalPlayerTask");

	auto playerTasks = GetPlayerTasks(player);
	std::vector<NormalPlayerTask*> normalPlayerTasks;
	normalPlayerTasks.reserve(playerTasks.size());

	for (auto playerTask : playerTasks)
		if (normalPlayerTaskType == playerTask->klass->_0.name || normalPlayerTaskType == playerTask->klass->_0.parent->name)
			normalPlayerTasks.push_back((NormalPlayerTask*)playerTask);

	return normalPlayerTasks;
}

SabotageTask* GetSabotageTask(PlayerControl* player) {
	static std::string sabotageTaskType = translate_type_name("SabotageTask");

	auto playerTasks = GetPlayerTasks(player);

	for (auto playerTask : playerTasks)
		if (sabotageTaskType == playerTask->klass->_0.name || sabotageTaskType == playerTask->klass->_0.parent->name)
			return (SabotageTask*)playerTask;

	return NULL;
}

void RepairSabotage(PlayerControl* player) {
	static std::string electricTaskType = translate_type_name("ElectricTask");
	static std::string hqHudOverrideTaskType = translate_type_name("HqHudOverrideTask");
	static std::string hudOverrideTaskType = translate_type_name("HudOverrideTask");
	static std::string noOxyTaskType = translate_type_name("NoOxyTask");
	static std::string reactorTaskType = translate_type_name("ReactorTask");

	auto sabotageTask = GetSabotageTask(player);
	if (sabotageTask == NULL) return;

	if (electricTaskType == sabotageTask->klass->_0.name) {
		auto electricTask = (ElectricTask*)sabotageTask;

		auto switchSystem = electricTask->fields.system;
		auto actualSwitches = switchSystem->fields.ActualSwitches;
		auto expectedSwitches = switchSystem->fields.ExpectedSwitches;

		if (actualSwitches != expectedSwitches) {
			for (auto i = 0; i < 5; i++) {
				auto switchMask = 1 << (i & 0x1F);

				if ((actualSwitches & switchMask) != (expectedSwitches & switchMask))
					State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Electrical, i));
			}
		}
	}

	if (hqHudOverrideTaskType == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Comms, 16));
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Comms, 17));
	}

	if (hudOverrideTaskType == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Comms, 0));
	}

	if (noOxyTaskType == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::LifeSupp, 64));
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::LifeSupp, 65));
	}

	if (reactorTaskType == sabotageTask->klass->_0.name) {
		if (State.mapType == Settings::MapType::Ship || State.mapType == Settings::MapType::Hq) {
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Reactor, 64));
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Reactor, 65));
		}

		if (State.mapType == Settings::MapType::Pb) {
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Laboratory, 64));
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Laboratory, 65));
		}
		if (State.mapType == Settings::MapType::Airship) {
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Reactor, 16));
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum::Reactor, 17));
		}
	}
}

void CompleteTask(NormalPlayerTask* playerTask) {
	if (playerTask->fields._._Owner_k__BackingField == (*Game::pLocalPlayer)) {
		while (playerTask->fields.taskStep < playerTask->fields.MaxStep)
			app::NormalPlayerTask_NextStep(playerTask, NULL);
	}
}

const char* TranslateTaskTypes(TaskTypes__Enum taskType) {
	static constexpr std::array TASK_TRANSLATIONS = { "Submit Scan", "Prime Shields", "Fuel Engines", "Chart Course", "Start Reactor", "Swipe Card", "Clear Asteroids", "Upload Data",
		"Inspect Sample", "Empty Chute", "Empty Garbage", "Align Engine Output", "Fix Wiring", "Calibrate Distributor", "Divert Power", "Unlock Manifolds", "Stop Reactor Meltdown",
		"Fix Lights", "Clean O2 Filter", "Fix Communications", "Restore Oxygen", "Stabilize Steering", "Assemble Artifact", "Sort Samples", "Measure Weather", "Enter ID Code",
		"Buy Beverage", "Process Data", "Run Diagnostics", "Water Plants", "Monitor Oxygen", "Store Artifacts", "Fill Canisters", "Activate Weather Nodes", "Insert Keys",
		"Reset Seismic Stabilizers", "Scan Boarding Pass", "Open Waterways", "Replace Water Jug", "Repair Drill", "Align Telescope", "Record Temperature", "Reboot Wifi",
		"Polish Ruby", "Reset Breakers", "Decontaminate", "Make Burger", "Unlock Safe", "Sort Records", "Put Away Pistols", "Fix Shower", "Clean Toilet", "Dress Mannequin",
		"Pick Up Towels", "Rewind Tapes", "Start Fans", "Develop Photos", "Get Biggol Sword", "Put Away Rifles", "Stop Charles", "Clean Vent"};
	return TASK_TRANSLATIONS.at(static_cast<size_t>(taskType));
}

const char* TranslateSystemTypes(SystemTypes__Enum systemType) {
	static constexpr std::array SYSTEM_TRANSLATIONS = { "Hallway", "Storage", "Cafeteria", "Reactor", "Upper Engine", "Navigation", "Admin", "Electrical", "Oxygen", "Shields",
		"MedBay", "Security", "Weapons", "Lower Engine", "Communications", "Ship Tasks", "Doors", "Sabotage", "Decontamination", "Launchpad", "Locker Room", "Laboratory",
		"Balcony", "Office", "Greenhouse", "Dropship", "Decontamination", "Outside", "Specimen Room", "Boiler Room", "Vault Room", "Cockpit", "Armory", "Kitchen", "Viewing Deck",
		"Hall Of Portraits", "Cargo Bay", "Ventilation", "Showers", "Engine Room", "The Brig", "Meeting Room", "Records", "Lounge Room", "Gap Room", "Main Hall", "Medical",
		"Decontamination" };
	return SYSTEM_TRANSLATIONS.at(static_cast<size_t>(systemType));
}

Color32 GetPlayerColor(Game::ColorId colorId) {
	il2cpp::Array colorArray = app::Palette__TypeInfo->static_fields->PlayerColors;
	if ((colorId < 0 || colorId > 17) || (size_t)colorId >= colorArray.size()) {
		// oops: game bug
		return app::Palette__TypeInfo->static_fields->VisorColor;
	}
	return colorArray[colorId];
}

std::filesystem::path getModulePath(HMODULE hModule) {
	TCHAR buff[MAX_PATH];
	GetModuleFileName(hModule, buff, MAX_PATH);
	return std::filesystem::path(buff);
}

std::string getGameVersion() {
	if (app::Application_get_version != nullptr)
		return convert_from_string(app::Application_get_version(NULL));
	else
		return "unavailable";
}

SystemTypes__Enum GetSystemTypes(const Vector2& vector) {
	if (*Game::pShipStatus) {
		auto shipStatus = *Game::pShipStatus;
		for (auto room : il2cpp::Array(shipStatus->fields._AllRooms_k__BackingField))
			if (room->fields.roomArea != nullptr && app::Collider2D_OverlapPoint(room->fields.roomArea, vector, NULL)) 
				return room->fields.RoomId;
	}
	return SystemTypes__Enum::Outside;
}

std::optional<EVENT_PLAYER> GetEventPlayer(GameData_PlayerInfo* playerInfo)
{
	if (!playerInfo) return std::nullopt;
	return EVENT_PLAYER(playerInfo);
}

std::optional<EVENT_PLAYER> GetEventPlayerControl(PlayerControl* player)
{
	GameData_PlayerInfo* playerInfo = GetPlayerData(player);

	if (!playerInfo) return std::nullopt;
	return EVENT_PLAYER(playerInfo);
}

std::optional<Vector2> GetTargetPosition(GameData_PlayerInfo* playerInfo)
{
	if (!playerInfo) return std::nullopt;
	auto object = GameData_PlayerInfo_get_Object(playerInfo, nullptr);
	if (!object) {
		// Likely disconnected player.
		if (playerInfo->fields.Disconnected != true)
			LOG_ERROR(ToString(playerInfo) + " _object is null");
		return std::nullopt;
	}
	return PlayerControl_GetTruePosition(object, NULL);
}

il2cpp::Array<Camera__Array> GetAllCameras() {
	int32_t cameraCount = app::Camera_get_allCamerasCount(nullptr);
	il2cpp::Array cameraArray = (Camera__Array*)il2cpp_array_new((Il2CppClass*)app::Camera__TypeInfo, cameraCount);
	int32_t returnedCount = app::Camera_GetAllCameras(cameraArray.get(), nullptr);
	assert(returnedCount == cameraCount);
	return cameraArray;
}

il2cpp::List<List_1_InnerNet_ClientData_> GetAllClients()
{
	return (*Game::pAmongUsClient)->fields._.allClients;
}

Vector2 GetSpawnLocation(Game::PlayerId playerId, int32_t numPlayer, bool initialSpawn)
{
	if (State.mapType == Settings::MapType::Ship || State.mapType != Settings::MapType::Pb || initialSpawn)
	{
		Vector2 vector = { 0, 1 };
		vector = Rotate(vector, (float)(playerId - 1) * (360.f / (float)numPlayer));
		float radius = (*Game::pShipStatus)->fields.SpawnRadius;
		vector = { vector.x * radius, vector.y * radius };
		Vector2 spawncenter = (initialSpawn ? (*Game::pShipStatus)->fields.InitialSpawnCenter : (*Game::pShipStatus)->fields.MeetingSpawnCenter);
		return { spawncenter.x + vector.x, spawncenter.y + vector.y + 0.3636f };
	}
	if (playerId < 5)
	{
		Vector2 spawncenter = (*Game::pShipStatus)->fields.MeetingSpawnCenter;
		return { (spawncenter.x + 1) * (float)playerId, spawncenter.y * (float)playerId };
	}
	Vector2 spawncenter = (*Game::pShipStatus)->fields.MeetingSpawnCenter2;
	return { (spawncenter.x + 1) * (float)(playerId - 5), spawncenter.y * (float)(playerId - 5) };
}

bool IsAirshipSpawnLocation(const Vector2& vec)
{
	return (State.mapType == Settings::MapType::Airship);
}

Vector2 Rotate(const Vector2& vec, float degrees)
{
	float f = 0.017453292f * degrees;
	float num = cos(f);
	float num2 = sin(f);
	return { vec.x * num - num2 * vec.y, vec.x * num2 + num * vec.y };
}

bool Equals(const Vector2& vec1, const Vector2& vec2) {
	return vec1.x == vec2.x && vec1.y == vec2.y;
}

std::string ToString(Object* object) {
	std::string type = convert_from_string(Object_ToString(object, NULL));
	if (type == "System.String") {
		return convert_from_string((String*)object);
	}
	return type;
}

std::string ToString(Game::PlayerId id) {
	if (auto data = GetPlayerDataById(id))
		return ToString(data);
	return std::format("<#{}>", +id);
}

std::string ToString(__maybenull PlayerControl* player) {
	if (player) {
		if (auto data = GetPlayerData(player))
			return ToString(data);
		return std::format("<#{}>", +player->fields.PlayerId);
	}
	return "<Unknown>";
}

std::string ToString(__maybenull GameData_PlayerInfo* data) {
	if (data) {
		if (const auto outfit = GetPlayerOutfit(data))
			return std::format("<#{} {}>", +data->fields.PlayerId, convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr)));
		return std::format("<#{}>", +data->fields.PlayerId);
	}
	return "<Unknown>";
}

#define ADD_QUOTES_HELPER(s) #s
#define ADD_QUOTES(s) ADD_QUOTES_HELPER(s)

std::string GetGitCommit()
{
#ifdef GIT_CUR_COMMIT
	return ADD_QUOTES(GIT_CUR_COMMIT);
#endif
	return "unavailable";
}

std::string GetGitBranch()
{
#ifdef GIT_BRANCH
	return ADD_QUOTES(GIT_BRANCH);
#endif
	return "unavailable";
}

void ImpersonateName(PlayerSelection& _player)
{
	auto player = _player.validate(); if (!player.has_value()) return;
	app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(player.get_PlayerData());
	if (!(IsInGame() || IsInLobby() || outfit)) return;
	const auto& playerName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
	if (!IsHost() && State.SafeMode) {
		if (IsInGame())
			State.rpcQueue.push(new RpcSetName(RemoveHtmlTags(playerName).substr(0,11) + "­"));
		else if (IsInLobby())
			State.lobbyRpcQueue.push(new RpcSetName(RemoveHtmlTags(playerName).substr(0, 11) + "­"));
	}
	else {
		if (IsInGame())
			State.rpcQueue.push(new RpcSetName(playerName));
		else if (IsInLobby())
			State.lobbyRpcQueue.push(new RpcSetName(playerName));
	}
}

Game::ColorId GetRandomColorId()
{
	Game::ColorId colorId;
	il2cpp::Array PlayerColors = app::Palette__TypeInfo->static_fields->PlayerColors;
	assert(PlayerColors.size() > 0);
	if (IsInGame() || IsInLobby())
	{
		auto players = GetAllPlayerControl();
		std::vector<Game::ColorId> availableColors = { };
		for (size_t i = 0; i < PlayerColors.size(); i++)
		{
			bool colorAvailable = true;
			for (PlayerControl* player : players)
			{
				app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(player));
				if (outfit == NULL) continue;
				if (i == outfit->fields.ColorId)
				{
					colorAvailable = false;
					break;
				}
			}

			if (colorAvailable)
				availableColors.push_back((Game::ColorId)i);
		}
		assert(availableColors.size() > 0);
		colorId = availableColors.at(randi(0, (int)availableColors.size() - 1));
	}
	else
	{
		colorId = randi(0, (int)PlayerColors.size() - 1);
	}
	return colorId;
}

void SaveOriginalAppearance()
{
	app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer));
	if (outfit == NULL) return;
	LOG_DEBUG("Set appearance values to current player");
	State.originalName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
	State.originalSkin = outfit->fields.SkinId;
	State.originalHat = outfit->fields.HatId;
	State.originalPet = outfit->fields.PetId;
	State.originalColor = outfit->fields.ColorId;
	State.activeImpersonation = false;
	State.originalVisor = outfit->fields.VisorId; 
	State.originalNamePlate = outfit->fields.NamePlateId;
}

void ResetOriginalAppearance()
{
	LOG_DEBUG("Reset appearance values to invalid");
	State.originalSkin = nullptr;
	State.originalHat = nullptr;
	State.originalPet = nullptr;
	State.originalColor = Game::NoColorId;
	State.originalVisor = nullptr;
	State.originalNamePlate = nullptr;
}

void ControlAppearance(bool randomize)
{

	std::queue<RPCInterface*>* queue = nullptr;
	if (IsInGame())
		queue = &State.rpcQueue;
	else if (IsInLobby())
		queue = &State.lobbyRpcQueue;
	if (randomize) {
		std::vector availableHats = { "hat_NoHat", "hat_bushhat", "hat_captain", "hat_doubletophat", "hat_flowerpot", "hat_military", "hat_MilitaryWinter", "hat_GovtDesert", "hat_police", "hat_Rupert", "hat_partyhat", "hat_tophat", "hat_towelwizard", "hat_russian", "hat_viking", "hat_wallcap", "hat_pk06_Snowman", "hat_pk06_Reindeer", "hat_pk06_Lights", "hat_pk06_Santa", "hat_pk06_tree", "hat_pk06_Present", "hat_pk06_Candycanes", "hat_pk06_ElfHat", "hats_newyears2018", "hat_whitetophat", "hat_pk02_Crown", "hat_pk02_Eyebrows", "hat_pk02_HaloHat", "hat_pk02_PipCap", "hat_pk02_ScubaHat", "hat_pk02_StickminHat", "hat_pk02_StrawHat", "hat_pk02_ThirdEyeHat", "hat_pk02_ToiletPaperHat", "hat_pk02_Toppat", "hat_pk03_Fedora", "hat_pk03_StrapHat", "hat_pk04_Banana", "hat_pk04_Bear", "hat_pk05_Cheese", "hat_pk05_Cherry", "hat_pk05_Egg", "hat_pk05_Fedora", "hat_pk05_Flamingo", "hat_pk05_FlowerPin", "hat_pk05_Helmet", "hat_pk05_Plant", "hat_pkHW01_PlagueHat", "hat_pkHW01_CatEyes", "hat_pkHW01_Horns", "hat_pkHW01_BatWings", "hat_pkHW01_Mohawk", "hat_pkHW01_Pumpkin", "hat_pkHW01_ScaryBag", "hat_pkHW01_Witch", "hat_pkHW01_Wolf", "hat_pkHW01_Pirate", "hat_pkHW01_Machete", "hat_pk04_Archae", "hat_pk04_Balloon", "hat_pk04_BirdNest", "hat_pk04_Chef", "hat_pk04_CCC", "hat_pk04_Fez", "hat_pk04_GeneralHat", "hat_pk04_Pompadour", "hat_pk04_HunterCap", "hat_pk04_JungleHat", "hat_pk04_MiniCrewmate", "hat_pk04_Vagabond", "hat_pk04_Snowman", "hat_pk05_davehat", "hat_pk05_Ellie", "hat_pk05_Svenhat", "hat_pk05_Burthat", "hat_pk05_Ellryhat", "hat_pk05_Wizardhat", "hat_pk05_cheesetoppat", "hat_pk05_Macbethhat", "hat_pk05_HenryToppat", "hat_pk05_EllieToppat", "hat_pk05_GeoffreyToppat", "hat_Chocolate", "hat_Heart", "hat_Ponytail", "hat_Rubberglove", "hat_Unicorn", "hat_Zipper", "hat_CuppaJoe", "hat_HardtopHat", "hat_Prototype", "hat_Records", "hat_ThomasC", "hat_ToppatHair", "hat_WilfordIV", "hat_Winston", "hat_AbominalHat", "hat_EarmuffGreen", "hat_EarmuffsPink", "hat_EarmuffsYellow", "hat_EarnmuffBlue", "hat_pk04_MinerCap", "hat_MinerBlack", "hat_MinerYellow", "hat_RockIce", "hat_RockLava", "hat_SnowbeanieGreen", "hat_SnowbeanieOrange", "hat_SnowBeaniePurple", "hat_SnowbeanieRed", "hat_WinterHelmet", "hat_pk04_WinterHat", "hat_WinterGreen", "hat_WinterRed", "hat_WinterYellow", "hat_Voleyball", "hat_Basketball", "hat_Bowlingball", "hat_Deitied", "hat_Dodgeball", "hat_DrillMetal", "hat_DrillStone", "hat_DrillWood", "hat_Janitor", "hat_Pot", "hat_Soccer", "hat_Visor", "hat_mira_bush", "hat_mira_case", "hat_mira_cloud", "hat_mira_flower", "hat_mira_flower_red", "hat_mira_gem", "hat_pk03_Headphones", "hat_GovtHeadset", "hat_mira_headset_blue", "hat_mira_headset_pink", "hat_mira_headset_yellow", "hat_mira_leaf", "hat_mira_milk", "hat_pk04_Slippery", "hat_mira_sign_blue", "hat_pk03_Security1", "hat_pk04_Antenna", "hat_Antenna_Black", "hat_astronaut", "hat_Astronaut-Blue", "hat_Astronaut-Cyan", "hat_Astronaut-Orange", "hat_pk04_Bandana", "hat_Bandana_Blue", "hat_Bandana_Green", "hat_Bandana_Pink", "hat_Bandana_Red", "hat_Bandana_White", "hat_Bandana_Yellow", "hat_pk01_BaseballCap", "hat_baseball_Black", "hat_baseball_Green", "hat_baseball_Lightblue", "hat_baseball_LightGreen", "hat_baseball_Lilac", "hat_baseball_Orange", "hat_baseball_Pink", "hat_baseball_Purple", "hat_baseball_Red", "hat_baseball_White", "hat_baseball_Yellow", "hat_pk04_Beanie", "hat_Beanie_Black", "hat_Beanie_Blue", "hat_Beanie_Green", "hat_Beanie_Lightblue", "hat_Beanie_LightGreen", "hat_Beanie_LightPurple", "hat_Beanie_Pink", "hat_Beanie_Purple", "hat_Beanie_White", "hat_Beanie_Yellow", "hat_stethescope", "hat_Doc_black", "hat_Doc_Orange", "hat_Doc_Purple", "hat_Doc_Red", "hat_Doc_White", "hat_pk04_DoRag", "hat_Dorag_Black", "hat_Dorag_Desert", "hat_Dorag_Jungle", "hat_Dorag_Purple", "hat_Dorag_Sky", "hat_Dorag_Snow", "hat_Dorag_Yellow", "hat_pk03_Goggles", "hat_goggles", "hat_Goggles_Black", "hat_Goggles_Chrome", "hat_hardhat", "hat_Hardhat_black", "hat_Hardhat_Blue", "hat_Hardhat_Green", "hat_Hardhat_Orange", "hat_Hardhat_Pink", "hat_Hardhat_Purple", "hat_Hardhat_Red", "hat_Hardhat_White", "hat_brainslug", "hat_headslug_Purple", "hat_headslug_Red", "hat_headslug_Yellow", "hat_headslug_White", "hat_pk02_HeroCap", "hat_Herohood_Black", "hat_Herohood_Blue", "hat_Herohood_Pink", "hat_Herohood_Purple", "hat_Herohood_Red", "hat_Herohood_White", "hat_Herohood_Yellow", "hat_paperhat", "hat_Paperhat_Black", "hat_Paperhat_Blue", "hat_Paperhat_Cyan", "hat_Paperhat_Lightblue", "hat_Paperhat_Pink", "hat_Paperhat_Yellow", "hat_pk02_PlungerHat", "hat_Plunger_Blue", "hat_Plunger_Yellow", "hat_pk04_RamHorns", "hat_Ramhorn_Black", "hat_Ramhorn_Red", "hat_Ramhorn_White", "hat_pk02_TenGallonHat", "hat_TenGallon_Black", "hat_TenGallon_White", "hat_pk03_Traffic", "hat_Traffic_Blue", "hat_Traffic_Red", "hat_Traffic_Yellow", "hat_traffic_purple", "hat_devilhorns_yellow", "hat_arrowhead", "hat_axe", "hat_papermask", "hat_bat_crewcolor", "hat_bat_green", "hat_bat_ice", "hat_bone", "hat_candycorn", "hat_cat_grey", "hat_cat_orange", "hat_cat_pink", "hat_cat_snow", "hat_clown_purple", "hat_devilhorns_crewcolor", "hat_devilhorns_green", "hat_devilhorns_murky", "hat_devilhorns_white", "hat_devilhorns_black", "hat_fairywings", "hat_fishhed", "hat_frankenbolts", "hat_frankenbride", "hat_glowstick", "hat_mohawk_bubblegum", "hat_mohawk_bumblebee", "hat_mohawk_purple_green", "hat_mohawk_rainbow", "hat_mummy", "hat_tombstone", "hat_witch_green", "hat_witch_murky", "hat_witch_pink", "hat_witch_white", "hat_wolf_murky", "hat_wolf_grey", "hat_vi", "hat_caitlin", "hat_clagger", "hat_comper", "hat_enforcer", "hat_heim", "hat_jayce", "hat_jinx" };
		std::vector availableSkins = { "skin_None", "skin_Capt", "skin_Police", "skin_Wall", "skin_Security", "skin_Tarmac", "skin_Archae", "skin_CCC", "skin_rhm", "skin_Bling", "skin_General", "skin_Mech", "skin_MechanicRed", "skin_MilitaryDesert", "skin_Military", "skin_prisoner", "skin_PrisonerBlue", "skin_PrisonerTanskin", "skin_SuitB", "skin_SuitW", "skin_Skin_SuitRedskin", "skin_ToppatSuitFem", "skin_ToppatVest", "skin_SweaterYellowskin", "skin_Winter", "skin_JacketGreenskin", "skin_JacketPurpleskin", "skin_JacketYellowskin", "skin_Abominalskin", "skin_MilitarySnowskin", "skin_Miner", "skin_MinerBlackskin", "skin_RockIceskin", "skin_RockLavaskin", "skin_SweaterBlueskin", "skin_SweaterPinkskin", "skin_Sweaterskin", "skin_SportsRedskin", "skin_D2Cskin", "skin_Janitorskin", "skin_SportsBlueskin", "skin_Bushskin", "skin_BusinessFemskin", "skin_BusinessFem-Aquaskin", "skin_BusinessFem-Tanskin", "skin_Hazmat", "skin_Hazmat-Blackskin", "skin_Hazmat-Blueskin", "skin_Hazmat-Greenskin", "skin_Hazmat-Pinkskin", "skin_Hazmat-Redskin", "skin_Hazmat-Whiteskin", "skin_Astro", "skin_Astronaut-Blueskin", "skin_Astronaut-Cyanskin", "skin_Astronaut-Orangeskin", "skin_Science", "skin_Scientist-Blueskin", "skin_Scientist-Darkskin", "skin_clown", "skin_fairy", "skin_fishmonger", "skin_mummy", "skin_pumpkin", "skin_vampire", "skin_witch", "skin_caitlin", "skin_enforcer", "skin_heim", "skin_jayce", "skin_jinx", "skin_vi" };
		std::vector availableVisors = { "visor_EmptyVisor", "visor_pk01_FredVisor", "hat_geoff", "visor_pk01_MonoclesVisor", "visor_pk01_PaperMaskVisor", "visor_pk01_PlagueVisor", "visor_pk01_RHMVisor", "visor_pk01_Security1Visor", "visor_pk01_AngeryVisor", "visor_BillyG", "visor_Galeforce", "visor_Krieghaus", "visor_Reginald", "visor_Scar", "visor_WinstonStache", "visor_SkiGogglesWhite", "visor_Lava", "visor_polus_ice", "visor_SkiGoggleBlack", "visor_SKiGogglesOrange", "visor_shopglasses", "visor_D2CGoggles", "visor_is_beard", "visor_JanitorStache", "visor_Mouth", "visor_mira_card_blue", "visor_mira_card_red", "visor_mira_glasses", "visor_pk01_HazmatVisor", "visor_mira_mask_black", "visor_mira_mask_blue", "visor_mira_mask_green", "visor_mira_mask_purple", "visor_mira_mask_red", "visor_mira_mask_white", "visor_pk01_DumStickerVisor", "visor_Stickynote_Cyan", "visor_Stickynote_Green", "visor_Stickynote_Orange", "visor_Stickynote_Pink", "visor_Stickynote_Purple", "visor_Blush", "visor_Bomba", "visor_Carrot", "visor_Crack", "visor_Dirty", "visor_Dotdot", "visor_EyepatchL", "visor_EyepatchR", "visor_LolliBlue", "visor_LolliBrown", "visor_LolliOrange", "visor_LolliRed", "visor_PiercingL", "visor_PiercingR", "visor_SciGoggles", "visor_SmallGlassesBlue", "visor_SmallGlasses", "visor_SmallGlassesRed", "visor_Straw", "visor_eyeball", "visor_clownnose", "visor_masque_blue", "visor_masque_green", "visor_masque_red", "visor_masque_white", "visor_mummy", "visor_heim", "visor_jinx" };
		std::vector availablePets = { "pet_EmptyPet", "pet_Alien", "pet_Crewmate", "pet_Doggy", "pet_Stickmin", "pet_Hamster", "pet_Robot", "pet_UFO", "pet_Ellie", "pet_Squig", "pet_Bedcrab", "pet_test", "pet_Lava", "pet_Snow", "pet_Charles", "pet_Charles_Red", "pet_Cube", "pet_Bush", "pet_frankendog", "pet_poro" };
		std::vector availableNamePlates = { "nameplate_NoPlate", "nameplate_airship_Toppat", "nameplate_airship_CCC", "nameplate_airship_Diamond", "nameplate_airship_Emerald", "nameplate_airship_Gems", "nameplate_airship_government", "nameplate_Airship_Hull", "nameplate_airship_Ruby", "nameplate_airship_Sky", "nameplate_Polus-Skyline", "nameplate_Polus-Snowmates", "nameplate_Polus_Colors", "nameplate_Polus_DVD", "nameplate_Polus_Ground", "nameplate_Polus_Lava", "nameplate_Polus_Planet", "nameplate_Polus_Snow", "nameplate_Polus_SpecimenBlue", "nameplate_Polus_SpecimenGreen", "nameplate_Polus_SpecimenPurple", "nameplate_is_yard", "nameplate_is_dig", "nameplate_is_game", "nameplate_is_ghost", "nameplate_is_green", "nameplate_is_sand", "nameplate_is_trees", "nameplate_Mira_Cafeteria", "nameplate_Mira_Glass", "nameplate_Mira_Tiles", "nameplate_Mira_Vines", "nameplate_Mira_Wood", "nameplate_hw_candy", "nameplate_hw_woods", "nameplate_hw_pumpkin" };
		std::string name = GenerateRandomString();
		int color = randi(0, 17);
		std::string hat = availableHats[randi(0, availableHats.size() - 1)];
		std::string visor = availableVisors[randi(0, availableVisors.size() - 1)];
		std::string skin = availableSkins[randi(0, availableSkins.size() - 1)];
		std::string pet = availablePets[randi(0, availablePets.size() - 1)];
		std::string nameplate = availableNamePlates[randi(0, availableNamePlates.size() - 1)];
		if (IsInGame() || IsInLobby()) {
			queue->push(new RpcSetName(name));
			queue->push(new RpcSetColor(color));
			queue->push(new RpcSetHat(convert_to_string(hat)));
			queue->push(new RpcSetSkin(convert_to_string(skin)));
			queue->push(new RpcSetVisor(convert_to_string(visor)));
			queue->push(new RpcSetPet(convert_to_string(pet)));
			queue->push(new RpcSetNamePlate(convert_to_string(nameplate)));
		}
	}
	else if (IsInGame() || IsInLobby()) {
		if (IsHost() || !State.SafeMode)
			queue->push(new RpcForceColor(*Game::pLocalPlayer, State.originalColor, true));
		else
			queue->push(new RpcSetColor(State.originalColor));
		queue->push(new RpcSetPet(State.originalPet));
		queue->push(new RpcSetSkin(State.originalSkin));
		queue->push(new RpcSetHat(State.originalHat));
		queue->push(new RpcSetVisor(State.originalVisor));
		queue->push(new RpcSetNamePlate(State.originalNamePlate));
		queue->push(new RpcSetName(State.originalName));
	}
}

GameData_PlayerOutfit* GetPlayerOutfit(GameData_PlayerInfo* player, bool includeShapeshifted /* = false */) {
	if (!player) return nullptr;
	const il2cpp::Dictionary dic(player->fields.Outfits);
	if (includeShapeshifted) {
		auto playerOutfit = dic[PlayerOutfitType__Enum::Shapeshifted];
		if (playerOutfit && !convert_from_string(GameData_PlayerOutfit_get_PlayerName(playerOutfit, nullptr)).empty()) {
			return playerOutfit;
		}
	}
	return dic[PlayerOutfitType__Enum::Default];
}

bool PlayerIsImpostor(GameData_PlayerInfo* player) {

	if (player->fields.Role == nullptr) return false;

	RoleBehaviour* role = player->fields.Role;
	return role->fields.TeamType == RoleTeamTypes__Enum::Impostor;
}


Color GetRoleColor(RoleBehaviour* roleBehaviour) {
	if (roleBehaviour == nullptr) return Palette__TypeInfo->static_fields->White;

	app::Color c;
	switch (roleBehaviour->fields.Role) {
	default:
	case RoleTypes__Enum::CrewmateGhost:
		c = Palette__TypeInfo->static_fields->HalfWhite;
		break;
	case RoleTypes__Enum::Crewmate:
		c = Palette__TypeInfo->static_fields->White;
		break;
	case RoleTypes__Enum::Engineer:
		c = Palette__TypeInfo->static_fields->CrewmateBlue;
		break;
	case RoleTypes__Enum::GuardianAngel:
		c = Palette__TypeInfo->static_fields->Purple;
		break;
	case RoleTypes__Enum::Scientist:
		c = Palette__TypeInfo->static_fields->Blue;
		break;
	case RoleTypes__Enum::Impostor:
		c = Palette__TypeInfo->static_fields->ImpostorRed;
		break;
	case RoleTypes__Enum::Shapeshifter:
		c = Palette__TypeInfo->static_fields->Orange;
		break;
	case RoleTypes__Enum::ImpostorGhost:
		c = Palette__TypeInfo->static_fields->DisabledGrey;
		break;
	}
	return c;
}

std::string GetRoleName(RoleBehaviour* roleBehaviour, bool abbreviated /* = false */)
{
	if (roleBehaviour == nullptr) return (abbreviated ? "Unk" : "Unknown");

	switch (roleBehaviour->fields.Role)
	{
		case RoleTypes__Enum::Engineer:
			return (abbreviated ? "Eng" : "Engineer");
		case RoleTypes__Enum::GuardianAngel:
			return (abbreviated ? "GA" : "Guardian Angel");
		case RoleTypes__Enum::Impostor:
			return (abbreviated ? "Imp" : "Impostor");
		case RoleTypes__Enum::Scientist:
			return (abbreviated ? "Sci" : "Scientist");
		case RoleTypes__Enum::Shapeshifter:
			return (abbreviated ? "SS" : "Shapeshifter");
		case RoleTypes__Enum::Crewmate:
			return (abbreviated ? "Crew" : "Crewmate");
		case RoleTypes__Enum::CrewmateGhost:
			return (abbreviated ? "CG" : "Crewmate Ghost");
		case RoleTypes__Enum::ImpostorGhost:
			return (abbreviated ? "IG" : "Impostor Ghost");
		default:
			return (abbreviated ? "Unk" : "Unknown");
	}
}

RoleTypes__Enum GetRoleTypesEnum(RoleType role)
{
	if (role == RoleType::Shapeshifter) {
		return RoleTypes__Enum::Shapeshifter;
	}
	else if (role == RoleType::Impostor) {
		return RoleTypes__Enum::Impostor;
	}
	else if (role == RoleType::Engineer) {
		return RoleTypes__Enum::Engineer;
	}
	else if (role == RoleType::Scientist) {
		return RoleTypes__Enum::Scientist;
	}
	return RoleTypes__Enum::Crewmate;
}

float GetDistanceBetweenPoints_Unity(const Vector2& p1, const Vector2& p2)
{
	float dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrtf(dx * dx + dy * dy);
}

float GetDistanceBetweenPoints_ImGui(const ImVec2& p1, const ImVec2& p2)
{
	float dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrtf(dx * dx + dy * dy);
}

void DoPolylineSimplification(std::vector<ImVec2>& inPoints, std::vector<std::chrono::system_clock::time_point>& inTimeStamps, std::vector<ImVec2>& outPoints, std::vector<std::chrono::system_clock::time_point>& outTimeStamps, float sqDistanceThreshold, bool clearInputs)
{
	sqDistanceThreshold = sqDistanceThreshold - FLT_EPSILON;
	size_t numPendingPoints = inPoints.size();
	if (numPendingPoints < 2)
		return;

	Profiler::BeginSample("PolylineSimplification");
	ImVec2 prevPoint = inPoints[0], point = inPoints[0];
	std::chrono::system_clock::time_point timestamp = inTimeStamps[0];
	size_t numNewPointsAdded = 0;

	// always add the first point
	outPoints.push_back(point);
	outTimeStamps.push_back(timestamp);
	numNewPointsAdded++;
	for (size_t index = 1; index < numPendingPoints; index++)
	{
		point = inPoints[index];
		timestamp = inTimeStamps[index];
		float diffX = point.x - prevPoint.x, diffY = point.y - prevPoint.y;
		if ((diffX * diffX + diffY * diffY) >= sqDistanceThreshold)
		{
			prevPoint = point;
			// add the point if it's beyond the distance threshold of prev point.
			outPoints.push_back(point);
			outTimeStamps.push_back(timestamp);
			numNewPointsAdded++;
		}
	}
	// add the last point if it's not also the first point nor has already been added as the last point
	if ((point.x != prevPoint.x) || (point.y != prevPoint.y))
	{
		outPoints.push_back(point);
		outTimeStamps.push_back(timestamp);
		numNewPointsAdded++;
	}

	if (clearInputs)
	{
		inPoints.clear();
		inTimeStamps.clear();
	}
	Profiler::EndSample("PolylineSimplification");
}

float getMapXOffsetSkeld(float x)
{
	GameOptions options;
	return (options.GetByte(app::ByteOptionNames__Enum::MapId) == 3) ? (-1) * x : x;
}

bool Object_1_IsNotNull(app::Object_1* obj)
{
	return app::Object_1_op_Implicit(obj, nullptr);
}

bool Object_1_IsNull(app::Object_1* obj)
{
	return !Object_1_IsNotNull(obj);
}

std::string GetPlayerName() {
	auto player = app::DataManager_get_Player(nullptr);
	static FieldInfo* field = il2cpp_class_get_field_from_name(player->Il2CppClass.klass, "customization");
	LOG_ASSERT(field != nullptr);
	auto customization = il2cpp_field_get_value_object(field, player);
	LOG_ASSERT(customization != nullptr);
	return convert_from_string(app::PlayerCustomizationData_get_Name(customization, nullptr));
}

void SetPlayerName(std::string_view name) {
	auto player = app::DataManager_get_Player(nullptr);
	static FieldInfo* field = il2cpp_class_get_field_from_name(player->Il2CppClass.klass, "customization");
	LOG_ASSERT(field != nullptr);
	auto customization = il2cpp_field_get_value_object(field, player);
	LOG_ASSERT(customization != nullptr);
	app::PlayerCustomizationData_set_Name(customization, convert_to_string(name), nullptr);
}

//TODO: Workaround
#define GET_VIRTUAL_INVOKE(obj, method) \
	((VirtualInvokeData*)(&obj->klass->vtable))[ \
		(obj->klass->interfaceOffsets ? obj->klass->interfaceOffsets[0].offset : 0) \
		+ offsetof(decltype(obj->klass->vtable), method) \
		/ sizeof(VirtualInvokeData)]

GameLogicOptions::GameLogicOptions() {
	auto mgr = app::GameManager_get_Instance(nullptr);
	if (mgr == nullptr)
		return;
	auto logic = app::GameManager_get_LogicOptions(mgr, nullptr);
	LOG_ASSERT(logic != nullptr);
	auto& func = GET_VIRTUAL_INVOKE(logic, __unknown_4);
	_options = ((app::IGameOptions * (*)(void*, const void*))(func.methodPtr))(logic, func.method);
	LOG_ASSERT(_options != nullptr);
}

GameOptions::GameOptions() : _options(nullptr) {
	auto mgr = app::GameOptionsManager_get_Instance(nullptr);
	if (mgr == nullptr) // see issue 477.
		return;
	if (app::GameOptionsManager_get_HasOptions(mgr, nullptr)) {
		_options = app::GameOptionsManager_get_CurrentGameOptions(mgr, nullptr);
		LOG_ASSERT(_options != nullptr);
	}
}

GameOptions& GameOptions::SetByte(app::ByteOptionNames__Enum option, uint8_t value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetByte);
	((void(*)(void*, app::ByteOptionNames__Enum, uint8_t, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

GameOptions& GameOptions::SetFloat(app::FloatOptionNames__Enum option, float value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetFloat);
	((void(*)(void*, app::FloatOptionNames__Enum, float, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

GameOptions& GameOptions::SetBool(app::BoolOptionNames__Enum option, bool value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetBool);
	((void(*)(void*, app::BoolOptionNames__Enum, bool, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

GameOptions& GameOptions::SetInt(app::Int32OptionNames__Enum option, int32_t value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetInt);
	((void(*)(void*, app::Int32OptionNames__Enum, int32_t, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

GameOptions& GameOptions::SetUInt(app::UInt32OptionNames__Enum option, uint32_t value) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetUInt);
	((void(*)(void*, app::UInt32OptionNames__Enum, uint32_t, const void*))(func.methodPtr))
		(_options, option, value, func.method);
	return *this;
}

uint8_t GameOptions::GetByte(app::ByteOptionNames__Enum option, uint8_t defaultValue) const {
	if (!_options) return defaultValue;
	auto& func = GET_VIRTUAL_INVOKE(_options, TryGetByte);
	uint8_t value;
	bool succ = ((bool(*)(void*, app::ByteOptionNames__Enum, uint8_t*, const void*))(func.methodPtr))
		(_options, option, &value, func.method);
	if (!succ)
		value = defaultValue;
	return value;
}

float GameOptions::GetFloat(app::FloatOptionNames__Enum option, float defaultValue) const {
	if (!_options) return defaultValue;
	auto& func = GET_VIRTUAL_INVOKE(_options, TryGetFloat);
	float value;
	bool succ = ((bool(*)(void*, app::FloatOptionNames__Enum, float*, const void*))(func.methodPtr))
		(_options, option, &value, func.method);
	if (!succ)
		value = defaultValue;
	return value;
}

bool GameOptions::GetBool(app::BoolOptionNames__Enum option, bool defaultValue) const {
	if (!_options) return defaultValue;
	auto& func = GET_VIRTUAL_INVOKE(_options, TryGetBool);
	bool value;
	bool succ = ((bool(*)(void*, app::BoolOptionNames__Enum, bool*, const void*))(func.methodPtr))
		(_options, option, &value, func.method);
	if (!succ)
		value = defaultValue;
	return value;
}

int32_t GameOptions::GetInt(app::Int32OptionNames__Enum option, int32_t defaultValue) const {
	if (!_options) return defaultValue;
	auto& func = GET_VIRTUAL_INVOKE(_options, TryGetInt);
	int32_t value;
	bool succ = ((bool(*)(void*, app::Int32OptionNames__Enum, int32_t*, const void*))(func.methodPtr))
		(_options, option, &value, func.method);
	if (!succ)
		value = defaultValue;
	return value;
}

app::GameModes__Enum GameOptions::GetGameMode() const {
	if (!_options) return app::GameModes__Enum::None;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_GameMode);
	return ((app::GameModes__Enum(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

int32_t GameOptions::GetMaxPlayers() const {
	if (!_options) return 0;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_MaxPlayers);
	return ((int32_t(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

uint8_t GameOptions::GetMapId() const {
	if (!_options) return 0;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_MapId);
	return ((uint8_t(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

int32_t GameOptions::GetNumImpostors() const {
	if (!_options) return 0;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_NumImpostors);
	return ((int32_t(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

int32_t GameOptions::GetTotalTaskCount() const {
	if (!_options) return 0;
	auto& func = GET_VIRTUAL_INVOKE(_options, get_TotalTaskCount);
	return ((int32_t(*)(void*, const void*))(func.methodPtr))(_options, func.method);
}

RoleOptions GameOptions::GetRoleOptions() const {
	auto& func = GET_VIRTUAL_INVOKE(_options, get_RoleOptions);
	return RoleOptions(((app::IRoleOptionsCollection*(*)(void*, const void*))(func.methodPtr))(_options, func.method));
}

float GameOptions::GetPlayerSpeedMod() const {
	return GetFloat(app::FloatOptionNames__Enum::PlayerSpeedMod, 1.0F);
}

float GameOptions::GetKillCooldown() const {
	return GetFloat(app::FloatOptionNames__Enum::KillCooldown, 1.0F);
}

float GameOptions::GetGACooldown() const {
	return GetFloat(app::FloatOptionNames__Enum::GuardianAngelCooldown, 1.0F);
}

RoleOptions& RoleOptions::SetRoleRate(app::RoleTypes__Enum role, int32_t maxCount, int32_t chance) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetRoleRate);
	((void(*)(void*, app::RoleTypes__Enum, int32_t, int32_t, const void*))(func.methodPtr))
		(_options, role, maxCount, chance, func.method);
	return *this;
}

RoleOptions& RoleOptions::SetRoleRecommended(app::RoleTypes__Enum role) {
	auto& func = GET_VIRTUAL_INVOKE(_options, SetRoleRecommended);
	((void(*)(void*, app::RoleTypes__Enum, const void*))(func.methodPtr))(_options, role, func.method);
	return *this;
}

int32_t RoleOptions::GetNumPerGame(app::RoleTypes__Enum role) const {
	auto& func = GET_VIRTUAL_INVOKE(_options, GetNumPerGame);
	return ((int32_t(*)(void*, app::RoleTypes__Enum, const void*))(func.methodPtr))(_options, role, func.method);
}

int32_t RoleOptions::GetChancePerGame(app::RoleTypes__Enum role) const {
	auto& func = GET_VIRTUAL_INVOKE(_options, GetChancePerGame);
	return ((int32_t(*)(void*, app::RoleTypes__Enum, const void*))(func.methodPtr))(_options, role, func.method);
}

void SaveGameOptions() {
	SaveGameOptions(GameOptions());
}

void SaveGameOptions(const class GameOptions& gameOptions) {
	State.PlayerSpeed = State.PrevPlayerSpeed = gameOptions.GetPlayerSpeedMod();
	State.KillCooldown = State.PrevKillCooldown = gameOptions.GetKillCooldown();
	State.GACooldown = State.PrevGACooldown = gameOptions.GetGACooldown();
	State.KillDistance = State.PrevKillDistance = gameOptions.GetInt(app::Int32OptionNames__Enum::KillDistance);
	State.TaskBarUpdates = State.PrevTaskBarUpdates = gameOptions.GetInt(app::Int32OptionNames__Enum::TaskBarMode);
	State.VisualTasks = State.PrevVisualTasks = gameOptions.GetBool(app::BoolOptionNames__Enum::VisualTasks);
	State.mapHostChoice = gameOptions.GetMapId();
	State.impostors_amount = gameOptions.GetNumImpostors();
}
