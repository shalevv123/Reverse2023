from ctypes import wintypes
import ctypes

def GetModuleHandle(module):
    kernel32 = ctypes.WinDLL('kernel32', use_last_error=True)
    kernel32.GetModuleHandleW.restype = wintypes.HMODULE
    kernel32.GetModuleHandleW.argtypes = [wintypes.LPCWSTR]
    hMod = kernel32.GetModuleHandleW(module)
    return hMod

if __name__ == '__main__':
    #print in hexadecimal
    print(hex(GetModuleHandle('ntdll.dll')))
