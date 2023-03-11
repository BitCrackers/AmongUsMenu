#include "pch-il2cpp.h"
#include "state.hpp"
#include <iostream>
#include <fstream>
#include "main.h"
#include "utility.h"
#include "logger.h"

Settings State;

void Settings::Load() {
    auto path = getModulePath(hModule);
    auto settingsPath = path.parent_path() / "settings.json";

    if (!std::filesystem::exists(settingsPath))
        return;

    try {
        std::ifstream inSettings(settingsPath);
        nlohmann::ordered_json j = nlohmann::ordered_json::parse(inSettings, NULL, false);

#define JSON_TRYGET(key, value) \
        try { \
            j.at(key).get_to(value); \
        } catch (nlohmann::detail::out_of_range& e) { \
            Log.Info(e.what()); \
        }

        JSON_TRYGET("ShowMenu", this->ShowMenu);
        JSON_TRYGET("KeyBinds", this->KeyBinds);
#ifdef _DEBUG
        JSON_TRYGET("ShowDebug", this->showDebugTab);
#endif

        JSON_TRYGET("PlayerSpeed", this->PlayerSpeed);
        JSON_TRYGET("CameraHeight", this->CameraHeight);
        JSON_TRYGET("FreeCamSpeed", this->FreeCamSpeed);
        JSON_TRYGET("UserName", this->userName);
        JSON_TRYGET("ShowGhosts", this->ShowGhosts);
        JSON_TRYGET("ShowRadar", this->ShowRadar);
        JSON_TRYGET("ShowRadar_DeadBodies", this->ShowRadar_DeadBodies);
        JSON_TRYGET("ShowRadar_Ghosts", this->ShowRadar_Ghosts);
        JSON_TRYGET("HideRadar_During_Meetings", this->HideRadar_During_Meetings);
        JSON_TRYGET("ShowRadar_RightClick_Teleport", this->ShowRadar_RightClick_Teleport);
        JSON_TRYGET("LockRadar", this->LockRadar);
        JSON_TRYGET("RadarColor_R", this->SelectedColor.x);
        JSON_TRYGET("RadarColor_G", this->SelectedColor.y);
        JSON_TRYGET("RadarColor_B", this->SelectedColor.z);
        JSON_TRYGET("RadarColor_A", this->SelectedColor.w);
        JSON_TRYGET("RadarDrawIcons", this->RadarDrawIcons);

        JSON_TRYGET("ShowReplay", this->ShowReplay);
        JSON_TRYGET("ReplayColor_R", this->SelectedReplayMapColor.x);
        JSON_TRYGET("ReplayColor_G", this->SelectedReplayMapColor.y);
        JSON_TRYGET("ReplayColor_B", this->SelectedReplayMapColor.z);
        JSON_TRYGET("ReplayColor_A", this->SelectedReplayMapColor.w);
        JSON_TRYGET("ReplayShowOnlyLastSeconds", this->Replay_ShowOnlyLastSeconds);
        JSON_TRYGET("ReplayLastSecondsValue", this->Replay_LastSecondsValue);
        JSON_TRYGET("ReplayClearAfterMeeting", this->Replay_ClearAfterMeeting);

        JSON_TRYGET("ShowEsp", this->ShowEsp);
        JSON_TRYGET("ShowEsp_Ghosts", this->ShowEsp_Ghosts);
        JSON_TRYGET("ShowEsp_Box", this->ShowEsp_Box);
        JSON_TRYGET("ShowEsp_Tracers", this->ShowEsp_Tracers);
        JSON_TRYGET("ShowEsp_Distance", this->ShowEsp_Distance);
        JSON_TRYGET("HideEsp_During_Meetings", this->HideEsp_During_Meetings);
        JSON_TRYGET("ShowEsp_RoleBased", this->ShowEsp_RoleBased);

        JSON_TRYGET("MaxVision", this->MaxVision);
        JSON_TRYGET("Wallhack", this->Wallhack);
        JSON_TRYGET("UnlockVents", this->UnlockVents);
        JSON_TRYGET("ChatPaste", this->ChatPaste);
        JSON_TRYGET("RevealRoles", this->RevealRoles);
        JSON_TRYGET("AbbreviatedRoleNames", this->AbbreviatedRoleNames);
        JSON_TRYGET("ChatAlwaysActive", this->ChatAlwaysActive);
        JSON_TRYGET("ReadGhostMessages", this->ReadGhostMessages);
        JSON_TRYGET("AutoOpenDoors", this->AutoOpenDoors);
        JSON_TRYGET("MoveInVent", this->MoveInVent);

        JSON_TRYGET("AdjustByDPI", this->AdjustByDPI);

        JSON_TRYGET("RevealVotes", this->RevealVotes);
        JSON_TRYGET("ShowProtections", this->ShowProtections);

        JSON_TRYGET("ShowConsole", this->ShowConsole);
        JSON_TRYGET("ShowUnityLogs", this->ShowUnityLogs);

        JSON_TRYGET("RevealAnonymousVotes", this->RevealAnonymousVotes);

        JSON_TRYGET("ShowChat", this->ShowChat);
        JSON_TRYGET("RightClickTeleport", this->RightClickTeleport);
        JSON_TRYGET("ShowKillCD", this->ShowKillCD);
    } catch (...) {
        Log.Info("Unable to load settings.json");
    }

    //Do not do any IL2CPP stuff here!  The constructors of most classes have not run yet!
}

void Settings::Save() {
    auto path = getModulePath(hModule);
    auto settingsPath = path.parent_path() / "settings.json";

    try {
        nlohmann::ordered_json j = nlohmann::ordered_json{
            {"ShowMenu", this->ShowMenu},
            {"KeyBinds", this->KeyBinds},
    #ifdef _DEBUG
            {"ShowDebug", this->showDebugTab},
    #endif

            {"PlayerSpeed", this->PlayerSpeed},
            {"CameraHeight", this->CameraHeight},
            {"FreeCamSpeed", this->FreeCamSpeed},
            {"UserName", this->userName},
            {"ShowGhosts", this->ShowGhosts},
            {"ShowRadar", this->ShowRadar},
            {"ShowRadar_DeadBodies", this->ShowRadar_DeadBodies},
            {"ShowRadar_Ghosts", this->ShowRadar_Ghosts},
            {"HideRadar_During_Meetings", this->HideRadar_During_Meetings},
            {"LockRadar", this->LockRadar},
            {"ShowRadar_RightClick_Teleport", this->ShowRadar_RightClick_Teleport},
            {"RadarColor_R", this->SelectedColor.x},
            {"RadarColor_G", this->SelectedColor.y},
            {"RadarColor_B", this->SelectedColor.z},
            {"RadarColor_A", this->SelectedColor.w},
            {"RadarDrawIcons", this->RadarDrawIcons},

            {"ShowReplay", this->ShowReplay},
            {"ReplayColor_R", this->SelectedReplayMapColor.x},
            {"ReplayColor_G", this->SelectedReplayMapColor.y},
            {"ReplayColor_B", this->SelectedReplayMapColor.z},
            {"ReplayColor_A", this->SelectedReplayMapColor.w},
            {"ReplayShowOnlyLastSeconds", this->Replay_ShowOnlyLastSeconds},
            {"ReplayLastSecondsValue", this->Replay_LastSecondsValue},
            {"ReplayClearAfterMeeting", this->Replay_ClearAfterMeeting},

            {"ShowEsp", this->ShowEsp},
            {"ShowEsp_Ghosts", this->ShowEsp_Ghosts},
            {"ShowEsp_Box", this->ShowEsp_Box},
            {"ShowEsp_Tracers", this->ShowEsp_Tracers},
            {"ShowEsp_Distance", this->ShowEsp_Distance},
            {"HideEsp_During_Meetings", this->HideEsp_During_Meetings},
            {"ShowEsp_RoleBased", this->ShowEsp_RoleBased},

            {"MaxVision", this->MaxVision},
            {"Wallhack", this->Wallhack},
            {"UnlockVents", this->UnlockVents},
            {"ChatPaste", this->ChatPaste},
            {"RevealRoles", this->RevealRoles},
            {"AbbreviatedRoleNames", this->AbbreviatedRoleNames},
            {"ChatAlwaysActive", this->ChatAlwaysActive},
            {"ReadGhostMessages", this->ReadGhostMessages},
            {"AutoOpenDoors", this->AutoOpenDoors},
            {"MoveInVent", this->MoveInVent},

            {"RevealVotes", this->RevealVotes},
            {"RevealAnonymousVotes", this->RevealAnonymousVotes},
            {"AdjustByDPI", this->AdjustByDPI},
            {"ShowProtections", this->ShowProtections},

            {"ShowConsole", this->ShowConsole},
            {"ShowUnityLogs", this->ShowUnityLogs},

            {"ShowChat", this->ShowChat},
            {"RightClickTeleport", this->RightClickTeleport},
            {"ShowKillCD", this->ShowKillCD},
        };

        std::ofstream outSettings(settingsPath);
        outSettings << std::setw(4) << j << std::endl;
    } catch (...) {
        Log.Info("Unable to save settings.json");
    }
}
