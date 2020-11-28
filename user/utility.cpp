#include "utility.h"

using namespace app;

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

int randi(int lo, int hi) {
	int n = hi - lo + 1;
	int i = rand() % n;
	if (i < 0) i = -i;
	return lo + i;
}

ImVec4 AmongUsColorToImVec4(Color color) {
	return ImVec4(color.r, color.g, color.b, color.a);
}

ImVec4 AmongUsColorToImVec4(CorrectedColor32 color) {
	return ImVec4(color.r / 255.0F, color.g / 255.0F, color.b / 255.0F, color.a / 255.0F);
}

#define LocalInGame (((*Game::pAmongUsClient)->fields.GameMode == GameModes__Enum_LocalGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum_Started))
#define OnlineInGame (((*Game::pAmongUsClient)->fields.GameMode == GameModes__Enum_OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum_Started))
#define OnlineInLobby (((*Game::pAmongUsClient)->fields.GameMode == GameModes__Enum_OnlineGame) && ((*Game::pAmongUsClient)->fields._.GameState == InnerNetClient_GameStates__Enum_Joined))
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
		if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Ship || (*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Hq) {
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Reactor, 64));
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Reactor, 65));
		}

		if ((*Game::pShipStatus)->fields.Type == ShipStatus_MapType__Enum_Pb) {
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Laboratory, 64));
			State.rpcQueue.push(new RpcRepairSystem(SystemTypes__Enum_Laboratory, 65));
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
		"Reset Seismic Stabilizers", "Scan Boarding Pass", "Open Waterways", "Replace Water Jug", "Repair Drill", "Align Telecopse", "Record Temperature", "Reboot Wifi" };
	return TASK_TRANSLATIONS[taskType];
}

#pragma warning(suppress:26812)
const char* TranslateSystemTypes(SystemTypes__Enum systemType) {
	static const char* const SYSTEM_TRANSLATIONS[] = { "Hallway", "Storage", "Cafeteria", "Reactor", "Upper Engine", "Navigation", "Admin", "Electrical", "Oxygen", "Shields",
		"MedBay", "Security", "Weapons", "Lower Engine", "Communications", "Ship Tasks", "Doors", "Sabotage", "Decontamination", "Launchpad", "Locker Room", "Laboratory",
		"Balcony", "Office", "Greenhouse", "Dropship", "Decontamination", "Outside", "Specimen Room", "Boiler Room" };
	return SYSTEM_TRANSLATIONS[systemType];
}

CorrectedColor32 GetPlayerColor(uint8_t colorId) {
	CorrectedColor32* colorArray = (CorrectedColor32*)app::Palette__TypeInfo->static_fields->PlayerColors->vector;
	return colorArray[colorId];
}

std::string getModulePath() {
	TCHAR buff[MAX_PATH];
	GetModuleFileName((HINSTANCE)&__ImageBase, buff, _countof(buff));
	std::wstring ws(buff);
	std::string path(ws.begin(), ws.end());
	return path.substr(0, path.find_last_of("\\")).append("\\");
}

std::string getGameVersion() {
	return convert_from_string(app::Application_get_version(NULL));
}

SystemTypes__Enum GetSystemTypes(Vector2 vector) {
	if (*Game::pShipStatus) {
		auto shipStatus = *Game::pShipStatus;
		auto allRooms = shipStatus->fields._AllRooms_k__BackingField;

		for (size_t i = 0; i < allRooms->max_length; i++)
			if (app::Collider2D_OverlapPoint(allRooms->vector[i]->fields.roomArea, vector, NULL)) return allRooms->vector[i]->fields.RoomId;
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

std::optional<Vector2> GetLastWalkEventPosition(uint8_t playerId) {
	if (IsInGame()) {
		for (int i = State.events.size() - 1; i >= 0; i--) {
			if (State.events[i]->getSource().playerId == playerId
				&& State.events[i]->getType() == EVENT_WALK) {
				return ((WalkEvent*)State.events[i])->position;
			}
		}
	}
	return std::nullopt;
}

std::vector<Camera*> GetAllCameras() {
	auto cameras = std::vector<Camera*>();

	int cameraCount = app::Camera_get_allCamerasCount(NULL);
	Camera__Array* cameraArray = (Camera__Array*)il2cpp_array_new((Il2CppClass*)app::Camera__TypeInfo, cameraCount);
	int returnedCount = app::Camera_GetAllCameras(cameraArray, NULL);

	for (size_t i = 0; i < returnedCount; i++)
		cameras.push_back(cameraArray->vector[i]);

	return cameras;
}