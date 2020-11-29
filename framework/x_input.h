#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <thread>
#include <chrono>
#include "main.h"

extern FARPROC p[7];
extern HMODULE originalXINPUT;

DWORD WINAPI Load(LPVOID lpParam);