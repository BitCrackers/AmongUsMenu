#include "pch-il2cpp.h"
#include "_hooks.h"
#include "logger.h"	

void fakeSuccessfulLogin(EOSManager* eosManager)
{
	eosManager->fields.loginFlowFinished = true;
	EOSManager_HasSignedIn(eosManager, NULL);
}

void dEOSManager_LoginWithExistingToken(EOSManager* __this, ExternalCredentialType__Enum externalCredentialType, MethodInfo* method)
{
	LOG_DEBUG("Faking login");
	fakeSuccessfulLogin(__this);
}

void dEOSManager_LogInWithDeviceID(EOSManager* __this, MethodInfo* method)
{
	LOG_DEBUG("Faking login");
	fakeSuccessfulLogin(__this);
}

void dEOSManager_LoginWithCorrectPlatform(EOSManager* __this, MethodInfo* method)
{
	LOG_DEBUG("Faking login");
	fakeSuccessfulLogin(__this);
}

void dEOSManager_InitializePlatformInterface(EOSManager* __this, MethodInfo* method)
{
	LOG_DEBUG("Skipping device identification");
	__this->fields.platformInitialized = false;
}