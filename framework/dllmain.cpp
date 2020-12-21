#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "il2cpp-init.h"
#include "main.h"
#if _VERSION
#include "version.h"
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
#if _VERSION
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Load, hModule, NULL, NULL);
#else
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Run, hModule, NULL, NULL);
#endif
		break;
	case DLL_PROCESS_DETACH:
#if _VERSION
		FreeLibrary(version_dll);
#endif
		break;
	}
	return TRUE;
}