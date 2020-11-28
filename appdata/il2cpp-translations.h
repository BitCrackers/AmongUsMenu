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
	{ {"", "AmongUsClient"}, {"", "MMMGPAPEEBJ"} },
	{ {"", "AutoOpenDoor"}, {"", "JDAKMDHPMMC"} },
	{ {"", "ChatBubble"}, {"", "KGGCABMODHL"} },
	{ {"", "ChatController"}, {"", "BPPJFAOEOMH"} },
	{ {"", "CustomNetworkTransform"}, {"", "AMOIOPOABJF"} },
	{ {"", "DeadBody"}, {"", "EJCEPCCBOCK"} },
	{ {"", "ElectricTask"}, {"", "KCAPJIHPKEM"} },
	{ {"", "GameData"}, {"", "FLIHHNFFPAO"} },
	{ {"", "GameData.PlayerInfo"}, {"", "FLIHHNFFPAO.LBGGNMFGAOO"} },
	{ {"", "GameData.TaskInfo"}, {"", "FLIHHNFFPAO.CJOIAHBNANN"} },
	{ {"", "GameOptionsData"}, {"", "CGMOHAPDEMD"} },
	{ {"", "HatManager"}, {"", "ADOLBBELNOJ"} },
	{ {"", "HqHudOverrideTask"}, {"", "AFFPOFMFHEF"} },
	{ {"", "HudManager"}, {"", "PINEMJODMGE"}},
	{ {"", "HudOverrideTask"}, {"", "KALDPINPHCD"} },
	{ {"", "ImportantTextTask"}, {"", "JFLNOBANPAP"} },
	{ {"", "KeyboardJoystick"}, {"", "BOEODBAABEE"} },
	{ {"", "MapBehaviour"}, {"", "DMOOMCJMPPG"} },
	{ {"", "MeetingHud"}, {"", "NEOCOBOAGFJ"} },
	{ {"", "NoOxyTask"}, {"", "CJFEMKEHOBC"} },
	{ {"", "NormalPlayerTask"}, {"", "NNAKCNADELG"} },
	{ {"", "Palette"}, {"", "JPNOMHDLBOP"} },
	{ {"", "PetBehaviour"}, {"", "JGKCAIIJGDO"} },
	{ {"", "PlainDoor"}, {"", "MPAHHEKBEJL"} },
	{ {"", "PlayerControl"}, {"", "JENJGDMOEOC"} },
	{ {"", "PlayerTask"}, {"", "CLCMPFJIIEN"} },
	{ {"", "ReactorTask"}, {"", "OAECDOIMMKL"} },
	{ {"", "SabotageTask"}, {"", "OOJPICGHPAA"} },
	{ {"", "ShipStatus"}, {"", "EIEMHBCHLNI"} },
	{ {"", "SomeKindaDoor"}, {"", "PLNHIICAGCL"} },
	{ {"", "StatsManager"}, {"", "GIMEIGKNDOK"} },
	{ {"", "SystemTypes"}, {"", "AOKAHIJINGJ"} },
	{ {"", "TextRenderer"}, {"", "MMLBCIOEOFD"} },
	{ {"", "Vent"}, {"", "DPFCPDGDEBA"} },
	{ {"InnerNet", "InnerNetClient"}, {"", "FMJPJKCNIKM"} },
	{ {"InnerNet", "InnerNetObject"}, {"", "JBBAENBKONG"} },
};

const std::vector<std::pair<std::string, std::string>> METHOD_TRANSLATIONS = {
	{ "get_BanMinutesLeft", "ONKOEABCOJC" },
	{ "get_AmBanned", "FGKPOKFBCHN" },
	{ "get_BanPoints", "OPHIIKILKJM" },
	{ "Deserialize", "GOHNICOHFAE" },
	{ "EnterVent", "CMMDEMNKJDF" },
	{ "ExitVent", "MINPENJBOED" },
	{ "ReportDeadBody", "JCFAKCAJIJK" }
};