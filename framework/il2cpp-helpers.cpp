#include "pch-il2cpp.h"
#include "il2cpp-helpers.h"
#include <codecvt>
#include <optional>
#include <thread>
#include <chrono>
#include "logger.h"

void new_console() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	// solve the disorder codes in the CJK character show
	SetConsoleOutputCP(CP_UTF8);
}

std::string utf16_to_utf8(std::u16string_view u16_string) {
	std::wstring wide_string(u16_string.begin(), u16_string.end());
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	return convert.to_bytes(wide_string);
}

std::string convert_from_string(Il2CppString* input) {
	// Il2CppString are the same thing as app::String.
	return convert_from_string((app::String*)input);
}

std::string convert_from_string(app::String* input) {
	if (input == nullptr) return "";
	return utf16_to_utf8({ reinterpret_cast<const char16_t*>(&input->fields.m_firstChar), static_cast<size_t>(input->fields.m_stringLength) });
}

app::String* convert_to_string(std::string_view input) {
	return (app::String*)il2cpp_string_new_len(input.data(), input.length());
}

KLASS translate_klass(KLASS klass_input) {
	for (KLASS_PAIR klass_pair : KLASS_TRANSLATIONS) {
		if (klass_input == klass_pair.obfuscated_klass)
			return klass_pair.deobfuscated_klass;

		if (klass_input == klass_pair.deobfuscated_klass)
			return klass_pair.obfuscated_klass;
	}
	return klass_input;
}

std::string_view translate_method_name(std::string_view input) {
	for (const std::pair<std::string, std::string>& pair : METHOD_TRANSLATIONS) {
		if (input.compare(pair.first) == 0) return pair.second;
		if (input.compare(pair.second) == 0) return pair.first;
	}
	return input;
}

std::string translate_type_name(std::string input) {
	const KLASS_PAIR* match = nullptr;
	int8_t conversion = 0;
	size_t match_length = 0;

	for (const KLASS_PAIR& klass_pair : KLASS_TRANSLATIONS) {
		if (conversion != 1) {
			auto deobfuscated_length = klass_pair.deobfuscated_klass.contains_type(input);
			if (deobfuscated_length > match_length) {
				match = &klass_pair;
				conversion = -1;
				match_length = deobfuscated_length;
			}
		}

		if (conversion != -1) {
			auto obfuscated_length = klass_pair.obfuscated_klass.contains_type(input);
			if (obfuscated_length > match_length) {
				match = &klass_pair;
				conversion = 1;
				match_length = obfuscated_length;
			}
		}
	}

	if (match) {
		const KLASS_PAIR& klass_pair = *match;
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

bool method_compare(const MethodInfo* methodInfo, std::string_view returnType, std::string_view methodName, std::string_view paramTypes) {
	if (methodName.compare(methodInfo->name) != 0) return false;
	if (returnType.compare(get_type_name(methodInfo->return_type)) != 0) return false;
	if (paramTypes.compare(get_method_params(methodInfo)) != 0) return false;

	return true;
}

Il2CppMethodPointer find_method(Il2CppClass* klass, std::string_view returnType, std::string_view methodName, std::string_view paramTypes) {
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
	STREAM_DEBUG("output_class_methods(" << klass->name << ")");
	void* iterator = NULL;
	const MethodInfo* method = NULL;
	while ((method = il2cpp_class_get_methods(klass, &iterator)) != NULL) {
		STREAM_DEBUG(get_method_description(method));
	}
}

void output_assembly_methods(const Il2CppAssembly* assembly) {
	STREAM_DEBUG("output_assembly_methods(" << assembly->aname.name << ")");
	for (size_t i = 0; i < il2cpp_image_get_class_count(assembly->image); i++) {
		output_class_methods(const_cast<Il2CppClass*>(il2cpp_image_get_class(assembly->image, i)));
	}
}

class ScopedThreadAttacher
{
public:
	ScopedThreadAttacher() : m_AttachedThread(nullptr) {
		m_AttachedThread = il2cpp_thread_attach(il2cpp_domain_get());
	}
	~ScopedThreadAttacher() {
		if (m_AttachedThread)
			il2cpp_thread_detach(m_AttachedThread);
	}

private:
	Il2CppThread* m_AttachedThread;
};

bool cctor_finished(Il2CppClass* klass)
{
	STREAM_DEBUG("Class " << klass->name << " Has Static Constructor: " << (klass->has_cctor ? "true" : "false"));
	// make sure we're attached before we call il2cpp_runtime_class_init
	ScopedThreadAttacher managedThreadAttached;
	if (!klass->initialized) {
		// enforce to call 'Class::Init'
		auto size = il2cpp_class_get_bitmap_size(klass);
		std::vector<size_t> buffer(size / sizeof(size_t));
		il2cpp_class_get_bitmap(klass, buffer.data());
		if (!klass->initialized) {
			STREAM_ERROR("Class " << klass->name << " il2cpp_class_get_bitmap() failure");
			return false;
		}
	}
	//If we don't have a static constructor, no need to wait
	if (!klass->has_cctor) return true; 
	if (!klass->cctor_finished) {
		// enforce to call 'Runtime::ClassInit'
		il2cpp_runtime_class_init(klass);
		if (!klass->cctor_finished) {
			STREAM_ERROR("Class " << klass->name << " il2cpp_runtime_class_init() failure");
			return false;
		}
	}
	return true;
}