#pragma once
#include <vector>

namespace GameTab {
	const std::vector<const char*> KILL_DISTANCE = { "Short", "Medium", "Long", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" };
	const std::vector<const char*> TASKBARUPDATES = { "Always", "Meetings", "Never", "3", "4", "5", "6" };
	const std::vector<const char*> COLORS = { "Red", "Blue", "Green", "Pink", "Orange", "Yellow", "Black", "White", "Purple", "Brown", "Cyan", "Lime", "Maroon", "Rose", "Banana", "Gray", "Tan", "Coral" };
	const std::vector<const char*> HOSTCOLORS = { "Red", "Blue", "Green", "Pink", "Orange", "Yellow", "Black", "White", "Purple", "Brown", "Cyan", "Lime", "Maroon", "Rose", "Banana", "Gray", "Tan", "Coral", "Fortegreen"};
	const std::vector<const char*> GAMEENDREASON = { "Crewmates (Votes)", "Crewmates (Tasks)", "Impostors (Votes)", "Impostors (Kill)", "Impostors (Sabotage)", "D/C (Imp)", "D/C (Crew)", "Timer (HNS)", "Kill (HNS)" };
	void Render();
}