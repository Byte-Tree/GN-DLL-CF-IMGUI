#pragma once
#include <windows.h>
//#include "VMProtectSDK.h"
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include <string>
using namespace std;
typedef UINT_PTR        SOCKET;


namespace 全_验证通讯
{
    EXTERN_C   SOCKET 通讯句柄;
    EXTERN_C   INT32 剩余时间;

    BOOL TCP_接收(char* 接收数据);
    BOOL TCP_发送(const char* 内容);
    BOOL TCP_连接(const char* ip, INT32 端口);
    BOOL TCP_断开();

    string 转换时间(INT32 秒数);
    BOOL 验证_初始化(const char* ip, INT32 端口);
    BOOL 验证_卡登录(string 卡号);
    BOOL 写配置项(LPCSTR lpKeyName, LPCSTR lpString);
    INT32 整数配置(LPCSTR lpKeyName);
    string 文本配置(LPCSTR lpKeyName);
}

void char_2_Hex(char* Char, char* Hex);
void Hex_2_char(char* Hex, char* Char);
char* RC4(char* C, char* key);
