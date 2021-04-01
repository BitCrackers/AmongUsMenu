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
	{ {"", "Constants"}, {"", "NFONDPLFBCP"}}, //done
	{ {"", "GameData.PlayerInfo"}, {"", "GameData.OFKOJOKOOAK"} }, //done
	{ {"", "GameData.TaskInfo"}, {"", "GameData.FPNIHBANCDO"} }, //done
	{ {"", "GameOptionsData"}, {"", "IGDMNKLDEPI"} }, //done
	{ {"", "Palette"}, {"", "GLNPIJPGGNJ"} }, //done
	{ {"", "SaveManager"}, {"", "ALOOOIHKCAC"} }, //done
	{ {"", "StatsManager"}, {"", "MOJBJJPEFPG"} }, //done
	{ {"", "SystemTypes"}, {"", "LGBKLKNAINN"} }, //done
	{ {"", "DisconnectReasons"}, {"", "ECELNFALKOB"} }, //done
	{ {"", "ISystemType"}, {"", "CBFMKGACLNE"} }, //done
	{ {"", "SwitchSystem"}, {"", "FNEHFOPHPJO"} }, //done
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "CHAKNIAAIDE" }, //done
	{ "get_AmBanned", "OOPPAGDFJIP" }, //done
	{ "get_BanPoints", "NDKIBBHCHPN" }, //done
	{ "Deserialize", "BBEAAOOCKOP" }, //done
	{ "EnterVent", "MGFMILKCEIN" }, // CACKHNHMCPM - LNLNBNLNDLM - MGFMILKCEIN - HFHOHEBHKOI - HAOGIFBEGFC
	{ "ExitVent", "HFHOHEBHKOI" }, // ^
	{ "ReportDeadBody", "AGANIGJHGNB" }, //done
	{ "ShouldFlipSkeld", "DECMMJMOCKM" }, //done
	{ "SendStartGame", "OFMEGDEDGOK" }, //done
	{ "SetMaskFunction", "NDMKNGFHFJO" }, //done
	{ "OnPlayerLeft", "NBDIGLAODOA" }, //done FBJJGMOIHOI
	{ "SnapTo", "BNNEAMEFHIG" }, //done
	{ "DrawOcclusion", "OGILAKHGLMJ" }
};