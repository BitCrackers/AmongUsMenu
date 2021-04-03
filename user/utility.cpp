#include "pch-il2cpp.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

int randi(int lo, int hi) {
	int n = hi - lo + 1;
	int i = rand() % n;
	if (i < 0) i = -i;
	return lo + i;
}

PlayerSelection::PlayerSelection()
{
	this->hasValue = false;
	this->clientId = 0;
	this->playerId = 0;
}

PlayerSelection::PlayerSelection(PlayerControl* playerControl)
{
	if (playerControl != NULL) {
		this->hasValue = true;
		this->clientId = playerControl->fields._.OwnerId;
		this->playerId = playerControl->fields.PlayerId;
	} else {
		*this = PlayerSelection();
	}
}

PlayerSelection::PlayerSelection(GameData_PlayerInfo* playerData)
{
	if (playerData != NULL) {
		*this = PlayerSelection(playerData->fields._object);
	} else {
		*this = PlayerSelection();
	}
}

bool PlayerSelection::equals(PlayerControl* playerControl)
{
	if (!this->has_value()) return false;
	return this->get_PlayerControl() == playerControl;
}

Vector2 GetTrueAdjustedPosition(PlayerControl* playerControl)
{
	Vector2 playerVector2 = PlayerControl_GetTruePosition(playerControl, NULL);
	playerVector2.y += 0.36f;
	return playerVector2;
}

bool PlayerSelection::equals(GameData_PlayerInfo* playerData)
{
	if (!this->has_value()) return false;
	return this->get_PlayerData() == playerData;
}

bool PlayerSelection::equals(PlayerSelection selectedPlayer)
{
	if (!this->has_value() || !selectedPlayer.has_value()) return false;
	return (this->get_PlayerId() == selectedPlayer.get_PlayerId() && this->get_PlayerId() == selectedPlayer.get_PlayerId());
}

PlayerControl* PlayerSelection::get_PlayerControl()
{
	if (!this->hasValue) return NULL;

	if (clientId == -2) {
		auto playerControl = GetPlayerControlById(this->playerId);
		if (playerControl != NULL)
			return playerControl;
	}

	for (auto client : GetAllClients()) {
		if (client->fields.Id == this->clientId) {
			return client->fields.Character;
		}
	}

	*this = PlayerSelection();
	return NULL;
}

GameData_PlayerInfo* PlayerSelection::get_PlayerData()
{
	if (!this->hasValue) return NULL;

	auto playerControl = this->get_PlayerControl();
	if (playerControl != NULL)
		return playerControl->fields._cachedData;

	*this = PlayerSelection();
	return NULL;
}

bool PlayerSelection::has_value()
{
	if (!this->hasValue)
		return false;

	if (this->get_PlayerControl() == NULL)
		return false;

	return true;
}

uint8_t PlayerSelection::get_PlayerId()
{
	if (!this->has_value()) return 0;
	return this->playerId;
}

int32_t PlayerSelection::get_ClientId()
{
	if (!this->has_value()) return 0;
	return this->clientId;
}

bool PlayerSelection::is_LocalPlayer()
{
	if (!this->has_value()) return false;
	return this->get_PlayerControl() == *Game::pLocalPlayer;
}

bool PlayerSelection::is_Disconnected()
{
	// This is a sanity check, I don't think this is necessary as when a player.
	// When a player disconnects their PlayerControl is destroyed and as such has_value() should return false
	if (!this->has_value()) return true;
	return this->get_PlayerData()->fields.Disconnected;
}

ImVec4 AmongUsColorToImVec4(Color color) {
	return ImVec4(color.r, color.g, color.b, color.a);
}

ImVec4 AmongUsColorToImVec4(CorrectedColor32 color) {
	return ImVec4(color.r / 255.0F, color.g / 255.0F, color.b / 255.0F, color.a / 255.0F);
}

#define LocalInGame (((*Game::pAmongUsClient)->fields._.GameMode == GameMode__Enum_LocalGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum_Started))
#define OnlineInGame (((*Game::pAmongUsClient)->fields._.GameMode == GameMode__Enum_OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum_Started))
#define OnlineInLobby (((*Game::pAmongUsClient)->fields._.GameMode == GameMode__Enum_OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum_Joined))
#define TutorialScene (State.CurrentScene.compare("Tutorial") == 0)

bool IsInLobby() {
	return OnlineInLobby && (*Game::pLocalPlayer);
}

bool IsHost() {
	return app::InnerNetClient_get_AmHost((InnerNetClient*)(*Game::pAmongUsClient), NULL);
}

bool IsInGame() {
	return (LocalInGame || OnlineInGame || TutorialScene) && (*Game::pShipStatus) && (*Game::pLocalPlayer);
}

bool IsInMultiplayerGame() {
	return (LocalInGame || OnlineInGame) && (*Game::pShipStatus) && (*Game::pLocalPlayer);
}

GameData_PlayerInfo* GetPlayerData(PlayerControl* player) {
	if (player) return app::PlayerControl_get_Data(player, NULL);
	return NULL;
}

GameData_PlayerInfo* GetPlayerDataById(uint8_t id) {
	return app::GameData_GetPlayerById((*Game::pGameData), id, NULL);
}

PlayerControl* GetPlayerControlById(uint8_t id) {
	for (auto player : GetAllPlayerControl()) {
		if (player->fields.PlayerId == id) return player;
	}

	return NULL;
}

PlainDoor* GetPlainDoorByRoom(SystemTypes__Enum room) {
	static std::string deadBodyType = translate_type_name("PlainDoor, Assembly-CSharp");

	std::vector<PlainDoor*> doors = std::vector<PlainDoor*>();

	Type* deadBody_Type = app::Type_GetType(convert_to_string(deadBodyType), NULL);
	PlainDoor__Array* deadBodyArray = (*Game::pShipStatus)->fields.AllDoors;

	for (il2cpp_array_size_t i = 0; i < deadBodyArray->max_length; i++)
		doors.push_back(deadBodyArray->vector[i]);

	for (PlainDoor* door : doors)
	{
		if (door->fields.Room == room)
		{
			return door;
		}
	}

	return nullptr;
}

std::vector<PlainDoor*> GetAllPlainDoors() {
	static std::string deadBodyType = translate_type_name("PlainDoor, Assembly-CSharp");

	std::vector<PlainDoor*> doors = std::vector<PlainDoor*>();

	Type* deadBody_Type = app::Type_GetType(convert_to_string(deadBodyType), NULL);
	PlainDoor__Array* deadBodyArray = (*Game::pShipStatus)->fields.AllDoors;

	for (il2cpp_array_size_t i = 0; i < deadBodyArray->max_length; i++)
		doors.push_back(deadBodyArray->vector[i]);

	return doors;
}

std::vector<PlayerControl*> GetAllPlayerControl() {
	static PlayerControl* (*getItem)(List_1_PlayerControl_*, int32_t, MethodInfo*);
	static int32_t(*getCount)(List_1_PlayerControl_*, MethodInfo*);
	if (getItem == NULL) getItem = decltype(getItem)(find_method((Il2CppClass*)(*Game::pAllPlayerControls)->klass, "PlayerControl", "get_Item", "System.Int32"));
	if (getCount == NULL) getCount = decltype(getCount)(find_method((Il2CppClass*)(*Game::pAllPlayerControls)->klass, "System.Int32", "get_Count", ""));

	std::vector<PlayerControl*> players = std::vector<PlayerControl*>();

	if (getItem != NULL && getCount != NULL) {
		for (int i = 0; i < getCount((*Game::pAllPlayerControls), NULL); i++)
			players.push_back(getItem((*Game::pAllPlayerControls), i, NULL));
	}

	return players;
}

std::vector<GameData_PlayerInfo*> GetAllPlayerData() {
	static GameData_PlayerInfo* (*getItem)(List_1_GameData_PlayerInfo_*, int32_t, MethodInfo*);
	static int32_t(*getCount)(List_1_GameData_PlayerInfo_*, MethodInfo*);
	if (getItem == NULL) getItem = decltype(getItem)(find_method((Il2CppClass*)(Il2CppClass*)(*Game::pGameData)->fields.AllPlayers->klass, "GameData.PlayerInfo", "get_Item", "System.Int32"));
	if (getCount == NULL) getCount = decltype(getCount)(find_method((Il2CppClass*)(Il2CppClass*)(*Game::pGameData)->fields.AllPlayers->klass, "System.Int32", "get_Count", ""));

	std::vector<GameData_PlayerInfo*> players = std::vector<GameData_PlayerInfo*>();

	if (getItem != NULL && getCount != NULL) {
		for (int i = 0; i < getCount((*Game::pGameData)->fields.AllPlayers, NULL); i++)
			players.push_back(getItem((*Game::pGameData)->fields.AllPlayers, i, NULL));
	}

	return players;
}

std::vector<DeadBody*> GetAllDeadBodies() {
	static std::string deadBodyType = translate_type_name("DeadBody, Assembly-CSharp");

	std::vector<DeadBody*> deadBodies = std::vector<DeadBody*>();

	Type* deadBody_Type = app::Type_GetType(convert_to_string(deadBodyType), NULL);
	DeadBody__Array* deadBodyArray = (DeadBody__Array*)app::Object_1_FindObjectsOfType(deadBody_Type, NULL);

	for (il2cpp_array_size_t i = 0; i < deadBodyArray->max_length; i++)
		deadBodies.push_back(deadBodyArray->vector[i]);

	return deadBodies;
}

std::vector<PlayerTask*> GetPlayerTasks(PlayerControl* player) {
	static PlayerTask* (*getItem)(List_1_PlayerTask_*, int32_t, MethodInfo*) = decltype(getItem)(find_method((Il2CppClass*)(Il2CppClass*)player->fields.myTasks->klass, "PlayerTask", "get_Item", "System.Int32"));
	static int32_t(*getCount)(List_1_PlayerTask_*, MethodInfo*) = decltype(getCount)(find_method((Il2CppClass*)(Il2CppClass*)player->fields.myTasks->klass, "System.Int32", "get_Count", ""));

	std::vector<PlayerTask*> playerTasks = std::vector<PlayerTask*>();

	if (getItem != NULL && getCount != NULL)
		for (int i = 0; i < getCount(player->fields.myTasks, NULL); i++)
			playerTasks.push_back(getItem(player->fields.myTasks, i, NULL));

	return playerTasks;
}

std::vector<NormalPlayerTask*> GetNormalPlayerTasks(PlayerControl* player) {
	static std::string normalPlayerTaskType = translate_type_name("NormalPlayerTask");

	std::vector<PlayerTask*> playerTasks = GetPlayerTasks(player);
	std::vector<NormalPlayerTask*> normalPlayerTasks = std::vector<NormalPlayerTask*>();

	for (auto playerTask : playerTasks)
		if (normalPlayerTaskType == playerTask->klass->_0.name || normalPlayerTaskType == playerTask->klass->_0.parent->name)
			normalPlayerTasks.push_back((NormalPlayerTask*)playerTask);

	return normalPlayerTasks;
}

SabotageTask* GetSabotageTask(PlayerControl* player) {
	static std::string sabotageTaskType = translate_type_name("SabotageTask");

	std::vector<PlayerTask*> playerTasks = GetPlayerTasks(player);

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
					State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Electrical, i));
			}
		}
	}

	if (hqHudOverrideTaskType == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Comms, 16));
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Comms, 17));
	}

	if (hudOverrideTaskType == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Comms, 0));
	}

	if (noOxyTaskType == sabotageTask->klass->_0.name) {
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_LifeSupp, 64));
		State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_LifeSupp, 65));
	}

	if (reactorTaskType == sabotageTask->klass->_0.name) {
		if (State.mapType == Settings::MapType::Ship || State.mapType == Settings::MapType::Hq) {
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Reactor, 64));
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Reactor, 65));
		}

		if (State.mapType == Settings::MapType::Pb) {
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Laboratory, 64));
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Laboratory, 65));
		}
		if (State.mapType == Settings::MapType::Airship) {
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Reactor, 16));
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Reactor, 17));
		}
	}
}

void CompleteTask(NormalPlayerTask* playerTask) {
	if (playerTask->fields._._Owner_k__BackingField == (*Game::pLocalPlayer)) {
		while (playerTask->fields.taskStep < playerTask->fields.MaxStep)
			app::NormalPlayerTask_NextStep(playerTask, NULL);
	}
}

#pragma warning(suppress:26812)
const char* TranslateTaskTypes(TaskTypes__Enum taskType) {
	static const char* const TASK_TRANSLATIONS[] = { "Submit Scan", "Prime Shields", "Fuel Engines", "Chart Course", "Start Reactor", "Swipe Card", "Clear Asteroids", "Upload Data",
		"Inspect Sample", "Empty Chute", "Empty Garbage", "Align Engine Output", "Fix Wiring", "Calibrate Distributor", "Divert Power", "Unlock Manifolds", "Reset Reactor",
		"Fix Lights", "Clean O2 Filter", "Fix Communications", "Restore Oxygen", "Stabilize Steering", "Assemble Artifact", "Sort Samples", "Measure Weather", "Enter ID Code",
		"Buy Beverage", "Process Data", "Run Diagnostics", "Water Plants", "Monitor Oxygen", "Store Artifacts", "Fill Canisters", "Activate Weather Nodes", "Insert Keys",
		"Reset Seismic Stabilizers", "Scan Boarding Pass", "Open Waterways", "Replace Water Jug", "Repair Drill", "Align Telecopse", "Record Temperature", "Reboot Wifi", 
		"Polish Ruby", "Reset Breakers", "Decontaminate", "Make Burger", "Unlock Safe", "Sort Records", "Put Away Pistols", "Fix Shower", "Clean Toilet", "Dress Mannequin",
		"Pick Up Towels", "Rewind Tapes", "Start Fans", "Develop Photos", "Get Biggol Sword", "Put Away Rifles", "Stop Charles" };
	return TASK_TRANSLATIONS[taskType];
}

#pragma warning(suppress:26812)
const char* TranslateSystemTypes(SystemTypes__Enum systemType) {
	static const char* const SYSTEM_TRANSLATIONS[] = { "Hallway", "Storage", "Cafeteria", "Reactor", "Upper Engine", "Navigation", "Admin", "Electrical", "Oxygen", "Shields",
		"MedBay", "Security", "Weapons", "Lower Engine", "Communications", "Ship Tasks", "Doors", "Sabotage", "Decontamination", "Launchpad", "Locker Room", "Laboratory",
		"Balcony", "Office", "Greenhouse", "Dropship", "Decontamination", "Outside", "Specimen Room", "Boiler Room", "Vault Room", "Cockpit", "Armory", "Kitchen", "Viewing Deck", 
		"Hall Of Portraits", "Cargo Bay", "Ventilation", "Showers", "Engine Room", "The Brig", "Meeting Room", "Records Room", "Lounge Room", "Gap Room", "Main Hall", "Medical" };
	return SYSTEM_TRANSLATIONS[systemType];
}

CorrectedColor32 GetPlayerColor(uint8_t colorId) {
	CorrectedColor32* colorArray = (CorrectedColor32*)app::Palette__TypeInfo->static_fields->PlayerColors->vector;
	return colorArray[colorId];
}

std::filesystem::path getModulePath(HMODULE hModule) {
	TCHAR buff[MAX_PATH];
	GetModuleFileName(hModule, buff, MAX_PATH);
	return std::filesystem::path(buff);
}

std::string getGameVersion() {
	return convert_from_string(app::Application_get_version(NULL));
}

SystemTypes__Enum GetSystemTypes(Vector2 vector) {
	if (*Game::pShipStatus) {
		auto shipStatus = *Game::pShipStatus;
		auto allRooms = shipStatus->fields._AllRooms_k__BackingField;

		for (size_t i = 0; i < allRooms->max_length; i++)
			if (allRooms->vector[i]->fields.roomArea != nullptr && app::Collider2D_OverlapPoint(allRooms->vector[i]->fields.roomArea, vector, NULL)) return allRooms->vector[i]->fields.RoomId;
	}
	return SystemTypes__Enum_Outside;
}

std::optional<EVENT_PLAYER> GetEventPlayer(GameData_PlayerInfo* playerInfo)
{
	if (!playerInfo) return std::nullopt;
	return EVENT_PLAYER(playerInfo);
}

EVENT_PLAYER GetEventPlayer(PlayerControl* player)
{
	return *GetEventPlayer(player->fields._cachedData);
}

std::vector<Camera*> GetAllCameras() {
	auto cameras = std::vector<Camera*>();

	int32_t cameraCount = app::Camera_get_allCamerasCount(NULL);
	Camera__Array* cameraArray = (Camera__Array*)il2cpp_array_new((Il2CppClass*)app::Camera__TypeInfo, cameraCount);
	int32_t returnedCount = app::Camera_GetAllCameras(cameraArray, NULL);

	for (int32_t i = 0; i < returnedCount; i++)
		cameras.push_back(cameraArray->vector[i]);

	return cameras;
}

std::vector<ClientData*> GetAllClients()
{
	static ClientData* (*getItem)(List_1_InnerNet_ClientData_*, int32_t, MethodInfo*) = decltype(getItem)(find_method((Il2CppClass*)(*Game::pAmongUsClient)->fields._.allClients->klass, "InnerNet.ClientData", "get_Item", "System.Int32"));
	static int32_t(*getCount)(List_1_InnerNet_ClientData_*, MethodInfo*) = decltype(getCount)(find_method((Il2CppClass*)(*Game::pAmongUsClient)->fields._.allClients->klass, "System.Int32", "get_Count", ""));

	std::vector<ClientData*> clients = std::vector<ClientData*>();
	auto allClients = (*Game::pAmongUsClient)->fields._.allClients;

	if (getItem != NULL && getCount != NULL)
		for (int i = 0; i < getCount(allClients, NULL); i++)
			clients.push_back(getItem(allClients, i, NULL));

	return clients;
}

Vector2 GetSpawnLocation(int32_t playerId, int32_t numPlayer, bool initialSpawn)
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

bool IsAirshipSpawnLocation(Vector2 vec)
{
	return (State.mapType == Settings::MapType::Airship);

	// unreachable code
	if (Equals(vec, { -25.f, 40.f })) return true;
	if (Equals(vec, { -0.66f, -0.5f })) return true;
	if (!State.spawnInGame.has_value()) return false;

	SpawnInMinigame* game = State.spawnInGame.value();
	for (auto location : game->fields.Locations->vector)
		if (Equals(vec, { location.Location.x, location.Location.y })) return true;

	return false;
}

Vector2 Rotate(Vector2 vec, float degrees)
{
	float f = 0.017453292f * degrees;
	float num = cos(f);
	float num2 = sin(f);
	return { vec.x * num - num2 * vec.y, vec.x * num2 + num * vec.y };
}

bool Equals(Vector2 vec1, Vector2 vec2) {
	return vec1.x == vec2.x && vec1.y == vec2.y;
}