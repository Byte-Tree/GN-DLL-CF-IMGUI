#pragma once
#include "../pch.h"
#include "Draw/Draw.h"
#include "Game/Game.h"
#include "Tools/Tools.h"
#include "MemoryTools/MemoryTools.h"
#include "CheatEngineApi/CheatEngineApi.h"
#include "../Driver/Driver.h"
#pragma comment(lib,"Driver/GN-Driver-Lib.lib")

#include "Hook/MinHook/MinHook/MinHook.h"
#pragma comment(lib, "CheatEngine/Hook/MinHook/lib/libMinHook-x64-v142-mt.lib")

typedef int (WINAPI* pfnsend)(_In_ SOCKET s, _In_reads_bytes_(len) const char FAR* buf, _In_ int len, _In_ int flags);
typedef HANDLE (WINAPI* pfnCreateThread)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress,
	LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);

class CheatEngine :public Game, public Draw, public MemoryTools, public Tools, public CheatEngineApi
{
private:
	HMODULE self_module_handle = NULL;

public:
	Driver* driver = nullptr;

public:
	void GameKeyCallBack(WPARAM wParam, LPARAM lParam);
	void GameCombinationKeyCallBack(WPARAM wParam, LPARAM lParam);
	static LONG WINAPI ExceptionHandler(PEXCEPTION_POINTERS ExceptionInfo);
	static LONG WINAPI NewExceptionHandler(PEXCEPTION_RECORD ExceptionRecord, PCONTEXT context);
	static LRESULT CALLBACK SelfGameWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	bool ByPassCheck(PCONTEXT context);
	void WhileByPassCheck();
	void InitHook();
	void SetSoftWareBreakPoint();

public:
	inline_hook* IsBadReadPtr_hook = nullptr;
	static BOOL WINAPI Self_IsBadReadPtr(CONST VOID* lp, UINT_PTR ucb);

	HANDLE SendToEvent = NULL;
	inline_hook* SendTo_hook = nullptr;
	static int WINAPI Self_SendTo(_In_ SOCKET s, _In_reads_bytes_(len) const char FAR* buf, _In_ int len,
		_In_ int flags, _In_reads_bytes_opt_(tolen) const struct sockaddr FAR* to, _In_ int tolen);

	pfnsend old_send = NULL;
	HANDLE SendEvent = NULL;
	inline_hook* Send_hook = nullptr;
	static int WINAPI Self_Send(_In_ SOCKET s, _In_reads_bytes_(len) const char FAR* buf, _In_ int len, _In_ int flags);

	pfnCreateThread old_createthread = NULL;

public:
	CheatEngine(HINSTANCE hinstance);
	~CheatEngine();

};


