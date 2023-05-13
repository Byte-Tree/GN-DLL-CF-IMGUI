#pragma once
#include "../../pch.h"

typedef HWND(WINAPI* FindWindowAStruct)(_In_opt_ LPCSTR lpClassName, _In_opt_ LPCSTR lpWindowName);
typedef DWORD(WINAPI* GetWindowThreadProcessIdStruct)(_In_ HWND hWnd, _Out_opt_ LPDWORD lpdwProcessId);
typedef DWORD(WINAPI* GetCurrentProcessIdStruct)(VOID);
typedef HANDLE(WINAPI* GetCurrentProcessStruct)(VOID);
typedef HMODULE(WINAPI* GetModuleHandleAStruct)(_In_opt_ LPCSTR lpModuleName);


class CheatEngineApi
{
private:
	HMODULE user32dll = 0, kernel32dll = 0;
	FindWindowAStruct findwindowaaddress = 0;
	GetWindowThreadProcessIdStruct getwindowthreadprocessid = 0;
	GetCurrentProcessIdStruct getcurrentprocessid = 0;
	GetCurrentProcessStruct getcurrentprocess = 0;
	GetModuleHandleAStruct getmodulehandlea = 0;

public:

public:
	CheatEngineApi();
	~CheatEngineApi();
	HWND FindWindowA(_In_opt_ LPCSTR lpClassName, _In_opt_ LPCSTR lpWindowName);
	DWORD GetWindowThreadProcessId(_In_ HWND hWnd, _Out_opt_ LPDWORD lpdwProcessId);
	DWORD GetCurrentProcessId();
	HANDLE GetCurrentProcess();
	HMODULE GetModuleHandleA(_In_opt_ LPCSTR lpModuleName);

};
