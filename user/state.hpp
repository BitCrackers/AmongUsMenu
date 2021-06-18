#pragma once
#include <bitset>
#include <queue>
#include "_events.h"
#include "_rpc.h"
#include "keybinds.h"

class Settings {
public:

    KeyBinds::Config KeyBinds = {
        VK_DELETE,
        VK_INSERT,
        VK_HOME,
        VK_END,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    bool ImGuiInitialized = false;
    bool ShowMenu = false;

#ifdef _DEBUG
    bool showDebugTab = false;
#endif

    std::string CurrentScene;

    bool MaxVision = false;
    float PrevPlayerSpeed = 1.f;
    float PlayerSpeed = 1.f;
    bool UnlockVents = false;
    bool ShowGhosts = false;

    bool RevealImpostors = false;
    int PrevKillDistance = 0;
    int KillDistance = 0;
    int PrevTaskBarUpdates = 0;
    int TaskBarUpdates = 0;

    bool NoClip = false;
    bool HotkeyNoClip = false;

    bool DisableLights = false;

    bool MoveInVent = false;

    PlayerSelection selectedPlayer;
    std::queue<RPCInterface*> rpcQueue;
    std::queue<RPCInterface*> lobbyRpcQueue;

    bool ShowRadar = false;
    bool ShowRadar_DeadBodies = false;
    bool ShowRadar_Ghosts = false;
    bool ShowHud = true;
    bool HideRadar_During_Meetings = false;
    bool ShowRadar_RightClick_Teleport = false;
    bool LockRadar = false;

    bool ShowEsp = false;
    bool ShowEsp_Ghosts = true;
    bool ShowEsp_Box = true;
    bool ShowEsp_Tracers = true;
    bool ShowEsp_Distance = true;
    bool HideEsp_During_Meetings = false;

    bool InMeeting = false;
    bool PlayMedbayScan = false;

    bool ChatAlwaysActive = false;
    bool ChatActiveOriginalState = false;
    bool ReadGhostMessages = false;

    SystemTypes__Enum selectedDoor;
    std::vector<SystemTypes__Enum> mapDoors;
    std::vector<SystemTypes__Enum> pinnedDoors;
    bool CloseAllDoors = false;

    bool ShowConsole = false;
    std::vector<EventInterface*> consoleEvents;
    std::vector<EventInterface*> events[15][EVENT_TYPES_SIZE];

    std::bitset<0xFF> voteMonitor;

    std::vector<int32_t> aumUsers;
    int32_t rpcCooldown = 15;
    int32_t playerKilledId = 0;

    std::vector<PlayerControl*> impostors = { nullptr, nullptr, nullptr };
    int mapHostChoice = -1;
    int impostors_amount = 0;

    bool Wallhack = false;
    bool FreeCam = false;
    float FreeCamSpeed = 1.f;

    float CameraHeight = 3.0;
    Camera* FollowerCam = nullptr;
    bool EnableZoom = false;

    bool FakeCameraUsage = false;

    ImVec4 SelectedColor = ImVec4(0.502f, 0.075f, 0.256f, 0.5f);

	int SelectedColorId = 0;
    std::string originalName = "-";
    uint32_t originalSkin = 0xFF;
    uint32_t originalHat = 0xFF;
    uint32_t originalPet = 0xFF;
    uint8_t originalColor = 0xFF;

    bool activeImpersonation = false;

    PlayerSelection playerToFollow;

    Vector3 camPos = { NULL, NULL, NULL };
    Vector3 prevCamPos = { NULL, NULL, NULL };

    bool FlipSkeld = false;

	bool OcclusionCulling = false;
    bool ShowUnityLogs = true;

    int LobbyTimer = -1;
    
    std::string userName = "";

    enum MapType : uint8_t
    {
        Ship = 0,
        Hq = 1,
        Pb = 2,
        Airship = 3,
        NotSet = 0xFF
    } mapType;

    bool AutoOpenDoors = false;

    void Load();
    void Save();
};

extern Settings State;