#pragma once
#include "../../../pch.h"


namespace HookApi
{
    LPVOID WINAPI Self_VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
    HMODULE WINAPI Self_LoadLibraryW(LPCWSTR lpLibFileName);

}

