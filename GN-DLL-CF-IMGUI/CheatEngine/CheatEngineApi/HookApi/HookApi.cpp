#include "HookApi.h"
#include "../../../DllMain/DllMain.h"


LPVOID WINAPI HookApi::Self_VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
{
	LPVOID paddress = ::VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);

	if (paddress != 0)
	{
		//OutputDebugStringA_2Param("[GN]:申请内存的地址：%p，大小：%d", paddress, dwSize);
		if (dwSize == 0x3E7F7)
		{
			ce->CheatEngine::Game::GameBase.PassReadNameTrack = (DWORD64)paddress;
			////OutputDebugStringA_1Param("[GN]:申请的指针：%p", paddress);
		}
	}

	//PVOID64 return_address = ::_ReturnAddress();
	//if (((DWORD64)return_address >= ce->CheatEngine::Game::GameBase.ACE_BASE64) && ((DWORD64)return_address <= ce->CheatEngine::Game::GameBase.ACE_BASE64End))
	//{
	//	if (dwSize == 0x3E7F7)
	//	{
	//		ce->CheatEngine::Game::GameBase.PassReadNameTrack = (DWORD64)paddress;
	//		//OutputDebugStringA_1Param("[GN]:申请的指针：%p", paddress);
	//		return paddress;
	//	}
	//
	//	//OutputDebugStringA_1Param("[GN]:Base-> VirtualAlloc进入死循环,地址：%p", return_address);
	//	//while (true)
	//	//{
	//	//	Sleep(1);
	//	//}
	//}

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

	if (_wcsicmp(lpLibFileName, L"ACE-IDS.dll") == 0)
	{
		OutputDebugStringA("[GN]:过滤加载ACE-IDS.dll");
		return 0;
	}

	pmodule = ::LoadLibraryW(lpLibFileName);

	return pmodule;
}

HMODULE WINAPI HookApi::Self_LoadLibraryA(_In_ LPCSTR lpLibFileName)
{
	HMODULE pmodule = NULL;

	OutputDebugStringA_1Param("[GN]:Self_LoadLibraryA()名称：%s", lpLibFileName);

	if (_stricmp(lpLibFileName, "ACE-IDS.dll") == 0)
	{
		OutputDebugStringA("[GN]:过滤加载ACE-IDS.dll");
		return 0;
	}

	pmodule = ::LoadLibraryA(lpLibFileName);

	return pmodule;
}

HMODULE WINAPI HookApi::Self_LoadLibraryExW(_In_ LPCWSTR lpLibFileName, _Reserved_ HANDLE hFile, _In_ DWORD dwFlags)
{
	HMODULE pmodule = NULL;

	OutputDebugStringA_1Param("[GN]:Self_LoadLibraryExW()名称：%S", lpLibFileName);

	if (_wcsicmp(lpLibFileName, L"ACE-IDS.dll") == 0)
	{
		OutputDebugStringA("[GN]:过滤加载ACE-IDS.dll");
		return 0;
	}

	pmodule = ::LoadLibraryExW(lpLibFileName, hFile, dwFlags);

	return pmodule;
}

HANDLE WINAPI HookApi::Self_CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	HANDLE phandle = NULL;

	OutputDebugStringA_1Param("[GN]:Self_CreateFileW() 名称：%S", lpFileName);
	if (_wcsicmp(lpFileName, L"ACE-IDS.dll") == 0)
	{
		OutputDebugStringA("[GN]:Self_CreateFileW(): 过滤加载ACE-IDS.dll");
		return 0;
	}

	phandle = ::CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	return phandle;
}

HANDLE WINAPI HookApi::Self_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	HANDLE phandle = NULL;

	OutputDebugStringA_1Param("[GN]:Self_CreateFileW() 名称：%s", lpFileName);
	
	phandle = ::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	return phandle;
}

VOID WINAPI HookApi::Self_Sleep(_In_ DWORD dwMilliseconds)
{
	DWORD64 return_address = (DWORD64)::_ReturnAddress();

	//Base处理
	if ((return_address > ce->CheatEngine::Game::GameBase.ACE_BASE64) && (return_address<return_address>ce->CheatEngine::Game::GameBase.ACE_BASE64End))
	{
		if (dwMilliseconds == 300000)
		{
			OutputDebugStringA("[GN]:Base:pass:ms");

			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
		}
	}

	//CSI处理
	if ((return_address > ce->CheatEngine::Game::GameBase.ACE_CSI64) && (return_address<return_address>ce->CheatEngine::Game::GameBase.ACE_CSI64End))
	{
		if (dwMilliseconds == 1)
		{
			OutputDebugStringA("[GN]:CSI:pass:ms");

			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
			::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
		}
	}

	return ::Sleep(dwMilliseconds);
}

BOOL WINAPI HookApi::Self_Process32NextW(__in HANDLE hSnapshot, __out LPPROCESSENTRY32W lppe)
{
	//OutputDebugStringA("[GN]:进入Process32休眠");

	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);
	::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF); ::Sleep(0xFFFFFFFFFFFFFFFF);

	return Process32NextW(hSnapshot, lppe);
}

HANDLE WINAPI HookApi::Self_CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
	DWORD64 return_address = (DWORD64)::_ReturnAddress();
	ce->CheatEngine::Game::GameBase.ACE_CSI64 = (__int64)ce->CheatEngine::CheatEngineApi::GetModuleHandleA("ACE-CSI64.dll");
	ce->CheatEngine::Game::GameBase.ACE_CSI64End = (__int64)ce->CheatEngine::Tools::GetModuleEndAddress(ce->CheatEngine::CheatEngineApi::GetModuleHandleA("ACE-CSI64.dll"));
	ce->CheatEngine::Game::GameBase.ACE_IDS = (__int64)ce->CheatEngine::CheatEngineApi::GetModuleHandleA("ACE-IDS.dll");
	ce->CheatEngine::Game::GameBase.ACE_IDSEnd = (__int64)ce->CheatEngine::Tools::GetModuleEndAddress(ce->CheatEngine::CheatEngineApi::GetModuleHandleA("ACE-IDS.dll"));
	ce->CheatEngine::Game::GameBase.ACE_IDS64 = (__int64)ce->CheatEngine::CheatEngineApi::GetModuleHandleA("ACE-IDS64.dll");
	ce->CheatEngine::Game::GameBase.ACE_IDS64End = (__int64)ce->CheatEngine::Tools::GetModuleEndAddress(ce->CheatEngine::CheatEngineApi::GetModuleHandleA("ACE-IDS64.dll"));

	if ((return_address > ce->CheatEngine::Game::GameBase.ACE_CSI64) && (return_address < ce->CheatEngine::Game::GameBase.ACE_CSI64End))
	{
		OutputDebugStringA("[GN]:ACE_CSI64-> CreateThread死循环");
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		//while (true)
		//{
		//	Sleep(0xFFFFFFFFFFFFFFFF);
		//}
	}
	if ((return_address > ce->CheatEngine::Game::GameBase.ACE_IDS) && (return_address < ce->CheatEngine::Game::GameBase.ACE_IDSEnd))
	{
		OutputDebugStringA("[GN]:ACE_IDS-> CreateThread死循环");
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		//while (true)
		//{
		//	Sleep(0xFFFFFFFFFFFFFFFF);
		//}
	}
	if ((return_address > ce->CheatEngine::Game::GameBase.ACE_IDS64) && (return_address < ce->CheatEngine::Game::GameBase.ACE_IDS64End))
	{
		OutputDebugStringA("[GN]:ACE_IDS64-> CreateThread死循环");
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		Sleep(0xFFFFFFFFFFFFFFFF);
		//while (true)
		//{
		//	Sleep(0xFFFFFFFFFFFFFFFF);
		//}
	}

	//OutputDebugStringA("[GN]:放过线程");

	//return ::CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
	return ce->CheatEngine::old_createthread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}



