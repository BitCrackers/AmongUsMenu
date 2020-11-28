#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "il2cpp-init.h"
#include "main.h"
#include "state.hpp"
#if _XINPUT
#include "x_input.h"
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		State.Load();
		DisableThreadLibraryCalls(hModule);
		init_il2cpp();
#if _XINPUT
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Load, hModule, NULL, NULL);
#else
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Run, hModule, NULL, NULL);
#endif
		break;
	case DLL_PROCESS_DETACH:
		State.Save();
#if _XINPUT
		FreeLibrary(originalXINPUT);
#endif
		break;
	}
	return TRUE;
}