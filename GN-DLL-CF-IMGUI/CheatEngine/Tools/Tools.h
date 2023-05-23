#pragma once
#include "../../pch.h"
#include <winternl.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")

struct systime
{
	int year; int month; int day; int hour; int min; int sec;
};

struct STACK_FRAME_INFO {
	PVOID returnAddress;
	PVOID functionAddress;
	PVOID callAddress;
	PVOID callTargetAddress;
};

struct CALL_STACK_INFO {
	PVOID stackBottom;
	PVOID stackTop;
	DWORD dwFrameCount;
	STACK_FRAME_INFO* pFrameList;
};

extern "C" LONG(__stdcall * ZwQueryInformationThread)(IN HANDLE ThreadHandle, IN THREADINFOCLASS ThreadInformationClass, OUT PVOID ThreadInformation, IN ULONG ThreadInformationLength, OUT PULONG ReturnLength OPTIONAL) = NULL;


class Tools
{
private:
	time_t rawtime;
	struct tm* timeinfo;

public:
	systime GetSystemtime();
	std::string string_to_utf8(const std::string& str);
	void BrokenModuleLink(HANDLE modulehandle);
	void StackTrace64();
	PVOID GetReturnAddress();
	void GetCallStackInfo(CALL_STACK_INFO& callStack, DWORD dwMaxFrame);
	void GetStack(void);
	bool SuspendThreadByTag(DWORD pid, const char* judgment_tag);
	bool ResumeThreadByTag(DWORD pid, const char* judgment_tag);
};
