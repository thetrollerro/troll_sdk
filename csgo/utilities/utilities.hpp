#pragma once
#define NOMINMAX
#include <Windows.h>
#include <string>
#include <initializer_list>
#include <Psapi.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#pragma comment(lib, "psapi.lib")
namespace utilities {
	template<typename FuncType>
	__forceinline static FuncType call_virtual(void* ppClass, int index) {
		int* pVTable = *(int**)ppClass;
		int dwAddress = pVTable[index];
		return (FuncType)(dwAddress);
	}

	uintptr_t find_sig_ida( const char* module, const char* signature );
	DWORD find_sig_byte( const char* module_name, const BYTE* mask, const char* mask_string );
}