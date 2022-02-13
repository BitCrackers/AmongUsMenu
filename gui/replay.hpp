#pragma once
#include <mutex>
#include "imgui/imgui.h"

namespace Replay
{
	extern std::mutex replayEventMutex;
	void Init();
	void Reset();
	void Render();

	struct WalkEvent_LineData
	{
		uint8_t playerId;
		uint8_t colorId;
		std::vector<ImVec2> pendingPoints;
		std::vector<ImVec2> simplifiedPoints;
	};
}