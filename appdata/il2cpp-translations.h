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
	{ {"", "Constants"}, {"", "GOPHKPFLLBH"}},
	{ {"", "GameData.PlayerInfo"}, {"", "GameData.JBDOMGNBCBH"} },
	{ {"", "GameData.TaskInfo"}, {"", "GameData.EOAGFELAMIM"} },
	{ {"", "GameOptionsData"}, {"", "ILHBIMBOFDI"} },
	{ {"", "Palette"}, {"", "GBHEJGBDGPJ"} },
	{ {"", "SaveManager"}, {"", "PKKCMGKHOJA"} },
	{ {"", "StatsManager"}, {"", "HLBPBMGBNGE"} },
	{ {"", "SystemTypes"}, {"", "LPKBKECNKLP"} },
	{ {"", "DisconnectReasons"}, {"", "HGANHCACPJM"} },
	{ {"", "ISystemType"}, {"", "IMDFAGKELHM"} },
	{ {"", "SwitchSystem"}, {"", "FFIMOMHKGBE"} },
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "JHCNMDBJOPL" },
	{ "get_AmBanned", "KPPPEDMNOAN" }, 
	{ "get_BanPoints", "GOCAPJKBFKG" },
	{ "Deserialize", "BMDKAMACEKH" },
	{ "EnterVent", "FOBALHHMNHP" },  // MIKKBFDJNFP - BIHNHHPGBPN - CHEEOCFIEPG 
	{ "ExitVent", "BIDJOGAPJHO" }, // NCHHIFHFIBA - IADEGJKGOHO - DDIKNENMFEJ - BMDFMJBGABF - BBJNFIACACA - AGBGLJBIDED - MDCMHFFPHKE
	{ "ReportDeadBody", "LFFPFIJGHKC" },
	{ "ShouldFlipSkeld", "MBOCPHKHNBG" },
	{ "SendStartGame", "ANCFEECEHKP" },
	{ "SetMaskFunction", "BGLIPIMPNFH" },
	{ "OnPlayerLeft", "CJDKFLEBMLI" },
	{ "SnapTo", "GOBEJFMLNNE" },
};