#pragma once

void new_console();
std::string convert_from_string(Il2CppString* input);
std::string convert_from_string(app::String* input);
app::String* convert_to_string(std::string_view input);
std::string translate_type_name(std::string input);
Il2CppMethodPointer find_method(Il2CppClass* klass, std::string_view returnType, std::string_view methodName, std::string_view paramTypes);
Il2CppMethodPointer get_method(std::string methodSignature);
Il2CppClass* get_class(std::string classSignature);
Il2CppClass* get_class(std::string_view assemblyName, std::string namespaze, std::string className);
std::string get_method_description(const MethodInfo* methodInfo);
void output_class_methods(Il2CppClass* klass);
void output_assembly_methods(const Il2CppAssembly* assembly);
bool cctor_finished(Il2CppClass* klass);

// NOTE ported this from c++23 so we can pin the project to c++20
template <class _Ty>
inline constexpr bool is_scoped_enum_v = std::conjunction_v<std::is_enum<_Ty>, std::negation<std::is_convertible<_Ty, int>>>;

namespace app {
	namespace il2cpp {
		template<typename E>
		class Dictionary {
		public:
			using iterator = decltype(&E::fields.entries->vector[0]);
			using key_type = decltype(E::fields.entries->vector->key);
			using value_type = decltype(E::fields.entries->vector->value);
			using pointer = std::conditional_t<std::is_pointer_v<value_type>, value_type, value_type*>;
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
			constexpr pointer operator[](const key_type& _Keyval) const {
				static_assert(std::is_arithmetic_v<key_type> || is_scoped_enum_v<key_type>);
				if (!_Ptr) return nullptr;
				const auto FindEntryMethod = ((System_Collections_Generic_Dictionary_TKey__TValue__RGCTXs*)(_Ptr->klass->rgctx_data))
					->_17_System_Collections_Generic_Dictionary_TKey__TValue__FindEntry;
				auto num = ((int32_t(*)(void*, key_type, const void*))(FindEntryMethod->methodPointer))(_Ptr, _Keyval, FindEntryMethod);
				if (num < 0)
					return nullptr;
				if constexpr (std::is_pointer_v<value_type>)
					return _Ptr->fields.entries->vector[num].value;
				else
					return &_Ptr->fields.entries->vector[num].value;
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
			using value_type = std::remove_cvref_t<decltype(E::fields._items->vector[0])>;
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
			constexpr void erase(size_t _Pos) {
				if (!_Ptr || _Pos >= size()) return;
				auto pList = (List_1_PlayerTask_*)_Ptr;
				((void(*)(void*, size_t, const void*))(pList->klass->vtable.RemoveAt.methodPtr))(pList, _Pos, pList->klass->vtable.RemoveAt.method);
			}
			constexpr void add(value_type item) {
				if (!_Ptr) return;
				auto pList = (List_1_PlayerTask_*)_Ptr;
				((void(*)(void*, value_type, const void*))(pList->klass->vtable.Add.methodPtr))(pList, item, pList->klass->vtable.Add.method);
			}
			constexpr bool contains(value_type item) const {
				if (!_Ptr) return false;
				auto pList = (List_1_PlayerTask_*)_Ptr;
				return ((bool(*)(void*, value_type, const void*))(pList->klass->vtable.Contains.methodPtr))(pList, item, pList->klass->vtable.Contains.method);
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

		Il2CppClass* get_system_type();
		app::Type* get_type_of(Il2CppClass* klass);

		class generic_class {
		public:
			operator Il2CppClass* () const {
				return _klass;
			}
		protected:
			generic_class() = default;

			bool is_inited() const {
				return _klass != nullptr;
			}

			bool init(std::string_view classSignature,
					  std::initializer_list<std::string_view> types);

			Il2CppClass* _klass = nullptr;
		};
	}
}

class ScopedThreadAttacher {
public:
	ScopedThreadAttacher();
	~ScopedThreadAttacher();

	void detach();
private:
	Il2CppThread* m_AttachedThread;
};