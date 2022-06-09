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
#include "gui-helpers.hpp"

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

			if (ImGui::CollapsingHeader("Replay##debug"))
			{
				synchronized(Replay::replayEventMutex) {
					size_t numWalkPoints = 0;
					for (const auto& pair : State.replayWalkPolylineByPlayer) {
						numWalkPoints += pair.second.pendingPoints.size() + pair.second.simplifiedPoints.size();
					}
					ImGui::Text("Num Walk Points: %d", numWalkPoints);
					ImGui::Text("Num Live Events: %d", State.liveReplayEvents.size());
				}

				ImGui::Text("ReplayMatchStart: %s", std::format("{:%OH:%OM:%OS}", State.MatchStart).c_str());
				ImGui::Text("ReplayMatchCurrent: %s", std::format("{:%OH:%OM:%OS}", State.MatchCurrent).c_str());
				ImGui::Text("ReplayMatchLive: %s", std::format("{:%OH:%OM:%OS}", std::chrono::system_clock::now()).c_str());
				ImGui::Text("ReplayIsLive: %s", (State.Replay_IsLive) ? "True" : "False");
				ImGui::Text("ReplayIsPlaying: %s", (State.Replay_IsPlaying) ? "True" : "False");

				if (ImGui::Button("Re-simplify polylines (check console)"))
				{
					SYNCHRONIZED(Replay::replayEventMutex);
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
			}

			if (ImGui::CollapsingHeader("Colors##debug"))
			{
				il2cpp::Array colArr = app::Palette__TypeInfo->static_fields->PlayerColors;
				auto colArr_raw = colArr.begin();
				size_t length = colArr.size();
				for (size_t i = 0; i < length; i++)
				{
					const app::Color32& col = colArr_raw[i];
					const ImVec4& conv_col = AmongUsColorToImVec4(col);
					static constexpr std::array COLORS = { "Red", "Blue", "Dark Green", "Pink", "Orange", "Yellow", "Black", "White", "Purple", "Brown", "Cyan", "Lime", "Maroon", "Rose", "Banana", "Gray", "Tan", "Coral" };
					ImGui::TextColored(conv_col, "%s [%d]: (%d, %d, %d, %d)", COLORS.at(i), i, col.r, col.g, col.b, col.a);
				}
			}

			if (ImGui::CollapsingHeader("Profiler##debug"))
			{
				if (ImGui::Button("Clear Stats"))
				{
					Profiler::ClearStats();
				}

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
			}

			ImGui::EndTabItem();
		}
	}
}