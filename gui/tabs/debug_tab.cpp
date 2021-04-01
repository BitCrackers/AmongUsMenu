#include "pch-il2cpp.h"
#include "debug_tab.h"
#include "imgui/imgui.h"
#include "state.hpp"
#include "main.h"
#include "game.h"
#include <iostream>

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
			if (ImGui::Button("Log")) {
				Vector2 spawn = (*Game::pShipStatus)->fields.InitialSpawnCenter;
				std::cout << spawn.x << ", " << spawn.y << "\n";
			}
			ImGui::EndTabItem();
		}
	}
}