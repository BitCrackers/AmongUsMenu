#include "debughelper.h"

namespace DebugHelper
{
	std::vector<TranslatedClassHelper> GetClassesFromImage(const Il2CppImage* image)
	{
		assert(image != NULL);
		auto allClasses = std::vector<TranslatedClassHelper>();
		auto classCount = il2cpp_image_get_class_count(image);

		for (size_t classidx = 0; classidx < classCount; classidx++)
		{
			auto il2class = il2cpp_image_get_class(image, classidx);
			allClasses.push_back(TranslatedClassHelper(il2class));
		}
		return allClasses;
	}

	std::vector<const MethodInfo*> GetMethodsFromClass(const Il2CppClass* klass) {
		auto methods = std::vector<const MethodInfo*>();
		assert(klass != NULL);

		void* iterator = NULL;
		const MethodInfo* method = NULL;
		while ((method = il2cpp_class_get_methods((Il2CppClass*)klass, &iterator)) != NULL) {

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