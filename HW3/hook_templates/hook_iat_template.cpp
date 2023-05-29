#include "pch.h"
#include <Windows.h>
#include <stdio.h>
// Add additional includes if needed
// using namespace std;

// for logging. format: log_file << ... << std::endl;
// #include <fstream> 
// using std::ofstream;
//ofstream log_file("log.txt");

// Typedef for the hooked function signature, such as:
// typedef INT(WINAPI* FUNC_PTR)(SOCKET, char*, int, int); (WINAPI is for _stdcall)
// or in the simple case:
typedef LPVOID FUNC_PTR;

// Ptr to the original function
FUNC_PTR original_func_address;

// Global variables
DWORD lpProtect = 0;
LPVOID IAT;
FUNC_PTR JumpTo;

// Helper function to remove the hook (for the current call):
void _stdcall remove_hook() {
	VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy(IAT, &original_func_address, 0x4);
	VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READ, &lpProtect);
}

// Helper function to restore the hook (for the next calls)
void _stdcall restore_hook() {
	VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy(IAT, &JumpTo, 0x4);
	VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READ, &lpProtect);
}

// Hook function. Might use helper functions in C, i.e. void _stdcall helper(int num) {}
// Might even use only a funcHook c function instead!
__declspec(naked) void funcHook() {
	// Restore overriden bytes
	// remove_hook();

	// Assembly part. Might call restore_hook somewhere inside
	__asm {
		// ...
		// call restore_hook;
		// ...
		// ret; // maybe
	}
}

void setHook() {
	HMODULE h = GetModuleHandle(L"<exe_name>.exe");
	HMODULE h2 = GetModuleHandle(L"<dll_with_func_to_hook_name>.dll");

	if ((h == NULL) || (h2 == NULL)) { return; }

	original_func_address = (FUNC_PTR)GetProcAddress(h2, "<func_to_hook_name>");
	if (original_func_address == NULL) {
		return;
	}

	int addr_beginning_of_our_exe = 0x400000; // change!
	int addr_func_to_hook_in_IAT = 0x40A2AC; // change!
	IAT = h + (addr_func_to_hook_in_IAT - addr_beginning_of_our_exe) / 4; // Calc address of address to override in IAT

	JumpTo = (FUNC_PTR)((char*)&funcHook);
	restore_hook();
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		setHook();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}