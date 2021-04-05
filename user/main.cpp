#include "pch-il2cpp.h"
#include "main.h"
#include "il2cpp-init.h"
#include <VersionHelpers.h>
#include "crc32.h"
#include <shellapi.h>
#include <iostream>
#include "game.h"
#include "_hooks.h"
#include "logger.h"
#include "state.hpp"
#include "version.h"
#include <fstream>
#include <sstream>
#include "gitparams.h"

HMODULE hModule;
HANDLE hUnloadEvent;

std::string GetCRC32(std::filesystem::path filePath) {
	CRC32 crc32;
	char buffer[4096];

	std::ifstream fin(filePath, std::ifstream::binary);

	while (!fin.eof()) {
		fin.read(&buffer[0], 4096);
		auto readSize = fin.gcount();
		crc32.add(&buffer[0], (size_t) readSize);
	}
	LOG_DEBUG("CRC32 of \"" + filePath.u8string() + "\" is " + crc32.getHash());
	return crc32.getHash();
}

bool GameVersionCheck() {
	auto modulePath = getModulePath(NULL);
	auto gameAssembly = modulePath.parent_path() / "GameAssembly.dll";
	auto steamApi = modulePath.parent_path() / "Among Us_Data" / "Plugins" / "x86" / "steam_api.dll";

	if (!IsWindows10OrGreater()) {
		Log.Error("Version of windows not supported exiting!");
		MessageBox(NULL, L"This version of Windows is not supported!", L"AmongUsMenu", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return false;
	}

	if (!std::filesystem::exists(gameAssembly)) {
		Log.Error("GameAssembly.dll was not found");
		MessageBox(NULL, L"Unable to locate GameAssembly.dll", L"AmongUsMenu", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return false;
	}

	if (GetCRC32(gameAssembly) != "6df51577") {
		Log.Error("GameAssembly.dll is either not the right version or corrupted");
		MessageBox(NULL, L"GameAssembly.dll is either not the right version or corrupted", L"AmongUsMenu", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return false;
	}

	if (std::filesystem::exists(steamApi) && GetCRC32(steamApi) != "815ba560") {
		Log.Error("SteamApi not found or incorrect version");
		ShellExecute(NULL, NULL, L"https://store.steampowered.com/app/945360/Among_Us/", NULL, NULL, SW_SHOW);
	}

	return true;
}

bool cctor_finished(Il2CppClass* klass)
{
	while (klass->has_cctor && !klass->cctor_finished);
	return true;
}

#define IL2CPP_STATIC_FIELD(f,c,m) \
	while (c##__TypeInfo->_0.klass->has_cctor && !c##__TypeInfo->_0.klass->cctor_finished); \
	f = &(c##__TypeInfo->static_fields->m);

void Run(LPVOID lpParam) {
#if _DEBUG
	new_console();
#endif
	Log.Create();
	if (!GameVersionCheck()) {
		fclose(stdout);
		FreeConsole();
		FreeLibraryAndExitThread((HMODULE)lpParam, 0);
		return;
	}

	hModule = (HMODULE)lpParam;
	init_il2cpp();
	std::ostringstream ss;
	ss << "\n\tAmongUsMenu - " << __DATE__ << " - " << __TIME__ << std::endl; // Log amongusmenu info
	ss << "\tBuild: " << _CONFIGURATION_NAME << std::endl;
	ss << "\tCommit: " << GetGitCommit() << " - " << GetGitBranch() << std::endl; // Log git info
	ss << "\tAmong Us Version: " << getGameVersion() << std::endl; // Log among us info
	LOG_INFO(ss.str());
	State.Load();
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

	IL2CPP_STATIC_FIELD(Game::pAmongUsClient, app::AmongUsClient, Instance);
	IL2CPP_STATIC_FIELD(Game::pGameData, app::GameData, Instance);
	IL2CPP_STATIC_FIELD(Game::pGameOptionsData, app::PlayerControl, GameOptions);
	IL2CPP_STATIC_FIELD(Game::pAllPlayerControls, app::PlayerControl, AllPlayerControls);
	IL2CPP_STATIC_FIELD(Game::pLocalPlayer, app::PlayerControl, LocalPlayer);
	IL2CPP_STATIC_FIELD(Game::pShipStatus, app::ShipStatus, Instance);
	IL2CPP_STATIC_FIELD(Game::pLobbyBehaviour, app::LobbyBehaviour, Instance);
	/*
	Game::pAmongUsClient = &(app::AmongUsClient__TypeInfo->static_fields->Instance);
	Game::pGameData = &(app::GameData__TypeInfo->static_fields->Instance);
	Game::pGameOptionsData = &(app::PlayerControl__TypeInfo->static_fields->GameOptions);
	Game::pAllPlayerControls = &(app::PlayerControl__TypeInfo->static_fields->AllPlayerControls);
	Game::pLocalPlayer = &(app::PlayerControl__TypeInfo->static_fields->LocalPlayer);
	Game::pShipStatus = &(app::ShipStatus__TypeInfo->static_fields->Instance);
	Game::pLobbyBehaviour = &(app::LobbyBehaviour__TypeInfo->static_fields->Instance);
	*/
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
