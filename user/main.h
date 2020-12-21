#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern HMODULE hModule;
extern HANDLE hUnloadEvent;

void Run(LPVOID lpParam);