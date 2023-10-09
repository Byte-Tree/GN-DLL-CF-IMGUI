#include "Exception.h"
#include "../GN-DLL-CF-IMGUI/NetVerification/NetVerification.h"
#include "MinHook/MinHook/MinHook.h"
//#pragma comment(lib,"../MinHook/lib/libMinHook-x64-v142-mt.lib")

#define ServerHost "118.123.202.72"
#define ServerPort 1882


GN_Exception* gn_exception = new GN_Exception();

typedef struct _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION
{
	ULONG Version;
	ULONG Reserved;
	PVOID Callback;
} PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION, * PPROCESS_INSTRUMENTATION_CALLBACK_INFORMATION;

typedef LONG(WINAPI* pfnNtSetContextThread)(IN HANDLE ThreadHandle, IN PCONTEXT Context);
typedef LONG(WINAPI* pfnNtSuspendThread)(IN HANDLE ThreadHandle, OUT PULONG PreviousSuspendCount OPTIONAL);
typedef LONG(WINAPI* pfnNtResumeThread)(IN HANDLE ThreadHandle, OUT PULONG PreviousSuspendCount OPTIONAL);
typedef LONG(WINAPI* pfnNtContinue)(IN PCONTEXT Context, IN BOOLEAN TestAlert);
typedef void (WINAPI* pfnKiUserExceptionDispatcher)(__in PEXCEPTION_RECORD ExceptionRecord, __in PCONTEXT ContextRecord);
extern "C" LONG(__stdcall * ZwQueryInformationThread)(IN HANDLE ThreadHandle, IN THREADINFOCLASS ThreadInformationClass, OUT PVOID ThreadInformation, IN ULONG ThreadInformationLength, OUT PULONG ReturnLength OPTIONAL) = NULL;
extern "C" NTSTATUS NTAPI NtSetInformationProcess(HANDLE ProcessHandle, ULONG ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength);
extern "C" NTSTATUS NtContinue(PCONTEXT, unsigned long long);
extern "C" void MyCallbackEntry();
extern "C" void MyCallbackRoutine(CONTEXT * context);
extern "C" void NtSetContextThreadProc();
extern "C" void NtSuspendThreadProc();
extern "C" void NtResumeThreadProc();
extern "C" void NtContinueProc();
void Self_KiUserExceptionDispatcher(__in PEXCEPTION_RECORD ExceptionRecord, __in PCONTEXT ContextRecord);
ULONG GetSSDTIndexByName(const char* function_name);

pfnNtSetContextThread pNtSetContextThread = NULL;
pfnNtSuspendThread pNtSuspendThread = NULL;
pfnNtResumeThread pNtResumeThread = NULL;
pfnNtContinue pNtContinue = NULL;
bool call_status = false;
__int64 sysret_address = 0, RtlRestoreContext_offset = 0;
pfnKiUserExceptionDispatcher old_KiUserExceptionDispatcher = NULL;


GN_Exception::GN_Exception()
{

}

GN_Exception::~GN_Exception()
{

}

void GN_Exception::SetVectoredExceptionHandler(bool potision, PVECTORED_EXCEPTION_HANDLER vectored_handler_pointer)
{
	//���VEH  ����1=1��ʾ����Veh����ͷ����=0��ʾ���뵽VEH����β��
	AddVectoredExceptionHandler(potision, vectored_handler_pointer);
}

LPTOP_LEVEL_EXCEPTION_FILTER GN_Exception::SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
	return ::SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
}

ULONG GN_Exception::UnSetVectoredExceptionHandler(PVECTORED_EXCEPTION_HANDLER vectored_handler_pointer)
{
	return RemoveVectoredExceptionHandler(vectored_handler_pointer);
}

void GN_Exception::SetMDR(DWORD64 dr0, DWORD64 dr1, DWORD64 dr2, DWORD64 dr3)
{
	this->mdr1 = dr0;
	this->mdr2 = dr1;
	this->mdr3 = dr2;
	this->mdr4 = dr3;
}

int GN_Exception::SetHardWareBreakPoint(const wchar_t* main_modulename, DWORD64 dr7_statu, __int64 br1, __int64 br2, __int64 br3, __int64 br4)
{
	//printf("��ģ������%S\n", main_modulename);
	//printf("br1:%p\n", br1);
	//printf("br2:%p\n", br2);
	//printf("br3:%p\n", br3);
	//printf("br4:%p\n", br4);
	this->SetMDR(br1, br2, br3, br4);
	//�����߳� ͨ��openthread��ȡ���̻߳���������Ӳ���ϵ�
	HANDLE hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hTool32 != INVALID_HANDLE_VALUE)
	{
		THREADENTRY32 thread_entry32;						//�̻߳����ṹ��
		thread_entry32.dwSize = sizeof(THREADENTRY32);
		HANDLE h_hook_thread = NULL;
		MODULEINFO module_info = { 0 };						//ģ����Ϣ

		HANDLE target_modulehandle = GetModuleHandleW(main_modulename);

		//�� ntdll.dll ��ȡ�� ZwQueryInformationThread
		(FARPROC&)ZwQueryInformationThread = ::GetProcAddress(GetModuleHandle(L"ntdll"), "ZwQueryInformationThread");

		if (target_modulehandle != 0)
		{
			//��ȡģ�������ַ
			GetModuleInformation(GetCurrentProcess(), (HMODULE)target_modulehandle, &module_info, sizeof(MODULEINFO));
			__int64 target_modulehandle_endaddress = ((__int64)module_info.lpBaseOfDll + module_info.SizeOfImage);
			//�����߳�
			if (Thread32First(hTool32, &thread_entry32))
			{
				do
				{
					//����̸߳�����IDΪ��ǰ����ID
					if (thread_entry32.th32OwnerProcessID == GetCurrentProcessId())
					{
						h_hook_thread = OpenThread(THREAD_ALL_ACCESS, FALSE, thread_entry32.th32ThreadID);
						// ��ȡ�߳���ڵ�ַ
						PVOID startaddr;//���������߳���ڵ�ַ
						ZwQueryInformationThread(h_hook_thread, (THREADINFOCLASS)ThreadQuerySetWin32StartAddress, &startaddr, sizeof(startaddr), NULL);
						if (((__int64)startaddr >= (__int64)target_modulehandle) && ((__int64)startaddr <= target_modulehandle_endaddress))
						{
							//OutputDebugStringA_1Param("[GN]:veh->�߳���ʼ��ַ��%p", startaddr);
							//��ͣ�߳�
							ULONG previous_count = NULL;
							pNtSuspendThread(h_hook_thread, &previous_count);

							//����Ӳ���ϵ�
							CONTEXT thread_context = { CONTEXT_DEBUG_REGISTERS };
							thread_context.ContextFlags = CONTEXT_ALL;
							//�õ�ָ���̵߳Ļ����������ģ�
							if (!GetThreadContext(h_hook_thread, &thread_context))
							{
								OutputDebugStringA("[GN]:veh->����߳�������ʧ��!");
								return 3;
							}
							thread_context.Dr0 = br1;
							thread_context.Dr1 = br2;
							thread_context.Dr2 = br3;
							thread_context.Dr3 = br4;
							thread_context.Dr7 = dr7_statu;
							if (pNtSetContextThread(h_hook_thread, &thread_context) != NULL)
							{
								OutputDebugStringA("[GN]:veh->�����߳�������ʧ��!");
								return 4;
							}
							//�ָ��߳�
							pNtResumeThread(h_hook_thread, &previous_count);
						}
						CloseHandle(h_hook_thread);
					}
				} while (Thread32Next(hTool32, &thread_entry32));
			}
			CloseHandle(hTool32);
			//OutputDebugStringA("[GN]:veh->it's over!");
			return true;
		}
		else
			return 2;//ģ������ȡʧ��
	}
	return 0;
}


bool GN_Exception::InstallException(const char* key, ExceptionHandlerApi exception_handler_api)
{
	//NetVerification
	if (!ȫ_��֤ͨѶ::��֤_��ʼ��(ServerHost, ServerPort))
	{
		//OutputDebugStringA("[GN]:��֤_��ʼ��() error");
		exit(-1);
	}
	string a(key);
	if (!ȫ_��֤ͨѶ::��֤_����¼(a))
	{
		//OutputDebugStringA("[GN]:��֤_����¼() error");
		exit(-1);
	}

	//��ȡsyscall������ַ
	pNtSetContextThread = (pfnNtSetContextThread)NtSetContextThreadProc;
	*(DWORD*)((DWORD64)&NtSetContextThreadProc + 0x04) = (DWORD)GetSSDTIndexByName("NtSetContextThread");
	pNtSuspendThread = (pfnNtSuspendThread)NtSuspendThreadProc;
	*(DWORD*)((DWORD64)&NtSuspendThreadProc + 0x04) = (DWORD)GetSSDTIndexByName("NtSuspendThread");
	pNtResumeThread = (pfnNtResumeThread)NtResumeThreadProc;
	*(DWORD*)((DWORD64)&NtResumeThreadProc + 0x04) = (DWORD)GetSSDTIndexByName("NtResumeThread");
	pNtContinue = (pfnNtContinue)NtContinueProc;
	*(DWORD*)((DWORD64)&NtContinueProc + 0x04) = (DWORD)GetSSDTIndexByName("NtContinue");

	//���溯��ָ��
	this->pExceptionHandlerApi = exception_handler_api;

	//�ж�ģ���ַ�Ƿ����
	HMODULE ntdll = ::GetModuleHandleA("ntdll.dll");
	if (ntdll == NULL)
		ntdll = ::LoadLibraryA("ntdll.dll");
	//��ȡhook�ķ��ص�ַ
	sysret_address = (__int64)::GetProcAddress(ntdll, "KiUserExceptionDispatcher");
	if (sysret_address == NULL)
		sysret_address = (__int64)::GetProcAddress(ntdll, "KiUserExceptionDispatcher");
	RtlRestoreContext_offset = this->GetOffset(sysret_address, 0x70, 0x10);
	//OutputDebugStringA_1Param("[GN]:RtlRestoreContext_offset:%p", RtlRestoreContext_offset);

	PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION info;
	info.Version = 0;
	info.Reserved = 0;
	info.Callback = MyCallbackEntry;
	ULONG status = NtSetInformationProcess(GetCurrentProcess(), 0x28, &info, sizeof(info));
	if (status)
	{
		OutputDebugStringA_1Param("[GN]:xxxxxxxProcess���� errorcode:%p", status);
		return false;
	}

	return true;
}

bool GN_Exception::InstallExceptionHook(const char* key, ExceptionHandlerApi exception_handler_api)
{
	////NetVerification
	//if (!ȫ_��֤ͨѶ::��֤_��ʼ��(ServerHost, ServerPort))
	//{
	//	OutputDebugStringA("[GN]:��֤_��ʼ��() error");
	//	exit(-1);
	//}
	//string a(key);
	//if (!ȫ_��֤ͨѶ::��֤_����¼(a))
	//{
	//	OutputDebugStringA("[GN]:��֤_����¼() error");
	//	exit(-1);
	//}

	//���溯��ָ��
	this->pExceptionHandlerApi = exception_handler_api;

	//��ʼ��MiniHook
	if (MH_Initialize() != MH_OK)
	{
		OutputDebugStringA("[GN]:MH_Initialize() error");
		::MessageBoxA(NULL, "GN_Exception: MiniHook��ʼ��ʧ�ܣ������ԣ�", "����", MB_OK);
		exit(-5);
	}
	if (MH_CreateHookApi(L"ntdll", "KiUserExceptionDispatcher", Self_KiUserExceptionDispatcher, (LPVOID*)&old_KiUserExceptionDispatcher) != MH_OK)
	{
		OutputDebugStringA("[GN]:MH_CreateHookApi() error");
		::MessageBoxA(NULL, "GN_Exception:MH_CreateHookApi KiUserExceptionDispatcher error", "Notice", MB_OK);
		exit(-5);
	}
	//if (MH_EnableHook((LPVOID)::GetProcAddress(GetModuleHandleA("ntdll.dll"), "KiUserExceptionDispatcher")) != MH_OK)
	if (MH_EnableHook(NULL) != MH_OK)
	{
		OutputDebugStringA("[GN]:MH_EnableHook() error");
		::MessageBoxA(NULL, "GN_Exception:MH_EnableHook error", "Notice", MB_OK);
		exit(-5);
	}

	OutputDebugStringA("[GN]:MiniHook over");
	return true;
}

bool GN_Exception::InitSymbol()
{
	SymSetOptions(SYMOPT_UNDNAME);
	return SymInitialize(GetCurrentProcess(), NULL, TRUE);
}

BYTE* GN_Exception::ReadBytes(DWORD64 address, SIZE_T size)
{
	BYTE ReturnValue[] = { NULL };

	if (IsBadReadPtr((VOID*)address, size))
		return { 0x00 };
	for (int i = 0; i < size; i++)
		ReturnValue[i] = *(BYTE*)address++;

	return ReturnValue;
}

__int64 GN_Exception::GetOffset(DWORD64 start_address, SIZE_T end_offset, SIZE_T weight)
{
	__int64 ret_address = 0;
	BYTE temp_address[5] = { NULL };
	BYTE judgment[5] = { 0x48,0x8B,0xCC,0x33,0xD2 };
	//������
	// mov	rcx, rsp
	// xor	edx, edx
	// call	RtlRestoreContext

	//��ʼ��ַ+��ʼƫ��
	start_address += weight;

	for (size_t i = 0; i < end_offset; i++)
	{
		memcpy((PVOID)temp_address, (PVOID)start_address, sizeof(judgment));
		if (_memicmp(temp_address, judgment, sizeof(judgment)) == 0)
		{
			//OutputDebugStringA_1Param("[GN]:�ҵ���������ַ��%p", start_address);
			ret_address = start_address;
			return ret_address;
		}
		else
			start_address++;
	}

	return ret_address;
}

PThreadData GN_Exception::GetThreadDataBuffer()
{
	void* thread_data = TlsGetValue(tls_index);
	if (!thread_data)
	{
		thread_data = LocalAlloc(LPTR, sizeof(ThreadData));
		if (!thread_data)
		{
			OutputDebugStringA("[GN]:LocalAlloc() error");
			//__debugbreak();
		}

		memset(thread_data, 0, sizeof(ThreadData));

		if (!TlsSetValue(tls_index, thread_data))
		{
			OutputDebugStringA("[GN]:TlsSetValue() error");
			//__debugbreak();
		}
	}

	return (PThreadData)thread_data;
}

ULONG GetSSDTIndexByName(const char* function_name)
{
	DWORD dwBytesRead = NULL;

	HANDLE hFile = CreateFileA("C:\\Windows\\System32\\ntdll.dll", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA_1Param("[GN]:%s-> CreateFileA:ntdll.dll is error!", __FUNCTION__);
		return 0;
	}
	DWORD dwLength = GetFileSize(hFile, NULL);
	if (dwLength == INVALID_FILE_SIZE || dwLength == 0)
	{
		OutputDebugStringA_1Param("[GN]:%s-> dwLength is null!", __FUNCTION__);
		return 0;
	}
	PVOID lpBuffer = HeapAlloc(GetProcessHeap(), 0, dwLength);
	if (!lpBuffer)
	{
		OutputDebugStringA_1Param("[GN]:%s-> lpBuffer is null!", __FUNCTION__);
		return 0;
	}
	if (ReadFile(hFile, lpBuffer, dwLength, &dwBytesRead, NULL) == FALSE)
	{
		OutputDebugStringA_1Param("[GN]:%s-> ReadFile is error!", __FUNCTION__);
		return 0;
	}


	//ȡ��������
	PIMAGE_DOS_HEADER  pDosHeader;
	PIMAGE_NT_HEADERS  pNtHeaders;
	PIMAGE_SECTION_HEADER pSectionHeader;
	ULONGLONG     FileOffset;//������64λ���ģ��������ﲻ��32���ֽ�
	PIMAGE_EXPORT_DIRECTORY pExportDirectory;
	//DLL�ڴ�����ת��DOSͷ�ṹ
	pDosHeader = (PIMAGE_DOS_HEADER)lpBuffer;
	//ȡ��PEͷ�ṹ
	pNtHeaders = (PIMAGE_NT_HEADERS)((ULONGLONG)lpBuffer + pDosHeader->e_lfanew);
	//�ж�PEͷ��������Ƿ�Ϊ��

	if (pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0)
		return 0;

	//ȡ��������ƫ��
	FileOffset = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

	//ȡ����ͷ�ṹ
	pSectionHeader = (PIMAGE_SECTION_HEADER)((ULONGLONG)pNtHeaders + sizeof(IMAGE_NT_HEADERS));
	PIMAGE_SECTION_HEADER pOldSectionHeader = pSectionHeader;
	//�����ڽṹ���е�ַ����
	for (UINT16 Index = 0; Index < pNtHeaders->FileHeader.NumberOfSections; Index++, pSectionHeader++)
	{
		if (pSectionHeader->VirtualAddress <= FileOffset && FileOffset <= pSectionHeader->VirtualAddress + pSectionHeader->SizeOfRawData)
			FileOffset = FileOffset - pSectionHeader->VirtualAddress + pSectionHeader->PointerToRawData;
	}

	//�������ַ
	pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((ULONGLONG)lpBuffer + FileOffset);
	//ȡ������������ַ
	PLONG AddressOfFunctions;
	FileOffset = pExportDirectory->AddressOfFunctions;
	//�����ڽṹ���е�ַ����
	pSectionHeader = pOldSectionHeader;
	for (UINT16 Index = 0; Index < pNtHeaders->FileHeader.NumberOfSections; Index++, pSectionHeader++)
	{
		if (pSectionHeader->VirtualAddress <= FileOffset && FileOffset <= pSectionHeader->VirtualAddress + pSectionHeader->SizeOfRawData)
			FileOffset = FileOffset - pSectionHeader->VirtualAddress + pSectionHeader->PointerToRawData;
	}
	AddressOfFunctions = (PLONG)((ULONGLONG)lpBuffer + FileOffset);//����ע��һ��foa��rva

	//ȡ��������������
	PUSHORT AddressOfNameOrdinals;
	FileOffset = pExportDirectory->AddressOfNameOrdinals;

	//�����ڽṹ���е�ַ����
	pSectionHeader = pOldSectionHeader;
	for (UINT16 Index = 0; Index < pNtHeaders->FileHeader.NumberOfSections; Index++, pSectionHeader++)
	{
		if (pSectionHeader->VirtualAddress <= FileOffset && FileOffset <= pSectionHeader->VirtualAddress + pSectionHeader->SizeOfRawData)
			FileOffset = FileOffset - pSectionHeader->VirtualAddress + pSectionHeader->PointerToRawData;
	}
	AddressOfNameOrdinals = (PUSHORT)((ULONGLONG)lpBuffer + FileOffset);//ע��һ��foa��rva

	//ȡ�������������
	PULONG AddressOfNames;
	FileOffset = pExportDirectory->AddressOfNames;

	//�����ڽṹ���е�ַ����
	pSectionHeader = pOldSectionHeader;
	for (UINT16 Index = 0; Index < pNtHeaders->FileHeader.NumberOfSections; Index++, pSectionHeader++)
	{
		if (pSectionHeader->VirtualAddress <= FileOffset && FileOffset <= pSectionHeader->VirtualAddress + pSectionHeader->SizeOfRawData)
			FileOffset = FileOffset - pSectionHeader->VirtualAddress + pSectionHeader->PointerToRawData;
	}
	AddressOfNames = (PULONG)((ULONGLONG)lpBuffer + FileOffset);//ע��һ��foa��rva
	//DbgPrint("\n AddressOfFunctions %llX AddressOfNameOrdinals %llX AddressOfNames %llX  \n", (ULONGLONG)AddressOfFunctions- (ULONGLONG)pBuffer, (ULONGLONG)AddressOfNameOrdinals- (ULONGLONG)pBuffer, (ULONGLONG)AddressOfNames- (ULONGLONG)pBuffer);
	//DbgPrint("\n AddressOfFunctions %llX AddressOfNameOrdinals %llX AddressOfNames %llX  \n", pExportDirectory->AddressOfFunctions, pExportDirectory->AddressOfNameOrdinals, pExportDirectory->AddressOfNames);

	//����������
	ULONG uNameOffset;
	ULONG uOffset;
	LPSTR FunName;
	PVOID pFuncAddr;
	ULONG uServerIndex;
	ULONG uAddressOfNames;
	for (ULONG uIndex = 0; uIndex < pExportDirectory->NumberOfNames; uIndex++, AddressOfNames++, AddressOfNameOrdinals++)
	{
		uAddressOfNames = *AddressOfNames;
		pSectionHeader = pOldSectionHeader;
		for (UINT32 Index = 0; Index < pNtHeaders->FileHeader.NumberOfSections; Index++, pSectionHeader++)
		{
			if (pSectionHeader->VirtualAddress <= uAddressOfNames && uAddressOfNames <= pSectionHeader->VirtualAddress + pSectionHeader->SizeOfRawData)
				uOffset = uAddressOfNames - pSectionHeader->VirtualAddress + pSectionHeader->PointerToRawData;
		}
		FunName = (LPSTR)((ULONGLONG)lpBuffer + uOffset);
		if (FunName[0] == 'Z' && FunName[1] == 'w')
		{
			pSectionHeader = pOldSectionHeader;
			uOffset = (ULONG)AddressOfFunctions[*AddressOfNameOrdinals];
			for (UINT32 Index = 0; Index < pNtHeaders->FileHeader.NumberOfSections; Index++, pSectionHeader++)
			{
				if (pSectionHeader->VirtualAddress <= uOffset && uOffset <= pSectionHeader->VirtualAddress + pSectionHeader->SizeOfRawData)
					uNameOffset = uOffset - pSectionHeader->VirtualAddress + pSectionHeader->PointerToRawData;
			}
			pFuncAddr = (PVOID)((ULONGLONG)lpBuffer + uNameOffset);
			uServerIndex = *(PULONG)((ULONGLONG)pFuncAddr + 4);
			FunName[0] = 'N';
			FunName[1] = 't';
			//���ָ���ı��
			if (!_stricmp(FunName, (const char*)function_name))
			{
				if (lpBuffer)
					HeapFree(GetProcessHeap(), 0, lpBuffer);
				CloseHandle(hFile);
				return uServerIndex;
			}
			//DbgPrint("Name: %s index:%d\n ", FunName, uServerIndex);//index��%d\n, uServerIndex
		}
	}


	if (lpBuffer)
		HeapFree(GetProcessHeap(), 0, lpBuffer);
	CloseHandle(hFile);
}

void MyCallbackRoutine(CONTEXT* context)
{
	context->Rip = __readgsqword(0x02D8);//syscall �ķ��ص�ַ
	context->Rsp = __readgsqword(0x02E0);//context = rsp, ExceptionRecord = rsp + 0x4F0
	context->Rcx = context->R10;

	////PThreadData current_thread_data = gn_exception->GetThreadDataBuffer();
	////if (current_thread_data->IsThreadHandlingSyscall)
	////	NtContinue(context, 0);
	////current_thread_data->IsThreadHandlingSyscall = true;
	////
	////////�������õĺ�����
	//////CHAR buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME] = { 0 };
	//////PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
	//////pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	//////pSymbol->MaxNameLen = MAX_SYM_NAME;
	//////DWORD64 Displacement;
	//////BOOLEAN result = SymFromAddr(GetCurrentProcess(), context->Rip, &Displacement, pSymbol);
	//////if (result)
	//////{
	//////	//if (_stricmp(pSymbol->Name, "ZwRaiseException") == 0)
	//////	if (_stricmp(pSymbol->Name, "KiUserExceptionDispatcher") == 0)
	//////	{
	//////		OutputDebugStringA_2Param("[GN]:Function: %s Address: %p", pSymbol->Name, context->Rip);
	//////		//LONG status = gn_exception->pExceptionHandlerApi((PEXCEPTION_RECORD)(context->Rsp + 0x4F0), (PCONTEXT)context->Rsp);
	//////		//if (status == EXCEPTION_CONTINUE_EXECUTION)
	//////		//{
	//////		//	//OutputDebugStringA("[GN]:RaxΪ0");
	//////		//	//context->Rax = 0;
	//////		//	RtlRestoreContext((PCONTEXT)context->Rsp, 0);
	//////		//}
	//////	}
	//////}
	////
	////if (context->Rip == sysret_address)
	////{
	////	LONG status = gn_exception->pExceptionHandlerApi((PEXCEPTION_RECORD)(context->Rsp + 0x4F0), (PCONTEXT)context->Rsp);
	////	if (status == EXCEPTION_CONTINUE_EXECUTION)
	////	{
	////		context->Rip = RtlRestoreContext_offset;
	////		//OutputDebugStringA("[GN]:�޸�context");
	////	}
	////}
	////current_thread_data->IsThreadHandlingSyscall = false;
	////NtContinue(context, 0);
	////
	////if (!call_status)
	////{
	////	call_status = true;
	////
	////	if (context->Rip == sysret_address)
	////	{
	////		LONG status = gn_exception->pExceptionHandlerApi((PEXCEPTION_RECORD)(context->Rsp + 0x4F0), (PCONTEXT)context->Rsp);
	////		if (status == EXCEPTION_CONTINUE_EXECUTION)
	////		{
	////			context->Rip = RtlRestoreContext_offset;
	////			//OutputDebugStringA("[GN]:�޸�context");
	////		}
	////	}
	////
	////	call_status = false;
	////}
	////NtContinue(context, 0);

	//�ȶ�����
	if (context->Rip == sysret_address)
	{
		LONG status = gn_exception->pExceptionHandlerApi((PEXCEPTION_RECORD)(context->Rsp + 0x4F0), (PCONTEXT)context->Rsp);
		if (status == EXCEPTION_CONTINUE_EXECUTION)
		{
			context->Rip = RtlRestoreContext_offset;
			//OutputDebugStringA("[GN]:�޸�context");
		}
	}

	pNtContinue(context, 0);
}

//MiniHook�ô˺���
void Self_KiUserExceptionDispatcher(__in PEXCEPTION_RECORD ExceptionRecord, __in PCONTEXT ContextRecord)
{
	LONG status = gn_exception->pExceptionHandlerApi(ExceptionRecord, ContextRecord);
	if (status == EXCEPTION_CONTINUE_EXECUTION)
	{
		OutputDebugStringA("[GN]:�ָ��Ĵ���ǰ");
		RtlRestoreContext(ContextRecord, ExceptionRecord);
		//NtContinue(ContextRecord, 0);
		OutputDebugStringA("[GN]:�ָ��Ĵ�����...");
	}
	else
		return old_KiUserExceptionDispatcher(ExceptionRecord, ContextRecord);

	OutputDebugStringA("[GN]:����KiUserExceptionDispatcher");

	//return old_KiUserExceptionDispatcher(ExceptionRecord, ContextRecord);
}


