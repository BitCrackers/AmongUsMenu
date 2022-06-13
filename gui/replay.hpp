#pragma once
#include "imgui/imgui.h"
#include <mutex>
#include <chrono>
#include "game.h"

namespace Replay
{
	extern std::mutex replayEventMutex;
	void Init();
	void Reset(bool all = true);
	void Render();

	struct WalkEvent_LineData
	{
		Game::PlayerId playerId = Game::NoPlayerId;
		Game::ColorId colorId = Game::NoColorId;
		std::vector<ImVec2> pendingPoints;
		std::vector<std::chrono::system_clock::time_point> pendingTimeStamps;

		std::vector<ImVec2> simplifiedPoints;
		std::vector<std::chrono::system_clock::time_point> simplifiedTimeStamps;
	};
}