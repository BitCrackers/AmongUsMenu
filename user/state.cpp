#include "state.hpp"

Settings State;

const char* pSettings = "settings.json";

inline bool Settings::Exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void Settings::Load() {
	if (!Settings::Exists(pSettings))
		return;

	std::ifstream inSettings(pSettings);
	nlohmann::ordered_json j = nlohmann::ordered_json::parse(inSettings, NULL, false);
	
    j.at("ShowMenu").get_to(this->ShowMenu);
    j.at("KeyBinds").get_to(this->KeyBinds);
#ifdef _DEBUG
    j.at("ShowDebug").get_to(this->showDebugTab);
#endif
    j.at("SelectedColor_x").get_to(this->SelectedColor.x);
    j.at("SelectedColor_y").get_to(this->SelectedColor.y);
    j.at("SelectedColor_z").get_to(this->SelectedColor.z);

    j.at("ShowGhosts").get_to(this->ShowGhosts);
    j.at("ShowRadar").get_to(this->ShowRadar);
    j.at("ShowRadar_DeadBodies").get_to(this->ShowRadar_DeadBodies);
    j.at("ShowRadar_Ghosts").get_to(this->ShowRadar_Ghosts);
    j.at("HideRadar_During_Meetings").get_to(this->HideRadar_During_Meetings);
    j.at("ShowRadar_RightClick_Teleport").get_to(this->ShowRadar_RightClick_Teleport);
    j.at("Radar_Opacity").get_to(this->SelectedColor.w);

    j.at("MaxVision").get_to(this->MaxVision);
    j.at("Wallhack").get_to(this->Wallhack);
    j.at("UnlockVents").get_to(this->UnlockVents);
    j.at("RevealImpostors").get_to(this->RevealImpostors);
    j.at("ChatAlwaysActive").get_to(this->ChatAlwaysActive);
    j.at("ReadGhostMessages").get_to(this->ReadGhostMessages);

    j.at("ShowConsole").get_to(this->ShowConsole);
}

void Settings::Save() {
	nlohmann::ordered_json j = nlohmann::ordered_json{
        {"ShowMenu", this->ShowMenu},
        {"KeyBinds", this->KeyBinds},
#ifdef _DEBUG
        {"ShowDebug", this->showDebugTab},
#endif
        {"SelectedColor_x", this->SelectedColor.x},
        {"SelectedColor_y", this->SelectedColor.y},
        {"SelectedColor_z", this->SelectedColor.z},

        {"ShowGhosts", this->ShowGhosts},
        {"ShowRadar", this->ShowRadar},
        {"ShowRadar_DeadBodies", this->ShowRadar_DeadBodies},
        {"ShowRadar_Ghosts", this->ShowRadar_Ghosts},
        {"HideRadar_During_Meetings", this->HideRadar_During_Meetings},
        {"LockRadar", this->LockRadar},
        {"ShowRadar_RightClick_Teleport", this->ShowRadar_RightClick_Teleport},
        {"Radar_Opacity", this->SelectedColor.w},

        {"MaxVision", this->MaxVision},
        {"Wallhack", this->Wallhack},
        {"UnlockVents", this->UnlockVents},
        {"RevealImpostors", this->RevealImpostors},
        {"ChatAlwaysActive", this->ChatAlwaysActive},
        {"ReadGhostMessages", this->ReadGhostMessages},

        {"ShowConsole", this->ShowConsole}
    };

	std::ofstream outSettings(pSettings);
	outSettings << std::setw(4) << j << std::endl;
}