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
	{ {"", "Constants"}, {"", "NFONDPLFBCP"}},
	{ {"", "GameData.PlayerInfo"}, {"", "GameData.OFKOJOKOOAK"} },
	{ {"", "GameData.TaskInfo"}, {"", "GameData.FPNIHBANCDO"} },
	{ {"", "GameOptionsData"}, {"", "IGDMNKLDEPI"} },
	{ {"", "Palette"}, {"", "GLNPIJPGGNJ"} },
	{ {"", "SaveManager"}, {"", "ALOOOIHKCAC"} },
	{ {"", "StatsManager"}, {"", "MOJBJJPEFPG"} },
	{ {"", "SystemTypes"}, {"", "LGBKLKNAINN"} },
	{ {"", "DisconnectReasons"}, {"", "ECELNFALKOB"} },
	{ {"", "ISystemType"}, {"", "CBFMKGACLNE"} },
	{ {"", "SwitchSystem"}, {"", "FNEHFOPHPJO"} },
	{ {"InnerNet", "MessageExtensions"}, {"", "AGJLGGLENOC"}},
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "CHAKNIAAIDE" },
	{ "get_AmBanned", "OOPPAGDFJIP" },
	{ "get_BanPoints", "NDKIBBHCHPN" },
	{ "Deserialize", "BBEAAOOCKOP" },
	{ "EnterVent", "AFIBGDGMNEA" },
	{ "ExitVent", "NFFLCEOEGNF" },
	{ "ReportDeadBody", "AGANIGJHGNB" },
	{ "ShouldFlipSkeld", "DECMMJMOCKM" },
	{ "SendStartGame", "OFMEGDEDGOK" },
	{ "SetMaskFunction", "NDMKNGFHFJO" },
	{ "OnPlayerLeft", "FBJJGMOIHOI" },
	{ "SnapTo", "BNNEAMEFHIG" },
	{ "SetSide", "BPIJLFKFMMN"},
	{ "WriteNetObject", "HPBDHGFGHHN"},
};