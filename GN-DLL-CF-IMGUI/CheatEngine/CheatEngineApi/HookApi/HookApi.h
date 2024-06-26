#pragma once
#include "../../../pch.h"

extern "C" void RetNullApi(void);
extern "C" void RetApi(void);


namespace HookApi
{
    LPVOID WINAPI Self_VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
    HMODULE WINAPI Self_LoadLibraryW(LPCWSTR lpLibFileName);
    HMODULE WINAPI Self_LoadLibraryA(_In_ LPCSTR lpLibFileName);
    HMODULE WINAPI Self_LoadLibraryExW(_In_ LPCWSTR lpLibFileName, _Reserved_ HANDLE hFile, _In_ DWORD dwFlags);
    HANDLE WINAPI Self_CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
    HANDLE WINAPI Self_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
    VOID WINAPI Self_Sleep(_In_ DWORD dwMilliseconds);
    BOOL WINAPI Self_Process32NextW(__in HANDLE hSnapshot,  __out LPPROCESSENTRY32W lppe);
    HANDLE WINAPI Self_CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);

}

