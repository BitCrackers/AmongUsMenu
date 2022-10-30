#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
#include "json.hpp"

namespace KeyBinds {
    struct Config {
        uint8_t Toggle_Menu;
        uint8_t Toggle_Radar;
        uint8_t Toggle_Console;
        uint8_t Repair_Sabotage;
        uint8_t Toggle_Noclip;
        uint8_t Close_All_Doors;
        uint8_t Toggle_Zoom;
        uint8_t Toggle_Freecam;
        uint8_t Close_Current_Room_Door;
        uint8_t Toggle_Replay;
        uint8_t Toggle_Chat;
    };

    void WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
    const char* ToString(uint8_t key);
    std::vector<uint8_t> GetValidKeys();
    bool IsKeyDown(uint8_t key);
    bool IsKeyPressed(uint8_t key);
    bool IsKeyReleased(uint8_t key);

    void to_json(nlohmann::ordered_json& j, KeyBinds::Config value);
    void from_json(const nlohmann::ordered_json& j, KeyBinds::Config& value);
}