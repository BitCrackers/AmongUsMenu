#include "il2cpp-helpers.h"

void new_console() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

std::string utf16_to_utf8(std::u16string u16_string) {
	std::wstring wide_string(u16_string.begin(), u16_string.end());
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	return convert.to_bytes(wide_string);
}

std::string convert_from_string(Il2CppString* input) {
	std::u16string u16(reinterpret_cast<const char16_t*>(input->chars));
	return utf16_to_utf8(u16);
}

std::string convert_from_string(app::String* input) {
	std::u16string u16(reinterpret_cast<const char16_t*>(&input->fields.m_firstChar));
	return utf16_to_utf8(u16);
}

app::String* convert_to_string(std::string input) {
	return app::Marshal_PtrToStringAnsi((void*)input.c_str(), NULL);
}

KLASS translate_klass(KLASS klass_input) {
	for (auto klass_pair : KLASS_TRANSLATIONS) {
		if (klass_input == klass_pair.obfuscated_klass)
			return klass_pair.deobfuscated_klass;

		if (klass_input == klass_pair.deobfuscated_klass)
			return klass_pair.obfuscated_klass;
	}
	return klass_input;
}

std::string translate_method_name(std::string input) {
	for (auto pair : METHOD_TRANSLATIONS) {
		if (input.compare(pair.first) == 0) return pair.second;
		if (input.compare(pair.second) == 0) return pair.first;
	}
	return input;
}

std::string translate_type_name(std::string input) {
	std::optional<KLASS_PAIR> match = std::nullopt;
	int8_t conversion = 0;
	size_t match_length = 0;

	for (auto klass_pair : KLASS_TRANSLATIONS) {
		if (conversion != 1) {
			auto deobfuscated_length = klass_pair.deobfuscated_klass.contains_type(input);
			if (deobfuscated_length > match_length) {
				match = klass_pair;
				conversion = -1;
				match_length = deobfuscated_length;
			}
		}

		if (conversion != -1) {
			auto obfuscated_length = klass_pair.obfuscated_klass.contains_type(input);
			if (obfuscated_length > match_length) {
				match = klass_pair;
				conversion = 1;
				match_length = obfuscated_length;
			}
		}
	}

	if (match.has_value()) {
		auto klass_pair = match.value();
		if (conversion == -1) {
			size_t position = input.find(klass_pair.deobfuscated_klass.klass_name, 0);
			input.replace(position, klass_pair.deobfuscated_klass.klass_name.length(), klass_pair.obfuscated_klass.klass_name);
			return input;
		}

		if (conversion == 1) {
			size_t position = input.find(klass_pair.obfuscated_klass.klass_name, 0);
			input.replace(position, klass_pair.obfuscated_klass.klass_name.length(), klass_pair.deobfuscated_klass.klass_name);
			return input;
		}
	}

	return input;
}

std::string get_type_name(const Il2CppType* type) {
	return translate_type_name(il2cpp_type_get_name(type));
}

std::string get_method_params(const MethodInfo* methodInfo) {
	std::string params = "";

	for (uint32_t i = 0; i < il2cpp_method_get_param_count(methodInfo); i++) {
		if (i != 0) params.append(", ");
		params.append(get_type_name(il2cpp_method_get_param(methodInfo, i)));
	}

	return params;
}

bool method_compare(const MethodInfo* methodInfo, std::string returnType, std::string methodName, std::string paramTypes) {
	if (methodName.compare(methodInfo->name) != 0) return false;
	if (returnType.compare(get_type_name(methodInfo->return_type)) != 0) return false;
	if (paramTypes.compare(get_method_params(methodInfo)) != 0) return false;

	return true;
}

Il2CppMethodPointer find_method(Il2CppClass* klass, std::string returnType, std::string methodName, std::string paramTypes) {
	methodName = translate_method_name(methodName);

	void* iterator = NULL;
	const MethodInfo* method = NULL;

	while ((method = il2cpp_class_get_methods(klass, &iterator)) != NULL) {
		if (method_compare(method, returnType, methodName, paramTypes)) return method->methodPointer;
	}

	return NULL;
}

Il2CppMethodPointer get_method(std::string methodSignature) {
	std::string assemblyName = methodSignature.substr(0, methodSignature.find(", "));
	methodSignature.erase(0, assemblyName.length() + 2);

	std::string returnType = methodSignature.substr(0, methodSignature.find(" "));
	methodSignature.erase(0, returnType.length() + 1);

	std::string methodName = methodSignature.substr(methodSignature.rfind("::") + 2);
	methodSignature.erase(methodSignature.rfind("::"));

	std::string namespaze = "";
	if (methodSignature.rfind(".") != std::string::npos) {
		namespaze = methodSignature.substr(0, methodSignature.rfind("."));
		methodSignature.erase(0, namespaze.length() + 1);
	}

	std::string className = methodSignature;

	std::string paramTypes = methodName.substr(methodName.find("(") + 1);
	methodName.erase(methodName.rfind("("));
	paramTypes.pop_back();

	auto klass_translation = translate_klass({ namespaze, className });
	namespaze = klass_translation.namespaze;
	className = klass_translation.klass_name;

	Il2CppDomain* domain = il2cpp_domain_get();
	const Il2CppAssembly* assembly = il2cpp_domain_assembly_open(domain, assemblyName.c_str());
	if (assembly == NULL) return NULL;

	Il2CppClass* klass = il2cpp_class_from_name(assembly->image, namespaze.c_str(), className.c_str());
	if (klass == NULL) return NULL;

	return find_method(klass, returnType, methodName, paramTypes);
}

Il2CppClass* get_class(std::string classSignature) {
	std::string assemblyName = classSignature.substr(0, classSignature.find(", "));
	classSignature.erase(0, assemblyName.length() + 2);

	std::string namespaze = "";
	if (classSignature.rfind(".") != std::string::npos) {
		namespaze = classSignature.substr(0, classSignature.rfind("."));
		classSignature.erase(0, namespaze.length() + 1);
	}

	std::string className = classSignature;

	auto klass_translation = translate_klass({ namespaze, className });
	namespaze = klass_translation.namespaze;
	className = klass_translation.klass_name;

	Il2CppDomain* domain = il2cpp_domain_get();
	const Il2CppAssembly* assembly = il2cpp_domain_assembly_open(domain, assemblyName.c_str());
	if (assembly == NULL) return NULL;

	Il2CppClass* klass = il2cpp_class_from_name(assembly->image, namespaze.c_str(), className.c_str());
	return klass;
}

std::string get_method_description(const MethodInfo* methodInfo) {
	std::string description = "";

	auto klass_translation = translate_klass({ methodInfo->klass->namespaze, methodInfo->klass->name });

	description.append(methodInfo->klass->image->assembly->aname.name);
	description.append(", ");

	description.append(get_type_name(methodInfo->return_type));
	description.append(" ");
	if (!klass_translation.namespaze.empty()) {
		description.append(klass_translation.namespaze);
		description.append(".");
	}
	description.append(klass_translation.klass_name);
	description.append("::");
	description.append(translate_method_name(methodInfo->name));
	description.append("(");
	description.append(get_method_params(methodInfo));
	description.append(")");

	return description;
}

void output_class_methods(Il2CppClass* klass) {
	if (klass == NULL) return;
	std::cout << "output_class_methods(" << klass->name << ")" << std::endl;
	void* iterator = NULL;
	const MethodInfo* method = NULL;
	while ((method = il2cpp_class_get_methods(klass, &iterator)) != NULL) {
		std::cout << get_method_description(method) << std::endl;
	}
}

void output_assembly_methods(const Il2CppAssembly* assembly) {
	std::cout << "output_assembly_methods(" << assembly->aname.name << ")" << std::endl;
	for (size_t i = 0; i < il2cpp_image_get_class_count(assembly->image); i++) {
		output_class_methods(const_cast<Il2CppClass*>(il2cpp_image_get_class(assembly->image, i)));
	}
}