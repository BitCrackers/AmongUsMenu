#pragma once
#include <mutex>

namespace Replay
{
	extern std::mutex replayEventMutex;
	void Init();
	void Reset();
	void Render();

	struct WalkEvent_LineData
	{
		float mapX = 0.f;
		float mapY = 0.f;
	};
}