#pragma once
#include <bitset>
#include <queue>
#include "_events.h"
#include "_rpc.h"
#include "keybinds.h"
#include "game.h"
#include "replay.hpp"

class Settings {
public:

    KeyBinds::Config KeyBinds = {
        VK_DELETE,
        VK_INSERT,
        VK_HOME,
        VK_NEXT,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        VK_END
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

    bool RevealRoles = false;
    bool AbbreviatedRoleNames = false;
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
    bool RadarDrawIcons = true;

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
    bool ShowReplay = false;
    bool Replay_ShowOnlyLastSeconds = false;
    int Replay_LastSecondsValue = 1;
    bool Replay_ClearAfterMeeting = false;
    std::chrono::system_clock::time_point MatchStart;
    std::chrono::system_clock::time_point MatchCurrent;
    std::chrono::system_clock::time_point MatchEnd;
    std::chrono::system_clock::time_point MatchLive;
    std::vector<std::unique_ptr<EventInterface>> rawEvents;
    std::vector<std::unique_ptr<EventInterface>> liveReplayEvents;
    std::vector<ImVec2> lastWalkEventPosPerPlayer;
    std::map<int, Replay::WalkEvent_LineData> replayWalkPolylineByPlayer;
    bool Replay_IsPlaying = true;
    bool Replay_IsLive = true;

    std::bitset<0xFF> voteMonitor;

    std::vector<int32_t> aumUsers;
    int32_t rpcCooldown = 15;
    int32_t playerKilledId = 0;

    std::vector<PlayerControl*> assignedRolesPlayer = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    std::vector<int> assignedRoles = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int mapHostChoice = -1;
    int impostors_amount = 0;
    int shapeshifters_amount = 0;
    int engineers_amount = 0;
    int scientists_amount = 0;

    bool Wallhack = false;
    bool FreeCam = false;
    float FreeCamSpeed = 1.f;

    float CameraHeight = 3.0;
    Camera* FollowerCam = nullptr;
    bool EnableZoom = false;

    bool FakeCameraUsage = false;

    ImVec4 SelectedColor = ImVec4(1.f, 1.f, 1.f, 0.75f);
    ImVec4 SelectedReplayMapColor = ImVec4(1.f, 1.f, 1.f, 0.75f);

	int SelectedColorId = 0;
    std::string originalName = "-";
    String* originalNamePlate = nullptr;
    String* originalSkin = nullptr;
    String* originalHat = nullptr;
    String* originalVisor = nullptr;
    String* originalPet = nullptr;
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
        Airship = 3
    } mapType;

    bool AutoOpenDoors = false;

    Settings()
    {
        for (int plyIdx = 0; plyIdx < MAX_PLAYERS; plyIdx++)
        {
            this->lastWalkEventPosPerPlayer.push_back(ImVec2(0.f, 0.f));
        }
    }

    void Load();
    void Save();
};

extern Settings State;