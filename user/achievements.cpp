#include "pch-il2cpp.h"
#include "utility.h"
#include "achievements.hpp"
#include "logger.h"

namespace Achievements {

	_Ret_maybenull_ AchievementManager_1* GetAchievementManager() {
		static AchievementManager_1* manager = nullptr;
		if (!manager) {
			static AccountManager* accountManager = nullptr;
			if (!accountManager) {
				Type* AccountManagerType = app::Type_GetType(convert_to_string(translate_type_name("AccountManager, Assembly-CSharp")), NULL);
				LOG_ASSERT(AccountManagerType != nullptr);
				il2cpp::Array results = app::Object_1_FindObjectsOfType(AccountManagerType, NULL);
				if (results.size() == 0)
					return nullptr;
				accountManager = reinterpret_cast<AccountManager*>(results[0]);
			}

			if (accountManager->fields.prevLoggedInStatus == EOSManager_AccountLoginStatus__Enum::Offline)
				return nullptr;

			Type* AchievementManagerType = app::Type_GetType(convert_to_string(translate_type_name("AchievementManager, Assembly-CSharp")), NULL);
			LOG_ASSERT(AchievementManagerType != nullptr);
			il2cpp::Array results = app::Object_1_FindObjectsOfType(AchievementManagerType, NULL);
			if (results.size() == 0)
				return nullptr;
			manager = reinterpret_cast<AchievementManager_1*>(results[0]);
		}
		return manager;
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