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

// hook: print out both strings in strcmp.
__declspec(naked) void funcHook() {
	__asm {
		push ebp
		mov ebp, esp
		push edi
		sub esp, 64
		call remove_hook

		
		mov edi, DWORD PTR [ebp+8]
		mov DWORD PTR [ebp-4], edi
		mov edi, DWORD PTR [ebp+12]
		mov DWORD PTR [ebp-8], edi
		mov WORD PTR[ebp - 14], 0x000A // "\n"

		// print return address
		mov edi, DWORD PTR[ebp + 4]
		mov DWORD PTR [esp+4], edi
		mov DWORD PTR [ebp-26], 0x000A5825
		lea edi, DWORD PTR [ebp-26]
		mov DWORD PTR [esp], edi
		call printf

		// print first string
		mov edi, DWORD PTR [ebp-4]
		mov DWORD PTR [esp], edi
		call printf
		lea edi, DWORD PTR [ebp-14]	// print newline
		mov DWORD PTR [esp], edi    // print newline
		call printf					// print newline

		// print second string
		mov edi, DWORD PTR [ebp-8]
		mov DWORD PTR[esp], edi
		call printf
		lea edi, DWORD PTR [ebp-14] // print newline
		mov DWORD PTR [esp], edi	// print newline
		call printf					// print newline


		// call strcmp with the two strings
		mov edi, DWORD PTR [ebp+8]
		mov DWORD PTR [esp+4], edi
		mov edi, DWORD PTR [ebp+12]
		mov DWORD PTR [esp], edi
		call strcmp

		// print return value 
		mov DWORD PTR [ebp-22], eax
		mov DWORD PTR [esp+4], eax
		mov DWORD PTR[ebp - 18], 0x000A6425 // "%d\n"
		lea edi, DWORD PTR[ebp - 18]
		mov DWORD PTR[esp], edi
		call printf

		
		call restore_hook
		mov eax, DWORD PTR [ebp - 22]
		add esp, 64
		pop edi
		leave
		ret
	}
}

void setHook() {
	HMODULE h = GetModuleHandle(L"codes.exe");
	HMODULE h2 = GetModuleHandle(L"msvcrt.dll");

	if ((h == NULL) || (h2 == NULL)) { return; }

	original_func_address = (FUNC_PTR)GetProcAddress(h2, "strcmp");
	if (original_func_address == NULL) {
		return;
	}

	int addr_beginning_of_our_exe = 0x400000; // change!
	int addr_func_to_hook_in_IAT = 0x409294; // change!
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