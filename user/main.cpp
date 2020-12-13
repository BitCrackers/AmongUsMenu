#include "main.h"
#include "il2cpp-init.h"
#include <VersionHelpers.h>
#include "crc32.h"
#include <shellapi.h>

using namespace app;

HMODULE hModule;
HANDLE hUnloadEvent;

std::string GetCRC32(std::filesystem::path filePath) {
	CRC32 crc32;
	char buffer[4096];

	std::ifstream fin(filePath, std::ifstream::binary);

	while (!fin.eof()) {
		fin.read(&buffer[0], 4096);
		auto readSize = fin.gcount();
		crc32.add(&buffer[0], readSize);
	}

	return crc32.getHash();
}

bool GameVersionCheck() {
	auto modulePath = getModulePath(NULL);
	auto gameAssembly = modulePath.parent_path() / "GameAssembly.dll";
	auto steamApi = modulePath.parent_path() / "Among Us_Data" / "Plugins" / "x86" / "steam_api.dll";

	if (!IsWindows10OrGreater()) {
		MessageBox(NULL, L"This version of Windows is not supported!", L"AmongUsMenu", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return false;
	}

	if (!std::filesystem::exists(gameAssembly)) {
		MessageBox(NULL, L"Unable to locate GameAssembly.dll", L"AmongUsMenu", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return false;
	}

	if (GetCRC32(gameAssembly) != "1bd6e116") {
		MessageBox(NULL, L"GameAssembly.dll is either not the right version or corrupted", L"AmongUsMenu", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return false;
	}

	if (std::filesystem::exists(steamApi) && GetCRC32(steamApi) != "815ba560") {
		ShellExecute(NULL, NULL, L"https://store.steampowered.com/app/945360/Among_Us/", NULL, NULL, SW_SHOW);
	}

	return true;
}

void Run(LPVOID lpParam) {
#if _DEBUG
	new_console();
#endif

	init_il2cpp();

	if (!GameVersionCheck()) {
		FreeLibraryAndExitThread((HMODULE)lpParam, 0);
		return;
	}

	hModule = (HMODULE)lpParam;
#if _DEBUG
	hUnloadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	#define DO_APP_CLASS(n, s) if(!n ## __TypeInfo) printf("Unable to locate %s\n", #n "__TypeInfo")
	#include "il2cpp-classes.h"
	#undef DO_APP_CLASS

	#define DO_APP_FUNC(r, n, p, s) if(!n) printf("Unable to locate %s\n", #n)
	#include "il2cpp-functions.h"
	#undef DO_APP_FUNC

	/*auto domain = il2cpp_domain_get();
	auto assembly = il2cpp_domain_assembly_open(domain, "Assembly-CSharp");
	auto klass = il2cpp_class_from_name(assembly->image, "", "ENHLBAECCDF");
	output_class_methods(klass);*/
#endif

	Game::pAmongUsClient = &(app::AmongUsClient__TypeInfo->static_fields->Instance);
	Game::pGameData = &(app::GameData__TypeInfo->static_fields->Instance);
	Game::pGameOptionsData = &(app::PlayerControl__TypeInfo->static_fields->GameOptions);
	Game::pAllPlayerControls = &(app::PlayerControl__TypeInfo->static_fields->AllPlayerControls);
	Game::pLocalPlayer = &(app::PlayerControl__TypeInfo->static_fields->LocalPlayer);
	Game::pShipStatus = &(app::ShipStatus__TypeInfo->static_fields->Instance);

	DetourInitilization();
#if _DEBUG
	DWORD dwWaitResult = WaitForSingleObject(hUnloadEvent, INFINITE);
	if (dwWaitResult != WAIT_OBJECT_0) {
		std::cout << "Failed to watch unload signal! dwWaitResult = " << dwWaitResult << " Error " << GetLastError() << std::endl;
		return;
	}
	
	DetourUninitialization();
	fclose(stdout);
	FreeConsole();
	CloseHandle(hUnloadEvent);
	FreeLibraryAndExitThread(hModule, 0);
#endif
}
