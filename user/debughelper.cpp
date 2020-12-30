#include "pch-il2cpp.h"
#include "debughelper.h"
#include <assert.h>

namespace DebugHelper
{
	TranslatedClassHelper::TranslatedClassHelper()
	{
		this->classReference = NULL;
	}
	TranslatedClassHelper::TranslatedClassHelper(const Il2CppClass* ref)
	{
		this->classReference = ref;
		KLASS translated_klass = translate_klass(KLASS({ "", ref->name }));
		this->translatedName = translated_klass.klass_name;
	}

	TranslatedFieldTypeHelper::TranslatedFieldTypeHelper()
	{
		this->fieldReference = NULL;
	}
	TranslatedFieldTypeHelper::TranslatedFieldTypeHelper(const FieldInfo* ref)
	{
		this->fieldReference = ref;
		this->translatedName = translate_type_name(il2cpp_field_get_name((FieldInfo*)ref));
	}

	TranslatedMethodTypeHelper::TranslatedMethodTypeHelper()
	{
		this->methodReference = NULL;
	}
	TranslatedMethodTypeHelper::TranslatedMethodTypeHelper(const MethodInfo* ref)
	{
		this->methodReference = ref;
		this->translatedName = translate_method_name(il2cpp_method_get_name(ref));
	}

	std::vector<TranslatedClassHelper> GetClassesFromImage(const Il2CppImage* image)
	{
		assert(image != NULL);
		auto allClasses = std::vector<TranslatedClassHelper>();
		auto classCount = il2cpp_image_get_class_count(image);

		for (size_t classidx = 0; classidx < classCount; classidx++)
		{
			auto il2class = il2cpp_image_get_class(image, classidx);
			auto classType = TranslatedClassHelper(il2class);
			if (!classType.translatedName.empty() && classType.translatedName != "<>c")
				allClasses.push_back(classType);
		}
		return allClasses;
	}

	std::vector<TranslatedMethodTypeHelper> GetMethodsFromClass(const Il2CppClass* klass) {
		auto methods = std::vector<TranslatedMethodTypeHelper>();
		assert(klass != NULL);

		void* iterator = NULL;
		const MethodInfo* method = NULL;
		while ((method = il2cpp_class_get_methods((Il2CppClass*)klass, &iterator)) != NULL) {
			methods.push_back(method);
		}
		return methods;
	}

	std::vector<TranslatedFieldTypeHelper> GetFieldTypesFromClass(const Il2CppClass* klass)
	{
		auto fields = std::vector<TranslatedFieldTypeHelper>();
		assert(klass != NULL);

		void* iterator = NULL;
		const FieldInfo* field = NULL;
		while ((field = il2cpp_class_get_fields((Il2CppClass*)klass, &iterator)) != NULL) {
			fields.push_back(field);
		}

		return fields;
	}
}