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
			ImGui::SameLine(0.0f, 1.0f);
			if (ImGui::Button("Force Save Settings"))
			{
				State.Save();
			}
			if (ImGui::Button("Dump PlayerControl methods"))
			{
				auto domain = il2cpp_domain_get();
				auto assembly = il2cpp_domain_assembly_open(domain, "Assembly-CSharp");
				
				auto klass = il2cpp_class_from_name(assembly->image, "", "BHHCHKFKPOE");
				output_class_methods(klass);
			}

			ImGui::EndTabItem();
		}
	}
}