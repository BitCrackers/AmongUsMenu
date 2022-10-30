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
        VK_DELETE, // toggle menu
        VK_INSERT, // toggle radar
        VK_HOME, // toggle console
        VK_NEXT, // repair sabotage
        0x00, // noclip
        0x00, // close all doors
        0x00, // toggle zoom
        0x00, // toggle freecam
        0x00, // close current room door
        VK_END // toggle replay
    };

    bool ImGuiInitialized = false;
    bool ShowMenu = false;

#ifdef _DEBUG
    bool showDebugTab = false;
#endif

    bool AdjustByDPI = true;
    float dpiScale = 1.f;
    bool dpiChanged = false;

    std::string CurrentScene;

    bool MaxVision = false;
    float PrevPlayerSpeed = 1.f;
    float PlayerSpeed = 1.f;
    bool UnlockVents = false;
    bool ShowGhosts = false;

    bool ShowProtections = false;
    std::map<Game::PlayerId, std::pair<Game::ColorId, float/*Time*/>> protectMonitor;
    std::mutex protectMutex;

    bool RevealVotes = false;
    bool RevealAnonymousVotes = false;

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
    bool ShowEsp_RoleBased = false;

    bool InMeeting = false;
    bool PlayMedbayScan = false;

    bool ChatAlwaysActive = false;
    bool ChatActiveOriginalState = false;
    bool ReadGhostMessages = false;

    SystemTypes__Enum selectedDoor = SystemTypes__Enum::Hallway;
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
    // NOTE:
    // any code that modifies State.liveReplayEvents or any other collection should use the Replay.replayEventMutex
    // failure to do so will invalidate any existing iterator of any thread which will lead to rare and hard to diagnose crashes
    std::vector<std::unique_ptr<EventInterface>> liveReplayEvents;
    std::array<ImVec2, Game::MAX_PLAYERS> lastWalkEventPosPerPlayer;
    std::array<std::chrono::system_clock::time_point, Game::MAX_PLAYERS> replayDeathTimePerPlayer;
    std::map<Game::PlayerId, Replay::WalkEvent_LineData> replayWalkPolylineByPlayer;
    bool Replay_IsPlaying = true;
    bool Replay_IsLive = true;

    std::map<Game::Voter, Game::VotedFor> voteMonitor;

    std::vector<Game::PlayerId> aumUsers;
    int32_t rpcCooldown = 15;
    int32_t playerKilledId = 0;

    std::array<PlayerControl*, Game::MAX_PLAYERS> assignedRolesPlayer = {};
    std::array<RoleType, Game::MAX_PLAYERS> assignedRoles = {};
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

    Game::ColorId SelectedColorId = 0; // Red
    std::string originalName = "-";
    String* originalNamePlate = nullptr;
    String* originalSkin = nullptr;
    String* originalHat = nullptr;
    String* originalVisor = nullptr;
    String* originalPet = nullptr;
    Game::ColorId originalColor = Game::NoColorId;

    bool activeImpersonation = false;

    PlayerSelection playerToFollow;

    Vector3 camPos = { NULL, NULL, NULL };
    Vector3 prevCamPos = { NULL, NULL, NULL };

    bool FlipSkeld = false;

	bool OcclusionCulling = false;
    bool ShowUnityLogs = true;

    int LobbyTimer = -1;

    std::string userName = "";

    bool ShowChat = false;
    bool newChatMessage = false;
    std::vector<std::unique_ptr<RpcChatMessage>> chatMessages;

    enum class MapType : uint8_t
    {
        Ship = 0,
        Hq = 1,
        Pb = 2,
        Airship = 3
    } mapType = MapType::Ship;

    bool AutoOpenDoors = false;

    Settings()
    {
        Replay::Reset();
    }

    void Load();
    void Save();
};

extern Settings State;