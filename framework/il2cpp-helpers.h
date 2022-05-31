#pragma once

void new_console();
std::string convert_from_string(Il2CppString* input);
std::string convert_from_string(app::String* input);
app::String* convert_to_string(std::string input);
std::string translate_type_name(std::string input);
Il2CppMethodPointer find_method(Il2CppClass* klass, std::string returnType, std::string methodName, std::string paramTypes);
Il2CppMethodPointer get_method(std::string methodSignature);
Il2CppClass* get_class(std::string classSignature);
std::string get_method_description(const MethodInfo* methodInfo);
void output_class_methods(Il2CppClass* klass);
void output_assembly_methods(const Il2CppAssembly* assembly);
bool cctor_finished(Il2CppClass* klass);

namespace app {
	namespace il2cpp {
		template<typename E>
		class Dictionary {
		public:
			using iterator = decltype(&E::fields.entries->vector[0]);
			using key_type = decltype(E::fields.entries->vector->key);
			using value_type = decltype(E::fields.entries->vector->value);
			constexpr Dictionary(E* dict) : _Ptr(dict) {}
			constexpr size_t size() const {
				if (!_Ptr) return 0;
				auto pDict = (Dictionary_2_SystemTypes_ISystemType_*)_Ptr;
				return ((size_t(*)(void*, const void*))(pDict->klass->vtable.get_Count.methodPtr))(pDict, pDict->klass->vtable.get_Count.method);
			}
			constexpr iterator begin() const {
				if (!_Ptr) return nullptr;
				return _Ptr->fields.entries->vector;
			}
			constexpr iterator end() const { return begin() + size(); }
			constexpr auto operator[](key_type&& _Keyval) const {
				for (auto& kvp : *this) {
					if (kvp.key == _Keyval) {
						return kvp.value;
					}
				}
				return (value_type)nullptr;
			}
			constexpr E* get() const { return _Ptr; }
		protected:
			E* _Ptr;
		};
		template<typename E>
		class Array {
		public:
			using iterator = decltype(&E::vector[0]);
			constexpr Array(E* arr) : _Ptr(arr) {}
			constexpr size_t size() const {
				if (!_Ptr) return 0;
				if (_Ptr->bounds)
					return _Ptr->bounds->length;
				return _Ptr->max_length;
			}
			constexpr iterator begin() const {
				if (!_Ptr) return nullptr;
				return _Ptr->vector;
			}
			constexpr iterator end() const { return begin() + size(); }
			constexpr auto& operator[](const size_t _Pos) const { return begin()[_Pos]; }
			constexpr E* get() const { return _Ptr; }
		protected:
			E* _Ptr;
		};
		template<typename E>
		class List {
		public:
			using iterator = decltype(&E::fields._items->vector[0]);
			constexpr List(E* list) : _Ptr(list) {}
			constexpr size_t size() const {
				if (!_Ptr) return 0;
				auto pList = (List_1_PlayerTask_*)_Ptr;
				return ((size_t(*)(void*, const void*))(pList->klass->vtable.get_Count.methodPtr))(pList, pList->klass->vtable.get_Count.method);
			}
			constexpr void clear() {
				if (!_Ptr) return;
				auto pList = (List_1_PlayerTask_*)_Ptr;
				((void(*)(void*, const void*))(pList->klass->vtable.Clear.methodPtr))(pList, pList->klass->vtable.Clear.method);
			}
			constexpr iterator begin() const {
				if (!_Ptr) return nullptr;
				return _Ptr->fields._items->vector;
			}
			constexpr iterator end() const { return begin() + size(); }
			constexpr auto& operator[](const size_t _Pos) const { return begin()[_Pos]; }
			constexpr E* get() const { return _Ptr; }
		protected:
			E* _Ptr;
		};
	}
}