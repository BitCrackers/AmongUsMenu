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
	{ {"", "AmongUsClient"}, {"", "KNKBHCOHCOM"} },
	{ {"", "AutoOpenDoor"}, {"", "BIBGGEEEJLK"} },
	{ {"", "ChatBubble"}, {"", "HDBFNJBMAMA"} },
	{ {"", "ChatController"}, {"", "FLICDOHEDCM"} },
	{ {"", "Constants"}, {"", "EGCHBLMHNCO"}},
	{ {"", "CustomNetworkTransform"}, {"", "PPOKHKBILED"} },
	{ {"", "DeadBody"}, {"", "EEEPAKPKIGA"} },
	{ {"", "ElectricTask"}, {"", "LBCFMJDKEMP"} },
	{ {"", "GameData"}, {"", "JIEKDDEDHBE"} },
	{ {"", "GameData.PlayerInfo"}, {"", "JIEKDDEDHBE.LAJIANHFLPC"} },
	{ {"", "GameData.TaskInfo"}, {"", "JIEKDDEDHBE.MLCBJGLEELO"} },
	{ {"", "GameOptionsData"}, {"", "FDNACAAEENB"} },
	{ {"", "HatManager"}, {"", "ENEIIEPECCK"} },
	{ {"", "HqHudOverrideTask"}, {"", "KEKFAIIFGLL"} },
	{ {"", "HudManager"}, {"", "IFIKCHKDMMC"}},
	{ {"", "HudOverrideTask"}, {"", "JGMIPAPJPGD"} },
	{ {"", "ImportantTextTask"}, {"", "BMKBBABBODC"} },
	{ {"", "KeyboardJoystick"}, {"", "KJCNMLOGNDE"} },
	{ {"", "MapBehaviour"}, {"", "NJLNLLLCLCM"} },
	{ {"", "MeetingHud"}, {"", "LMJOGIIMCMB"} },
	{ {"", "NoOxyTask"}, {"", "NPAIEEHBJBK"} },
	{ {"", "NormalPlayerTask"}, {"", "GENAMHGNGGA"} },
	{ {"", "Palette"}, {"", "GGNFIBGLLFG"} },
	{ {"", "PetBehaviour"}, {"", "BLGIILCPFLL"} },
	{ {"", "PlainDoor"}, {"", "OOMDBBPODML"} },
	{ {"", "PlayerControl"}, {"", "LBADNGJPJGH"} },
	{ {"", "PlayerTask"}, {"", "IPPPHJACDBN"} },
	{ {"", "ReactorTask"}, {"", "DJAENCBCNNK"} },
	{ {"", "SabotageTask"}, {"", "OJCGNJOJGLD"} },
	{ {"", "ShipStatus"}, {"", "MIBEMIGLLGF"} },
	{ {"", "SomeKindaDoor"}, {"", "HPAIMDJPGAI"} },
	{ {"", "StatsManager"}, {"", "NMADDOBOILN"} },
	{ {"", "SystemTypes"}, {"", "NJIICKDHECA"} },
	{ {"", "TextRenderer"}, {"", "JDACDEHOMGB"} },
	{ {"", "Vent"}, {"", "PLFLGJFFFKL"} },
	{ {"InnerNet", "InnerNetClient"}, {"", "IFEMMDOEKDL"} },
	{ {"InnerNet", "InnerNetObject"}, {"", "GBDEKNMGFAI"} },
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "OMJIDIPEGMF" },
	{ "get_AmBanned", "PCJCFCBHJDA" },
	{ "get_BanPoints", "OBAPAPFDDHM" },
	{ "Deserialize", "GOCFDAMBMLH" },
	{ "EnterVent", "FLENNEBBHOK" },
	{ "ExitVent", "EKDCGJEACKM" },
	{ "ReportDeadBody", "MAPFKCHFLHH" },
	{ "ShouldFlipSkeld", "FBNFKGDCOAI"}
};