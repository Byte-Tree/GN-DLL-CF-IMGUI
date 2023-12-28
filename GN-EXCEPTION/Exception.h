#pragma once
#include <Windows.h>
#include <stdio.h>
#include <psapi.h>
#include <DbgHelp.h>
#include <tlhelp32.h>
#include <winternl.h>

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "imagehlp.lib")

#define OutputDebugStringA_1Param(fmt,var) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var);OutputDebugStringA(sOut);}
#define OutputDebugStringA_2Param(fmt,var1,var2) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var1,var2);OutputDebugStringA(sOut);}
#define OutputDebugStringA_3Param(fmt,var1,var2,var3) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var1,var2,var3);OutputDebugStringA(sOut);}

#define ThreadQuerySetWin32StartAddress 0x09

typedef struct _ThreadData
{
    volatile unsigned char IsThreadHandlingSyscall;
}ThreadData, * PThreadData;
typedef LONG(__stdcall* ExceptionHandlerApi)(PEXCEPTION_RECORD ExceptionRecord, PCONTEXT context);


class GN_Exception
{
private:
    unsigned long tls_index = 0;
    bool InitSymbol();

public:
    __int64 mdr1 = 0;//�ϵ��ַ1
    __int64 mdr2 = 0;//�ϵ��ַ2
    __int64 mdr3 = 0;//�ϵ��ַ3
    __int64 mdr4 = 0;//�ϵ��ַ4
    //����ϵ�
    __int64 software_breakpoint1 = 0;
    __int64 software_breakpoint2 = 0;
    __int64 software_breakpoint3 = 0;
    __int64 software_breakpoint4 = 0;
    __int64 software_breakpoint5 = 0;
    __int64 software_breakpoint6 = 0;
    __int64 software_breakpoint7 = 0;
    __int64 software_breakpoint8 = 0;
    __int64 software_breakpoint9 = 0;
    __int64 software_breakpoint10 = 0;
    __int64 software_breakpoint11 = 0;
    __int64 software_breakpoint12 = 0;
    __int64 software_breakpoint13 = 0;
    __int64 software_breakpoint14 = 0;
    __int64 software_breakpoint15 = 0;
    __int64 software_breakpoint16 = 0;
    __int64 software_breakpoint17 = 0;
    __int64 software_breakpoint18 = 0;
    __int64 software_breakpoint19 = 0;
    __int64 software_breakpoint20 = 0;
    __int64 software_breakpoint21 = 0;
    __int64 software_breakpoint22 = 0;
    __int64 software_breakpoint23 = 0;
    __int64 software_breakpoint24 = 0;
    __int64 software_breakpoint25 = 0;

public:
    ExceptionHandlerApi pExceptionHandlerApi = NULL;

private:
    void SetMDR(DWORD64 dr0, DWORD64 dr1, DWORD64 dr2, DWORD64 dr3);
    BYTE* ReadBytes(DWORD64 address, SIZE_T size);
    __int64 GetOffset(DWORD64 start_address, SIZE_T end_offset, SIZE_T weight);

public:
    GN_Exception();
    ~GN_Exception();
    bool InstallException(const char* key, ExceptionHandlerApi exception_handler_api);
    PThreadData GetThreadDataBuffer();
    //�����쳣������
    void SetVectoredExceptionHandler(bool potision, PVECTORED_EXCEPTION_HANDLER vectored_handler_pointer);
    //���ýṹ�쳣������
    LPTOP_LEVEL_EXCEPTION_FILTER SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
    //ж���쳣������
    ULONG UnSetVectoredExceptionHandler(PVECTORED_EXCEPTION_HANDLER vectored_handler_pointer);
    //0 ��������ʧ�ܣ�1 �ɹ���2 ģ������ȡʧ�ܣ�3 ����߳�������ʧ�ܣ�4 �����߳�������ʧ��
    int SetHardWareBreakPoint(const wchar_t* main_modulename, DWORD64 dr7_statu, __int64 br1, __int64 br2, __int64 br3, __int64 br4);

};


extern GN_Exception* gn_exception;

