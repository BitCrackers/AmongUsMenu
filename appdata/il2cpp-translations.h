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
	{ {"", "Constants"}, {"", "LNCOKMACBKP"}},
	{ {"", "GameData.PlayerInfo"}, {"", "GameData.LGBOMGHJELL"} },
	{ {"", "GameData.TaskInfo"}, {"", "GameData.NGBCKJFEBBJ"} },
	{ {"", "DoorCardSwipeGame.TaskStages"}, {"", "DoorCardSwipeGame.FJAMAKBHCLP"}},
	{ {"", "GameOptionsData"}, {"", "CEIOGGEDKAN"} },
	{ {"", "Palette"}, {"", "BLMBFIODBKL"} },
	{ {"", "SaveManager"}, {"", "BLCGIFOPMIA"} },
	{ {"", "StatsManager"}, {"", "IAJICOPDKHA"} },
	{ {"", "SystemTypes"}, {"", "BCPJLGGNHBC"} },
	{ {"", "DisconnectReasons"}, {"", "GABADEGMIHF"} },
	{ {"", "ISystemType"}, {"", "JBBCJFNFOBB"} },
	{ {"", "SwitchSystem"}, {"", "ABIMJJMBJJM"} },
	{ {"", "TaskTypes"}, {"", "DMOAGPGAFKM"} },
	{ {"", "TaskBarUpdates"}, {"", "NJIFIEMPGEC"} },
	{ {"", "GameMode"}, {"", "IDLLMBGOEPL"} },
	{ {"", "Announcement"}, {"", "DEMJCHFGGHP"} },
	{ {"InnerNet", "MessageExtensions"}, {"", "GNECIFEPIHB"} },
	{ {"InnerNet", "GameKeywords"}, {"", "HPPGMINEFNF"} },
	{ {"InnerNetClient", "GameStates"}, {"", "GCDONLGCMIL"} },
	{ {"InnerNet", "GameCode"}, {"", "GLNIFBJGNFJ"} }
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "ABJEJPPKINE" },
	{ "get_AmBanned", "GJMGEHKGFDA" },
	{ "get_BanPoints", "NAMLHJLDMNN" },
	{ "Deserialize", "GGJDCBJNFBH" },
	{ "EnterVent", "FCHLKLJCBEP" },
	{ "ExitVent", "AGOIHGCNABM" },
	{ "ReportDeadBody", "OAEFBFNHJGG" },
	{ "ShouldFlipSkeld", "OCGFJNHBAPE" },
	{ "SendStartGame", "MFLPHJGDGDB" },
	{ "SetMaskFunction", "ODDFGCMOGOA" },
	{ "OnPlayerLeft", "LIOEBBDDACD" },
	{ "SnapTo", "ODDILDEGEOD" },
	{ "SetSide", "OMLGOAEHPKJ"},
	{ "WriteNetObject", "HHECOFHJFEE"},
	{ "IntToGameName", "LAEAGKNJOAK"},
};