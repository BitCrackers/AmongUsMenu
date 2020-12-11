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
	{ {"", "AmongUsClient"}, {"", "FMLLKEACGIO"} },
	{ {"", "AutoOpenDoor"}, {"", ""} },
	{ {"", "ChatBubble"}, {"", ""} },
	{ {"", "ChatController"}, {"", ""} },
	{ {"", "Constants"}, {"", ""}},
	{ {"", "CustomNetworkTransform"}, {"", "LNBAPKHKDPG"} },
	{ {"", "DeadBody"}, {"", ""} },
	{ {"", "ElectricTask"}, {"", ""} },
	{ {"", "GameData"}, {"", "EGLJNOMOGNP"} },
	{ {"", "GameData.PlayerInfo"}, {"", "EGLJNOMOGNP.DCJMABDDJCF"} },
	{ {"", "GameData.TaskInfo"}, {"", "EGLJNOMOGNP.CAAACHLJJNE"} },
	{ {"", "GameOptionsData"}, {"", ""} },
	{ {"", "HatManager"}, {"", ""} },
	{ {"", "HqHudOverrideTask"}, {"", ""} },
	{ {"", "HudManager"}, {"", ""}},
	{ {"", "HudOverrideTask"}, {"", ""} },
	{ {"", "ImportantTextTask"}, {"", ""} },
	{ {"", "KeyboardJoystick"}, {"", ""} },
	{ {"", "MapBehaviour"}, {"", "CBAGIJCCEGG"} },
	{ {"", "MeetingHud"}, {"", ""} },
	{ {"", "NoOxyTask"}, {"", ""} },
	{ {"", "NormalPlayerTask"}, {"", "IPNGEOLGOFC"} },
	{ {"", "Palette"}, {"", ""} },
	{ {"", "PetBehaviour"}, {"", "DLMDFGBMGPC"} },
	{ {"", "PlainDoor"}, {"", "EEHJPJEBAGP"} },
	{ {"", "PlayerControl"}, {"", "FFGALNAPKCD"} },
	{ {"", "PlayerTask"}, {"", "PILBGHDHJLH"} },
	{ {"", "ReactorTask"}, {"", ""} },
	{ {"", "SabotageTask"}, {"", ""} },
	{ {"", "ShipStatus"}, {"", "HLBNNHFCNAJ"} },
	{ {"", "SomeKindaDoor"}, {"", ""} },
	{ {"", "StatsManager"}, {"", ""} },
	{ {"", "SystemTypes"}, {"", "LJFDDJHBOGF"} },
	{ {"", "TextRenderer"}, {"", "AELDHKGBIFD"} },
	{ {"", "Vent"}, {"", "OPPMFCFACJB"} },
	{ {"InnerNet", "InnerNetClient"}, {"", "KHNHJFFECBP"} },
	{ {"InnerNet", "InnerNetObject"}, {"", "NJAHILONGKN"} },
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "" },
	{ "get_AmBanned", "" },
	{ "get_BanPoints", "" },
	{ "Deserialize", "" },
	{ "EnterVent", "" },
	{ "ExitVent", "" },
	{ "ReportDeadBody", "" },
	{ "ShouldFlipSkeld", ""}
};