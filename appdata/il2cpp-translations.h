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
	{ {"", "AutoOpenDoor"}, {"", "BOFFADCMGAK"} },
	{ {"", "ChatBubble"}, {"", "KILPMABPOEH"} },
	{ {"", "ChatController"}, {"", "GEHKHGLKFHE"} },
	{ {"", "Constants"}, {"", "CAMOCHFAHMA"}},
	{ {"", "CustomNetworkTransform"}, {"", "LNBAPKHKDPG"} },
	{ {"", "DeadBody"}, {"", "DDPGLPLGFOI"} },
	{ {"", "ElectricTask"}, {"", "FFIDNPFJKPB"} },
	{ {"", "FollowerCamera"}, {"", "KGIKNCBGPFJ"} },
	{ {"", "GameData"}, {"", "EGLJNOMOGNP"} },
	{ {"", "GameData.PlayerInfo"}, {"", "EGLJNOMOGNP.DCJMABDDJCF"} },
	{ {"", "GameData.TaskInfo"}, {"", "EGLJNOMOGNP.CAAACHLJJNE"} },
	{ {"", "GameOptionsData"}, {"", "KMOGFLPJLLK"} },
	{ {"", "HatManager"}, {"", "OFCPCFDHIEF"} },
	{ {"", "HqHudOverrideTask"}, {"", "NIAFLKKACLE"} },
	{ {"", "HudManager"}, {"", "PIEFJFEOGOL"}},
	{ {"", "HudOverrideTask"}, {"", "LFOILEODBMA"} },
	{ {"", "ImportantTextTask"}, {"", "ABFBCNBODMA"} },
	{ {"", "KeyboardJoystick"}, {"", "ADEHDODPMHJ"} },
	{ {"", "LobbyBehaviour"}, {"", "PFLIBLFPGGB"} },
	{ {"", "MapBehaviour"}, {"", "CBAGIJCCEGG"} },
	{ {"", "MeetingHud"}, {"", "OOCJALPKPEP"} },
	{ {"", "NoOxyTask"}, {"", "FBIJCIMFFJP"} },
	{ {"", "NormalPlayerTask"}, {"", "IPNGEOLGOFC"} },
	{ {"", "Palette"}, {"", "LOCPGOACAJF"} },
	{ {"", "PetBehaviour"}, {"", "DLMDFGBMGPC"} },
	{ {"", "PlainDoor"}, {"", "EEHJPJEBAGP"} },
	{ {"", "PlayerControl"}, {"", "FFGALNAPKCD"} },
	{ {"", "PlayerTask"}, {"", "PILBGHDHJLH"} },
	{ {"", "ReactorTask"}, {"", "PMNHCPJEPJH"} },
	{ {"", "SabotageTask"}, {"", "MOKGEPINKEH"} },
	{ {"", "SaveManager"}, {"", "IANFCOGHJMJ"} },
	{ {"", "ScreenJoystick"}, {"", "OAJOCHMLEDJ"} },
	{ {"", "ShipStatus"}, {"", "HLBNNHFCNAJ"} },
	{ {"", "SomeKindaDoor"}, {"", "NBEJDLGKDGA"} },
	{ {"", "StatsManager"}, {"", "ENHLBAECCDF"} },
	{ {"", "SystemTypes"}, {"", "LJFDDJHBOGF"} },
	{ {"", "TextRenderer"}, {"", "AELDHKGBIFD"} },
	{ {"", "Vent"}, {"", "OPPMFCFACJB"} },
	{ {"InnerNet", "InnerNetClient"}, {"", "KHNHJFFECBP"} },
	{ {"InnerNet", "InnerNetObject"}, {"", "EKDECEPHHGP"} },
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "GALKJBNDNJO" },
	{ "get_AmBanned", "OKPJOODJHID" },
	{ "get_BanPoints", "INDPECBGFNO" },
	{ "Deserialize", "FEJLLGGCJCC" },
	{ "EnterVent", "JBNFMBNNPJB" },
	{ "ExitVent", "ENCPOOAFILD" },
	{ "ReportDeadBody", "MKAIDPJOJFP" },
	{ "ShouldFlipSkeld", "LKHNHNEEOOJ"},
	{ "set_BodyColor", "LBBABKKKFAJ"},
	{ "get_BodyColor", "GMJIBKDIKAI"},
	{ "SendStartGame", "DBFLAJLNBBN"}
};