#include "keybinds.h"
#include <bitset>
#include <map>

static const std::map<uint8_t, const char*> KeyMap = {
    {0x02, "MOUSE 2"},
    {0x04, "MOUSE 3"},
    {0x05, "MOUSE 4"},
    {0x06, "MOUSE 5"},
    {0x08, "BACKSPACE"},
    {0x09, "TAB"},
    {0x0C, "CLEAR"},
    {0x0D, "RETURN"},
    {0x10, "SHIFT"},
    {0x11, "CTRL"},
    {0x12, "ALT"},
    {0x13, "PAUSE"},
    {0x14, "CAPS LOCK"},
    {0x1B, "ESC"},
    {0x20, "SPACE"},
    {0x21, "PG UP"},
    {0x22, "PG DN"},
    {0x23, "END"},
    {0x24, "HOME"},
    {0x2D, "INS"},
    {0x2E, "DEL"},
    {0x2C, "PRNTSCR"},
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
    {0x42, "B"},
    {0x43, "C"},
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
    {0x54, "T"},
    {0x55, "U"},
    {0x56, "V"},
    {0x58, "X"},
    {0x59, "Y"},
    {0x5A, "Z"},
    {0x5B, "WINDOWS"},
    {0x5C, "WINDOWS"},
    {0x60, "NUM 0"},
    {0x61, "NUM 1"},
    {0x62, "NUM 2"},
    {0x63, "NUM 3"},
    {0x64, "NUM 4"},
    {0x65, "NUM 5"},
    {0x66, "NUM 6"},
    {0x67, "NUM 7"},
    {0x68, "NUM 8"},
    {0x69, "NUM 9"},
    {0x6A, "MULTIPLY"},
    {0x6B, "ADD"},
    {0x6C, "SEPARATOR"},
    {0x6D, "SUBTRACT"},
    {0x6E, "DECIMAL"},
    {0x6F, "DIVIDE"},
    {0x70, "F1"},
    {0x71, "F2"},
    {0x72, "F3"},
    {0x73, "F4"},
    {0x74, "F5"},
    {0x75, "F6"},
    {0x76, "F7"},
    {0x77, "F8"},
    {0x78, "F9"},
    {0x79, "F10"},
    {0x7A, "F11"},
    {0x7B, "F12"},
    {0xA0, "L SHIFT"},
    {0xA1, "R SHIFT"},
    {0xA2, "L CTRL"},
    {0xA3, "R CTRL"},
};

static std::bitset<256> PrevKeyState;
static std::bitset<256> KeyState;

void KeyBinds::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PrevKeyState = KeyState;
    switch (uMsg) {
        case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
        case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
        {
            uint8_t mouseButton = 0;

            if (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK) { mouseButton = 0x01; }
            if (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK) { mouseButton = 0x02; }
            if (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONDBLCLK) { mouseButton = 0x04; }
            if (uMsg == WM_XBUTTONDOWN || uMsg == WM_XBUTTONDBLCLK) { mouseButton = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 0x05 : 0x06; }
            KeyState[mouseButton] = true;
            return;
        }
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
        {
            uint8_t mouseButton = 0;

            if (uMsg == WM_LBUTTONUP) { mouseButton = 0x01; }
            if (uMsg == WM_RBUTTONUP) { mouseButton = 0x02; }
            if (uMsg == WM_MBUTTONUP) { mouseButton = 0x04; }
            if (uMsg == WM_XBUTTONUP) { mouseButton = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 0x05 : 0x06; }
            KeyState[mouseButton] = false;
            return;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            if (wParam < 256)
                KeyState[wParam] = true;
            return;
        }
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            if (wParam < 256)
                KeyState[wParam] = false;
            return;
        }
        case WM_KILLFOCUS:
            KeyState.reset();
            break;
    }
}

const char* KeyBinds::ToString(uint8_t key)
{
    auto iter = KeyMap.find(key);
    if (iter != KeyMap.end())
        return iter->second;

    return "NONE";
}

std::vector<uint8_t> KeyBinds::GetValidKeys()
{
    std::vector<uint8_t> validKeys = std::vector<uint8_t>();

    for (auto const& [key, value] : KeyMap)
        validKeys.push_back(key);

    return validKeys;
}

bool KeyBinds::IsKeyDown(uint8_t key)
{
    return KeyState[key];
}

bool KeyBinds::IsKeyPressed(uint8_t key)
{
    return (!PrevKeyState[key] && KeyState[key]);
}

bool KeyBinds::IsKeyReleased(uint8_t key)
{
    return (PrevKeyState[key] && !KeyState[key]);
}

void KeyBinds::to_json(nlohmann::ordered_json& j, KeyBinds::Config value)
{
    j = nlohmann::ordered_json{
        {"Toggle_Menu", value.Toggle_Menu},
        {"Toggle_Radar", value.Toggle_Radar},
        {"Toggle_Console", value.Toggle_Console},
        {"Repair_Sabotage", value.Repair_Sabotage},
        {"Toggle_Noclip", value.Toggle_Noclip},
        {"Close_All_Doors", value.Close_All_Doors},
        {"Toggle_Zoom", value.Toggle_Zoom},
        {"Toggle_Freecam", value.Toggle_Freecam},
        {"Close_Current_Room_Door", value.Close_Current_Room_Door},
        {"Toggle_Replay", value.Toggle_Replay},
        {"Toggle_Chat", value.Toggle_Chat},
    };
}

void KeyBinds::from_json(const nlohmann::ordered_json& j, KeyBinds::Config& value)
{
    j.at("Toggle_Menu").get_to(value.Toggle_Menu);
    j.at("Toggle_Radar").get_to(value.Toggle_Radar);
    j.at("Toggle_Console").get_to(value.Toggle_Console);
    j.at("Repair_Sabotage").get_to(value.Repair_Sabotage);
    j.at("Toggle_Noclip").get_to(value.Toggle_Noclip);
    j.at("Close_All_Doors").get_to(value.Close_All_Doors);
    j.at("Toggle_Zoom").get_to(value.Toggle_Zoom);
    j.at("Toggle_Freecam").get_to(value.Toggle_Freecam);
    j.at("Close_Current_Room_Door").get_to(value.Close_Current_Room_Door);
    j.at("Toggle_Replay").get_to(value.Toggle_Replay);
    j.at("Toggle_Chat").get_to(value.Toggle_Chat);
}