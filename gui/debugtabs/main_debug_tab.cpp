#include "main_debug_tab.h"
namespace MainDebugTab {

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
			if (ImGui::Button("Force Load Settings"))
			{
				State.Load();
			}
			ImGui::SameLine(0.0f, 8.0f);
			if (ImGui::Button("Force Save Settings"))
			{
				State.Save();
			}

			ImGui::EndTabItem();
		}
	}
}