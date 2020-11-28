#include "x_input.h"

FARPROC p[7];
HMODULE originalXINPUT = NULL;

void loadOriginalINPUT() {
	char dllpath[MAX_PATH];
	GetSystemDirectoryA(dllpath, MAX_PATH);
	strcat_s(dllpath, "\\xinput1_3.dll");
	originalXINPUT = LoadLibraryA(dllpath);

	if (!originalXINPUT)
		return;

	p[0] = GetProcAddress(originalXINPUT, "XInputEnable");
	p[1] = GetProcAddress(originalXINPUT, "XInputGetBatteryInformation");
	p[2] = GetProcAddress(originalXINPUT, "XInputGetCapabilities");
	p[3] = GetProcAddress(originalXINPUT, "XInputGetDSoundAudioDeviceGuids");
	p[4] = GetProcAddress(originalXINPUT, "XInputGetKeystroke");
	p[5] = GetProcAddress(originalXINPUT, "XInputGetState");
	p[6] = GetProcAddress(originalXINPUT, "XInputSetState");
}

DWORD WINAPI Load(LPVOID lpParam) {
	loadOriginalINPUT();
	if (!originalXINPUT)
		return 0;

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	Run(lpParam);

	return 0;
}

extern "C" __declspec(dllexport) void XInputEnable() {
	__asm {jmp p + 0 * 4};
}

extern "C" __declspec(dllexport) void XInputGetBatteryInformation() {
	__asm {jmp p + 1 * 4};
}

extern "C" __declspec(dllexport) void XInputGetCapabilities() {
	__asm {jmp p + 2 * 4};
}

extern "C" __declspec(dllexport) void XInputGetDSoundAudioDeviceGuids() {
	__asm {jmp p + 3 * 4};
}

extern "C" __declspec(dllexport) void XInputGetKeystroke() {
	__asm {jmp p + 4 * 4};
}

extern "C" __declspec(dllexport) void XInputGetState() {
	__asm {jmp p + 5 * 4};
}

extern "C" __declspec(dllexport) void XInputSetState() {
	__asm {jmp p + 6 * 4};
}