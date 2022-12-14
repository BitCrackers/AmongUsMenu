#pragma once
#include "logger.h"

template<typename T>
class DestroyableSingleton : public il2cpp::generic_class {
public:
	DestroyableSingleton() = default;

	DestroyableSingleton(std::string_view instanceSignature)
		: _instanceSignature(instanceSignature) {
	}

	bool IsInstanceExists() {
		if (!is_inited() && !_init())
			return false;
		return ((T(*)(const void*))(_get_InstanceExists->methodPointer))(_get_InstanceExists);
	}

	T GetInstance() {
		if (!is_inited() && !_init()) 
			return T{};
		return ((T(*)(const void*))(_get_Instance->methodPointer))(_get_Instance);
	}

protected:
	std::string _instanceSignature;
	const MethodInfo* _get_Instance = nullptr;
	const MethodInfo* _get_InstanceExists = nullptr;

	bool _init() {
		if (init("Assembly-CSharp, DestroyableSingleton",
				 { _instanceSignature })) {
			_get_Instance = il2cpp_class_get_method_from_name(_klass, "get_Instance", 0);
			LOG_ASSERT(_get_Instance);
			_get_InstanceExists = il2cpp_class_get_method_from_name(_klass, "get_InstanceExists", 0);
			LOG_ASSERT(_get_InstanceExists);
			return true;
		}
		return false;
	}
};