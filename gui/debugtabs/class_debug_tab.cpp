#include "class_debug_tab.h"
namespace ClassDebugTab
{
	DebugHelper::TranslatedClassHelper selectedClass;
	DebugHelper::TranslatedFieldTypeHelper selectedField;
	DebugHelper::TranslatedMethodTypeHelper selectedMethod;
	std::vector<DebugHelper::TranslatedClassHelper> classList;
	std::vector<DebugHelper::TranslatedFieldTypeHelper> fieldList;
	std::vector<DebugHelper::TranslatedMethodTypeHelper> methodList;
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
						methodList = DebugHelper::GetMethodsFromClass(selectedClass.classReference);
						fieldList = DebugHelper::GetFieldTypesFromClass(selectedClass.classReference);
						selectedField = DebugHelper::TranslatedFieldTypeHelper(); //Reset
						selectedMethod = DebugHelper::TranslatedMethodTypeHelper(); //Reset
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
				ImGui::Text("Methods");
				if (ImGui::ListBoxHeader("##methodlist", ImVec2(-1, 200)))
				{
					for (auto method : methodList)
					{
						//filter out here
						ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
						if (ImGui::Selectable(std::string("##" + method.translatedName).c_str(), selectedMethod.methodReference == method.methodReference)) {
							selectedMethod = method;
						}
						ImGui::SameLine();
						ImGui::PopStyleVar(2);
						ImGui::Dummy(ImVec2(0, 0));
						ImGui::SameLine();
						ImGui::Text("%s(%s)", method.translatedName.c_str(), get_method_params(method.methodReference).c_str());
					}

					ImGui::ListBoxFooter();
				}
				if (selectedMethod.methodReference != NULL && ImGui::Button("Output method to console"))
				{
					std::cout << get_method_description(selectedMethod.methodReference) << std::endl;
				}
				ImGui::Text("Fields");
				if (ImGui::ListBoxHeader("##fieldlist", ImVec2(-1, -1)))
				{
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