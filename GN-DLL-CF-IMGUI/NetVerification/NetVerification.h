#pragma once
#include <windows.h>
//#include "VMProtectSDK.h"
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include <string>
using namespace std;
typedef UINT_PTR        SOCKET;


namespace ȫ_��֤ͨѶ
{
    EXTERN_C   SOCKET ͨѶ���;
    EXTERN_C   INT32 ʣ��ʱ��;

    BOOL TCP_����(char* ��������);
    BOOL TCP_����(const char* ����);
    BOOL TCP_����(const char* ip, INT32 �˿�);
    BOOL TCP_�Ͽ�();

    string ת��ʱ��(INT32 ����);
    BOOL ��֤_��ʼ��(const char* ip, INT32 �˿�);
    BOOL ��֤_����¼(string ����);
    BOOL д������(LPCSTR lpKeyName, LPCSTR lpString);
    INT32 ��������(LPCSTR lpKeyName);
    string �ı�����(LPCSTR lpKeyName);
}

void char_2_Hex(char* Char, char* Hex);
void Hex_2_char(char* Hex, char* Char);
char* RC4(char* C, char* key);
