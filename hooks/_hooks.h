#pragma once

void DetourInitilization();
void DetourUninitialization();

bool dAutoOpenDoor_DoUpdate(AutoOpenDoor* __this, float dt, MethodInfo* method);
bool dConstants_ShouldFlipSkeld(MethodInfo* method);
void dInnerNetClient_Update(InnerNetClient* __this, MethodInfo* method);
void dAmongUsClient_OnPlayerLeft(AmongUsClient* __this, ClientData* data, DisconnectReasons__Enum reason, MethodInfo* method);
void dCustomNetworkTransform_SnapTo(CustomNetworkTransform* __this, Vector2 position, uint16_t minSid, MethodInfo* method);
bool dStatsManager_get_AmBanned(StatsManager* __this, MethodInfo* method);
float dShipStatus_CalculateLightRadius(ShipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method);
float dStatsManager_get_BanPoints(StatsManager* __this, MethodInfo* method);
float dVent_CanUse(Vent* __this, GameData_PlayerInfo* pc, bool* canUse, bool* couldUse, MethodInfo* method);
GameOptionsData* dGameOptionsData_Deserialize(BinaryReader* reader, MethodInfo* method);
GameOptionsData* dGameOptionsData_Deserialize_1(MessageReader* reader, MethodInfo* method);
HatData__Array* dHatManager_GetUnlockedHats(HatManager* __this, MethodInfo* method);
int32_t dStatsManager_get_BanMinutesLeft(StatsManager* __this, MethodInfo* method);
PetData__Array* dHatManager_GetUnlockedPets(HatManager* __this, MethodInfo* method);
SkinData__Array* dHatManager_GetUnlockedSkins(HatManager* __this, MethodInfo* method);
void dChatBubble_SetName(ChatBubble* __this, String* playerName, bool isDead, bool voted, Color color, MethodInfo* method);
void dChatController_AddChat(ChatController* __this, PlayerControl* sourcePlayer, String* chatText, MethodInfo* method);
void dChatController_SetVisible(ChatController* __this, bool visible, MethodInfo* method);
void dHudManager_ShowMap(HudManager* __this, Action_1_MapBehaviour_* mapAction, MethodInfo* method);
void dHudManager_Update(HudManager* __this, MethodInfo* method);
Vector3 dCamera_ScreenToWorldPoint(Camera* __this, Vector3 position, MethodInfo* method);
void dKeyboardJoystick_Update(KeyboardJoystick* __this, MethodInfo* method);
void dScreenJoystick_FixedUpdate(ScreenJoystick* __this, MethodInfo* method);
void dMeetingHud_Awake(MeetingHud* __this, MethodInfo* method);
void dMeetingHud_Close(MeetingHud* __this, MethodInfo* method);
void dMeetingHud_Update(MeetingHud* __this, MethodInfo* method);
void dMeetingHud_PopulateResults(MeetingHud* __this, void* states, MethodInfo* method);
void dPlainDoor_SetDoorway(PlainDoor* __this, bool open, MethodInfo* method);
void dPlayerControl_CompleteTask(PlayerControl* __this, uint32_t idx, MethodInfo* method);
void dPlayerControl_FixedUpdate(PlayerControl* __this, MethodInfo* method);
void dPlayerControl_MurderPlayer(PlayerControl* __this, PlayerControl* target, MethodInfo* method);
void dPlayerControl_CmdReportDeadBody(PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method);
void dPlayerControl_ReportDeadBody(PlayerControl*__this, GameData_PlayerInfo* target, MethodInfo *method);
void dPlayerControl_RpcSyncSettings(PlayerControl* __this, GameOptionsData* gameOptions, MethodInfo* method);
void dPlayerControl_HandleRpc(PlayerControl* __this, uint8_t callId, MessageReader* reader, MethodInfo* method);
void dPlayerControl_Shapeshift(PlayerControl* __this, PlayerControl* target, bool animate, MethodInfo* method);
void dPlayerControl_ProtectPlayer(PlayerControl* __this, PlayerControl* target, int32_t colorId, MethodInfo* method);
void dRenderer_set_enabled(Renderer * __this, bool value, MethodInfo * method);
void dSceneManager_Internal_ActiveSceneChanged(Scene previousActiveScene, Scene newActiveScene, MethodInfo* method);
void dShipStatus_OnEnable(ShipStatus* __this, MethodInfo* method);
void dPolusShipStatus_OnEnable(PolusShipStatus* __this, MethodInfo* method);
void dVent_EnterVent(Vent* __this, PlayerControl* pc, MethodInfo * method);
void dVent_ExitVent(Vent* __this, PlayerControl* pc, MethodInfo * method);
void dLobbyBehaviour_Start(LobbyBehaviour* __this, MethodInfo* method);
void dGameObject_SetActive(GameObject* __this, bool value, MethodInfo* method);
void dNoShadowBehaviour_LateUpdate(NoShadowBehaviour* __this, MethodInfo* method);
void dFollowerCamera_Update(FollowerCamera* __this, MethodInfo* method);
void dAirshipStatus_OnEnable (AirshipStatus* __this, MethodInfo* method);
float dAirshipStatus_CalculateLightRadius(AirshipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method);
void dFollowerCamera_Update(FollowerCamera* __this, MethodInfo* method);
void dDoorBreakerGame_Start(DoorBreakerGame* __this, MethodInfo* method);
void dDoorCardSwipeGame_Begin(DoorCardSwipeGame* __this, PlayerTask* playerTask, MethodInfo* method);
void dDebug_Log(Object* message, MethodInfo* method);
void dDebug_LogError(Object* message, MethodInfo* method);
void dDebug_LogException(Exception* exception, MethodInfo* method);
void dDebug_LogWarning(Object* message, MethodInfo* method);
void dVersionShower_Start(VersionShower* __this, MethodInfo* method);
void dEOSManager_LoginFromAccountTab(EOSManager* __this, MethodInfo* method);
void dEOSManager_LoginForKWS(EOSManager* __this, bool allowOffline, MethodInfo* method);
void dEOSManager_InitializePlatformInterface(EOSManager* __this, MethodInfo* method);
void dEOSManager_BeginLoginFlow(EOSManager* __this, MethodInfo* method);
void dEOSManager_ReallyBeginFlow(EOSManager* __this, MethodInfo* method);
bool dEOSManager_IsFreechatAllowed(EOSManager* __this, MethodInfo* method);
void dChatController_Update(ChatController* __this, MethodInfo* method);
void dInnerNetClient_EnqueueDisconnect(InnerNetClient* __this, DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method);
void dRoleManager_SelectRoles(RoleManager* __this, MethodInfo * method);
void dRoleManager_AssignRolesForTeam(List_1_GameData_PlayerInfo_* players, RoleOptionsData* opts, RoleTeamTypes__Enum team, int32_t teamMax, Nullable_1_RoleTypes_ defaultRole, MethodInfo* method);
void dRoleManager_AssignRolesFromList(List_1_GameData_PlayerInfo_* players, int32_t teamMax, List_1_RoleTypes_* roleList, int32_t* rolesAssigned, MethodInfo* method);
void dPlayerPhysics_FixedUpdate (PlayerPhysics* __this, MethodInfo* method);

// 55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 3F 80 78 50 00
bool dHatManager_c__GetUnlockedHats_b__11_0(HatManager_c* __this, HatData* h, MethodInfo* method);

// 55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 42 80 B8 ? ? ? ? ?
bool dHatManager_c__GetUnlockedSkins_b__12_0(HatManager_c* __this, SkinData* s, MethodInfo* method);

// 55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 3F 80 78 2C 00
bool dHatManager_c__GetUnlockedPets_b__9_0(HatManager_c* __this, PetData* h, MethodInfo* method);

// 55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 3F 80 78 40 00
bool dHatManager_c__GetUnlockedVisors_b__15_0(HatManager_c* __this, VisorData* s, MethodInfo* method);

// 55 8B EC 80 3D ? ? ? ? ? 75 14 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 C6 05 ? ? ? ? ? 8B 45 0C 85 C0 74 3F 80 78 30 00
bool dHatManager_c__GetUnlockedNamePlates_b__17_0(HatManager_c* __this, NamePlateData* s, MethodInfo* method);