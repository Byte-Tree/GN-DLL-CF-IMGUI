#pragma once
#include "../pch.h"
#include "Draw/Draw.h"
#include "Game/Game.h"
#include "Tools/Tools.h"
#include "MemoryTools/MemoryTools.h"
#include "CheatEngineApi/CheatEngineApi.h"
#include "../Driver/Driver.h"
#pragma comment(lib,"Driver/GN-Driver-Lib.lib")


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
	void InitHook();
	void SetSoftWareBreakPoint();

public:
	CheatEngine(HINSTANCE hinstance);
	~CheatEngine();

};


