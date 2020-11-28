using namespace app;

DO_APP_FUNC(String*, Marshal_PtrToStringAnsi, (void* ptr, MethodInfo* method), "mscorlib, System.String System.Runtime.InteropServices.Marshal::PtrToStringAnsi(System.IntPtr)");
DO_APP_FUNC(String*, Marshal_PtrToStringUni, (void* ptr, MethodInfo* method), "mscorlib, System.String System.Runtime.InteropServices.Marshal::PtrToStringUni(System.IntPtr)");
DO_APP_FUNC(Type*, Type_GetType, (String* typeName, MethodInfo* method), "mscorlib, System.Type System.Type::GetType(System.String)");

DO_APP_FUNC(GameObject*, Component_get_gameObject, (Component* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.GameObject UnityEngine.Component::get_gameObject()");
DO_APP_FUNC(Transform*, Component_get_transform, (Component* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Transform UnityEngine.Component::get_transform()");
DO_APP_FUNC(String*, Component_get_tag, (Component* __this, MethodInfo* method), "UnityEngine.CoreModule, System.String UnityEngine.Component::get_tag()");
DO_APP_FUNC(void, GameObject_set_layer, (GameObject* __this, int32_t value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.GameObject::set_layer(System.Int32)");
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

DO_APP_FUNC(bool, AutoOpenDoor_DoUpdate, (AutoOpenDoor* __this, float dt, MethodInfo* method), "Assembly-CSharp, System.Boolean AutoOpenDoor::DoUpdate(System.Single)");

DO_APP_FUNC(void, CustomNetworkTransform_RpcSnapTo, (CustomNetworkTransform* __this, Vector2 position, MethodInfo* method), "Assembly-CSharp, System.Void CustomNetworkTransform::RpcSnapTo(UnityEngine.Vector2)");

DO_APP_FUNC(Vector2, DeadBody_get_TruePosition, (DeadBody* __this, MethodInfo* method), "Assembly-CSharp, UnityEngine.Vector2 DeadBody::get_TruePosition()");

DO_APP_FUNC(GameData_PlayerInfo*, GameData_GetPlayerById, (GameData* __this, uint8_t id, MethodInfo* method), "Assembly-CSharp, GameData.PlayerInfo GameData::GetPlayerById(System.Byte)");

DO_APP_FUNC(GameOptionsData*, GameOptionsData_Deserialize, (BinaryReader* reader, MethodInfo* method), "Assembly-CSharp, GameOptionsData GameOptionsData::Deserialize(System.IO.BinaryReader)");
DO_APP_FUNC(GameOptionsData*, GameOptionsData_Deserialize_1, (MessageReader* reader, MethodInfo* method), "Assembly-CSharp, GameOptionsData GameOptionsData::Deserialize(Hazel.MessageReader)");

DO_APP_FUNC(HatBehaviour__Array*, HatManager_GetUnlockedHats, (HatManager* __this, MethodInfo* method), "Assembly-CSharp, HatBehaviour[] HatManager::GetUnlockedHats()");
DO_APP_FUNC(PetBehaviour__Array*, HatManager_GetUnlockedPets, (HatManager* __this, MethodInfo* method), "Assembly-CSharp, PetBehaviour[] HatManager::GetUnlockedPets()");
DO_APP_FUNC(SkinData__Array*, HatManager_GetUnlockedSkins, (HatManager* __this, MethodInfo* method), "Assembly-CSharp, SkinData[] HatManager::GetUnlockedSkins()");

DO_APP_FUNC(void, KeyboardJoystick_Update, (KeyboardJoystick* __this, MethodInfo* method), "Assembly-CSharp, System.Void KeyboardJoystick::Update()");

DO_APP_FUNC(void, MeetingHud_Awake, (MeetingHud* __this, MethodInfo* method), "Assembly-CSharp, System.Void MeetingHud::Awake()");
DO_APP_FUNC(void, MeetingHud_Close, (MeetingHud* __this, MethodInfo* method), "Assembly-CSharp, System.Void MeetingHud::Close()");
DO_APP_FUNC(void, MeetingHud_Update, (MeetingHud* __this, MethodInfo* method), "Assembly-CSharp, System.Void MeetingHud::Update()");

DO_APP_FUNC(bool, NormalPlayerTask_get_IsComplete, (NormalPlayerTask* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean NormalPlayerTask::get_IsComplete()");
DO_APP_FUNC(void, NormalPlayerTask_NextStep, (NormalPlayerTask* __this, MethodInfo* method), "Assembly-CSharp, System.Void NormalPlayerTask::NextStep()");

DO_APP_FUNC(void, PlainDoor_SetDoorway, (PlainDoor* __this, bool open, MethodInfo* method), "Assembly-CSharp, System.Void PlainDoor::SetDoorway(System.Boolean)");

DO_APP_FUNC(void, PlayerControl_CompleteTask, (PlayerControl* __this, uint32_t idx, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::CompleteTask(System.UInt32)");
DO_APP_FUNC(void, PlayerControl_FixedUpdate, (PlayerControl* __this, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::FixedUpdate()");
DO_APP_FUNC(GameData_PlayerInfo*, PlayerControl_get_Data, (PlayerControl* __this, MethodInfo* method), "Assembly-CSharp, GameData.PlayerInfo PlayerControl::get_Data()");
DO_APP_FUNC(Vector2, PlayerControl_GetTruePosition, (PlayerControl* __this, MethodInfo* method), "Assembly-CSharp, UnityEngine.Vector2 PlayerControl::GetTruePosition()");
DO_APP_FUNC(void, PlayerControl_RpcSyncSettings, (PlayerControl* __this, GameOptionsData* gameOptions, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSyncSettings(GameOptionsData)");
DO_APP_FUNC(void, PlayerControl_CmdReportDeadBody, (PlayerControl* __this, GameData_PlayerInfo* target, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::CmdReportDeadBody(GameData.PlayerInfo)");
DO_APP_FUNC(void, PlayerControl_MurderPlayer, (PlayerControl* __this, PlayerControl* target, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::MurderPlayer(PlayerControl)");
DO_APP_FUNC(void, PlayerControl_ReportDeadBody, (PlayerControl*__this, GameData_PlayerInfo* target, MethodInfo *method), "Assembly-CSharp, System.Void PlayerControl::ReportDeadBody(GameData.PlayerInfo)");
DO_APP_FUNC(void, PlayerControl_RpcSetInfected, (PlayerControl* __this, GameData_PlayerInfo__Array* infected, MethodInfo* method), "Assembly-CSharp, System.Void PlayerControl::RpcSetInfected(GameData.PlayerInfo[])");

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

DO_APP_FUNC(void, HudManager_ShowMap, (HudManager* __this, Action_1_MapBehaviour_* mapAction, MethodInfo* method), "Assembly-CSharp, System.Void HudManager::ShowMap(System.Action<MapBehaviour>)");
DO_APP_FUNC(void, ChatController_AddChat, (ChatController* __this, PlayerControl* sourcePlayer, String* chatText, MethodInfo* method), "Assembly-CSharp, System.Void ChatController::AddChat(PlayerControl, System.String)");
DO_APP_FUNC(void, ChatController_SetVisible, (ChatController* __this, bool visible, MethodInfo* method), "Assembly-CSharp, System.Void ChatController::SetVisible(System.Boolean)");
DO_APP_FUNC(void, ChatBubble_SetName, (ChatBubble* __this, String* playerName, bool isDead, bool voted, Color color, MethodInfo* method), "Assembly-CSharp, System.Void ChatBubble::SetName(System.String, System.Boolean, System.Boolean, UnityEngine.Color)");

DO_APP_FUNC(bool, InnerNetClient_get_AmHost, (InnerNetClient* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean InnerNet.InnerNetClient::get_AmHost()");