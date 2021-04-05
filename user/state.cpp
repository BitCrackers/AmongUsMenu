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

        j.at("ShowMenu").get_to(this->ShowMenu);
        j.at("KeyBinds").get_to(this->KeyBinds);
#ifdef _DEBUG
        j.at("ShowDebug").get_to(this->showDebugTab);
#endif

        j.at("ShowGhosts").get_to(this->ShowGhosts);
        j.at("ShowRadar").get_to(this->ShowRadar);
        j.at("ShowRadar_DeadBodies").get_to(this->ShowRadar_DeadBodies);
        j.at("ShowRadar_Ghosts").get_to(this->ShowRadar_Ghosts);
        j.at("HideRadar_During_Meetings").get_to(this->HideRadar_During_Meetings);
        j.at("ShowRadar_RightClick_Teleport").get_to(this->ShowRadar_RightClick_Teleport);
        j.at("LockRadar").get_to(this->LockRadar);
        j.at("RadarColor_R").get_to(this->SelectedColor.x);
        j.at("RadarColor_G").get_to(this->SelectedColor.y);
        j.at("RadarColor_B").get_to(this->SelectedColor.z);
        j.at("RadarColor_A").get_to(this->SelectedColor.w);

        j.at("ShowEsp").get_to(this->ShowEsp);
        j.at("ShowEsp_Ghosts").get_to(this->ShowEsp_Ghosts);
        j.at("ShowEsp_Box").get_to(this->ShowEsp_Box);
        j.at("ShowEsp_Tracers").get_to(this->ShowEsp_Tracers);
        j.at("ShowEsp_Distance").get_to(this->ShowEsp_Distance);
        j.at("HideEsp_During_Meetings").get_to(this->HideEsp_During_Meetings);

        j.at("MaxVision").get_to(this->MaxVision);
        j.at("Wallhack").get_to(this->Wallhack);
        j.at("UnlockVents").get_to(this->UnlockVents);
        j.at("RevealImpostors").get_to(this->RevealImpostors);
        j.at("ChatAlwaysActive").get_to(this->ChatAlwaysActive);
        j.at("ReadGhostMessages").get_to(this->ReadGhostMessages);
        j.at("AutoOpenDoors").get_to(this->AutoOpenDoors);
        j.at("MoveInVent").get_to(this->MoveInVent);

        j.at("ShowConsole").get_to(this->ShowConsole);
        j.at("ShowUnityLogs").get_to(this->ShowUnityLogs);
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

            {"ShowEsp", this->ShowEsp},
            {"ShowEsp_Ghosts", this->ShowEsp_Ghosts},
            {"ShowEsp_Box", this->ShowEsp_Box},
            {"ShowEsp_Tracers", this->ShowEsp_Tracers},
            {"ShowEsp_Distance", this->ShowEsp_Distance},
            {"HideEsp_During_Meetings", this->HideEsp_During_Meetings},

            {"MaxVision", this->MaxVision},
            {"Wallhack", this->Wallhack},
            {"UnlockVents", this->UnlockVents},
            {"RevealImpostors", this->RevealImpostors},
            {"ChatAlwaysActive", this->ChatAlwaysActive},
            {"ReadGhostMessages", this->ReadGhostMessages},
            {"AutoOpenDoors", this->AutoOpenDoors},
            {"MoveInVent", this->MoveInVent},

            {"ShowConsole", this->ShowConsole},
            {"ShowUnityLogs", this->ShowUnityLogs}
        };

        std::ofstream outSettings(settingsPath);
        outSettings << std::setw(4) << j << std::endl;
    } catch (...) {
        Log.Info("Unable to save settings.json");
    }
}
