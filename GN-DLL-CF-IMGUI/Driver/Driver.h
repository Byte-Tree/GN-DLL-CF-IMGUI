#pragma once
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <TlHelp32.h>
#include <winhttp.h>

#include "GN-ManualMap.h"
#include "GN-ReflectiveLoader.h"

#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"winhttp.lib")
#pragma comment(lib,"Wldap32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Crypt32.lib")
#pragma comment(lib,"Normaliz.lib")

#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)					//ntsubauth
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

#define OutputDebugStringA_1Param(fmt,var) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var);OutputDebugStringA(sOut);}
#define OutputDebugStringA_2Param(fmt,var1,var2) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var1,var2);OutputDebugStringA(sOut);}
#define OutputDebugStringA_3Param(fmt,var1,var2,var3) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var1,var2,var3);OutputDebugStringA(sOut);}

struct PARAMX
{
	PVOID lpFileData;
	DWORD DataLength;
	PVOID LdrGetProcedureAddress;
	PVOID dwNtAllocateVirtualMemory;
	PVOID pLdrLoadDll;
	PVOID RtlInitAnsiString;
	PVOID RtlAnsiStringToUnicodeString;
	PVOID RtlFreeUnicodeString;
};

using namespace std;

extern "C" __declspec(dllexport) class Driver
{
private:
	ULONG m_pid = 0;
	BYTE* ToBytes(DWORD64 num);

private:
	void MyDeleteFile();
	int InstallSYS(IN const char* lpszDriverName, IN const char* lpszDriverPath);
	bool UninstallSYS(IN const char* lpszDriverName);
	bool MyClearService(IN const char* lpszDriverName);

public:
	char sysfilename[MAX_PATH] = { NULL };
	char sysfilepath[4096] = { NULL };
	bool User_Call_InstallSYS();
	bool User_Call_UninstallSYS();

public:
	Driver();
	~Driver();
	bool charTowchar(IN const char* MyChar, OUT wchar_t* MyWchar);
	void SetProcessID(ULONG pid) { this->m_pid = pid; }
	bool GetProcessNameByID(IN ULONG pid, OUT char* process_name);
	ULONG GetProcessPIDW(IN CONST WCHAR* ProcessName);
	PVOID GetKernelModuleHandle(IN CONST WCHAR* module_name);
	HANDLE GetUserModuleHandle(IN CONST WCHAR* module_name);
	HANDLE GetUserModuleHandleEx(IN ULONG pid, IN CONST WCHAR* module_name);

	bool SetMemoryProtect(IN PVOID64 address, IN SIZE_T size, IN ULONG protect_attribute);
	bool SetMemoryProtectEx(IN ULONG pid, IN PVOID64 address, IN SIZE_T size, IN ULONG protect_attribute);
	bool SetExecutePage(IN ULONG64 virtualaddress, IN ULONG size);
	bool SetExecutePageEx(IN ULONG pid, IN ULONG64 virtualaddress, IN ULONG size);

	//�����ڴ�
	PVOID AllocMemory(IN ULONG size, IN ULONG protect);
	PVOID AllocMemoryEx(IN ULONG pid, IN ULONG size, IN ULONG protect);

	//�ͷ��ڴ�
	bool FreeMemory(IN ULONG64 free_address, IN ULONG memory_size);
	bool FreeMemoryEx(IN ULONG pid, IN ULONG64 free_address, IN ULONG memory_size);

	//VAD�����ڴ� ��ʱֻ֧������ʮ���ڴ��ַ
	bool HideMemoryByVAD(IN ULONG64 virtual_address, IN ULONG virtual_address_size);
	bool HideMemoryByVADEx(IN ULONG pid, IN ULONG64 virtual_address, IN ULONG virtual_address_size);

	//VAD�޸��ڴ�����
	bool SetMemoryVADProtection(IN ULONG64 virtual_address, IN ULONG virtual_address_size, IN DWORD new_protection);
	bool SetMemoryVADProtectionEx(IN ULONG pid, IN ULONG64 virtual_address, IN ULONG virtual_address_size, IN DWORD new_protection);

	//ɱ������
	bool KillProcess(IN ULONG pid);

	//ɾ���ļ�
	bool DeleteExecuteFile(IN WCHAR file_path[]);

	//��ȡ�������߳�
	DWORD GetProcessMainThread(DWORD pid);

	//��ͣ�ں��߳�
	bool SuspendKernelThread(const char* kernel_module_name, const char* judgment);
	bool SuspendKernelThreadByID(const char* kernel_module_name, HANDLE tid);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DownLoad File:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	void subString(char str[], char sub[], int index, int len);

public:
	int DownLoadFile(IN const char* host, IN const char* get, IN char* bufRecv, IN int* phttpHead);
	int DownLoadFile(IN const char* host, IN const char* get, IN char* bufRecv, IN int* phttpHead, IN const char* file_name);

	int DownLoadFileByWinHttp(IN const char* host, IN const wchar_t* file_path, OUT char* buffer);
	int DownLoadFileByWinHttpEx(IN const char* host, IN const wchar_t* file_path, IN const char* save_path);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Read/Write Process Memory By MDL:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	BOOL ReadFromKernelByMDL(IN ULONG pid, IN PVOID target_address, OUT PVOID read_buffer, IN SIZE_T read_data_size);
	BOOL WriteToKernelByMDL(IN ULONG pid, IN PVOID target_address, IN PVOID write_data, IN SIZE_T write_data_size);

public:
	//Read
	DWORD ReadIntByMDL(IN PVOID target_address);
	DWORD ReadIntByMDLEx(IN ULONG pid, IN PVOID target_address);
	DWORD64 ReadLongByMDL(IN PVOID target_address);
	DWORD64 ReadLongByMDLEx(IN ULONG pid, IN PVOID target_address);
	float ReadFloatByMDL(IN PVOID target_address);
	float ReadFloatByMDLEx(IN ULONG pid, IN PVOID target_address);
	BOOL ReadBytesByMDL(IN PVOID target_address, IN SIZE_T read_size, OUT BYTE* read_buffer);
	BOOL ReadBytesByMDLEx(IN ULONG pid, IN PVOID target_address, IN SIZE_T read_size, OUT BYTE* read_buffer);

	//Write
	BOOL WriteIntByMDL(IN PVOID target_address, IN int write_data);
	BOOL WriteIntByMDLEx(IN ULONG pid, IN PVOID target_address, IN int write_data);
	BOOL WriteLongByMDL(IN PVOID target_address, IN DWORD64 write_data);
	BOOL WriteLongByMDLEx(IN ULONG pid, IN PVOID target_address, IN DWORD64 write_data);
	BOOL WriteFloatByMDL(IN PVOID target_address, IN float write_data);
	BOOL WriteFloatByMDLEx(IN ULONG pid, IN PVOID target_address, IN float write_data);
	BOOL WriteBytesByMDL(IN PVOID target_address, IN PVOID write_data, IN SIZE_T write_size);
	BOOL WriteBytesByMDLEx(IN ULONG pid, IN PVOID target_address, IN PVOID write_data, IN SIZE_T write_size);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Read/Write Process Memory By CR3 No Attach:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	BOOL ReadFromKernelByCR3(IN ULONG pid, IN PVOID target_address, OUT PVOID read_buffer);
	BOOL WriteToKernelByCR3(IN ULONG pid, IN PVOID target_address, IN PVOID write_data, IN SIZE_T write_data_size);

public:
	//Read
	DWORD ReadIntByCR3(IN PVOID target_address);
	DWORD ReadIntByCR3Ex(IN ULONG pid, IN PVOID target_address);
	DWORD64 ReadLongByCR3(IN PVOID target_address);
	DWORD64 ReadLongByCR3Ex(IN ULONG pid, IN PVOID target_address);
	float ReadFloatByCR3(IN PVOID target_address);
	float ReadFloatByCR3Ex(IN ULONG pid, IN PVOID target_address);

	//Write
	BOOL WriteIntByCR3(IN PVOID target_address, IN int write_data);
	BOOL WriteIntByCR3Ex(IN ULONG pid, IN PVOID target_address, IN int write_data);
	BOOL WriteLongByCR3(IN PVOID target_address, IN DWORD64 write_data);
	BOOL WriteLongByCR3Ex(IN ULONG pid, IN PVOID target_address, IN DWORD64 write_data);
	BOOL WriteFloatByCR3(IN PVOID target_address, IN float write_data);
	BOOL WriteFloatByCR3Ex(IN ULONG pid, IN PVOID target_address, IN float write_data);
	BOOL WriteBytesByCR3(IN PVOID target_address, IN PVOID write_data, IN SIZE_T write_size);
	BOOL WriteBytesByCR3Ex(IN ULONG pid, IN PVOID target_address, IN PVOID write_data, IN SIZE_T write_size);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DLL Injecter:
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	bool WriteSections(LPBYTE dll_buffer, LPBYTE target_base, IMAGE_SECTION_HEADER* section_header, IMAGE_FILE_HEADER* old_file_header);
	bool WriteSectionsEx(ULONG pid, LPBYTE dll_buffer, LPBYTE target_base, IMAGE_SECTION_HEADER* section_header, IMAGE_FILE_HEADER* old_file_header);
	static void __stdcall Shellcode(MANUAL_MAPPING_DATA* lpData);
	HINSTANCE GetReturnModule(LPBYTE lpParamBuff);
	DWORD mManualMapInject(__int64 hook_point, int hook_byte_size, LPBYTE dll_buffer, DWORD dll_file_size, bool bClearHeader = true, bool bClearNonNeededSections = true, bool bAdjustProtections = false, bool bSEHExceptionSupport = true, DWORD fdwReason = DLL_PROCESS_ATTACH, LPVOID lpReserved = 0);

	//����ʽע��
	DWORD SeCreateBootstrap(IN LPBYTE Bootstrap, IN DWORD BootstrapLength, IN DWORD TargetArchitecture, IN ULONG_PTR ParameterData, IN ULONG_PTR RemoteBufferData, IN DWORD FunctionHashValue, IN ULONG_PTR UserData, IN DWORD UserDataLength, IN ULONG_PTR ReflectiveLoader);
	DWORD RvaToOffset(OUT DWORD Rva, IN UINT_PTR ImageBaseAddress);
	DWORD SeGetReflectiveLoaderOffset(IN VOID* BufferData);
	DWORD WINAPI SeLoadRemoteLibrary(IN DWORD64 hook_point, IN int hook_byte_size, IN PVOID file_buffer, IN DWORD file_buffer_size, IN LPVOID parameter_data, IN DWORD function_hash, IN PVOID transfer_data, IN DWORD transfer_data_size);
	DWORD WINAPI SeLoadRemoteLibraryByInstCallback(IN PVOID file_buffer, IN DWORD file_buffer_size, IN LPVOID parameter_data, IN DWORD function_hash, IN PVOID transfer_data, IN DWORD transfer_data_size, IN LONG kernel_wait_millisecond, IN BOOL isclear_proccallback);
	HANDLE WINAPI Original_SeLoadRemoteLibrary(HANDLE ProcessHandle, LPVOID FileData, DWORD FileLength, LPVOID ParameterData, DWORD FunctionHash, LPVOID UserData, DWORD UserDataLength);
	DWORD Wow64CreateRemoteThread(HANDLE ProcessHandle, LPVOID ThreadProcedure, LPVOID ParameterData, HANDLE* ThreadHandle);

	bool KernelHackThread(IN ULONG pid, IN ULONG64 param_buffer_address, IN ULONG64 loader_shellcode_address, IN LONG kernel_wait_millisecond);
	DWORD mInjectByKernelHackThread(IN ULONG pid, IN PVOID dll_file_buffer, IN DWORD dll_file_buffer_size, IN LONG kernel_wait_millisecond, IN PVOID transfer_data, IN DWORD transfer_data_size);

	bool NtCreateThreadByKernel(IN ULONG pid, IN ULONG64 param_buffer_address, IN ULONG64 loader_shellcode_address, IN LONG kernel_wait_millisecond);
	DWORD mInjectByKernelCreateThread(IN ULONG pid, IN PVOID dll_file_buffer, IN DWORD dll_file_buffer_size, IN LONG kernel_wait_millisecond);

	bool KernelCallback(IN ULONG pid, IN ULONG64 param_buffer_address, IN ULONG64 loader_shellcode_address, IN ULONG64 rtlcapturecontext_address, IN ULONG64 ntcontinue_address, IN LONG kernel_wait_millisecond, IN BOOL isclear_proccallback);
	DWORD mInjectByProcessCallback(IN ULONG pid, IN PVOID dll_file_buffer, IN DWORD dll_file_buffer_size, IN LONG kernel_wait_millisecond, IN BOOL isclear_proccallback);

public:
	//�ֶ�����ʽע��
	DWORD ManualMapInject(__int64 hook_point, int hook_byte_size, LPBYTE dll_buffer, DWORD dll_file_size);

	//����ʽע�� ����ֵ��0:Unkown Error 1:ok 2:��ȡ������Ϣʧ�� 3:��������ͬ�ļܹ� 4:�޷���ȡ����ƫ�� 5:�����ַʧ�� 6:��dll����д��Ŀ����� 7:д�봫���û����� 8:������������Ϊ0 999::�쳣ʧ��
	DWORD ReflectiveInject(IN DWORD64 hook_point, IN int hook_byte_size, IN PVOID file_buffer, IN DWORD file_buffer_size, IN PVOID transfer_data, IN DWORD transfer_data_size);
	DWORD ReflectiveInjectByInstCallback(IN PVOID file_buffer, IN DWORD file_buffer_size, IN PVOID transfer_data, IN DWORD transfer_data_size, IN LONG kernel_wait_millisecond, IN BOOL isclear_proccallback);

	//ԭ���ķ���ʽע��
	bool Original_ReflectiveInject(IN ULONG pid, IN PVOID file_buffer, IN DWORD file_buffer_size, IN PVOID transfer_data, IN DWORD transfer_data_size);

	//Զ���߳�ע��
	bool InjectByRemoteThread(IN const wchar_t* file_path);
	bool InjectByRemoteThreadEx(IN ULONG pid, IN const wchar_t* file_path);

	//�ں˽ٳ��߳�ע��
	bool InjectByKernelHackThread(IN PVOID file_buffer, IN DWORD file_buffer_size, IN LONG kernel_wait_millisecond, IN PVOID transfer_data, IN DWORD transfer_data_size);
	bool InjectByKernelHackThreadEx(IN ULONG pid, IN PVOID file_buffer, IN DWORD file_buffer_size, IN LONG kernel_wait_millisecond, IN PVOID transfer_data, IN DWORD transfer_data_size);

	//�ں�Զ���߳�ע��
	bool InjectByKernelCreateThread(IN PVOID file_buffer, IN DWORD file_buffer_size, IN LONG kernel_wait_millisecond);
	bool InjectByKernelCreateThreadEx(IN ULONG pid, IN PVOID file_buffer, IN DWORD file_buffer_size, IN LONG kernel_wait_millisecond);

	//�ں˽��̻ص�ע��
	bool InjectByProcessCallback(IN PVOID file_buffer, IN DWORD file_buffer_size, IN LONG kernel_wait_millisecond, IN BOOL isclear_proccallback);
	bool InjectByProcessCallbackEx(IN ULONG pid, IN PVOID file_buffer, IN DWORD file_buffer_size, IN LONG kernel_wait_millisecond, IN BOOL isclear_proccallback);

};


