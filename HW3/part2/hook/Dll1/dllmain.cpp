#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
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
// LPVOID to_return_address;

// Global variables
CHAR OrigOpcode[6] = "\x90\x90\x90\x90\x90"; // Restores overriden bytes from hooked function
CHAR JmpOpcode[6] = "\xE9\x90\x90\x90\x90"; // Inserted into hooked function, in order to jmp to hook
DWORD lpProtect = 0;

// Helper function to remove the hook (for the current call):
void _stdcall remove_hook() {
	VirtualProtect((char*)original_func_address, 0x5, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy((char*)original_func_address, &OrigOpcode, 0x5);
	VirtualProtect((char*)original_func_address, 0x5, PAGE_EXECUTE_READ, &lpProtect);
}

// Helper function to restore the hook (for the next calls)
void _stdcall restore_hook() {
	VirtualProtect((char*)original_func_address, 0x5, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy((char*)original_func_address, &JmpOpcode, 0x5);
	VirtualProtect((char*)original_func_address, 0x5, PAGE_EXECUTE_READ, &lpProtect);
}


int strSeqToNum(std::string str) {
	if (str.length() == 3) {
		if (str[1] == '+')
			return int(str[0]) + int(str[2]) - 2 * int('0');
		if (str[1] == '-')
			return 0;
	}

	if (str[0] == 'A')
		return 1;
	else if (str[0] == 'J')
		return 10;
	else if (str[0] == 'Q')
		return 11;
	else if (str[0] == 'K')
		return 12;
	else
		return int(str[0]) - int('0');
}

std::string processString(std::string str) {
	std::string decrypted;
	std::string upper;
	std::string lower;
	for (int i = 0; i < str.length();) {
		if (str[i] == '\n') {
			decrypted += '\n';
			i++;
			continue;
		}

		if (i + 1 < str.length() and (str[i + 1] == '+' or str[i + 1] == '-')) {
			upper = str.substr(i, 3);
			i += 3;
		}
		else {
			upper = str[i];
			i += 1;
		}

		if (i + 1 < str.length() and (str[i + 1] == '+' or str[i + 1] == '-')) {
			lower = str.substr(i, 3);
			i += 3;
		}
		else {
			lower = str[i];
			i += 1;
		}
		decrypted += (strSeqToNum(upper) << 4) + strSeqToNum(lower);


	}
	return decrypted;
}



// Hook function. Might use helper functions in C, i.e. void _stdcall helper(int num) {}
__declspec() void funcHook() {
	// Restore overriden bytes
	remove_hook();
	// Assembly part. Should call restore_hook somewhere inside, can call original_func_addr
	char* message;
	int ret_val;
	int flag;
	__asm {
		
		mov edi, DWORD PTR[ebp + 12]
		mov message, edi

		mov edi, DWORD PTR[ebp + 20]
		push edi
		mov flag, edi

		mov edi, DWORD PTR[ebp + 16]
		push edi
		mov edi, DWORD PTR[ebp + 12]
		push edi
		mov edi, DWORD PTR[ebp + 8]
		push edi
		call original_func_address
		mov ret_val, eax
		add esp, 16
	}
	if (flag == 0) {
		std::string str = processString(message);
		std::memset(message, 0, strlen(message));
		std::memcpy(message, str.c_str(), str.length());
	}

	restore_hook();
	__asm {
		mov eax, ret_val 
		leave
		ret
	}
}

void setHook() {
	HMODULE h = GetModuleHandle(L"Ws2_32.dll");
	// Another option: HMODULE h = GetModuleHandle(L"<name_of_our_program>.exe");
	LPVOID JumpTo;

	if (h == NULL) {
		// can't find module
		return;
	}

	original_func_address = (FUNC_PTR)GetProcAddress(h, "recv");
	// Another option: original_func_address = (char*)h + <offset> if h == our_program.exe, for example.
	if (original_func_address == NULL) {
		// can't find function
		return;
	}

	JumpTo = (FUNC_PTR)((char*)&funcHook - ((char*)original_func_address + 5)); // The "+5" part is for the offset to be calculated relatively to the address AFTER jmp
	memcpy(JmpOpcode + 1, &JumpTo, 0x4); // prepare the jmp opcode

	// save old bytes - save this arr globally if needed to be restored in hook_func
	memcpy(&OrigOpcode, (char*)original_func_address, 0x5); // override the first five bytes with jmp

	// override these bytes
	restore_hook();

	// save address to return to after hook. Can be used directly if hook is written in C.
	// to_return_address = (LPVOID)((char*)original_func_address); // can be changed to original_func_address+<some offset>
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