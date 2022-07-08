#include "pch-il2cpp.h"
#include "_hooks.h"
#include "logger.h"

void dAccountManager_UpdateKidAccountDisplay(AccountManager* __this, MethodInfo* method) {
    // grant permissions
    __this->fields.freeChatAllowed = KWSPermissionStatus__Enum::Granted;
    __this->fields.customDisplayName = KWSPermissionStatus__Enum::Granted;
    __this->fields.friendsListAllowed = KWSPermissionStatus__Enum::Granted;
    app::AccountManager_UpdateKidAccountDisplay(__this, method);
}