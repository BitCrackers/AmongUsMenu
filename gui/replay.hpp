#pragma once
#include "imgui/imgui.h"
#include <mutex>
#include <chrono>

namespace Replay
{
	extern std::mutex replayEventMutex;
	void Init();
	void Reset(bool all = true);
	void Render();

	struct WalkEvent_LineData
	{
		uint8_t playerId;
		uint8_t colorId;
		std::vector<ImVec2> pendingPoints;
		std::vector<std::chrono::system_clock::time_point> pendingTimeStamps;

		std::vector<ImVec2> simplifiedPoints;
		std::vector<std::chrono::system_clock::time_point> simplifiedTimeStamps;
	};
}