#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <codecvt>
#include <optional>
#include "il2cpp-appdata.h"
#include <string>
#include <sstream>
#include <iomanip>

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