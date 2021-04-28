#pragma once
#include <mutex>

namespace Radar
{
	extern std::mutex radarEventMutex;
	void Init();
	void Render();
}