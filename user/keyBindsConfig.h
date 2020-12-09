#pragma once
#include <cstdint>

#include <vector>
#include "json.hpp"

struct KeyBindsConfig {
    uint8_t Toggle_Menu;
    uint8_t Toggle_Radar;
    uint8_t Toggle_Console;
    uint8_t Repair_Sabotage;

    static KeyBindsConfig fromJson(nlohmann::ordered_json json);
    static nlohmann::ordered_json toJson(KeyBindsConfig keyBinds);
    static const char* toString(uint8_t key);
    static std::vector<uint8_t> getValidKeys();
};