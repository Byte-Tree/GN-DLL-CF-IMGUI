#include "Exception.h"
#include "../GN-DLL-CF-IMGUI/NetVerification/������֤.h"
#include "MinHook/MinHook/MinHook.h"
//#pragma comment(lib,"../MinHook/lib/libMinHook-x64-v142-mt.lib")

#define ServerHost "221.236.21.196"
#define ServerPort 1882

GN_Exception* gn_exception = new GN_Exception();

typedef struct _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION
{
	ULONG Version;
	ULONG Reserved;
	PVOID Callback;
} PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION, * PPROCESS_INSTRUMENTATION_CALLBACK_INFORMATION;

typedef void (WINAPI* pfnKiUserExceptionDispatcher)(__in PEXCEPTION_RECORD ExceptionRecord, __in PCONTEXT ContextRecord);
extern "C" LONG(__stdcall * ZwQueryInformationThread)(IN HANDLE ThreadHandle, IN THREADINFOCLASS ThreadInformationClass, OUT PVOID ThreadInformation, IN ULONG ThreadInformationLength, OUT PULONG ReturnLength OPTIONAL) = NULL;
extern "C" NTSTATUS NTAPI NtSetInformationProcess(HANDLE ProcessHandle, ULONG ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength);
extern "C" NTSTATUS NtContinue(PCONTEXT, unsigned long long);
extern "C" void MyCallbackEntry();
extern "C" void MyCallbackRoutine(CONTEXT * context);
void Self_KiUserExceptionDispatcher(__in PEXCEPTION_RECORD ExceptionRecord, __in PCONTEXT ContextRecord);

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
						//h_hook_thread = OpenThread(THREAD_SET_CONTEXT | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, thread_entry32.th32ThreadID);
						h_hook_thread = OpenThread(THREAD_SET_CONTEXT | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME, FALSE, thread_entry32.th32ThreadID);
						// ��ȡ�߳���ڵ�ַ
						PVOID startaddr;//���������߳���ڵ�ַ
						ZwQueryInformationThread(h_hook_thread, (THREADINFOCLASS)ThreadQuerySetWin32StartAddress, &startaddr, sizeof(startaddr), NULL);
						if (((__int64)startaddr >= (__int64)target_modulehandle) && ((__int64)startaddr <= target_modulehandle_endaddress))
						{
							//OutputDebugStringA_1Param("[GN]:veh->�߳���ʼ��ַ��%p", startaddr);
							//��ͣ�߳�
							SuspendThread(h_hook_thread);
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
							if (!SetThreadContext(h_hook_thread, &thread_context))
							{
								OutputDebugStringA("[GN]:veh->�����߳�������ʧ��!");
								return 4;
							}
							//�ָ��߳�
							ResumeThread(h_hook_thread);
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

	//��ȡhook�ķ��ص�ַ
	sysret_address = (__int64)::GetProcAddress(::LoadLibraryA("ntdll.dll"), "KiUserExceptionDispatcher");
	if (sysret_address == NULL)
		sysret_address = (__int64)::GetProcAddress(::LoadLibraryA("ntdll.dll"), "KiUserExceptionDispatcher");
	RtlRestoreContext_offset = this->GetOffset(sysret_address, 0x70, 0x10);

	//if (!this->InitSymbol())
	//{
	//	OutputDebugStringA("[GN]:InitSymbol() error!");
	//	return false;
	//}
	//
	//this->tls_index = TlsAlloc();

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
	//NetVerification
	if (!ȫ_��֤ͨѶ::��֤_��ʼ��(ServerHost, ServerPort))
	{
		OutputDebugStringA("[GN]:��֤_��ʼ��() error");
		exit(-1);
	}
	string a(key);
	if (!ȫ_��֤ͨѶ::��֤_����¼(a))
	{
		OutputDebugStringA("[GN]:��֤_����¼() error");
		exit(-1);
	}

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

void MyCallbackRoutine(CONTEXT* context)
{
	context->Rip = __readgsqword(0x02D8);//syscall �ķ��ص�ַ
	context->Rsp = __readgsqword(0x02E0);//context = rsp, ExceptionRecord = rsp + 0x4F0
	context->Rcx = context->R10;

	//PThreadData current_thread_data = gn_exception->GetThreadDataBuffer();
	//if (current_thread_data->IsThreadHandlingSyscall)
	//	NtContinue(context, 0);
	//current_thread_data->IsThreadHandlingSyscall = true;
	//
	//////�������õĺ�����
	////CHAR buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME] = { 0 };
	////PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
	////pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	////pSymbol->MaxNameLen = MAX_SYM_NAME;
	////DWORD64 Displacement;
	////BOOLEAN result = SymFromAddr(GetCurrentProcess(), context->Rip, &Displacement, pSymbol);
	////if (result)
	////{
	////	//if (_stricmp(pSymbol->Name, "ZwRaiseException") == 0)
	////	if (_stricmp(pSymbol->Name, "KiUserExceptionDispatcher") == 0)
	////	{
	////		OutputDebugStringA_2Param("[GN]:Function: %s Address: %p", pSymbol->Name, context->Rip);
	////		//LONG status = gn_exception->pExceptionHandlerApi((PEXCEPTION_RECORD)(context->Rsp + 0x4F0), (PCONTEXT)context->Rsp);
	////		//if (status == EXCEPTION_CONTINUE_EXECUTION)
	////		//{
	////		//	//OutputDebugStringA("[GN]:RaxΪ0");
	////		//	//context->Rax = 0;
	////		//	RtlRestoreContext((PCONTEXT)context->Rsp, 0);
	////		//}
	////	}
	////}
	//
	//if (context->Rip == sysret_address)
	//{
	//	LONG status = gn_exception->pExceptionHandlerApi((PEXCEPTION_RECORD)(context->Rsp + 0x4F0), (PCONTEXT)context->Rsp);
	//	if (status == EXCEPTION_CONTINUE_EXECUTION)
	//	{
	//		context->Rip = RtlRestoreContext_offset;
	//		//OutputDebugStringA("[GN]:�޸�context");
	//	}
	//}
	//current_thread_data->IsThreadHandlingSyscall = false;
	//NtContinue(context, 0);

	//if (!call_status)
	//{
	//	call_status = true;
	//
	//	if (context->Rip == sysret_address)
	//	{
	//		LONG status = gn_exception->pExceptionHandlerApi((PEXCEPTION_RECORD)(context->Rsp + 0x4F0), (PCONTEXT)context->Rsp);
	//		if (status == EXCEPTION_CONTINUE_EXECUTION)
	//		{
	//			context->Rip = RtlRestoreContext_offset;
	//			//OutputDebugStringA("[GN]:�޸�context");
	//		}
	//	}
	//
	//	call_status = false;
	//}
	//NtContinue(context, 0);

	if (context->Rip == sysret_address)
	{
		LONG status = gn_exception->pExceptionHandlerApi((PEXCEPTION_RECORD)(context->Rsp + 0x4F0), (PCONTEXT)context->Rsp);
		if (status == EXCEPTION_CONTINUE_EXECUTION)
		{
			context->Rip = RtlRestoreContext_offset;
			//OutputDebugStringA("[GN]:�޸�context");
		}
	}
	NtContinue(context, 0);
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


