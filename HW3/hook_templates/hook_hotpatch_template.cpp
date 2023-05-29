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
// Ptr to return to after hook
LPVOID to_return_address;

// Global variables
CHAR OrigOpcode[8] = "\x90\x90\x90\x90\x90\x90\x90"; // Restores overriden bytes from hooked function
CHAR JmpOpcode[8] = "\x90\x90\x90\x90\x90\xEB\xF9"; // Inserted into hooked function, in order to jmp to hook
DWORD lpProtect = 0;

// Helper function to remove the hook (for the current call):
void _stdcall remove_hook() {
	VirtualProtect((char*)original_func_address - 5, 0x7, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy((char*)original_func_address - 5, &OrigOpcode, 0x7);
	VirtualProtect((char*)original_func_address - 5, 0x7, PAGE_EXECUTE_READ, &lpProtect);
}

// Helper function to restore the hook (for the next calls)
void _stdcall restore_hook() {
	VirtualProtect((char*)original_func_address - 5, 0x7, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy((char*)original_func_address - 5, &JmpOpcode, 0x7);
	VirtualProtect((char*)original_func_address - 5, 0x7, PAGE_EXECUTE_READ, &lpProtect);
}

// Hook function. Might use helper functions in C, i.e. void _stdcall helper(int num) {}
__declspec(naked) void funcHook() {
	// Restore overriden bytes
	remove_hook();

	// Assembly part. Should call restore_hook somewhere inside, can jmp to to_return_addr
	__asm {
		// ...
		// call restore_hook;
		// ...
		// ret; // maybe
	}
}

void setHook() {
	HMODULE h = GetModuleHandle(L"<dll_with_func_to_hook_name>.dll");
	// Another option: HMODULE h = GetModuleHandle(L"<name_of_our_program>.exe");
	LPVOID JumpTo;

	if (h == NULL) {
		// can't find module
		return;
	}

	original_func_address = (FUNC_PTR)GetProcAddress(h, "<func_to_hook_name>");
	// Another option: original_func_address = (char*)h + <offset> if h == our_program.exe, for example.
	if (original_func_address == NULL) {
		// can't find function
		return;
	}

	JumpTo = (FUNC_PTR)((char*)&funcHook - (char*)original_func_address);
	memcpy(JmpOpcode + 1, &JumpTo, 0x4); // prepare the jmp opcode

	// save old bytes - save this arr globally if needed to be restored in hook_func
	memcpy(&OrigOpcode, (char*)original_func_address - 5, 0x7); // override the first five bytes with jmp

	// override these bytes
	restore_hook();

	// save address to return to after hook. Can be used directly if hook is written in C.
	to_return_address = (LPVOID)((char*)original_func_address + 2);
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