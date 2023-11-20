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
        JSON_TRYGET("RgbTheme", this->RgbMenuTheme);
        JSON_TRYGET("SetName", this->SetName);
        JSON_TRYGET("MenuThemeColor_R", this->MenuThemeColor.x);
        JSON_TRYGET("MenuThemeColor_G", this->MenuThemeColor.y);
        JSON_TRYGET("MenuThemeColor_B", this->MenuThemeColor.z);
        JSON_TRYGET("MenuThemeColor_A", this->MenuThemeColor.w);
        JSON_TRYGET("UnlockCosmetics", this->UnlockCosmetics);
        JSON_TRYGET("SetLevel", this->SetLevel);
        JSON_TRYGET("FakeLevel", this->FakeLevel);
        JSON_TRYGET("ShowKeybinds", this->ShowKeybinds);
        JSON_TRYGET("HideFriendCode", this->HideFriendCode);

        JSON_TRYGET("SelectedColorId", this->SelectedColorId);
        JSON_TRYGET("SnipeColor", this->SnipeColor);
        JSON_TRYGET("CycleBetweenPlayers", this->CycleBetweenPlayers);
        JSON_TRYGET("CycleInMeeting", this->CycleInMeeting);
        JSON_TRYGET("CycleTimer", this->CycleTimer);
        JSON_TRYGET("CyclerUserNames", this->cyclerUserNames);
        JSON_TRYGET("HostUsername", this->hostUserName);
        JSON_TRYGET("ChatMessage", this->chatMessage);
        JSON_TRYGET("CycleName", this->CycleName);
        JSON_TRYGET("CycleColor", this->RandomColor);
        JSON_TRYGET("CycleHat", this->RandomHat);
        JSON_TRYGET("CycleVisor", this->RandomVisor);
        JSON_TRYGET("CycleSkin", this->RandomSkin);
        JSON_TRYGET("CyclePet", this->RandomPet);
        JSON_TRYGET("CycleNamePlate", this->RandomNamePlate);
        JSON_TRYGET("PlayerSpeed", this->PlayerSpeed);
        JSON_TRYGET("MultiplySpeed", this->MultiplySpeed);
        JSON_TRYGET("KillDistance", this->KillDistance);
        JSON_TRYGET("ModifyKillDistance", this->ModifyKillDistance);
        JSON_TRYGET("ModifyTaskBarUpdates", this->ModifyTaskBarUpdates);
        JSON_TRYGET("UserName", this->userName);
        JSON_TRYGET("ShowGhosts", this->ShowGhosts);
        JSON_TRYGET("ShowRadar", this->ShowRadar);
        JSON_TRYGET("ShowRadar_DeadBodies", this->ShowRadar_DeadBodies);
        JSON_TRYGET("ShowRadar_Ghosts", this->ShowRadar_Ghosts);
        JSON_TRYGET("HideRadar_During_Meetings", this->HideRadar_During_Meetings);
        JSON_TRYGET("ShowRadar_RightClickTP", this->ShowRadar_RightClickTP);
        JSON_TRYGET("LockRadar", this->LockRadar);
        JSON_TRYGET("RadarColor_R", this->SelectedColor.x);
        JSON_TRYGET("RadarColor_G", this->SelectedColor.y);
        JSON_TRYGET("RadarColor_B", this->SelectedColor.z);
        JSON_TRYGET("RadarColor_A", this->SelectedColor.w);
        JSON_TRYGET("RadarDrawIcons", this->RadarDrawIcons);
        JSON_TRYGET("RadarVisorRoleColor", this->RadarVisorRoleColor);
        JSON_TRYGET("RadarBorder", this->RadarBorder);
        JSON_TRYGET("RadarExtraWidth", this->RadarExtraWidth);
        JSON_TRYGET("RadarExtraHeight", this->RadarExtraHeight);

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
        JSON_TRYGET("ShowEsp_Crew", this->ShowEsp_Crew);
        JSON_TRYGET("ShowEsp_Imp", this->ShowEsp_Imp);

        JSON_TRYGET("MaxVision", this->MaxVision);
        JSON_TRYGET("Wallhack", this->Wallhack);
        JSON_TRYGET("FreeCamSpeed", this->FreeCamSpeed);
        JSON_TRYGET("ZoomLevel", this->CameraHeight);
        JSON_TRYGET("UnlockVents", this->UnlockVents);
        JSON_TRYGET("ChatPaste", this->ChatPaste);
        JSON_TRYGET("RevealRoles", this->RevealRoles);
        JSON_TRYGET("AbbreviatedRoleNames", this->AbbreviatedRoleNames);
        JSON_TRYGET("PlayerColoredDots", this->PlayerColoredDots);
        JSON_TRYGET("ShowPlayerInfo", this->ShowPlayerInfo);
        JSON_TRYGET("ChatAlwaysActive", this->ChatAlwaysActive);
        JSON_TRYGET("ReadGhostMessages", this->ReadGhostMessages);
        JSON_TRYGET("CustomName", this->CustomName);
        JSON_TRYGET("RgbName", this->RgbName);
        JSON_TRYGET("ResizeName", this->ResizeName);
        JSON_TRYGET("ItalicName", this->ItalicName);
        JSON_TRYGET("UnderlineName", this->UnderlineName);
        JSON_TRYGET("StrikethroughName", this->StrikethroughName);
        JSON_TRYGET("ColoredName", this->ColoredName);
        JSON_TRYGET("NameColor1_R", this->NameColor1.x);
        JSON_TRYGET("NameColor1_G", this->NameColor1.y);
        JSON_TRYGET("NameColor1_B", this->NameColor1.z);
        JSON_TRYGET("NameColor1_A", this->NameColor1.w);
        JSON_TRYGET("NameColor2_R", this->NameColor2.x);
        JSON_TRYGET("NameColor2_G", this->NameColor2.y);
        JSON_TRYGET("NameColor2_B", this->NameColor2.z);
        JSON_TRYGET("NameColor2_A", this->NameColor2.w);
        JSON_TRYGET("AutoOpenDoors", this->AutoOpenDoors);
        JSON_TRYGET("MoveInVent", this->MoveInVent);
        JSON_TRYGET("AlwaysMove", this->AlwaysMove);
        JSON_TRYGET("AnimationlessShapeshift", this->AnimationlessShapeshift);
        JSON_TRYGET("DisableKillAnimation", this->DisableKillAnimation);
        JSON_TRYGET("KillImpostors", this->KillImpostors);
        JSON_TRYGET("KillThroughWalls", this->KillThroughWalls);
        JSON_TRYGET("InfiniteKillRange", this->InfiniteKillRange);
        JSON_TRYGET("FakeAlive", this->FakeAlive);
        JSON_TRYGET("ShowHost", this->ShowHost);
        JSON_TRYGET("ShowVoteKicks", this->ShowVoteKicks);
        JSON_TRYGET("DoTasksAsImpostor", this->DoTasksAsImpostor);
        JSON_TRYGET("NoClip", this->NoClip);

        JSON_TRYGET("AdjustByDPI", this->AdjustByDPI);

        JSON_TRYGET("RevealVotes", this->RevealVotes);
        JSON_TRYGET("ShowProtections", this->ShowProtections);

        JSON_TRYGET("CustomImpostorAmount", this->CustomImpostorAmount);
        JSON_TRYGET("ImpostorCount", this->ImpostorCount);

        JSON_TRYGET("ShowConsole", this->ShowConsole);
        JSON_TRYGET("ShowUnityLogs", this->ShowUnityLogs);
        JSON_TRYGET("ShowChat", this->ShowChat);

        JSON_TRYGET("RevealAnonymousVotes", this->RevealAnonymousVotes);

        JSON_TRYGET("ShiftRightClickTP", this->ShiftRightClickTP);
        JSON_TRYGET("RotateRadius", this->RotateRadius);
        JSON_TRYGET("ShowKillCD", this->ShowKillCD);

        JSON_TRYGET("Confuser", this->confuser);
        JSON_TRYGET("ConfuseOnJoin", this->confuseOnJoin);
        JSON_TRYGET("ConfuseOnStart", this->confuseOnStart);
        JSON_TRYGET("ConfuseOnKill", this->confuseOnKill);
        JSON_TRYGET("ConfuseOnVent", this->confuseOnVent);
        JSON_TRYGET("ConfuseOnMeeting", this->confuseOnMeeting);

        JSON_TRYGET("CyclerNameGeneration", this->cyclerNameGeneration);
        JSON_TRYGET("ConfuserNameGeneration", this->confuserNameGeneration);

        JSON_TRYGET("CustomCode", this->customCode);
        JSON_TRYGET("HideCode", this->HideCode);
        JSON_TRYGET("RgbLobbyCode", this->RgbLobbyCode);
    } catch (...) {
        Log.Info("Unable to load settings.json");
    }

    //Do not do any IL2CPP stuff here!  The constructors of most classes have not run yet!
}

void Settings::Save() {
    auto path = getModulePath(hModule);
    auto settingsPath = path.parent_path() / "settings.json";

    try {
        nlohmann::ordered_json j = nlohmann::ordered_json {
            { "ShowMenu", this->ShowMenu },
            { "KeyBinds", this->KeyBinds },
    #ifdef _DEBUG
            { "ShowDebug", this->showDebugTab },
    #endif
            { "RgbTheme", this->RgbMenuTheme },
            { "SetName", this->SetName },
            { "MenuThemeColor_R", this->MenuThemeColor.x },
            { "MenuThemeColor_G", this->MenuThemeColor.y },
            { "MenuThemeColor_B", this->MenuThemeColor.z },
            { "MenuThemeColor_A", this->MenuThemeColor.w },
            { "UnlockCosmetics", this->UnlockCosmetics },
            { "SetLevel", this->SetLevel },
            { "FakeLevel", this->FakeLevel },
            { "ShowKeybinds", this->ShowKeybinds },
            { "HideFriendCode", this->HideFriendCode },

            { "SelectedColorId", this->SelectedColorId },
            { "SnipeColor", this->SnipeColor },
            { "CycleBetweenPlayers", this->CycleBetweenPlayers },
            { "CycleInMeeting", this->CycleInMeeting },
            { "CycleTimer", this->CycleTimer },
            { "CyclerUserNames", this->cyclerUserNames },
            { "HostUsername", this->hostUserName },
            { "ChatMessage", this->chatMessage },
            { "CycleName", this->CycleName },
            { "CycleColor", this->RandomColor },
            { "CycleHat", this->RandomHat },
            { "CycleVisor", this->RandomVisor },
            { "CycleSkin", this->RandomSkin },
            { "CyclePet", this->RandomPet },
            { "CycleNamePlate", this->RandomNamePlate },

            { "PlayerSpeed", this->PlayerSpeed },
            { "MultiplySpeed", this->MultiplySpeed },
            { "KillDistance", this->KillDistance },
            { "ModifyKillDistance", this->ModifyKillDistance },
            { "ModifyTaskBarUpdates", this->ModifyTaskBarUpdates },
            { "UserName", this->userName },
            { "ShowGhosts", this->ShowGhosts },
            { "ShowRadar", this->ShowRadar },
            { "ShowRadar_DeadBodies", this->ShowRadar_DeadBodies },
            { "ShowRadar_Ghosts", this->ShowRadar_Ghosts },
            { "HideRadar_During_Meetings", this->HideRadar_During_Meetings },
            { "LockRadar", this->LockRadar },
            { "ShowRadar_RightClickTP", this->ShowRadar_RightClickTP },
            { "RadarColor_R", this->SelectedColor.x },
            { "RadarColor_G", this->SelectedColor.y },
            { "RadarColor_B", this->SelectedColor.z },
            { "RadarColor_A", this->SelectedColor.w },
            { "RadarDrawIcons", this->RadarDrawIcons },
            { "RadarVisorRoleColor", this->RadarVisorRoleColor },
            { "RadarBorder", this->RadarBorder },
            { "RadarExtraWidth", this->RadarExtraWidth },
            { "RadarExtraHeight", this->RadarExtraHeight },

            { "ShowReplay", this->ShowReplay },
            { "ReplayColor_R", this->SelectedReplayMapColor.x },
            { "ReplayColor_G", this->SelectedReplayMapColor.y },
            { "ReplayColor_B", this->SelectedReplayMapColor.z },
            { "ReplayColor_A", this->SelectedReplayMapColor.w },
            { "ReplayShowOnlyLastSeconds", this->Replay_ShowOnlyLastSeconds },
            { "ReplayLastSecondsValue", this->Replay_LastSecondsValue },
            { "ReplayClearAfterMeeting", this->Replay_ClearAfterMeeting },

            { "ShowEsp", this->ShowEsp },
            { "ShowEsp_Ghosts", this->ShowEsp_Ghosts },
            { "ShowEsp_Box", this->ShowEsp_Box },
            { "ShowEsp_Tracers", this->ShowEsp_Tracers },
            { "ShowEsp_Distance", this->ShowEsp_Distance },
            { "HideEsp_During_Meetings", this->HideEsp_During_Meetings },
            { "ShowEsp_RoleBased", this->ShowEsp_RoleBased },
            { "ShowEsp_Crew", this->ShowEsp_Crew },
            { "ShowEsp_Imp", this->ShowEsp_Imp },

            { "MaxVision", this->MaxVision },
            { "Wallhack", this->Wallhack },
            { "FreeCamSpeed", this->FreeCamSpeed },
            { "ZoomLevel", this->CameraHeight },
            { "UnlockVents", this->UnlockVents },
            { "ChatPaste", this->ChatPaste },
            { "RevealRoles", this->RevealRoles },
            { "AbbreviatedRoleNames", this->AbbreviatedRoleNames },
            { "PlayerColoredDots", this->PlayerColoredDots },
            { "ShowPlayerInfo", this->ShowPlayerInfo },
            { "ChatAlwaysActive", this->ChatAlwaysActive },
            { "ReadGhostMessages", this->ReadGhostMessages },
            { "CustomName", this->CustomName },
            { "RgbName", this->RgbName },
            { "ResizeName", this->ResizeName },
            { "ItalicName", this->ItalicName },
            { "UnderlineName", this->UnderlineName },
            { "StrikethroughName", this->StrikethroughName },
            { "ColoredName", this->ColoredName },
            { "NameColor1_R", this->NameColor1.x },
            { "NameColor1_G", this->NameColor1.y },
            { "NameColor1_B", this->NameColor1.z },
            { "NameColor1_A", this->NameColor1.w },
            { "NameColor2_R", this->NameColor2.x },
            { "NameColor2_G", this->NameColor2.y },
            { "NameColor2_B", this->NameColor2.z },
            { "NameColor2_A", this->NameColor2.w },
            { "AutoOpenDoors", this->AutoOpenDoors },
            { "MoveInVent", this->MoveInVent },
            { "AlwaysMove", this->AlwaysMove },
            { "AnimationlessShapeshift", this->AnimationlessShapeshift },
            { "DisableKillAnimation", this->DisableKillAnimation },
            { "KillImpostors", this->KillImpostors },
            { "KillThroughWalls", this->KillThroughWalls },
            { "InfiniteKillRange", this->InfiniteKillRange },
            { "FakeAlive", this->FakeAlive },
            { "ShowHost", this->ShowHost },
            { "ShowVoteKicks", this->ShowVoteKicks },
            { "DoTasksAsImpostor", this->DoTasksAsImpostor },
            { "NoClip", this->NoClip },

            { "RevealVotes", this->RevealVotes },
            { "RevealAnonymousVotes", this->RevealAnonymousVotes },
            { "AdjustByDPI", this->AdjustByDPI },
            { "ShowProtections", this->ShowProtections },

            { "CustomImpostorAmount", this->CustomImpostorAmount },
            { "ImpostorCount", this->ImpostorCount },

            { "ShowConsole", this->ShowConsole },
            { "ShowUnityLogs", this->ShowUnityLogs },
            { "ShowChat", this->ShowChat },

            { "ShiftRightClickTP", this->ShiftRightClickTP },
            { "RotateRadius", this->RotateRadius },
            { "ShowKillCD", this->ShowKillCD },

            { "Confuser", this->confuser },
            { "ConfuseOnJoin", this->confuseOnJoin },
            { "ConfuseOnStart", this->confuseOnStart },
            { "ConfuseOnKill", this->confuseOnKill },
            { "ConfuseOnVent", this->confuseOnVent },
            { "ConfuseOnMeeting", this->confuseOnMeeting },

            { "CyclerNameGeneration", this->cyclerNameGeneration },
            { "ConfuserNameGeneration", this->confuserNameGeneration },

            { "CustomCode", this->customCode },
            { "HideCode", this->HideCode },
            { "RgbLobbyCode", this->RgbLobbyCode },
        };

        std::ofstream outSettings(settingsPath);
        outSettings << std::setw(4) << j << std::endl;
    } catch (...) {
        Log.Info("Unable to save settings.json");
    }
}
