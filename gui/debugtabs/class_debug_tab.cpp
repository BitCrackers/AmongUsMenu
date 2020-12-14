#include "class_debug_tab.h"
namespace ClassDebugTab
{
	DebugHelper::TranslatedClassHelper selectedClass;
	DebugHelper::TranslatedFieldTypeHelper selectedField;
	std::vector<DebugHelper::TranslatedClassHelper> classList;
	bool init = false;
	void Render() 
	{
		if (!init)
			ClassDebugTab::Init();
		if (ImGui::BeginTabItem("Classes")) {
			ImGui::BeginChild("classes#list", ImVec2(250, 0), true);
			if (ImGui::ListBoxHeader("", ImVec2(-1, -1)))
			{
				for (auto classIter : classList)
				{
					//filter out here
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
					if (ImGui::Selectable(std::string("##" + classIter.translatedName).c_str(), (selectedClass.classReference == classIter.classReference))) {
						selectedClass = classIter;
					}
					ImGui::SameLine();
					ImGui::PopStyleVar(2);
					ImGui::Dummy(ImVec2(0, 0));
					ImGui::SameLine();
					ImGui::Text("%s", classIter.translatedName.c_str());
				}
				ImGui::ListBoxFooter();	
			}
			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("classmembers#list", ImVec2(-1, -1), true);
			if (selectedClass.classReference != NULL)
			{
				ImGui::Text("Fields");
				if (ImGui::ListBoxHeader("##fieldlist", ImVec2(-1, 200)))
				{
					auto fieldList = DebugHelper::GetFieldTypesFromClass(selectedClass.classReference);

					for (auto field : fieldList)
					{
						//filter out here
						ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
						if (ImGui::Selectable(std::string("##" + field.translatedName).c_str(), selectedField.fieldReference == field.fieldReference)) {
							selectedField = field;
						}
						ImGui::SameLine();
						ImGui::PopStyleVar(2);
						ImGui::Dummy(ImVec2(0, 0));
						ImGui::SameLine();
						ImGui::Text("%s %s", get_type_name(field.fieldReference->type).c_str(), field.translatedName.c_str());
					}
					ImGui::ListBoxFooter();
				}
				ImGui::Text("Methods");
				if (ImGui::ListBoxHeader("##methodlist", ImVec2(-1, 250)))
				{
					ImGui::ListBoxFooter();
				}
			}

			ImGui::EndChild();
			ImGui::EndTabItem();
		}
	}

	void Init()
	{
		auto domain = il2cpp_domain_get();
		auto assembly = il2cpp_domain_assembly_open(domain, "Assembly-CSharp");
		auto csharpimage = il2cpp_assembly_get_image(assembly);
		classList = DebugHelper::GetClassesFromImage(csharpimage);
		init = true;
	}
}