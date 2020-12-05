#include "debug_tab.h"

namespace DebugTab {

	void Render() {
		if (ImGui::BeginTabItem("Debug")) {
#ifndef _XINPUT
			if (ImGui::Button("Unload DLL"))
			{
				SetEvent(hUnloadEvent);
			}
#endif
			ImGui::EndTabItem();
		}
	}
}