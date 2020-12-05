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
	{ {"", "AmongUsClient"}, {"", "OIMFAEOPLBD"} },
	{ {"", "AutoOpenDoor"}, {"", "MELBGJMBHKO"} },
	{ {"", "ChatBubble"}, {"", "KNFDIHGOGCI"} },
	{ {"", "ChatController"}, {"", "BNGAGGNFPLK"} },
	{ {"", "Constants"}, {"", "EFMMAGLBNBL"}},
	{ {"", "CustomNetworkTransform"}, {"", "IDLHEGPAGNM"} },
	{ {"", "DeadBody"}, {"", "HOIINFBKEHJ"} },
	{ {"", "ElectricTask"}, {"", "KGADDEGHBKN"} },
	{ {"", "GameData"}, {"", "JPEFLJOLPBJ"} },
	{ {"", "GameData.PlayerInfo"}, {"", "JPEFLJOLPBJ.NPEBLJEDBCC"} },
	{ {"", "GameData.TaskInfo"}, {"", "JPEFLJOLPBJ.CHOEDCDMMJN"} },
	{ {"", "GameOptionsData"}, {"", "PHKMAOFPLPP"} },
	{ {"", "HatManager"}, {"", "PPHACOLFNPK"} },
	{ {"", "HqHudOverrideTask"}, {"", "PODCFBLFNLO"} },
	{ {"", "HudManager"}, {"", "DAHMEPKHADP"}},
	{ {"", "HudOverrideTask"}, {"", "OOCOMHBLGPD"} },
	{ {"", "ImportantTextTask"}, {"", "APKKCBMIEGA"} },
	{ {"", "KeyboardJoystick"}, {"", "HKCJAPNAAML"} },
	{ {"", "MapBehaviour"}, {"", "EIJEFBNCOAI"} },
	{ {"", "MeetingHud"}, {"", "CHDFKFMCJFM"} },
	{ {"", "NoOxyTask"}, {"", "BGGCFKONLKH"} },
	{ {"", "NormalPlayerTask"}, {"", "KNLHBLCJMBO"} },
	{ {"", "Palette"}, {"", "KINELLGPGAP"} },
	{ {"", "PetBehaviour"}, {"", "EGDNPILJBBG"} },
	{ {"", "PlainDoor"}, {"", "PPNHOGBIENG"} },
	{ {"", "PlayerControl"}, {"", "BHHCHKFKPOE"} },
	{ {"", "PlayerTask"}, {"", "ACOHBJAJBND"} },
	{ {"", "ReactorTask"}, {"", "DKEOFIMPENN"} },
	{ {"", "SabotageTask"}, {"", "IDHEODMILAB"} },
	{ {"", "ShipStatus"}, {"", "KEJLBMGIBBL"} },
	{ {"", "SomeKindaDoor"}, {"", "KNJAGEBANEE"} },
	{ {"", "StatsManager"}, {"", "MBKPIIKBDCC"} },
	{ {"", "SystemTypes"}, {"", "FMGLMLCIFEF"} },
	{ {"", "TextRenderer"}, {"", "AKBBBLGBBPO"} },
	{ {"", "Vent"}, {"", "BALHIMJIGMI"} },
	{ {"InnerNet", "InnerNetClient"}, {"", "KIFAJMBCIGE"} },
	{ {"InnerNet", "InnerNetObject"}, {"", "LIINGCCJNPA"} },
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "FEGJEDHIPNA" },
	{ "get_AmBanned", "NMMDCJEFIPK" },
	{ "get_BanPoints", "GBIOGLNGGPK" },
	{ "Deserialize", "CMIKIIEJDDP" },
	{ "EnterVent", "MJBLECKPOGN" },
	{ "ExitVent", "LFABHLKHJEP" },
	{ "ReportDeadBody", "PKIPLGAJLJL" },
	{ "ShouldFlipSkeld", "LHNPJIMKODL"}
};