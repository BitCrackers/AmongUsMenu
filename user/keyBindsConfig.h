#pragma once
#include <vector>
#include "json.hpp"

struct KeyBindsConfig {
    uint8_t Toggle_Menu;
    uint8_t Toggle_Radar;
    uint8_t Toggle_Console;
    uint8_t Repair_Sabotage;
    uint8_t Toggle_Noclip;
    uint8_t Close_All_Doors;
    uint8_t Toggle_Zoom;
    uint8_t Toggle_Freecam;
    uint8_t Close_Current_Room_Door;
    uint8_t Complete_Task_0;
    uint8_t Complete_Task_1;
    uint8_t Complete_Task_2;
    uint8_t Complete_Task_3;
    uint8_t Complete_Task_4;
    uint8_t Complete_Task_5;
    uint8_t Complete_Task_6;
    uint8_t Complete_Task_7;
    uint8_t Complete_Task_8;
    uint8_t Complete_Task_9;

    static const char* toString(uint8_t key);
    static std::vector<uint8_t> getValidKeys();
    static bool IsReleased(uint8_t key);
};

static void to_json(nlohmann::ordered_json& j, KeyBindsConfig value) {
    j = nlohmann::ordered_json{
        {"Toggle_Menu", value.Toggle_Menu},
        {"Toggle_Radar", value.Toggle_Radar},
        {"Toggle_Console", value.Toggle_Console},
        {"Repair_Sabotage", value.Repair_Sabotage},
        {"Toggle_Noclip", value.Toggle_Noclip},
        {"Close_All_Doors", value.Close_All_Doors},
        {"Toggle_Zoom", value.Toggle_Zoom},
        {"Toggle_Freecam", value.Toggle_Freecam},
        {"Close_Current_Room_Door", value.Close_Current_Room_Door}
    };
}

static void from_json(const nlohmann::ordered_json& j, KeyBindsConfig& value) {
    j.at("Toggle_Menu").get_to(value.Toggle_Menu);
    j.at("Toggle_Radar").get_to(value.Toggle_Radar);
    j.at("Toggle_Console").get_to(value.Toggle_Console);
    j.at("Repair_Sabotage").get_to(value.Repair_Sabotage);
    j.at("Toggle_Noclip").get_to(value.Toggle_Noclip);
    j.at("Close_All_Doors").get_to(value.Close_All_Doors);
    j.at("Toggle_Zoom").get_to(value.Toggle_Zoom);
    j.at("Toggle_Freecam").get_to(value.Toggle_Freecam);
    j.at("Close_Current_Room_Door").get_to(value.Close_Current_Room_Door);
}