#pragma once
#include <mutex>

namespace Replay
{
	extern std::mutex replayEventMutex;
	void Init();
	void Render();
}