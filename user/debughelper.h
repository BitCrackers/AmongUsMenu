#pragma once
#include <assert.h>
#include "il2cpp-helpers.h"

namespace DebugHelper
{
	struct TranslatedClassHelper
	{
		const Il2CppClass* classReference;
		std::string translatedName;
		TranslatedClassHelper()
		{
			this->classReference = NULL;
		}
		TranslatedClassHelper(const Il2CppClass* ref)
		{
			this->classReference = ref;
			KLASS translated_klass = translate_klass(KLASS({"", ref->name }));
			this->translatedName = translated_klass.klass_name;
		}
	};

	struct TranslatedFieldTypeHelper
	{
		const FieldInfo* fieldReference;
		std::string translatedName;
		TranslatedFieldTypeHelper()
		{
			this->fieldReference = NULL;
		}
		TranslatedFieldTypeHelper(const FieldInfo* ref)
		{
			this->fieldReference = ref;
			this->translatedName = translate_type_name(il2cpp_field_get_name((FieldInfo*)ref));
		}
	};

	std::vector<TranslatedClassHelper> GetClassesFromImage(const Il2CppImage* image);
	std::vector<const MethodInfo*> GetMethodsFromClass(const Il2CppClass* klass);
	std::vector<TranslatedFieldTypeHelper> GetFieldTypesFromClass(const Il2CppClass* klass);
	
}