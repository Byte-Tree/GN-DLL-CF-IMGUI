#include "DllMain.h"

Draw* draw = nullptr;


void DllInit()
{
	draw = new Draw();

	RTL_OSVERSIONINFOW osversion{};
	LI_FN(RtlGetVersion)(&osversion);
	DWORD init_result = -1;
	if (osversion.dwBuildNumber >= 10240)
		init_result = dwm::win10::init(0);
	else
		init_result = dwm::win7::init(0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{ //Èë¿Úº¯Êý
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DllInit, NULL, NULL, NULL);
		break;
	}
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}

