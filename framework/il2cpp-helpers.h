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
			Dictionary(E* dict) : _Ptr(dict) {}
			size_t size() const {
				auto pDict = (Dictionary_2_SystemTypes_ISystemType_*)_Ptr;
				return ((size_t(*)(void*, const void*))(pDict->klass->vtable.get_Count.methodPtr))(pDict, pDict->klass->vtable.get_Count.method);
			}
			auto begin() { return _Ptr->fields.entries->vector; }
			auto end() { return _Ptr->fields.entries->vector + size(); }
		protected:
			E* _Ptr;
		};
		template<typename E>
		class Array {
		public:
			Array(E* arr) : _Ptr(arr) {}
			size_t size() const {
				if (_Ptr->bounds)
					return _Ptr->bounds->length;
				return _Ptr->max_length;
			}
			auto begin() { return _Ptr->vector; }
			auto end() { return _Ptr->vector + size(); }
			auto& operator[](const size_t _Pos) { return begin()[_Pos]; }
		protected:
			E* _Ptr;
		};
		template<typename E>
		class List {
		public:
			List(E* list) : _Ptr(list) {}
			size_t size() const {
				auto pList = (List_1_PlayerTask_*)_Ptr;
				return ((size_t(*)(void*, const void*))(pList->klass->vtable.get_Count.methodPtr))(pList, pList->klass->vtable.get_Count.method);
			}
			auto clear() {
				auto pList = (List_1_PlayerTask_*)_Ptr;
				((void(*)(void*, const void*))(pList->klass->vtable.Clear.methodPtr))(pList, pList->klass->vtable.get_Count.method);
			}
			auto begin() { return _Ptr->fields._items->vector; }
			auto end() { return _Ptr->fields._items->vector + size(); }
			auto& operator[](const size_t _Pos) { return begin()[_Pos]; }
		protected:
			E* _Ptr;
		};
	}
}