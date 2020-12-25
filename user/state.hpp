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

    bool AntiBan = false;

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

    bool InMeeting = false;
    bool PlayMedbayScan = false;

    bool ChatAlwaysActive = false;
    bool ReadGhostMessages = false;

    SystemTypes__Enum selectedDoor;
    std::vector<SystemTypes__Enum> mapDoors;
    std::vector<SystemTypes__Enum> pinnedDoors;
    bool CloseAllDoors = false;

    bool ShowConsole = false;
    std::vector<EventInterface*> events;

    std::bitset<0xFF> voteMonitor;

    std::vector<PlayerControl*> impostors = { nullptr, nullptr, nullptr };
    int map = -1;
    ShipStatus_MapType__Enum previousMap = (ShipStatus_MapType__Enum)0;
    int impostors_amount = 0;

    bool Wallhack = false;
    bool FreeCam = false;
    float FreeCamSpeed = 1.f;

    float CameraHeight = 3.0;
    Camera* FollowerCam = nullptr;
    bool EnableZoom = false;

    ImVec4 SelectedColor = ImVec4(0.502f, 0.075f, 0.256f, 0.5f);

	int SelectedColorId = 0;
    std::string originalName = "-";

	PlayerSelection playerToFollow;

    Vector3 camPos = { NULL, NULL, NULL };
    Vector3 prevCamPos = { NULL, NULL, NULL };

    bool FlipSkeld = false;

    int LobbyTimer = -1;

    void Load();
    void Save();
};

extern Settings State;