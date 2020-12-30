#include "pch-il2cpp.h"
#include "translations_debug_tab.h"
#include <imgui/imgui.h>
#include "imgui/imgui_internal.h"
#include "_hooks.h"
#include "main.h"

namespace TranslationsDebugTab {

	KLASS_PAIR selectedClass;
	std::pair<std::string, std::string> selectedMethod;

	void Render() {
		if (ImGui::BeginTabItem("Translations")) {
			ImGui::Dummy(ImVec2(4, 4));
			ImGui::BeginChild("classtranslations#list", ImVec2(0, 250), true);
			if (ImGui::ListBoxHeader("", ImVec2(-1, -1)))
			{
				for (auto klass : KLASS_TRANSLATIONS)
				{
					//filter out here
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
					if (ImGui::Selectable(std::string("##" + klass.deobfuscated_klass.klass_name).c_str(), (selectedClass.deobfuscated_klass == klass.deobfuscated_klass))) {
						selectedClass = klass;
					}
					ImGui::SameLine();
					ImGui::PopStyleVar(2);
					ImGui::Dummy(ImVec2(0, 0));
					ImGui::SameLine();
					ImGui::Text("%s -> %s", klass.deobfuscated_klass.klass_name.c_str(), klass.obfuscated_klass.klass_name.c_str());
				}
				ImGui::ListBoxFooter();
			}
			ImGui::EndChild();
			ImGui::BeginChild("methodtranslations#list", ImVec2(0, 250), true);
			if (ImGui::ListBoxHeader("", ImVec2(-1, -1)))
			{
				for (auto method : METHOD_TRANSLATIONS)
				{
					//filter out here
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
					if (ImGui::Selectable(std::string("##" + method.first).c_str(), selectedMethod == method)) {
						selectedMethod = method;
					}
					ImGui::SameLine();
					ImGui::PopStyleVar(2);
					ImGui::Dummy(ImVec2(0, 0));
					ImGui::SameLine();
					ImGui::Text("%s -> %s", method.first.c_str(), method.second.c_str());
				}
				ImGui::ListBoxFooter();
			}
			ImGui::EndChild();

			ImGui::EndTabItem();
		}
	}

}