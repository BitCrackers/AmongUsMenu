#include "pch-il2cpp.h"
#include "_hooks.h"
#include "logger.h"	

void fakeSuccessfulLogin(EOSManager* eosManager)
{
	eosManager->fields.loginFlowFinished = true;
	EOSManager_HasFinishedLoginFlow(eosManager, NULL);
}

void dEOSManager_LoginFromAccountTab(EOSManager* __this, MethodInfo* method)
{
	//EOSManager_DeleteDeviceID(__this, NULL);
	EOSManager_LoginFromAccountTab(__this, method);
	//LOG_DEBUG("Faking login");
	//fakeSuccessfulLogin(__this);
}

void dEOSManager_InitializePlatformInterface(EOSManager* __this, MethodInfo* method)
{
	EOSManager_InitializePlatformInterface(__this, method);
	//LOG_DEBUG("Skipping device identification");
	//__this->fields.platformInitialized = true;
}

bool dEOSManager_IsFreechatAllowed(EOSManager* __this, MethodInfo* method)
{
	return app::EOSManager_IsFreechatAllowed(__this, method);
	//SaveManager__TypeInfo->static_fields->chatModeType = (uint32_t)QuickChatModes__Enum::FreeChatOrQuickChat;
	//return true;
}

void dEOSManager_UpdatePermissionKeys(EOSManager* __this, void* callback, MethodInfo* method) {
	__this->fields.isKWSMinor = false;
	app::EOSManager_UpdatePermissionKeys(__this, callback, method);
}