#pragma once
#include <vector>
#include <string>

struct KLASS {
	std::string namespaze;
	std::string klass_name;

	size_t contains_type(std::string type_input) {
		size_t position;

		if ((position = type_input.find(klass_name, 0)) != std::string::npos)
			return klass_name.length();

		return 0;
	}

	friend bool operator==(const KLASS& lhs, const KLASS& rhs) {
		return (lhs.namespaze.compare(rhs.namespaze) == 0 && lhs.klass_name.compare(rhs.klass_name) == 0);
	}
};

struct KLASS_PAIR {
	KLASS deobfuscated_klass;
	KLASS obfuscated_klass;
};

const std::vector<KLASS_PAIR> KLASS_TRANSLATIONS = {
	{ {"", "Constants"}, {"", "DPHADHMAPCB"}},	
	{ {"", "GameData.PlayerInfo"}, {"", "GameData.GOOIGLGKMCE"} },
	{ {"", "GameData.TaskInfo"}, {"", "GameData.HKFJOIBBOBD"} },
	{ {"", "GameOptionsData"}, {"", "PAMOPBEDCNI"} },
	{ {"", "Palette"}, {"", "KOBANOHPIIA"} },
	{ {"", "SaveManager"}, {"", "BNAOOLKPIBG"} },
	{ {"", "StatsManager"}, {"", "HHCMEENGBEI"} },
	{ {"", "SystemTypes"}, {"", "GOODOHMJKLN"} },
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "MBFOPPGNFAF" },
	{ "get_AmBanned", "HLEKGEFELJO" },
	{ "get_BanPoints", "FHELDINHHMJ" },
	{ "Deserialize", "OBBPKOCNPDG" },
	{ "EnterVent", "AAFOLJNFDOH" },
	{ "ExitVent", "KJAPJGIAEDD" },
	{ "ReportDeadBody", "AMPIGFMHGBM" },
	{ "ShouldFlipSkeld", "HOFPIHJFIGI" },
	{ "set_BodyColor", "GJJMKCLFAAA" },
	{ "get_BodyColor", "PDNHBJIIOCP" },
	{ "SendStartGame", "KFBAMPOABEN" },
	{ "SetMaskFunction", "OGHEGEOFGNP" }
};