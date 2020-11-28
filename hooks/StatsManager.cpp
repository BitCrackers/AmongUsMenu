#include "_hooks.hpp"

using namespace app;

bool dStatsManager_get_AmBanned(StatsManager* __this, MethodInfo* method) {
	return false;
}

float dStatsManager_get_BanPoints(StatsManager* __this, MethodInfo* method) {
	__this->fields.banPoints = 0.F;
	return 0.F;
}

int32_t dStatsManager_get_BanMinutesLeft(StatsManager* __this, MethodInfo* method) {
	return (int32_t)0;
}