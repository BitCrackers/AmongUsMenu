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

// test autoRelease main ver increment

HMODULE hModule;
HANDLE hUnloadEvent;

std::string GetCRC32(std::filesystem::path filePath) {
	CRC32 crc32;
	char buffer[4096] = { 0 };

	std::ifstream fin(filePath, std::ifstream::binary);

	while (!fin.eof()) {
		fin.read(&buffer[0], 4096);
		auto readSize = fin.gcount();
		crc32.add(&buffer[0], (size_t) readSize);
	}
	//LOG_DEBUG("CRC32 of \"" + filePath.u8string() + "\" is " + crc32.getHash());
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

	std::string gameAssemblyCRC = GetCRC32(gameAssembly); //We won't use this, but it will log it

	return true;
}

#define ToString(s) stringify(s)
#define stringify(s) #s

#define GAME_STATIC_POINTER(f,c,m) \
	do \
	{ \
		assert(cctor_finished(c##__TypeInfo->_0.klass)); \
		f = &(c##__TypeInfo->static_fields->m); \
		std::ostringstream ss; \
		ss << std::internal << std::setfill('0') << std::hex << std::setw(8) \
		 << stringify(f) << " is 0x" << f << " -> 0x" << *f; \
		LOG_DEBUG(ss.str()); \
	} while (0);

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
	ScopedThreadAttacher managedThreadAttached;
	{
		std::ostringstream ss;
		ss << "\n\tAmongUsMenu - " << __DATE__ << " - " << __TIME__ << std::endl; // Log amongusmenu info
		ss << "\tBuild: " << _CONFIGURATION_NAME << std::endl;
		ss << "\tCommit: " << GetGitCommit() << " - " << GetGitBranch() << std::endl; // Log git info
		ss << "\tAmong Us Version: " << getGameVersion() << std::endl; // Log among us info
		LOG_INFO(ss.str());
	}
	State.Load();
#if _DEBUG
	hUnloadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	#define DO_APP_CLASS(n, s) if(!n ## __TypeInfo) printf("Unable to locate %s\n", #n "__TypeInfo")
	#include "il2cpp-classes.h"
	#undef DO_APP_CLASS

	#define DO_APP_FUNC(r, n, p, s) if(!n) printf("Unable to locate %s\n", #n)
	#include "il2cpp-functions.h"
	#undef DO_APP_FUNC
	/*
	auto domain = il2cpp_domain_get();
	auto assembly = il2cpp_domain_assembly_open(domain, "Assembly-CSharp");
	auto klass = il2cpp_class_from_name(assembly->image, "", "MovingPlatformBehaviour");
	output_class_methods(klass);
	*/
#endif
	GAME_STATIC_POINTER(Game::pAmongUsClient, app::AmongUsClient, Instance);
	GAME_STATIC_POINTER(Game::pGameData, app::GameData, Instance);
	GAME_STATIC_POINTER(Game::pAllPlayerControls, app::PlayerControl, AllPlayerControls);
	GAME_STATIC_POINTER(Game::pLocalPlayer, app::PlayerControl, LocalPlayer);
	GAME_STATIC_POINTER(Game::pShipStatus, app::ShipStatus, Instance);
	GAME_STATIC_POINTER(Game::pLobbyBehaviour, app::LobbyBehaviour, Instance);
	LOG_DEBUG(std::format("Game::RoleManager is {}", static_cast<void*>(Game::RoleManager.GetInstance())));
	State.userName = GetPlayerName();

	Game::scanGameFunctions();
	DetourInitilization();
#if _DEBUG
	managedThreadAttached.detach();
	DWORD dwWaitResult = WaitForSingleObject(hUnloadEvent, INFINITE);
	if (dwWaitResult != WAIT_OBJECT_0) {
		STREAM_ERROR("Failed to watch unload signal! dwWaitResult = " << dwWaitResult << " Error " << GetLastError());
		return;
	}
	
	DetourUninitialization();
	fclose(stdout);
	FreeConsole();
	CloseHandle(hUnloadEvent);
	FreeLibraryAndExitThread(hModule, 0);
#endif
}
