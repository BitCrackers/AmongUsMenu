#include "pch-il2cpp.h"
#include "utility.h"
#include "achievements.hpp"

namespace Achievements {
	bool IsSupported() {
		return GetAchievementManager() != nullptr;
	}

	void UnlockAll() {
		if (auto manager = GetAchievementManager()) {
			ScopedThreadAttacher managedThreadAttached;

			il2cpp::Dictionary achievementGameModeKey = manager->klass->static_fields->AchievementGameModeKey;
			for (auto pair : achievementGameModeKey) {
				il2cpp::List list = pair.value;
				if (!list.contains(app::GameModes__Enum::Normal)) {
					list.add(app::GameModes__Enum::Normal);
				}
				if (!list.contains(app::GameModes__Enum::HideNSeek)) {
					list.add(app::GameModes__Enum::HideNSeek);
				}

				app::AchievementManager_1_UnlockAchievement(manager, pair.key, nullptr);
			}
		}
	}
}