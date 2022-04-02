#include "pch-il2cpp.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"
#include "gitparams.h"
#include "logger.h"
#include "profiler.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

int randi(int lo, int hi) {
	int n = hi - lo + 1;
	int i = rand() % n;
	if (i < 0) i = -i;
	return lo + i;
}

RoleRates::RoleRates(GameOptionsData__Fields gameOptionsDataFields) {
	this->ImposterCount = gameOptionsDataFields._.numImpostors;
	auto roleRates = gameOptionsDataFields.RoleOptions->fields.roleRates;
	if (roleRates->fields.count != 0) {
		auto vectors = roleRates->fields.entries[0].vector;
		for (auto iVector = 0; iVector < 32; iVector++)
		{
			if (vectors[iVector].key == RoleTypes__Enum::Engineer)
			{
				this->EngineerChance = vectors[iVector].value.Chance;
				this->EngineerCount = vectors[iVector].value.MaxCount;
			}
			else if (vectors[iVector].key == RoleTypes__Enum::Scientist)
			{
				this->ScientistChance = vectors[iVector].value.Chance;
				this->ScientistCount = vectors[iVector].value.MaxCount;
			}
			else if (vectors[iVector].key == RoleTypes__Enum::Shapeshifter)
			{
				this->ShapeshifterChance = vectors[iVector].value.Chance;
				this->ShapeshifterCount = vectors[iVector].value.MaxCount;
			}
		}
	}
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

#define LocalInGame (((*Game::pAmongUsClient)->fields._.GameMode == GameModes__Enum::LocalGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Started))
#define OnlineInGame (((*Game::pAmongUsClient)->fields._.GameMode == GameModes__Enum::OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Started))
#define OnlineInLobby (((*Game::pAmongUsClient)->fields._.GameMode == GameModes__Enum::OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum::Joined))
#define TutorialScene (State.CurrentScene.compare("Tutorial") == 0)

bool IsInLobby() {
	if ((*Game::pAmongUsClient) == nullptr) return false;
	return OnlineInLobby && (*Game::pLocalPlayer);
}

bool IsHost() {
	if ((*Game::pAmongUsClient) == nullptr) return false;
	return app::InnerNetClient_get_AmHost((InnerNetClient*)(*Game::pAmongUsClient), NULL);
}

bool IsInGame() {
	if ((*Game::pAmongUsClient) == nullptr) return false;
	return (LocalInGame || OnlineInGame || TutorialScene) && (*Game::pShipStatus) && (*Game::pLocalPlayer);
}

bool IsInMultiplayerGame() {
	if ((*Game::pAmongUsClient) == nullptr) return false;
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

#pragma warning(suppress:26812)
const char* TranslateTaskTypes(TaskTypes__Enum taskType) {
	static const char* const TASK_TRANSLATIONS[] = { "Submit Scan", "Prime Shields", "Fuel Engines", "Chart Course", "Start Reactor", "Swipe Card", "Clear Asteroids", "Upload Data",
		"Inspect Sample", "Empty Chute", "Empty Garbage", "Align Engine Output", "Fix Wiring", "Calibrate Distributor", "Divert Power", "Unlock Manifolds", "Reset Reactor",
		"Fix Lights", "Clean O2 Filter", "Fix Communications", "Restore Oxygen", "Stabilize Steering", "Assemble Artifact", "Sort Samples", "Measure Weather", "Enter ID Code",
		"Buy Beverage", "Process Data", "Run Diagnostics", "Water Plants", "Monitor Oxygen", "Store Artifacts", "Fill Canisters", "Activate Weather Nodes", "Insert Keys",
		"Reset Seismic Stabilizers", "Scan Boarding Pass", "Open Waterways", "Replace Water Jug", "Repair Drill", "Align Telecopse", "Record Temperature", "Reboot Wifi",
		"Polish Ruby", "Reset Breakers", "Decontaminate", "Make Burger", "Unlock Safe", "Sort Records", "Put Away Pistols", "Fix Shower", "Clean Toilet", "Dress Mannequin",
		"Pick Up Towels", "Rewind Tapes", "Start Fans", "Develop Photos", "Get Biggol Sword", "Put Away Rifles", "Stop Charles", "Vent Cleaning"};
	return TASK_TRANSLATIONS[(uint8_t)taskType];
}

#pragma warning(suppress:26812)
const char* TranslateSystemTypes(SystemTypes__Enum systemType) {
	static const char* const SYSTEM_TRANSLATIONS[] = { "Hallway", "Storage", "Cafeteria", "Reactor", "Upper Engine", "Navigation", "Admin", "Electrical", "Oxygen", "Shields",
		"MedBay", "Security", "Weapons", "Lower Engine", "Communications", "Ship Tasks", "Doors", "Sabotage", "Decontamination", "Launchpad", "Locker Room", "Laboratory",
		"Balcony", "Office", "Greenhouse", "Dropship", "Decontamination", "Outside", "Specimen Room", "Boiler Room", "Vault Room", "Cockpit", "Armory", "Kitchen", "Viewing Deck",
		"Hall Of Portraits", "Cargo Bay", "Ventilation", "Showers", "Engine Room", "The Brig", "Meeting Room", "Records Room", "Lounge Room", "Gap Room", "Main Hall", "Medical" };
	return SYSTEM_TRANSLATIONS[(uint8_t)systemType];
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
	return SystemTypes__Enum::Outside;
}

std::optional<EVENT_PLAYER> GetEventPlayer(GameData_PlayerInfo* playerInfo)
{
	if (!playerInfo) return std::nullopt;
	return EVENT_PLAYER(playerInfo);
}

std::optional<EVENT_PLAYER> GetEventPlayerControl(PlayerControl* player)
{
	GameData_PlayerInfo* playerInfo = player->fields._cachedData;

	if (!playerInfo) return std::nullopt;
	return EVENT_PLAYER(playerInfo);
}

std::optional<Vector2> GetTargetPosition(GameData_PlayerInfo* playerInfo)
{
	if (!playerInfo) return std::nullopt;
	return PlayerControl_GetTruePosition(playerInfo->fields._object, NULL);
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

std::string ToString(Object* object) {
	std::string type = convert_from_string(Object_ToString(object, NULL));
	if (type == "System.String") {
		return convert_from_string((String*)object);
	}
	return type;
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

void ImpersonateName(PlayerSelection player)
{
	if (!(IsInGame() || IsInLobby())) return;
	if (convert_from_string(GetPlayerOutfit(player.get_PlayerData())->fields._playerName).length() < 10) {
		if (IsInGame())
			State.rpcQueue.push(new RpcSetName(convert_from_string(GetPlayerOutfit(player.get_PlayerData())->fields._playerName) + " "));
		else if (IsInLobby())
			State.lobbyRpcQueue.push(new RpcSetName(convert_from_string(GetPlayerOutfit(player.get_PlayerData())->fields._playerName) + " "));
	}
	else {
		if (IsInGame())
			State.rpcQueue.push(new RpcSetName(convert_from_string(GetPlayerOutfit(player.get_PlayerData())->fields._playerName)));
		else if (IsInLobby())
			State.lobbyRpcQueue.push(new RpcSetName(convert_from_string(GetPlayerOutfit(player.get_PlayerData())->fields._playerName)));
	}
}

int GetRandomColorId()
{
	int colorId = 0;
	if (IsInGame() || IsInLobby())
	{
		auto players = GetAllPlayerControl();
		std::vector<int> availableColors = { };
		for (il2cpp_array_size_t i = 0; i < app::Palette__TypeInfo->static_fields->PlayerColors->max_length; i++)
		{
			bool colorAvailable = true;
			for (PlayerControl* player : players)
			{
				if (i == GetPlayerOutfit(GetPlayerData(player))->fields.ColorId)
				{
					colorAvailable = false;
					break;
				}
			}

			if (colorAvailable)
				availableColors.push_back(i);
		}

		colorId = availableColors.at(randi(0, availableColors.size() - 1));
	}
	else
	{
		colorId = randi(0, app::Palette__TypeInfo->static_fields->PlayerColors->max_length - 1);
	}
	return colorId;
}

void SaveOriginalAppearance()
{
	PlayerSelection player = *Game::pLocalPlayer;
	LOG_DEBUG("Set appearance values to current player");
	State.originalName = convert_from_string(GetPlayerOutfit(player.get_PlayerData())->fields._playerName);
	State.originalSkin = GetPlayerOutfit(player.get_PlayerData())->fields.SkinId;
	State.originalHat = GetPlayerOutfit(player.get_PlayerData())->fields.HatId;
	State.originalPet = GetPlayerOutfit(player.get_PlayerData())->fields.PetId;
	State.originalColor = GetPlayerOutfit(player.get_PlayerData())->fields.ColorId;
	State.activeImpersonation = false;
}

void ResetOriginalAppearance()
{
	LOG_DEBUG("Reset appearance values to invalid");
	State.originalSkin = nullptr;
	State.originalHat = nullptr;
	State.originalPet = nullptr;
	State.originalColor = 0xFF;
}

GameData_PlayerOutfit* GetPlayerOutfit(GameData_PlayerInfo* player, bool includeShapeshifted) {
	auto arr = player->fields.Outfits->fields.entries;
	auto outfitCount = player->fields.Outfits->fields.count;
	GameData_PlayerOutfit* playerOutfit = NULL;
	for (int i = 0; i < outfitCount; i++) {
		auto kvp = arr->vector[i];
		if (kvp.key == PlayerOutfitType__Enum::Default) {
			if(playerOutfit == nullptr)
				playerOutfit = kvp.value;
			if(!includeShapeshifted)
				break;
		}
		if (kvp.key == PlayerOutfitType__Enum::Shapeshifted && !convert_from_string(kvp.value->fields._playerName).empty()) {
			playerOutfit = kvp.value;
			break;
		}
	}
	return playerOutfit ? playerOutfit : 0;
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
	case RoleTypes__Enum::Crewmate:
		c = Palette__TypeInfo->static_fields->White;
		break;
	case RoleTypes__Enum::Engineer:
	case RoleTypes__Enum::GuardianAngel:
	case RoleTypes__Enum::Scientist:
		c = Palette__TypeInfo->static_fields->CrewmateBlue;
		break;
	case RoleTypes__Enum::Impostor:
	case RoleTypes__Enum::Shapeshifter:
		c = Palette__TypeInfo->static_fields->ImpostorRed;
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
			return (abbreviated ? "GA" : "GuardianAngel");
		case RoleTypes__Enum::Impostor:
			return (abbreviated ? "Imp" : "Impostor");
		case RoleTypes__Enum::Scientist:
			return (abbreviated ? "Sci" : "Scientist");
		case RoleTypes__Enum::Shapeshifter:
			return (abbreviated ? "SH" : "Shapeshifter");
		case RoleTypes__Enum::Crewmate:
			return (abbreviated ? "Crew" : "Crewmate");
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

float GetDistanceBetweenPoints_Unity(Vector2 p1, Vector2 p2)
{
	float dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrtf(dx * dx + dy * dy);
}

float GetDistanceBetweenPoints_ImGui(ImVec2 p1, ImVec2 p2)
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
	if ((point.x != prevPoint.x) && (point.y != prevPoint.y))
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
	return (State.mapType == Settings::MapType::Ship && State.FlipSkeld) ? x - 50.0f : x;
}