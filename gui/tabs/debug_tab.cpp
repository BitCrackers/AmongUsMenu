#include "pch-il2cpp.h"
#include "debug_tab.h"
#include "imgui/imgui.h"
#include "state.hpp"
#include "main.h"
#include "game.h"
#include "profiler.h"
#include "logger.h"
#include <iostream>
#include <sstream>

namespace DebugTab {

	void Render() {
		if (ImGui::BeginTabItem("Debug")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
#ifndef _VERSION
			if (ImGui::Button("Unload DLL"))
			{
				SetEvent(hUnloadEvent);
			}
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
#endif
			ImGui::Checkbox("Enable Occlusion Culling", &State.OcclusionCulling);
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if (ImGui::Button("Force Load Settings"))
			{
				State.Load();
			}
			if (ImGui::Button("Force Save Settings"))
			{
				State.Save();
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			ImGui::Checkbox("Log Unity Debug Messages", &State.ShowUnityLogs);

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			ImGui::Text("Num Raw Events: %d", State.rawEvents.size());
			ImGui::Text("Num Live Events: %d", State.liveReplayEvents.size());

			ImGui::Text("ReplayMatchStart: %s", std::format("{:%OH:%OM:%OS}", State.MatchStart).c_str());
			ImGui::Text("ReplayMatchCurrent: %s", std::format("{:%OH:%OM:%OS}", State.MatchCurrent).c_str());
			ImGui::Text("ReplayMatchLive: %s", std::format("{:%OH:%OM:%OS}", std::chrono::system_clock::now()).c_str());
			ImGui::Text("ReplayIsLive: %s", (State.Replay_IsLive) ? "True" : "False");
			ImGui::Text("ReplayIsPlaying: %s", (State.Replay_IsPlaying) ? "True" : "False");

			if (ImGui::Button("Re-simplify polylines (check console)"))
			{
				for (auto& playerPolylinePair : State.replayWalkPolylineByPlayer)
				{
					std::vector<ImVec2> resimplifiedPoints;
					std::vector<std::chrono::system_clock::time_point> resimplifiedTimeStamps;
					Replay::WalkEvent_LineData& plrLineData = playerPolylinePair.second;
					size_t numOldSimpPoints = plrLineData.simplifiedPoints.size();
					DoPolylineSimplification(plrLineData.simplifiedPoints, plrLineData.simplifiedTimeStamps, resimplifiedPoints, resimplifiedTimeStamps, 50.f, false);
					STREAM_DEBUG("Player[" << playerPolylinePair.first << "]: Re-simplification could reduce " << numOldSimpPoints << " points to " << resimplifiedPoints.size());
				}
			}

			if (ImGui::CollapsingHeader("Profiler"))
			{
				if (ImGui::Button("Clear Stats"))
				{
					Profiler::ClearStats();
				}

				ImGui::BeginChild("debug#profiler", ImVec2(0, 0) * State.dpiScale, true);

				std::stringstream statStream;
				Profiler::AppendStatStringStream("WalkEventCreation", statStream);
				Profiler::AppendStatStringStream("ReplayRender", statStream);
				Profiler::AppendStatStringStream("ReplayPolyline", statStream);
				Profiler::AppendStatStringStream("PolylineSimplification", statStream);
				Profiler::AppendStatStringStream("ReplayPlayerIcons", statStream);
				Profiler::AppendStatStringStream("ReplayEventIcons", statStream);
				// NOTE:
				// can also just do this to dump all stats, but i like doing them individually so i can control the order better:
				// Profiler::WriteStatsToStream(statStream);

				ImGui::TextUnformatted(statStream.str().c_str());

				ImGui::EndChild();
			}

			ImGui::EndTabItem();
		}
	}
}