#pragma once
#include <Windows.h>
#include <iostream>
#include <Psapi.h>
#include <vector>

#define INRANGE(x, a, b) (x >= a && x <= b)
#define getBits(x) (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))

template<typename T>
class SignatureScan
{
	SignatureScan() {
		pointer = NULL;
		moduleHandle = nullptr;
	}
	uintptr_t pointer;
	HMODULE moduleHandle;
	int SignatureSize(const char* signature) {
		int count = 0, i = 0;
		char ch = signature[0];
		while (ch != ' ') {
			ch = signature[i];
			if (isspace(ch))
				count++;
			i++;
		}
		return count;
	}
	uintptr_t FindSignature(uintptr_t pStart, uintptr_t pEnd, const char* signature) {
		const char* pattern = signature;
		uintptr_t pFirstMatch = 0;
		for (uintptr_t i = pStart; i < pEnd; i++) {
			if (!*pattern) return pFirstMatch;
			if (*(PBYTE)pattern == '\?' || *(BYTE*)i == getByte(pattern))
			{
				if (!pFirstMatch) pFirstMatch = i;
				if (!pattern[2]) return pFirstMatch;
				if (*(PWORD)pattern == '\?\?' || *(PBYTE)pattern != '\?') pattern += 3;
				else pattern += 2;
			}
			else
			{
				pattern = signature;
				pFirstMatch = 0;
			}
		}
		return 0;
	}
	uintptr_t FindSignatures(const char* signature, size_t index) {
		MODULEINFO moduleInfo;
		GetModuleInformation(GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(MODULEINFO));
		uintptr_t pStart = uintptr_t(moduleInfo.lpBaseOfDll);
		uintptr_t pEnd = pStart + moduleInfo.SizeOfImage;

		std::vector<uintptr_t> results;
		int signatureSize = SignatureSize(signature);

		while (true) {
			uintptr_t result = FindSignature(pStart, pEnd, signature);
			if (result != 0) {
				results.push_back(result);
				pStart = result + signatureSize;
			}
			else
				break;

			if (results.size() > index)
				return results[index];
		}

		return 0;
	}
public:
	SignatureScan(const char* signature, size_t index, HMODULE module) {
		moduleHandle = module;
		pointer = FindSignatures(signature, index);
	}
	SignatureScan(const char* signature, HMODULE module) : SignatureScan(signature, 0, module) {}
	operator T () {
		return (T)pointer;
	}
	operator uintptr_t () {
		return pointer;
	}
	SignatureScan<T> OffsetPointer(int32_t value) {
		SignatureScan<T> result;
		if (this->pointer != 0) {
			result.pointer = this->pointer;
			return result.Offset(value).ResolvePointer();
		}
		return result;
	}
	SignatureScan<T> Offset(int32_t value) {
		SignatureScan<T> result;
		if (this->pointer != 0) {
			result.pointer = this->pointer + value;
		}
		return result;
	}
	SignatureScan<T> ResolveCall() {
		SignatureScan<T> result;
		if (this->pointer != 0) {
			int32_t pOffset = *(int32_t*)(this->pointer + 0x01);
			result.pointer = this->pointer + pOffset + 0x05;
		}
		return result;
	}
	SignatureScan<T> ResolvePointer() {
		SignatureScan<T> result;
		if (this->pointer != 0) {
			result.pointer = *(uint32_t*)(this->pointer);
		}
		return result;
	}
};