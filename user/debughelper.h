#pragma once

namespace DebugHelper
{
	struct TranslatedClassHelper
	{
		const Il2CppClass* classReference;
		std::string translatedName;
		TranslatedClassHelper();
		TranslatedClassHelper(const Il2CppClass* ref);
	};

	struct TranslatedFieldTypeHelper
	{
		const FieldInfo* fieldReference;
		std::string translatedName;
		TranslatedFieldTypeHelper();
		TranslatedFieldTypeHelper(const FieldInfo* ref);
	};

	struct TranslatedMethodTypeHelper
	{
		const MethodInfo* methodReference;
		std::string translatedName;
		TranslatedMethodTypeHelper();
		TranslatedMethodTypeHelper(const MethodInfo* ref);
	};

	std::vector<TranslatedClassHelper> GetClassesFromImage(const Il2CppImage* image);
	std::vector<TranslatedMethodTypeHelper> GetMethodsFromClass(const Il2CppClass* klass);
	std::vector<TranslatedFieldTypeHelper> GetFieldTypesFromClass(const Il2CppClass* klass);
	
}