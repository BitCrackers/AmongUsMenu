#include "debug_tab.h"

namespace DebugTab {

	void Render() {
		if (ImGui::BeginTabItem("Debug")) {
			if (ImGui::Button("Unload DLL"))
			{
				SetEvent(hUnloadEvent);
			}
			ImGui::EndTabItem();
		}
	}
}