#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <bitset>
#include <functional>

namespace ImHotkeys
{
	union KeyCombo {
		uint8_t Key[4];
		uint32_t Keys;
	};

	struct HotKey {
		const char* Name;
		KeyCombo Combo;
		std::function<void()> Function;
	};

	static std::bitset<0xFF> KeyState;

	static void WndProc(UINT uMsg, WPARAM wParam) {
		if (uMsg == WM_KEYDOWN)
			ImHotkeys::KeyState[uint8_t(wParam)] = true;

		if (uMsg == WM_KEYUP)
			ImHotkeys::KeyState[uint8_t(wParam)] = false;
	}

	static bool CheckKey(uint8_t key) {
		if (key == 0xFF) return true;
		return ImHotkeys::KeyState[key];
	}

	static bool CheckKeyCombo(KeyCombo keyCombo) {
		return CheckKey(keyCombo.Key[0]) && CheckKey(keyCombo.Key[1]) && CheckKey(keyCombo.Key[2]) && CheckKey(keyCombo.Key[3]);
	}

	static int GetShortcut(std::vector<HotKey>* hotkeys) {
		static uint32_t lastKeys = 0xFFFFFFFF;

		for (size_t i = 0; i < hotkeys->size(); i++) {
			if (CheckKeyCombo((*hotkeys)[i].Combo)) {
				if (lastKeys != (*hotkeys)[i].Combo.Keys) {
					lastKeys = (*hotkeys)[i].Combo.Keys;
					return int(i);
				}
				else {
					return -1;
				}
			}
		}
		lastKeys = 0xFFFFFFFF;
		return -1;
	}
}