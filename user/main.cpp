#include "main.h"

using namespace app;

extern const LPCWSTR LOG_FILE = L"debug.txt";

void Run(LPVOID lpParam) {
	if (getGameVersion().compare(GAME_VERSION) != 0) {
		MessageBox(NULL, L"This Game Version is not supported!", L"AmongUsMenu", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		FreeLibraryAndExitThread((HMODULE)lpParam, 0);
		return;
	}

#if _DEBUG
	new_console();

	using namespace app;

	#define DO_APP_CLASS(n, s) printf("%s = %p\n", #n "__TypeInfo" , n ## __TypeInfo)
	#include "il2cpp-classes.h"
	#undef DO_APP_CLASS

	#define DO_APP_FUNC(r, n, p, s) printf("%s = %p\n", #n, n)
	#include "il2cpp-functions.h"
	#undef DO_APP_FUNC

	/*auto domain = il2cpp_domain_get();
	auto assembly = il2cpp_domain_assembly_open(domain, "Assembly-CSharp");
	auto klass = il2cpp_class_from_name(assembly->image, "", "GPOHFPAIEMA");
	output_class_methods(klass);*/
#endif

	Game::pAmongUsClient = &(app::AmongUsClient__TypeInfo->static_fields->Instance);
	Game::pGameData = &(app::GameData__TypeInfo->static_fields->Instance);
	Game::pGameOptionsData = &(app::PlayerControl__TypeInfo->static_fields->GameOptions);
	Game::pAllPlayerControls = &(app::PlayerControl__TypeInfo->static_fields->AllPlayerControls);
	Game::pLocalPlayer = &(app::PlayerControl__TypeInfo->static_fields->LocalPlayer);
	Game::pShipStatus = &(app::ShipStatus__TypeInfo->static_fields->Instance);

	DetourInitilization();
}