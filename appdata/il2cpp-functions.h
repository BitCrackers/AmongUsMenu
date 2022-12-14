using namespace app;

DO_APP_FUNC(Type*, Type_GetType, (String* typeName, MethodInfo* method), "mscorlib, System.Type System.Type::GetType(System.String)");
DO_APP_FUNC(Type*, RuntimeType_MakeGenericType_1, (Type* gt, /*Type__Array**/void* types, MethodInfo* method), "mscorlib, System.Type System.RuntimeType::MakeGenericType(System.Type, System.Type[])");

DO_APP_FUNC(Object*, MonoMethod_InternalInvoke, (MonoMethod* __this, Object* obj, /*Object__Array*/void* parameters, Exception** exc, MethodInfo* method), "mscorlib, System.Object System.Reflection.MonoMethod::InternalInvoke(System.Object, System.Object[], System.Exception&)");

DO_APP_FUNC(GameObject*, Component_get_gameObject, (Component_1* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.GameObject UnityEngine.Component::get_gameObject()");
DO_APP_FUNC(Transform*, Component_get_transform, (Component_1* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Transform UnityEngine.Component::get_transform()");

DO_APP_FUNC(void, Object_DestroyImmediate, (Object_1* obj, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Object::DestroyImmediate(UnityEngine.Object)");
DO_APP_FUNC(Component_1*, Component_GetComponent, (Component_1* __this, Type* type, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Component UnityEngine.Component::GetComponent(System.Type)");

DO_APP_FUNC(Transform*, GameObject_get_transform, (GameObject* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Transform UnityEngine.GameObject::get_transform()");
DO_APP_FUNC(Transform*, Transform_GetRoot, (Transform* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Transform UnityEngine.Transform::GetRoot()");
DO_APP_FUNC(String*, Component_get_tag, (Component_1* __this, MethodInfo* method), "UnityEngine.CoreModule, System.String UnityEngine.Component::get_tag()");
DO_APP_FUNC(void, GameObject_set_layer, (GameObject* __this, int32_t value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.GameObject::set_layer(System.Int32)");
DO_APP_FUNC(int32_t, GameObject_get_layer, (GameObject* __this, MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.GameObject::get_layer()");
DO_APP_FUNC(int32_t, LayerMask_NameToLayer, (String* layerName, MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.LayerMask::NameToLayer(System.String)");
DO_APP_FUNC(Object_1__Array*, Object_1_FindObjectsOfType, (Type* type, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Object[] UnityEngine.Object::FindObjectsOfType(System.Type)");
DO_APP_FUNC(String*, Scene_GetNameInternal, (int32_t sceneHandle, MethodInfo* method), "UnityEngine.CoreModule, System.String UnityEngine.SceneManagement.Scene::GetNameInternal(System.Int32)");
DO_APP_FUNC(void, SceneManager_Internal_ActiveSceneChanged, (Scene previousActiveScene, Scene newActiveScene, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.SceneManagement.SceneManager::Internal_ActiveSceneChanged(UnityEngine.SceneManagement.Scene, UnityEngine.SceneManagement.Scene)");
DO_APP_FUNC(Vector3, Transform_get_position, (Transform* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Transform::get_position()");
DO_APP_FUNC(void, Transform_set_position, (Transform* __this, Vector3 value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Transform::set_position(UnityEngine.Vector3)");
DO_APP_FUNC(float, Vector2_Distance, (Vector2 a, Vector2 b, MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Vector2::Distance(UnityEngine.Vector2, UnityEngine.Vector2)");
DO_APP_FUNC(bool, Collider2D_OverlapPoint, (Collider2D* __this, Vector2 point, MethodInfo* method), "UnityEngine.Physics2DModule, System.Boolean UnityEngine.Collider2D::OverlapPoint(UnityEngine.Vector2)");
DO_APP_FUNC(String*, Application_get_version, (MethodInfo* method), "UnityEngine.CoreModule, System.String UnityEngine.Application::get_version()");
DO_APP_FUNC(void, Renderer_set_enabled, (Renderer* __this, bool value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Renderer::set_enabled(System.Boolean)");
DO_APP_FUNC(int32_t, Camera_GetAllCameras, (Camera__Array* cameras, MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.Camera::GetAllCameras(UnityEngine.Camera[])");
DO_APP_FUNC(int32_t, Camera_get_allCamerasCount, (MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.Camera::get_allCamerasCount()");
DO_APP_FUNC(Camera*, Camera_get_main, (MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Camera UnityEngine.Camera::get_main()");
DO_APP_FUNC(void, Camera_set_orthographicSize, (Camera* __this, float value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Camera::set_orthographicSize(System.Single)");
DO_APP_FUNC(float, Camera_get_orthographicSize, (Camera* __this, MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Camera::get_orthographicSize()");
DO_APP_FUNC(Color, SpriteRenderer_get_color, (SpriteRenderer* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Color UnityEngine.SpriteRenderer::get_color()");
DO_APP_FUNC(float, Time_get_fixedDeltaTime, (MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Time::get_fixedDeltaTime()");
DO_APP_FUNC(float, Time_get_realtimeSinceStartup, (MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Time::get_realtimeSinceStartup()");
DO_APP_FUNC(float, Time_get_time, (MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Time::get_time()");

DO_APP_FUNC(int32_t, Screen_get_width, (MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.Screen::get_width()");
DO_APP_FUNC(int32_t, Screen_get_height, (MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.Screen::get_height()");
DO_APP_FUNC(bool, Screen_get_fullScreen, (MethodInfo* method), "UnityEngine.CoreModule, System.Boolean UnityEngine.Screen::get_fullScreen()");

DO_APP_FUNC(void, AirshipStatus_OnEnable, (AirshipStatus* __this, MethodInfo* method), "Assembly-CSharp, System.Void AirshipStatus::OnEnable()");
DO_APP_FUNC(float, AirshipStatus_CalculateLightRadius, (AirshipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method), "Assembly-CSharp, System.Single AirshipStatus::CalculateLightRadius(GameData.PlayerInfo)");

DO_APP_FUNC(bool, AutoOpenDoor_DoUpdate, (AutoOpenDoor* __this, float dt, MethodInfo* method), "Assembly-CSharp, System.Boolean AutoOpenDoor::DoUpdate(System.Single)");

//DO_APP_FUNC(void, NoShadowBehaviour_LateUpdate, (NoShadowBehaviour* __this, MethodInfo* method), "Assembly-CSharp, System.Void NoShadowBehaviour::LateUpdate()");
DO_APP_FUNC(void, NoShadowBehaviour_SetMaskFunction, (NoShadowBehaviour* __this, int32_t func, MethodInfo* method), "Assembly-CSharp, System.Void NoShadowBehaviour::SetMaskFunction(System.Int32)");

DO_APP_FUNC(Vector3, Camera_ScreenToWorldPoint, (Camera* __this, Vector3 position, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Camera::ScreenToWorldPoint(UnityEngine.Vector3)");

DO_APP_FUNC(void, CustomNetworkTransform_RpcSnapTo, (CustomNetworkTransform* __this, Vector2 position, MethodInfo* method), "Assembly-CSharp, System.Void CustomNetworkTransform::RpcSnapTo(UnityEngine.Vector2)");
DO_APP_FUNC(void, CustomNetworkTransform_SnapTo, (CustomNetworkTransform* __this, Vector2 position, uint16_t minSid, MethodInfo* method), "Assembly-CSharp, System.Void CustomNetworkTransform::SnapTo(UnityEngine.Vector2, System.UInt16)");

DO_APP_FUNC(Vector2, DeadBody_get_TruePosition, (DeadBody* __this, MethodInfo* method), "Assembly-CSharp, UnityEngine.Vector2 DeadBody::get_TruePosition()");

DO_APP_FUNC(GameData_PlayerInfo*, GameData_GetPlayerById, (GameData* __this, uint8_t id, MethodInfo* method), "Assembly-CSharp, GameData.PlayerInfo GameData::GetPlayerById(System.Byte)");

DO_APP_FUNC(void, GameObject_SetActive, (GameObject* __this, bool value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.GameObject::SetActive(System.Boolean)");

DO_APP_FUNC(void, KeyboardJoystick_Update, (KeyboardJoystick* __this, MethodInfo* method), "Assembly-CSharp, System.Void KeyboardJoystick::Update()");
DO_APP_FUNC(void, ScreenJoystick_FixedUpdate, (ScreenJoystick* __this, MethodInfo* method), "Assembly-CSharp, System.Void ScreenJoystick::FixedUpdate()");

DO_APP_FUNC(void, MainMenuManager_Start, (MainMenuManager* __this, MethodInfo* method), "Assembly-CSharp, System.Void MainMenuManager::Start()");

DO_APP_FUNC(void, MeetingHud_Awake, (MeetingHud* __this, MethodInfo* method), "Assembly-CSharp, System.Void MeetingHud::Awake()");
DO_APP_FUNC(void, MeetingHud_Close, (MeetingHud* __this, MethodInfo* method), "Assembly-CSharp, System.Void MeetingHud::Close()");
DO_APP_FUNC(void, MeetingHud_Update, (MeetingHud* __this, MethodInfo* method), "Assembly-CSharp, System.Void MeetingHud::Update()");
DO_APP_FUNC(void, MeetingHud_BloopAVoteIcon, (MeetingHud* __this, GameData_PlayerInfo* voterPlayer, int index, Transform* parent, MethodInfo* method), "Assembly-CSharp, System.Void MeetingHud::BloopAVoteIcon(GameData.PlayerInfo, System.Int32, UnityEngine.Transform)");
DO_APP_FUNC(void, MeetingHud_PopulateResults, (MeetingHud* __this, Il2CppArraySize* states, MethodInfo* method), "Assembly-CSharp, System.Void MeetingHud::PopulateResults(MeetingHud.VoterState[])");

DO_APP_FUNC(void, MovingPlatformBehaviour_SetSide, (MovingPlatformBehaviour* __this, bool isLeft, MethodInfo* method), "Assembly-CSharp, System.Void MovingPlatformBehaviour::SetSide(System.Boolean)");

DO_APP_FUNC(bool, NormalPlayerTask_get_IsComplete, (NormalPlayerTask* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean NormalPlayerTask::get_IsComplete()");
DO_APP_FUNC(void, NormalPlayerTask_NextStep, (NormalPlayerTask* __this, MethodInfo* method), "Assembly-CSharp, System.Void NormalPlayerTask::NextStep()");

DO_APP_FUNC(void, PlainDoor_SetDoorway, (PlainDoor* __this, bool open, MethodInfo* method), "Assembly-CSharp, System.Void PlainDoor::SetDoorway(System.Boolean)");
DO_APP_FUNC(void, DoorBreakerGame_Start, (DoorBreakerGame* __this, MethodInfo* method), "Assembly-CSharp, System.Void DoorBreakerGame::Start()");
DO_APP_FUNC(void, DoorCardSwipeGame_Begin, (DoorCardSwipeGame* __this, PlayerTask* playerTask, MethodInfo* method), "Assembly-CSharp, System.Void DoorCardSwipeGame::Begin(PlayerTask)");
DO_APP_FUNC(void, Minigame_Close, (Minigame* __this, MethodInfo* method), "Assembly-CSharp, System.Void Minigame::Close()");

DO_APP_FUNC(void, PlayerControl_CompleteTask, (PlayerControl* __this, uint32_t idx, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::CompleteTask(System.UInt32)");
DO_APP_FUNC(void, PlayerControl_FixedUpdate, (PlayerControl* __this, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::FixedUpdate()");
DO_APP_FUNC(GameData_PlayerInfo*, PlayerControl_get_Data, (PlayerControl* __this, MethodInfo* method), "Assembly-CSharp, GameData.PlayerInfo PlayerControl::get_Data()");
DO_APP_FUNC(Vector2, PlayerControl_GetTruePosition, (PlayerControl* __this, MethodInfo* method), "Assembly-CSharp, UnityEngine.Vector2 PlayerControl::GetTruePosition()");
DO_APP_FUNC(void, PlayerControl_RpcSyncSettings, (PlayerControl* __this, Byte__Array* optionsByteArray, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSyncSettings(System.Byte[])");
DO_APP_FUNC(void, PlayerControl_RpcPlayAnimation, (PlayerControl* __this, uint8_t animType, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcPlayAnimation(System.Byte)");
DO_APP_FUNC(void, PlayerControl_CmdReportDeadBody, (PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::CmdReportDeadBody(GameData.PlayerInfo)");
DO_APP_FUNC(void, PlayerControl_MurderPlayer, (PlayerControl* __this, PlayerControl* target, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::MurderPlayer(PlayerControl)");
DO_APP_FUNC(void, PlayerControl_RpcMurderPlayer, (PlayerControl* __this, PlayerControl* target, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcMurderPlayer(PlayerControl)");
DO_APP_FUNC(void, PlayerControl_ReportDeadBody, (PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::ReportDeadBody(GameData.PlayerInfo)");
DO_APP_FUNC(void, PlayerControl_StartMeeting, (PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::StartMeeting(GameData.PlayerInfo)");
DO_APP_FUNC(void, PlayerControl_RpcSetRole, (PlayerControl* __this, RoleTypes__Enum roleType, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSetRole(AmongUs.GameOptions.RoleTypes)");
DO_APP_FUNC(void, PlayerControl_RpcSetScanner, (PlayerControl* __this, bool value, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSetScanner(System.Boolean)");
DO_APP_FUNC(void, PlayerControl_CmdCheckColor, (PlayerControl* __this, uint8_t bodyColor, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::CmdCheckColor(System.Byte)");
DO_APP_FUNC(void, PlayerControl_RpcSetColor, (PlayerControl* __this, uint8_t bodyColor, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSetColor(System.Byte)");
DO_APP_FUNC(void, PlayerControl_CmdCheckName, (PlayerControl* __this, String* name, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::CmdCheckName(System.String)");
DO_APP_FUNC(void, PlayerControl_set_Visible, (PlayerControl* __this, bool value, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::set_Visible(System.Boolean)");
DO_APP_FUNC(void, PlayerControl_HandleRpc, (PlayerControl* __this, uint8_t callId, MessageReader* reader, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::HandleRpc(System.Byte, Hazel.MessageReader)");
DO_APP_FUNC(void, PlayerControl_RpcSetPet, (PlayerControl* __this, String* petId, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSetPet(System.String)");
DO_APP_FUNC(void, PlayerControl_RpcSetSkin, (PlayerControl* __this, String* skinId, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSetSkin(System.String)");
DO_APP_FUNC(void, PlayerControl_RpcSetHat, (PlayerControl* __this, String* hatId, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSetHat(System.String)");
DO_APP_FUNC(void, PlayerControl_RpcSetVisor, (PlayerControl* __this, String* visorId, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSetVisor(System.String)");
DO_APP_FUNC(void, PlayerControl_RpcSetNamePlate, (PlayerControl* __this, String* namePlateId, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSetNamePlate(System.String)");
DO_APP_FUNC(bool, PlayerControl_RpcSendChat, (PlayerControl* __this, String* message, MethodInfo* method), "Assembly-CSharp, System.Boolean PlayerControl::RpcSendChat(System.String)");
DO_APP_FUNC(void, PlayerControl_Shapeshift, (PlayerControl* __this, PlayerControl* target, bool animate, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::Shapeshift(PlayerControl, System.Boolean)");
DO_APP_FUNC(void, PlayerControl_ProtectPlayer, (PlayerControl* __this, PlayerControl* target, int32_t colorId, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::ProtectPlayer(PlayerControl, System.Int32)");
DO_APP_FUNC(void, PlayerMaterial_SetColors, (int32_t colorId, Renderer* rend, MethodInfo* method), "Assembly-CSharp, System.Void PlayerMaterial::SetColors(System.Int32, UnityEngine.Renderer)");
DO_APP_FUNC(void, PlayerMaterial_SetColors_1, (Color color, Renderer* rend, MethodInfo* method), "Assembly-CSharp, System.Void PlayerMaterial::SetColors(UnityEngine.Color, UnityEngine.Renderer)");

DO_APP_FUNC(void, PolusShipStatus_OnEnable, (PolusShipStatus* __this, MethodInfo* method), "Assembly-CSharp, System.Void PolusShipStatus::OnEnable()");

DO_APP_FUNC(float, ShipStatus_CalculateLightRadius, (ShipStatus* __this, GameData_PlayerInfo* player, MethodInfo* method), "Assembly-CSharp, System.Single ShipStatus::CalculateLightRadius(GameData.PlayerInfo)");
DO_APP_FUNC(void, ShipStatus_OnEnable, (ShipStatus* __this, MethodInfo* method), "Assembly-CSharp, System.Void ShipStatus::OnEnable()");
DO_APP_FUNC(void, ShipStatus_RpcCloseDoorsOfType, (ShipStatus* __this, SystemTypes__Enum type, MethodInfo* method), "Assembly-CSharp, System.Void ShipStatus::RpcCloseDoorsOfType(SystemTypes)");
DO_APP_FUNC(void, ShipStatus_RpcRepairSystem, (ShipStatus* __this, SystemTypes__Enum systemType, int32_t amount, MethodInfo* method), "Assembly-CSharp, System.Void ShipStatus::RpcRepairSystem(SystemTypes, System.Int32)");
DO_APP_FUNC(void, ShipStatus_RepairSystem, (ShipStatus* __this, SystemTypes__Enum systemType, PlayerControl* player, uint8_t amount, MethodInfo* method), "Assembly-CSharp, System.Void ShipStatus::RepairSystem(SystemTypes, PlayerControl, System.Byte)");

DO_APP_FUNC(float, StatsManager_get_BanPoints, (StatsManager* __this, MethodInfo* method), "Assembly-CSharp, System.Single StatsManager::get_BanPoints()");
DO_APP_FUNC(int32_t, StatsManager_get_BanMinutesLeft, (StatsManager* __this, MethodInfo* method), "Assembly-CSharp, System.Int32 StatsManager::get_BanMinutesLeft()");
DO_APP_FUNC(bool, StatsManager_get_AmBanned, (StatsManager* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean StatsManager::get_AmBanned()");

DO_APP_FUNC(float, Vent_CanUse, (Vent* __this, GameData_PlayerInfo* player, bool* canUse, bool* couldUse, MethodInfo* method), "Assembly-CSharp, System.Single Vent::CanUse(GameData.PlayerInfo, System.Boolean&, System.Boolean&)");
DO_APP_FUNC(float, Vent_get_UsableDistance, (Vent* __this, MethodInfo* method), "Assembly-CSharp, System.Single Vent::get_UsableDistance()");
DO_APP_FUNC(void, Vent_EnterVent, (Vent* __this, PlayerControl* pc, MethodInfo* method), "Assembly-CSharp, System.Void Vent::EnterVent(PlayerControl)");
DO_APP_FUNC(void, Vent_ExitVent, (Vent* __this, PlayerControl* pc, MethodInfo* method), "Assembly-CSharp, System.Void Vent::ExitVent(PlayerControl)");

DO_APP_FUNC(void, HudManager_Update, (HudManager* __this, MethodInfo* method), "Assembly-CSharp, System.Void HudManager::Update()");
DO_APP_FUNC(void, HudManager_SetHudActive, (HudManager* __this, bool isActive, MethodInfo* method), "Assembly-CSharp, System.Void HudManager::SetHudActive(System.Boolean)");
DO_APP_FUNC(void, ChatController_AddChat, (ChatController* __this, PlayerControl* sourcePlayer, String* chatText, MethodInfo* method), "Assembly-CSharp, System.Void ChatController::AddChat(PlayerControl, System.String)");
DO_APP_FUNC(void, ChatController_SetVisible, (ChatController* __this, bool visible, MethodInfo* method), "Assembly-CSharp, System.Void ChatController::SetVisible(System.Boolean)");
DO_APP_FUNC(void, ChatController_Update, (ChatController* __this, MethodInfo* method), "Assembly-CSharp, System.Void ChatController::Update()");
DO_APP_FUNC(void, ChatBubble_SetName, (ChatBubble* __this, String* playerName, bool isDead, bool voted, Color color, MethodInfo* method), "Assembly-CSharp, System.Void ChatBubble::SetName(System.String, System.Boolean, System.Boolean, UnityEngine.Color)");

DO_APP_FUNC(void, AmongUsClient_OnPlayerLeft, (AmongUsClient* __this, ClientData* data, DisconnectReasons__Enum reason, MethodInfo* method), "Assembly-CSharp, System.Void AmongUsClient::OnPlayerLeft(InnerNet.ClientData, DisconnectReasons)");
DO_APP_FUNC(bool, InnerNetClient_get_AmHost, (InnerNetClient* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean InnerNet.InnerNetClient::get_AmHost()");
DO_APP_FUNC(void, InnerNetClient_SendStartGame, (InnerNetClient* __this, MethodInfo* method), "Assembly-CSharp, System.Void InnerNet.InnerNetClient::SendStartGame()");
DO_APP_FUNC(void, InnerNetClient_Update, (InnerNetClient* __this, MethodInfo* method), "Assembly-CSharp, System.Void InnerNet.InnerNetClient::Update()");
DO_APP_FUNC(MessageWriter*, InnerNetClient_StartRpc, (InnerNetClient* __this, uint32_t targetNetId, uint8_t callId, SendOption__Enum option, MethodInfo* method), "Assembly-CSharp, Hazel.MessageWriter InnerNet.InnerNetClient::StartRpc(System.UInt32, System.Byte, Hazel.SendOption)");
DO_APP_FUNC(MessageWriter*, InnerNetClient_StartRpcImmediately, (InnerNetClient* __this, uint32_t targetNetId, uint8_t callId, SendOption__Enum option, int32_t targetClientId, MethodInfo* method), "Assembly-CSharp, Hazel.MessageWriter InnerNet.InnerNetClient::StartRpcImmediately(System.UInt32, System.Byte, Hazel.SendOption, System.Int32)");
DO_APP_FUNC(void, InnerNetClient_FinishRpcImmediately, (InnerNetClient* __this, MessageWriter* msg, MethodInfo* method), "Assembly-CSharp, System.Void InnerNet.InnerNetClient::FinishRpcImmediately(Hazel.MessageWriter)");

DO_APP_FUNC(void, MessageExtensions_WriteNetObject, (MessageWriter* self, InnerNetObject* obj, MethodInfo* method), "Assembly-CSharp, System.Void InnerNet.MessageExtensions::WriteNetObject(Hazel.MessageWriter, InnerNet.InnerNetObject)");

DO_APP_FUNC(bool, Constants_ShouldFlipSkeld, (MethodInfo* method), "Assembly-CSharp, System.Boolean Constants::ShouldFlipSkeld()");

DO_APP_FUNC(void, LobbyBehaviour_Start, (LobbyBehaviour* __this, MethodInfo* method), "Assembly-CSharp, System.Void LobbyBehaviour::Start()");

DO_APP_FUNC(MessageWriter*, MessageWriter_Get, (SendOption__Enum sendOption, MethodInfo* method), "Hazel, Hazel.MessageWriter Hazel.MessageWriter::Get(Hazel.SendOption)");
DO_APP_FUNC(void, MessageWriter_StartMessage, (MessageWriter* __this, uint8_t typeFlag, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::StartMessage(System.Byte)");
DO_APP_FUNC(void, MessageWriter_WritePacked, (MessageWriter* __this, int32_t value, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::WritePacked(System.Int32)");

DO_APP_FUNC(bool, MessageReader_ReadBoolean, (MessageReader* __this, MethodInfo* method), "Hazel, System.Boolean Hazel.MessageReader::ReadBoolean()");
DO_APP_FUNC(uint8_t, MessageReader_ReadByte, (MessageReader* __this, MethodInfo* method), "Hazel, System.Byte Hazel.MessageReader::ReadByte()");
DO_APP_FUNC(uint32_t, MessageReader_ReadUInt32, (MessageReader* __this, MethodInfo* method), "Hazel, System.UInt32 Hazel.MessageReader::ReadUInt32()");
DO_APP_FUNC(int32_t, MessageReader_ReadInt32, (MessageReader* __this, MethodInfo* method), "Hazel, System.Int32 Hazel.MessageReader::ReadInt32()");
DO_APP_FUNC(float, MessageReader_ReadSingle, (MessageReader* __this, MethodInfo* method), "Hazel, System.Single Hazel.MessageReader::ReadSingle()");
DO_APP_FUNC(String*, MessageReader_ReadString, (MessageReader* __this, MethodInfo* method), "Hazel, System.String Hazel.MessageReader::ReadString()");
DO_APP_FUNC(Byte__Array*, MessageReader_ReadBytesAndSize, (MessageReader* __this, MethodInfo* method), "Hazel, System.Byte[] Hazel.MessageReader::ReadBytesAndSize()");
DO_APP_FUNC(Byte__Array*, MessageReader_ReadBytes, (MessageReader* __this, int32_t length, MethodInfo* method), "Hazel, System.Byte[] Hazel.MessageReader::ReadBytes(System.Int32)");
DO_APP_FUNC(void, MessageWriter_WriteBoolean, (MessageWriter* __this, bool value, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::Write(System.Boolean)");
DO_APP_FUNC(void, MessageWriter_WriteByte, (MessageWriter* __this, uint8_t value, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::Write(System.Byte)");
DO_APP_FUNC(void, MessageWriter_WriteUShort, (MessageWriter* __this, uint16_t value, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::Write(System.UInt16)");
DO_APP_FUNC(void, MessageWriter_WriteInt32, (MessageWriter* __this, int32_t value, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::Write(System.Int32)");
DO_APP_FUNC(void, MessageWriter_WriteSingle, (MessageWriter* __this, float value, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::Write(System.Single)");
DO_APP_FUNC(void, MessageWriter_WriteString, (MessageWriter* __this, String* value, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::Write(System.String)");
DO_APP_FUNC(void, MessageWriter_WriteBytesAndSize, (MessageWriter* __this, Byte__Array* bytes, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::Write(System.Byte[])");
DO_APP_FUNC(void, MessageWriter_WriteByteArray, (MessageWriter* __this, Byte__Array* bytes, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::Write(System.Byte[])");
DO_APP_FUNC(void, MessageWriter_EndMessage, (MessageWriter* __this, MethodInfo* method), "Hazel, System.Void Hazel.MessageWriter::EndMessage()");

DO_APP_FUNC(void, AccountTab_Open, (AccountTab* __this, MethodInfo* method), "Assembly-CSharp, System.Void AccountTab::Open()");
DO_APP_FUNC(void, FullAccount_CanSetCustomName, (FullAccount* __this, bool canSetName, MethodInfo* method), "Assembly-CSharp, System.Void FullAccount::CanSetCustomName(System.Boolean)");
DO_APP_FUNC(void, FollowerCamera_Update, (FollowerCamera* __this, MethodInfo* method), "Assembly-CSharp, System.Void FollowerCamera::Update()");
DO_APP_FUNC(void, AmongUsClient_OnGameEnd, (AmongUsClient* __this, Object* endGameResult, MethodInfo* method), "Assembly-CSharp, System.Void AmongUsClient::OnGameEnd(EndGameResult)");

DO_APP_FUNC(void, Debug_Log, (Object* message, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Debug::Log(System.Object)");
DO_APP_FUNC(void, Debug_LogError, (Object* message, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Debug::LogError(System.Object)");
DO_APP_FUNC(void, Debug_LogException, (Exception* exception, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Debug::LogException(System.Exception)");
DO_APP_FUNC(void, Debug_LogWarning, (Object* message, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Debug::LogWarning(System.Object)");
DO_APP_FUNC(String*, Object_ToString, (Object* __this, MethodInfo* method), "mscorlib, System.String System.Object::ToString()");
DO_APP_FUNC(void, VersionShower_Start, (VersionShower* __this, MethodInfo* method), "Assembly-CSharp, System.Void VersionShower::Start()");

DO_APP_FUNC(void, EOSManager_LoginFromAccountTab, (EOSManager* __this, MethodInfo* method), "Assembly-CSharp, System.Void EOSManager::LoginFromAccountTab()");
DO_APP_FUNC(bool, EOSManager_HasFinishedLoginFlow, (EOSManager* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean EOSManager::HasFinishedLoginFlow()");
DO_APP_FUNC(void, EOSManager_InitializePlatformInterface, (EOSManager* __this, MethodInfo* method), "Assembly-CSharp, System.Void EOSManager::InitializePlatformInterface()");
DO_APP_FUNC(bool, EOSManager_IsFreechatAllowed, (EOSManager* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean EOSManager::IsFreechatAllowed()");
DO_APP_FUNC(void, EOSManager_UpdatePermissionKeys, (EOSManager* __this, void* callback, MethodInfo* method), "Assembly-CSharp, System.Void EOSManager::UpdatePermissionKeys(System.Action)");

DO_APP_FUNC(void, TextMeshPro_SetFaceColor, (TextMeshPro* __this, Color32 color, MethodInfo* method), "Unity.TextMeshPro, System.Void TMPro.TextMeshPro::SetFaceColor(UnityEngine.Color32)");
DO_APP_FUNC(void, TextMeshPro_SetOutlineColor, (TextMeshPro* __this, Color32 color, MethodInfo* method), "Unity.TextMeshPro, System.Void TMPro.TextMeshPro::SetOutlineColor(UnityEngine.Color32)");
DO_APP_FUNC(void, TMP_Text_set_alignment, (TMP_Text* __this, TextAlignmentOptions__Enum value, MethodInfo* method), "Unity.TextMeshPro, System.Void TMPro.TMP_Text::set_alignment(TMPro.TextAlignmentOptions)");
DO_APP_FUNC(String*, TMP_Text_get_text, (TMP_Text* __this, MethodInfo* method), "Unity.TextMeshPro, System.String TMPro.TMP_Text::get_text()");
DO_APP_FUNC(void, TMP_Text_set_text, (TMP_Text* __this, String* value, MethodInfo* method), "Unity.TextMeshPro, System.Void TMPro.TMP_Text::set_text(System.String)");
DO_APP_FUNC(Color32, Color32_op_Implicit, (Color c, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Color32 UnityEngine.Color32::op_Implicit(UnityEngine.Color)");

DO_APP_FUNC(void, RoleManager_SelectRoles, (RoleManager* __this, MethodInfo* method), "Assembly-CSharp, System.Void RoleManager::SelectRoles()");
//DO_APP_FUNC(void, RoleManager_AssignRolesForTeam, (List_1_GameData_PlayerInfo_* players, RoleOptionsData* opts, RoleTeamTypes__Enum team, int32_t teamMax, Nullable_1_RoleTypes_ defaultRole, MethodInfo* method), "Assembly-CSharp, System.Void RoleManager::AssignRolesForTeam(System.Collections.Generic.List<GameData.PlayerInfo>, RoleOptionsData, RoleTeamTypes, System.Int32, System.Nullable<RoleTypes>)");
//DO_APP_FUNC(void, RoleManager_AssignRolesFromList, (List_1_GameData_PlayerInfo_* players, int32_t teamMax, List_1_RoleTypes_* roleList, int32_t* rolesAssigned, MethodInfo* method), "Assembly-CSharp, System.Void RoleManager::AssignRolesFromList(System.Collections.Generic.List<GameData.PlayerInfo>, System.Int32, System.Collections.Generic.List<RoleTypes>, System.Int32&)");
DO_APP_FUNC(void, InnerNetClient_EnqueueDisconnect, (InnerNetClient* __this, DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method), "Assembly-CSharp, System.Void InnerNet.InnerNetClient::EnqueueDisconnect(DisconnectReasons, System.String)");
DO_APP_FUNC(void, InnerNetClient_DisconnectInternal, (InnerNetClient* __this, DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method), "Assembly-CSharp, System.Void InnerNet.InnerNetClient::DisconnectInternal(DisconnectReasons, System.String)");

DO_APP_FUNC(void, PlayerPhysics_FixedUpdate, (PlayerPhysics* __this, MethodInfo* method), "Assembly-CSharp, System.Void PlayerPhysics::FixedUpdate()");

DO_APP_FUNC(void, PlayerControl_TurnOnProtection, (PlayerControl* __this, bool visible, int32_t colorId, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::TurnOnProtection(System.Boolean, System.Int32)");
DO_APP_FUNC(void, PlayerControl_RemoveProtection, (PlayerControl* __this, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RemoveProtection()");

DO_APP_FUNC(bool, Object_1_op_Implicit, (Object_1* exists, MethodInfo* method), "UnityEngine.CoreModule, System.Boolean UnityEngine.Object::op_Implicit(UnityEngine.Object)");
DO_APP_FUNC(void, PlayerControl_ShowFailedMurder, (PlayerControl* __this, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::ShowFailedMurder()");

DO_APP_FUNC(PlayerControl*, GameData_PlayerInfo_get_Object, (GameData_PlayerInfo* __this, MethodInfo* method), "Assembly-CSharp, PlayerControl GameData+PlayerInfo::get_Object()");
DO_APP_FUNC(GameData_PlayerOutfit*, GameData_PlayerInfo_get_DefaultOutfit, (GameData_PlayerInfo* __this, MethodInfo* method), "Assembly-CSharp, GameData.PlayerOutfit GameData+PlayerInfo::get_DefaultOutfit()");
DO_APP_FUNC(String*, GameData_PlayerOutfit_get_PlayerName, (GameData_PlayerOutfit* __this, MethodInfo* method), "Assembly-CSharp, System.String GameData+PlayerOutfit::get_PlayerName()");
DO_APP_FUNC(String*, GameData_PlayerInfo_get_PlayerName, (GameData_PlayerInfo* __this, MethodInfo* method), "Assembly-CSharp, System.String GameData+PlayerInfo::get_PlayerName()");

DO_APP_FUNC(void, AccountManager_UpdateKidAccountDisplay, (AccountManager* __this, MethodInfo* method), "Assembly-CSharp, System.Void AccountManager::UpdateKidAccountDisplay()");
DO_APP_FUNC(void, PlayerStorageManager_OnReadPlayerPrefsComplete, (PlayerStorageManager* __this, void* data, MethodInfo* method), "Assembly-CSharp, System.Void PlayerStorageManager::OnReadPlayerPrefsComplete(Epic.OnlineServices.PlayerDataStorage.ReadFileCallbackInfo)");

DO_APP_FUNC(void, AchievementManager_1_UnlockAchievement, (AchievementManager_1* __this, String* key, MethodInfo* method), "Assembly-CSharp, System.Void AchievementManager::UnlockAchievement(System.String)");

// 2022.10.25s
DO_APP_FUNC(PlayerData*, DataManager_get_Player, (MethodInfo* method), "Assembly-CSharp, AmongUs.Data.Player.PlayerData AmongUs.Data.DataManager::get_Player()");
DO_APP_FUNC(String*, PlayerCustomizationData_get_Name, (PlayerCustomizationData* __this, MethodInfo* method), "Assembly-CSharp, System.String AmongUs.Data.Player.PlayerCustomizationData::get_Name()");
DO_APP_FUNC(void, PlayerCustomizationData_set_Name, (PlayerCustomizationData* __this, String* value, MethodInfo* method), "Assembly-CSharp, System.Void AmongUs.Data.Player.PlayerCustomizationData::set_Name(System.String)");
DO_APP_FUNC(bool, PlayerPurchasesData_GetPurchase, (PlayerPurchasesData* __this, String* itemKey, String* bundleKey, MethodInfo* method), "Assembly-CSharp, System.Boolean PlayerPurchasesData::GetPurchase(System.String, System.String)");

// 2022.12.08e
DO_APP_FUNC(void, GameOptionsManager_set_CurrentGameOptions, (GameOptionsManager* __this, IGameOptions* value, MethodInfo* method), "Assembly-CSharp, System.Void GameOptionsManager::set_CurrentGameOptions(AmongUs.GameOptions.IGameOptions)");
DO_APP_FUNC(GameManager*, GameManager_get_Instance, (MethodInfo* method), "Assembly-CSharp, GameManager GameManager::get_Instance()");
DO_APP_FUNC(LogicOptions*, GameManager_get_LogicOptions, (GameManager* __this, MethodInfo* method), "Assembly-CSharp, LogicOptions GameManager::get_LogicOptions()");