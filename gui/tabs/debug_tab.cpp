#include "pch-il2cpp.h"
#include "debug_tab.h"
#include "imgui/imgui.h"
#include "state.hpp"
#include "main.h"
#include "game.h"
#include "profiler.h"
#include <iostream>
#include <sstream>

namespace DebugTab {

	void Render() {
		if (ImGui::BeginTabItem("Debug")) {
			ImGui::Dummy(ImVec2(4, 4));
#ifndef _VERSION
			if (ImGui::Button("Unload DLL"))
			{
				SetEvent(hUnloadEvent);
			}
			ImGui::Dummy(ImVec2(4, 4));
#endif
			ImGui::Checkbox("Enable Occlusion Culling", &State.OcclusionCulling);
			ImGui::Dummy(ImVec2(4, 4));

			if (ImGui::Button("Force Load Settings"))
			{
				State.Load();
			}
			if (ImGui::Button("Force Save Settings"))
			{
				State.Save();
			}

			ImGui::Dummy(ImVec2(4, 4));

			ImGui::Checkbox("Log Unity Debug Messages", &State.ShowUnityLogs);

			ImGui::Dummy(ImVec2(4, 4));

			if (ImGui::CollapsingHeader("Profiler"))
			{
				if (ImGui::Button("Clear Stats"))
				{
					Profiler::ClearStats();
				}

				ImGui::BeginChild("debug#profiler", ImVec2(0, 0), true);

				std::stringstream statStream;
				Profiler::AppendStatStringStream("ReplayRender", statStream);
				Profiler::AppendStatStringStream("ReplayLoop", statStream);
				Profiler::AppendStatStringStream("ReplayFilter", statStream);
				Profiler::AppendStatStringStream("ReplayCoreLoopIter", statStream);
				Profiler::AppendStatStringStream("ReplayKillEvent", statStream);
				Profiler::AppendStatStringStream("ReplayVentEvent", statStream);
				Profiler::AppendStatStringStream("ReplayTaskEvent", statStream);
				Profiler::AppendStatStringStream("ReplayMeetingEvent", statStream);
				Profiler::AppendStatStringStream("ReplayWalkEvent", statStream);
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