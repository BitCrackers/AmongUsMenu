#include "pch-il2cpp.h"
#include "_hooks.h"

bool dStatsManager_get_AmBanned(StatsManager* __this, MethodInfo* method) {
	return false;
}

float dStatsManager_get_BanPoints(StatsManager* __this, MethodInfo* method) {

	if ((__this->fields.loadedStats == true) && (__this->fields.stats != nullptr))
		__this->fields.stats->fields.banPoints = 0.F;

	return 0.F;
}

int32_t dStatsManager_get_BanMinutesLeft(StatsManager* __this, MethodInfo* method) {
	return (int32_t)0;
}