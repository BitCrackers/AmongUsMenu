#include "keyBindsConfig.h"
#include <map>

static const std::map<uint8_t, const char*> KeyMap = {
        {0x21, "PG UP"},
        {0x22, "PG DN"},
        {0x23, "END"},
        {0x24, "HOME"},
        {0x2D, "INS"},
        {0x2E, "DEL"},
        {0x30, "0"},
        {0x31, "1"},
        {0x32, "2"},
        {0x33, "3"},
        {0x34, "4"},
        {0x35, "5"},
        {0x36, "6"},
        {0x37, "7"},
        {0x38, "8"},
        {0x39, "9"},
        {0x41, "A"},
        {0x42, "B"},
        {0x43, "C"},
        {0x44, "D"},
        {0x45, "E"},
        {0x46, "F"},
        {0x47, "G"},
        {0x48, "H"},
        {0x49, "I"},
        {0x4A, "J"},
        {0x4B, "K"},
        {0x4C, "L"},
        {0x4D, "M"},
        {0x4E, "N"},
        {0x4F, "O"},
        {0x50, "P"},
        {0x51, "Q"},
        {0x52, "R"},
        {0x53, "S"},
        {0x54, "T"},
        {0x55, "U"},
        {0x56, "V"},
        {0x57, "W"},
        {0x58, "X"},
        {0x59, "Y"},
        {0x5A, "Z"},
};

KeyBindsConfig KeyBindsConfig::fromJson(nlohmann::ordered_json json)
{
    KeyBindsConfig keyBinds = KeyBindsConfig();

    keyBinds.Toggle_Menu = json["Toggle_Menu"].get<uint8_t>();
    keyBinds.Toggle_Radar = json["Toggle_Radar"].get<uint8_t>();
    keyBinds.Toggle_Console = json["Toggle_Console"].get<uint8_t>();
    keyBinds.Repair_Sabotage = json["Repair_Sabotage"].get<uint8_t>();

    return keyBinds;
}

nlohmann::ordered_json KeyBindsConfig::toJson(KeyBindsConfig keyBinds)
{
    nlohmann::ordered_json json = nlohmann::ordered_json();

    json["Toggle_Menu"] = keyBinds.Toggle_Menu;
    json["Toggle_Radar"] = keyBinds.Toggle_Radar;
    json["Toggle_Console"] = keyBinds.Toggle_Console;
    json["Repair_Sabotage"] = keyBinds.Repair_Sabotage;

    return json;
}

const char* KeyBindsConfig::toString(uint8_t key)
{
    auto iter = KeyMap.find(key);
    if (iter != KeyMap.end())
        return iter->second;

    return "NONE";
}

std::vector<uint8_t> KeyBindsConfig::getValidKeys()
{
    std::vector<uint8_t> validKeys = std::vector<uint8_t>();

    for (auto const& [key, value] : KeyMap)
        validKeys.push_back(key);

    return validKeys;
}