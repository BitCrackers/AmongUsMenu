#include "pch-il2cpp.h"
#include "DestroyableSingleton.h"
#include "utility.h"
#include "achievements.hpp"
#include "logger.h"

namespace Achievements {

	_Ret_maybenull_ AchievementManager_1* GetAchievementManager() {
		static DestroyableSingleton<AccountManager*> accountManager{ "Assembly-CSharp, AccountManager" };
		if (!accountManager.IsInstanceExists()
			|| accountManager.GetInstance()->fields.prevLoggedInStatus == EOSManager_AccountLoginStatus__Enum::Offline)
			return nullptr;

		static DestroyableSingleton<AchievementManager_1*> manager{ "Assembly-CSharp, AchievementManager" };
		return manager.GetInstance();
	}

	bool IsSupported() {
		return GetAchievementManager() != nullptr;
	}

	void UnlockAll() {
		auto manager = GetAchievementManager();
		if (!manager) return;

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