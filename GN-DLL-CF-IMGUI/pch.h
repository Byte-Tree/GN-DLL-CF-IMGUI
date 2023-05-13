#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <Winuser.h>
#include <vector>
#include <iostream>
#include <atlstr.h>
#include <string>
#include <tchar.h>
#include <time.h>
#include <Psapi.h>
#include <fstream>
#include <winnls.h>
#include <tlhelp32.h>
#include <winsock.h>
#include "VMProtectSDK/VMProtectSDK.h"

#pragma comment(lib,"dwmapi.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"ComCtl32.lib")
#pragma comment(lib,"dwrite.lib")

#pragma warning (disable:4244)
#pragma warning( disable : 4996 )

#define OutputDebugStringA_1Param(fmt,var) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var);OutputDebugStringA(sOut);}
#define OutputDebugStringA_2Param(fmt,var1,var2) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var1,var2);OutputDebugStringA(sOut);}
#define OutputDebugStringA_3Param(fmt,var1,var2,var3) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var1,var2,var3);OutputDebugStringA(sOut);}
#define OutputDebugStringA_4Param(fmt,var1,var2,var3,var4) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var1,var2,var3,var4);OutputDebugStringA(sOut);}

using namespace std;

