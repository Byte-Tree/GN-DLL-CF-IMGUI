#include "HookApi.h"
#include "../../../DllMain/DllMain.h"


LPVOID WINAPI HookApi::Self_VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
	LPVOID paddress = ::VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
	if (paddress != 0)
	{
		//OutputDebugStringA_2Param("[GN]:申请内存的地址：%p，大小：%d", paddress, dwSize);
		if (dwSize == 0x3B15F)
		{
			ce->CheatEngine::Game::GameBase.PassReadNameTrack = (DWORD64)paddress;
			OutputDebugStringA_1Param("[GN]:申请的指针：%p", paddress);
		}
	}

	return paddress;
}

HMODULE WINAPI HookApi::Self_LoadLibraryW(LPCWSTR lpLibFileName)
{
	HMODULE pmodule = NULL;

	OutputDebugStringA_1Param("[GN]:名称：%S", lpLibFileName);
	pmodule = ::LoadLibraryW(lpLibFileName);

	return pmodule;
}



