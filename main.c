#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"

//#pragma comment(linker, "/entry:WinMain")

//compile with main : x86_64-w64-mingw32-gcc .\main.c .\helpers.c -o pe.exe -Wall -m64 -s -Os

//++++++++++//
//comiple withWinMain : 

// CC_64=x86_64-w64-mingw32-gcc
// #CFLAGS_64=-nostartfiles -Wall -m64 -s -Os -Wl,--entry=WinMain -Wno-missing-braces --machine-windows
// CFLAGS_64=-nostartfiles -Wall -m64 -s -Os -Wl,--entry=WinMain --machine-windows

// customwinapi:
// 	$(CC_64) main.c helpers.c -o pe.exe $(CFLAGS_64) 
//++++++++++//

//change Entry Point to WinMain for no imports in a PE.

HMODULE WINAPI myGetModuleHandle(LPCWSTR sModuleName);
FARPROC WINAPI myGetProcAddress(HMODULE hMod, const char* sProcName);

int main(void) {

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow){

    //NTDLL.dll
    LPVOID pNTDLL = myGetModuleHandle(L"NTDLL.DLL");
    printf("NTDLL : %p\n", pNTDLL);

    //kernel32.dll
    //Unicode Char
    wchar_t kernel32[] = { 'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', 0x00 };
    LPVOID pKernel32 = myGetModuleHandle(kernel32);
    printf("Kernel32 : %p\n", pKernel32);

    //L"KERNEL32.DLL" - for unicode if not L then it is ASCII
	//LPVOID pKernel32 = myGetModuleHandle(L"KERNEL32.DLL");

    //kernelbase32.dll
    LPVOID pKernelBase = myGetModuleHandle(L"KERNELBASE.DLL");
    printf("Kernelbase32 : %p\n", pKernelBase);

    //resolve symbols
    char proc[] = { 'C', 'r', 'e', 'a', 't', 'e', 'P', 'r', 'o', 'c', 'e', 's', 's', 'A', 0x00 };
    LPVOID pCreateProcessA = myGetProcAddress(myGetModuleHandle(kernel32), proc);
    //CreateProcessA_t pCreateProcessA = (CreateProcessA_t)myGetProcAddress(myGetModuleHandle(L"KERNEL32.DLL"), "CreateProcessA");
    printf("CreateProcessA : %p\n", pCreateProcessA);
	

	return 0;
}

