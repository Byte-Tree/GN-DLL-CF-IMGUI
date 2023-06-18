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

	//if ((dwSize == 0x3B15F))
	//{
	//	LPVOID paddress = ::VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
	//
	//	if (paddress != 0)
	//	{
	//		ce->CheatEngine::Game::GameBase.PassReadNameTrack = (DWORD64)paddress;
	//		OutputDebugStringA_1Param("[GN]:申请的指针：%p", paddress);
	//	}
	//
	//	return paddress;
	//}
	//
	//if (dwSize == 0x1000)
	//{
	//	LPVOID paddress = ::VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
	//
	//	if (paddress != 0)
	//		OutputDebugStringA_2Param("[GN]:申请内存的地址：%p，大小：%d", paddress, dwSize);
	//
	//	return paddress;
	//}
	//
	//return 0;
}

HMODULE WINAPI HookApi::Self_LoadLibraryW(LPCWSTR lpLibFileName)
{
	HMODULE pmodule = NULL;

	OutputDebugStringA_1Param("[GN]:Self_LoadLibraryW()名称：%S", lpLibFileName);
	pmodule = ::LoadLibraryW(lpLibFileName);

	return pmodule;
}

HMODULE WINAPI HookApi::Self_LoadLibraryA(_In_ LPCSTR lpLibFileName)
{
	HMODULE pmodule = NULL;

	OutputDebugStringA_1Param("[GN]:Self_LoadLibraryA()名称：%s", lpLibFileName);
	pmodule = ::LoadLibraryA(lpLibFileName);

	return pmodule;
}

HMODULE WINAPI HookApi::Self_LoadLibraryExW(_In_ LPCWSTR lpLibFileName, _Reserved_ HANDLE hFile, _In_ DWORD dwFlags)
{
	HMODULE pmodule = NULL;

	OutputDebugStringA_1Param("[GN]:Self_LoadLibraryExW()名称：%S", lpLibFileName);

	if (wcsicmp(lpLibFileName, L"ACE-IDS.dll") == 0)
	{
		OutputDebugStringA("[GN]:过滤加载ACE-IDS.dll");
		return 0;
	}

	pmodule = ::LoadLibraryExW(lpLibFileName, hFile, dwFlags);

	return pmodule;
}


