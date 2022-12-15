#include "pch-il2cpp.h"
#include "il2cpp-helpers.h"
#include <codecvt>
#include <optional>
#include <thread>
#include <chrono>
#include "logger.h"

static std::vector<std::string> Tokenize(std::string_view str, std::string_view delimiters) {
	std::vector<std::string> tokens;
	// Skip delimiters at beginning.
	auto lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	auto pos = str.find_first_of(delimiters, lastPos);
	while (pos != std::string::npos || lastPos != std::string::npos) {
		// Found a token, add it to the vector.
		tokens.emplace_back(std::string{ str.substr(lastPos, pos - lastPos) });
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
	return tokens;
}

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
	if (auto pos = methodSignature.rfind("."); pos != std::string::npos) {
		namespaze = methodSignature.substr(0, pos);
		methodSignature.erase(0, namespaze.length() + 1);
	}

	std::string className = methodSignature;

	std::string paramTypes = methodName.substr(methodName.find("(") + 1);
	methodName.erase(methodName.rfind("("));
	paramTypes.pop_back();

	Il2CppClass* klass = get_class(assemblyName, namespaze, className);
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

	return get_class(assemblyName, namespaze, classSignature);
}

Il2CppClass* get_class(std::string_view assemblyName, std::string namespaze, std::string className) {
	auto klass_translation = translate_klass({ namespaze, className });
	namespaze = klass_translation.namespaze;
	className = klass_translation.klass_name;

	Il2CppDomain* domain = il2cpp_domain_get();
	const Il2CppAssembly* assembly = il2cpp_domain_assembly_open(domain, assemblyName.data());
	if (assembly == NULL) return NULL;

	const auto& vecClassNames = Tokenize(className, "+");

	Il2CppClass* klass = il2cpp_class_from_name(assembly->image, namespaze.c_str(), vecClassNames[0].c_str());
	if (!klass) return nullptr;

	for (size_t i = 1; i < vecClassNames.size(); i++) {
		void* iter = nullptr;
		Il2CppClass* nested;
		while (nested = il2cpp_class_get_nested_types(klass, &iter)) {
			if (vecClassNames[i].compare(nested->name) == 0)
				break;
		}
		if (!nested) return nullptr;
		klass = nested;
	}
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

ScopedThreadAttacher::ScopedThreadAttacher() : m_AttachedThread(nullptr) {
	if (il2cpp_thread_current() == nullptr)
		m_AttachedThread = il2cpp_thread_attach(il2cpp_domain_get());
}

ScopedThreadAttacher::~ScopedThreadAttacher() {
	detach();
}

void ScopedThreadAttacher::detach() {
	if (m_AttachedThread) {
		il2cpp_thread_detach(m_AttachedThread);
		m_AttachedThread = nullptr;
	}
}

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

namespace app {
	namespace il2cpp {

		Il2CppClass* get_system_type() {
			static auto klass = get_class("mscorlib, System.Type");
			return klass;
		}

		app::Type* get_type_of(Il2CppClass* klass) {
			auto il2cpp_type = il2cpp_class_get_type(klass);
			LOG_ASSERT(il2cpp_type);
			return reinterpret_cast<app::Type*>(il2cpp_type_get_object(il2cpp_type));
		}

		bool generic_class::init(std::string_view classSignature,
								 std::initializer_list<std::string_view> types) {
#ifdef _DEBUG
			LOG_ASSERT(types.size() >= 1);
			LOG_ASSERT(classSignature.find('`') == std::string_view::npos);
			LOG_ASSERT(classSignature.find('<') == std::string_view::npos);
			LOG_ASSERT(classSignature.find('>') == std::string_view::npos);
#endif
			auto klass = get_class(std::string(classSignature) + std::format("`{}", types.size()));
			if (!klass || !il2cpp_class_is_generic(klass)) {
				return false;
			}
			auto runtimeType = get_type_of(klass);
			LOG_ASSERT(runtimeType);

			auto arr = reinterpret_cast<Il2CppArraySize*>(
				il2cpp_array_new_specific(
					get_system_type(),
					types.size()));
			LOG_ASSERT(arr != nullptr);

			size_t i = 0;
			for (auto& typeSig : types) {
				auto klass = get_class(std::string(typeSig));
				if (!klass) {
					return false;
				}
				if (il2cpp_class_is_generic(klass)) {
					// TODO: Foo<Bar<T>>, Foo<String, Bar<T>>, ...
					return false;
				}
				auto type = get_type_of(klass);
				LOG_ASSERT(type);
				arr->vector[i++] = type;
			}

			auto genericType = app::RuntimeType_MakeGenericType_1(runtimeType, arr, nullptr);
			if (!genericType) {
				return false;
			}
			auto genericClass = il2cpp_class_from_system_type(reinterpret_cast<Il2CppReflectionType*>(genericType));
			if (!genericClass) {
				return false;
			}

			this->_klass = genericClass;
			return true;
		}
	}
}