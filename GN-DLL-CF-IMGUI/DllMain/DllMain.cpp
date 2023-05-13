#include "DllMain.h"
#include "../ReflectiveLoader-User/GN-ReflectiveLoader-User.h"

CheatEngine* ce = nullptr;


void CheatEngineInit(HINSTANCE hinstance)
{
    ce = new CheatEngine(hinstance);
}

extern "C" __declspec(dllexport) BOOL MyDLLFunction(LPVOID data, DWORD data_length)
{
    char temp[1024] = { NULL };
    sprintf_s(temp, "调用的参数：%s", data);
    //OutputDebugStringA_1Param("[GN]:传入的用户数据:\n%s\n", temp);
    //printf("传入的用户数据：\n");
    //printf("%s\n", data);
    ////MessageBoxA(NULL, temp, "MyDLLFunction", MB_OK);
    //CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)TestFunc, NULL, NULL, NULL);
    return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CheatEngineInit, (LPVOID)hModule, NULL, NULL);
        break;
    }
    case DLL_THREAD_ATTACH: break;
    case DLL_PROCESS_DETACH:
    {
        delete ce;
        break;
    }
    case DLL_THREAD_DETACH: break;
    }
    return TRUE;
}


