#include "Tools.h"
#include "../../DllMain/DllMain.h"

LONG(__stdcall* pZwQueryInformationThread)(IN HANDLE ThreadHandle, IN THREADINFOCLASS ThreadInformationClass, OUT PVOID ThreadInformation, IN ULONG ThreadInformationLength, OUT PULONG ReturnLength OPTIONAL) = NULL;


systime Tools::GetSystemtime()
{
	systime ret_time = { NULL };
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	ret_time.year = 1900 + timeinfo->tm_year;
	ret_time.month = 1 + timeinfo->tm_mon;
	ret_time.day = timeinfo->tm_mday;
	ret_time.hour = timeinfo->tm_hour;
	ret_time.min = timeinfo->tm_min;
	ret_time.sec = timeinfo->tm_sec;
	return ret_time;
}

std::string Tools::string_to_utf8(const std::string& str)
{
	int nwLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	memset(pwBuf, 0, nwLen * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);
	WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string ret = pBuf;
	delete[] pwBuf;
	delete[] pBuf;
	return ret;
}

void Tools::BrokenModuleLink(HANDLE modulehandle)
{
	OutputDebugStringA_1Param("[GN]:模块地址：%p", modulehandle);
	////抹除pe头
	//PIMAGE_DOS_HEADER pdosheader = (PIMAGE_DOS_HEADER)modulehandle;									//抹去z标志
	//pdosheader->e_magic = 0;																			//dos头后面就是pe头
	//PIMAGE_NT_HEADERS pntheader = (PIMAGE_NT_HEADERS)((char*)modulehandle + pdosheader->e_lfanew);	//抹去pe标志
	//pntheader->Signature = 0;
	ZeroMemory((PVOID)modulehandle, 1024);
}

DWORD Tools::RVA_2_RAW(char* buf, DWORD RVA, DWORD RAW, BOOL flag)				// RVA为导入表或导出表的RVA；flag为1，RVA转偏移，为0反过来——事实上此程序只用到了1
{
	PIMAGE_DOS_HEADER pDOS = (PIMAGE_DOS_HEADER)buf;					// 获取DOS头，pDos为PIMAGE_DOS_HEADER结构体的实例,buf则指向PE文件的基地址
	PIMAGE_NT_HEADERS pNT = (PIMAGE_NT_HEADERS)(buf + pDOS->e_lfanew);	// 获取NT头，pNT为PIMAGE_DOS_HEADER的实例，DOS头的e_lfanew成员指示了NT头的偏移量
	PIMAGE_SECTION_HEADER pSection = (PIMAGE_SECTION_HEADER)(buf + pDOS->e_lfanew + 0x18 + pNT->FileHeader.SizeOfOptionalHeader);
	// 获取区块表头，pSection为PIMAGE_SECTION_HEADER的实例
	// +0x18指向了可选头，加上可选头的大小即指向了Section表头的首部，可选头的大小存放在文件头的成员中

	DWORD SectionNumber = pNT->FileHeader.NumberOfSections;							// 通过文件头获取区块数（节区数）
	DWORD SizeOfAllHeadersAndSectionList = pNT->OptionalHeader.SizeOfHeaders;		// 所有头(DOS+NT)+区块表的大小，是一个大小而不是地址
	DWORD Imp_Exp_FA = 0;															// 导入导出表在磁盘文件中的地址
	DWORD SectionRVA = 0;															// 暂存每个节区表的RVA

	int i = 0;
	if (flag)
	{
		if (RVA < SizeOfAllHeadersAndSectionList)									// 如果导入导出表的RVA连节区表都没出，直接返回，因为(DOS+NT头+节区表)在内存中不展开
		{
			Imp_Exp_FA = RVA;
		}
		for (; i < SectionNumber; i++)												// 有多少节区就循环几次，从第一个节区表开始操作，如果PE文件有N个节，那么区块表就是由N个IMAGE_SECTION_HEADER组成的数组
		{
			SectionRVA = pSection[i].VirtualAddress;								// 该区块加载到内存中的RVA
			// 计算该导入导出表的RVA位于哪个区块内
			if (RVA > SectionRVA && SectionRVA + pSection[i].Misc.VirtualSize > RVA)// &&后面为：该区块的RVA(该区块在内存中的起始地址) + 该区块没有对齐处理之前的实际大小(磁盘中的大小。Misc是共用体)
			{
				Imp_Exp_FA = RVA - SectionRVA + pSection[i].PointerToRawData;				// （导入导出表的RVA - 所在节区的基址）得到导入导出表相对该节区的偏移量offset，然后offset + 该节区在磁盘文件中的VA = FOA，得到了文件偏移地址(即导入导出表在磁盘文件中的地址)
				break;																// 找到了就不再遍历节区了
			}
		}
	}
	else
	{
		if (RAW < SizeOfAllHeadersAndSectionList)									// 这里就是通过RAW求RVA了（该程序并未用到）  注意文件偏移地址就是在磁盘文件中的地址：RAW==FOA==FA   （其实一共就3个概念：VA RVA FA，分别是虚拟绝对地址，虚拟相对地址，文件绝对地址）
		{
			Imp_Exp_FA = RAW;
		}
		for (; i < SectionNumber; i++)
		{
			SectionRVA = pSection[i].PointerToRawData;
			if (RAW > SectionRVA && SectionRVA + pSection[i].SizeOfRawData > RAW)
			{
				Imp_Exp_FA = RAW - SectionRVA + pSection[i].VirtualAddress;
				break;
			}
		}
	}
	return Imp_Exp_FA;
}

DWORD64 Tools::GetImportTableIndexOffset(HANDLE modulehandle, PDWORD import_table_size)
{
	PIMAGE_DOS_HEADER pdos_header = (PIMAGE_DOS_HEADER)modulehandle;
	PIMAGE_NT_HEADERS pnt_header = (PIMAGE_NT_HEADERS)((char*)modulehandle + pdos_header->e_lfanew);	//dos头后面就是pe头
	DWORD64 import_table_rva = pnt_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;				//获取导入表的相对虚拟地址，DataDirectory[1]是导入表，0是导出表
	*import_table_size = pnt_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size;

	//PIMAGE_DOS_HEADER pDOS = (PIMAGE_DOS_HEADER)buf;
	//PIMAGE_NT_HEADERS pNT = (PIMAGE_NT_HEADERS)(buf + pDOS->e_lfanew);
	//DWORD ImportTableRVA = pNT->OptionalHeader.DataDirectory[1].VirtualAddress;					// 获得导入表的RVA，DataDirectory[1]是导入表，0是导出表
	//DWORD ImportDLL_FA = this->RVA_2_RAW(buf, ImportTableRVA, 0, 1);									// 计算导入DLL在磁盘文件中的地址，这个变量专门保存DLL地址
	//IMAGE_IMPORT_DESCRIPTOR* pImportTable = (IMAGE_IMPORT_DESCRIPTOR*)(buf + ImportDLL_FA);	// pImportTable指向导入的DLL在磁盘文件中的地址
	//OutputDebugStringA_1Param("[GN]:导出表地址：%p", pImportTable->FirstThunk);

	return import_table_rva;
}

PVOID64 Tools::GetModuleEndAddress(HMODULE module_handle)
{
	PVOID64 return_address = 0;
	MODULEINFO moduleinfo = { 0 };
	GetModuleInformation(ce->CheatEngineApi::GetCurrentProcess(), module_handle, &moduleinfo, sizeof(MODULEINFO));
	return return_address = (PVOID64)((__int64)moduleinfo.lpBaseOfDll + moduleinfo.SizeOfImage);
}

void Tools::StackTrace64()
{
	CONTEXT                       Context;
	KNONVOLATILE_CONTEXT_POINTERS NvContext;
	UNWIND_HISTORY_TABLE          UnwindHistoryTable;
	PRUNTIME_FUNCTION             RuntimeFunction;
	PVOID                         HandlerData;
	ULONG64                       EstablisherFrame;
	ULONG64                       ImageBase;

	// 首先得到当前Context
	RtlCaptureContext(&Context);

	// 初始化 UnwindHistoryTable，这个结构体主要用于多次查找RUNTIME_FUNCTION时加快查找效率
	RtlZeroMemory(&UnwindHistoryTable, sizeof(UNWIND_HISTORY_TABLE));

	// 下面的循环就是得到调用堆栈
	for (ULONG Frame = 0; ; Frame++)
	{
		// 在PE+ 的.pdata 段中找到函数对应的RuntimeFunction 结构
		// 只有叶函数没有此结构
		// 既不调用函数、又没有修改栈指针，也没有使用 SEH 的函数就叫做“叶函数”。
		RuntimeFunction = RtlLookupFunctionEntry(Context.Rip, &ImageBase, &UnwindHistoryTable);
		RtlZeroMemory(&NvContext, sizeof(KNONVOLATILE_CONTEXT_POINTERS));
		if (!RuntimeFunction)
		{
			// 我们没有得到结构体，我们当前得到了一个叶函数
			// 此时Rsp 直接指向Rip，调用叶函数只包含Call 操作，即只包含push eip 操作，Rsp += 8即可
			Context.Rip = (ULONG64)(*(PULONG64)Context.Rsp);
			Context.Rsp += 8;
		}
		else
		{
			// 虚拟展开，得到调用堆栈
			// 第一个参数表示Rip 所在函数没有过滤和处理函数
			// 仅仅进行虚拟展开得到上层调用堆栈
			RtlVirtualUnwind(UNW_FLAG_NHANDLER, ImageBase, Context.Rip, RuntimeFunction, &Context, &HandlerData, &EstablisherFrame, &NvContext);
		}

		// 没有得到Rip 即是调用失败
		if (!Context.Rip)
		{
			//printf("没有得到Rip 即是调用失败\n");
			break;
		}

		// 展示相关信息
		printf(
			"FRAME %02x: CallAddress=%p\r\n",
			Frame,
			Context.Rip);
	}
	return;
}

PVOID Tools::GetReturnAddress()
{
	PVOID pret = _ReturnAddress();
	printf("Return address from %s: %p\n", __FUNCTION__, pret);
	return pret;
}

void Tools::GetCallStackInfo(CALL_STACK_INFO& callStack, DWORD dwMaxFrame)
{
	std::vector<STACK_FRAME_INFO> vecFrames;
#ifdef _M_IX86
	STACK_FRAME_INFO StackFrame;
	std::vector<PVOID> vecRetAddr;
	ULONG StackCount = 0;
	RTLWALKFRAMECHAIN pRtlWalkFrameChain =
		(RTLWALKFRAMECHAIN)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlWalkFrameChain");

	vecRetAddr.resize(50);
	StackCount = pRtlWalkFrameChain(&vecRetAddr[0], vecRetAddr.size(), 0);

	for (ULONG i = 0; i < StackCount; i++)
	{
		RtlZeroMemory(&StackFrame, sizeof(StackFrame));

		if (vecRetAddr[i] == nullptr)
		{
			break;
		}

		StackFrame.returnAddress = vecRetAddr[i];

		vecFrames.push_back(StackFrame);
	}
#elif (_M_X64)
	CONTEXT                       Context;
	KNONVOLATILE_CONTEXT_POINTERS NvContext;
	UNWIND_HISTORY_TABLE          UnwindHistoryTable;
	PRUNTIME_FUNCTION             RuntimeFunction;
	PVOID                         HandlerData;
	ULONG64                       EstablisherFrame;
	ULONG64                       ImageBase;
	STACK_FRAME_INFO              StackFrame;

	RtlCaptureContext(&Context);

	RtlZeroMemory(&UnwindHistoryTable, sizeof(UNWIND_HISTORY_TABLE));

	for (ULONG Frame = 0; Frame <= dwMaxFrame; Frame++)
	{
		RuntimeFunction = RtlLookupFunctionEntry(Context.Rip, &ImageBase, &UnwindHistoryTable);

		RtlZeroMemory(&NvContext, sizeof(KNONVOLATILE_CONTEXT_POINTERS));

		//PVOID pUnwindInfo;
		//RtlCopyMemory(&pUnwindInfo, &(ImageBase + RuntimeFunction->UnwindInfoAddress), sizeof(ImageBase + RuntimeFunction->UnwindInfoAddress));

		if (!RuntimeFunction)
		{
			Context.Rip = (ULONG64)(*(PULONG64)Context.Rsp);
			Context.Rsp += 8;
		}
		else
			RtlVirtualUnwind(UNW_FLAG_NHANDLER, ImageBase, Context.Rip, RuntimeFunction, &Context, &HandlerData, &EstablisherFrame, &NvContext);

		if (!Context.Rip)
		{
			break;
		}

		RtlZeroMemory(&StackFrame, sizeof(StackFrame));

		StackFrame.returnAddress = (PVOID)Context.Rip;
		StackFrame.functionAddress = (PVOID)(ImageBase + RuntimeFunction->BeginAddress);

		vecFrames.push_back(StackFrame);
	}
#endif

	callStack.pFrameList = (STACK_FRAME_INFO*)malloc(vecFrames.size() * sizeof(STACK_FRAME_INFO));
	if (!callStack.pFrameList)
	{
		callStack.dwFrameCount = 0;
		return;
	}

	callStack.dwFrameCount = vecFrames.size();
	for (DWORD dwFrame = 0; dwFrame < vecFrames.size(); dwFrame++)
	{
		RtlCopyMemory(&callStack.pFrameList[dwFrame], &vecFrames[dwFrame], sizeof(STACK_FRAME_INFO));
	}
}

void Tools::GetStack(void)
{
	char cBuff[1024] = { 0 };
	unsigned int   i;
	void* stack[128];
	unsigned short frames;
	SYMBOL_INFO* symbol;
	HANDLE	process;

	process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	frames = CaptureStackBackTrace(0, 128, stack, NULL);
	symbol = (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

	OutputDebugString(L"[dwm_stack_trace]##########################################################################\n");
	for (i = 0; i < frames; i++)
	{
		SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
		sprintf_s(cBuff, 1024, ("[dwm_stack_trace]%i: %s - 0x%llx\n"), frames - i - 1, symbol->Name, symbol->Address);
		OutputDebugStringA(cBuff);
	}
	OutputDebugString(L"[dwm_stack_trace]--------------------------------------------------------------------\n");

	free(symbol);
}

bool Tools::SuspendThreadByNoModulehandle(DWORD pid)
{
	DWORD suspend_status = false;

	(FARPROC&)pZwQueryInformationThread = ::GetProcAddress(GetModuleHandle(L"ntdll"), "ZwQueryInformationThread");

	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32 = { NULL };

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("[GN]:CreateToolhelp32Snapshot() error!\n");
		return false;
	}

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		OutputDebugStringA("[GN]:Thread32First() error!\n");
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return false;
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == pid)
		{
			//打开线程
			HANDLE thread_handle = OpenThread(THREAD_SET_CONTEXT | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
			if (thread_handle)
			{
				//获取线程起始地址
				PVOID thread_start_address = 0;
				pZwQueryInformationThread(thread_handle, (THREADINFOCLASS)0x09, &thread_start_address, sizeof(thread_start_address), NULL);

				if (thread_start_address == 0)
				{
					suspend_status = SuspendThread(thread_handle);
					CloseHandle(thread_handle);
					//if (suspend_status != NULL)
					//	return suspend_status;
					//else
					//	return suspend_status;
				}
			}
			else
				return suspend_status;
		}
	} while (Thread32Next(hThreadSnap, &te32));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	if (suspend_status != -1)
		return true;
	else
		return false;
}

bool Tools::SuspendThreadByModulehandle(DWORD pid, DWORD64 module_handle, DWORD64 module_handle_end_address)
{
	DWORD suspend_status = false;

	(FARPROC&)pZwQueryInformationThread = ::GetProcAddress(GetModuleHandle(L"ntdll"), "ZwQueryInformationThread");

	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32 = { NULL };

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("[GN]:CreateToolhelp32Snapshot() error!\n");
		return false;
	}

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		OutputDebugStringA("[GN]:Thread32First() error!\n");
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return false;
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == pid)
		{
			//打开线程
			HANDLE thread_handle = OpenThread(THREAD_SET_CONTEXT | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
			if (thread_handle)
			{
				//获取线程起始地址
				PVOID thread_start_address = 0;
				pZwQueryInformationThread(thread_handle, (THREADINFOCLASS)0x09, &thread_start_address, sizeof(thread_start_address), NULL);

				if (((DWORD64)thread_start_address >= module_handle) && ((DWORD64)thread_start_address <= module_handle_end_address))
				{
					suspend_status = SuspendThread(thread_handle);
				}

				CloseHandle(thread_handle);
			}
		}
	} while (Thread32Next(hThreadSnap, &te32));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	if (suspend_status != -1)
		return true;
	else
		return false;
}

bool Tools::SuspendThreadByTag(DWORD pid, const char* judgment_tag)
{
	DWORD suspend_status = false;

	(FARPROC&)pZwQueryInformationThread = ::GetProcAddress(GetModuleHandle(L"ntdll"), "ZwQueryInformationThread");

	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32 = { NULL };

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("[GN]:CreateToolhelp32Snapshot() error!\n");
		return false;
	}

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		OutputDebugStringA("[GN]:Thread32First() error!\n");
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return false;
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == pid)
		{
			//打开线程
			HANDLE thread_handle = OpenThread(THREAD_SET_CONTEXT | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
			if (thread_handle)
			{
				//获取线程起始地址
				PVOID thread_start_address = 0;
				pZwQueryInformationThread(thread_handle, (THREADINFOCLASS)0x09, &thread_start_address, sizeof(thread_start_address), NULL);
				//OutputDebugStringA_2Param("[GN]:tid:%d，地址：%p", te32.th32ThreadID, thread_start_address);

				//转换为字符串
				char judgment[16] = { NULL };
				ltoa((long)thread_start_address, judgment, 16);
				if (strlen(judgment) == 8)	strcpy(judgment, &judgment[4]);
				else
					strcpy(judgment, &judgment[3]);
				//OutputDebugStringA_1Param("[GN]:转换后的数据：%s\n", judgment);

				if (_stricmp(judgment, judgment_tag) == 0)
				{
					suspend_status = SuspendThread(thread_handle);
					CloseHandle(thread_handle);
					//if (suspend_status != NULL)
					//	return suspend_status;
					//else
					//	return suspend_status;
				}
			}
			else
				return suspend_status;
		}
	} while (Thread32Next(hThreadSnap, &te32));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	if (suspend_status != -1)
		return true;
	else
		return false;
}

bool Tools::ResumeThreadByTag(DWORD pid, const char* judgment_tag)
{
	(FARPROC&)pZwQueryInformationThread = ::GetProcAddress(GetModuleHandle(L"ntdll"), "ZwQueryInformationThread");

	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32 = { NULL };

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("[GN]:CreateToolhelp32Snapshot() error!\n");
		return false;
	}

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		OutputDebugStringA("[GN]:Thread32First() error!\n");
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return false;
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == pid)
		{
			//打开线程
			HANDLE thread_handle = OpenThread(THREAD_SET_CONTEXT | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
			if (thread_handle)
			{
				//获取线程起始地址
				PVOID thread_start_address = 0;
				pZwQueryInformationThread(thread_handle, (THREADINFOCLASS)0x09, &thread_start_address, sizeof(thread_start_address), NULL);

				//转换为字符串
				char judgment[16] = { NULL };
				ltoa((long)thread_start_address, judgment, 16);
				if (strlen(judgment) == 8)	strcpy(judgment, &judgment[4]);
				else
					strcpy(judgment, &judgment[3]);
				//printf("转换后的数据：%s\n", judgment);

				if (_stricmp(judgment, judgment_tag) == 0)
				{
					DWORD status = ResumeThread(thread_handle);
					CloseHandle(thread_handle);
					if (status == -1)
						return false;
					else
						return true;
				}
			}
			else
				return false;
		}
	} while (Thread32Next(hThreadSnap, &te32));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	return false;
}

bool Tools::TerminateThreadByModulehandle(DWORD pid, DWORD64 module_handle, DWORD64 module_handle_end_address)
{
	bool terminate_status = false;

	(FARPROC&)pZwQueryInformationThread = ::GetProcAddress(GetModuleHandle(L"ntdll"), "ZwQueryInformationThread");

	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32 = { NULL };

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("[GN]:CreateToolhelp32Snapshot() error!\n");
		return false;
	}

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		OutputDebugStringA("[GN]:Thread32First() error!\n");
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return false;
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == pid)
		{
			//打开线程
			HANDLE thread_handle = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
			if (thread_handle)
			{
				//获取线程起始地址
				PVOID thread_start_address = 0;
				pZwQueryInformationThread(thread_handle, (THREADINFOCLASS)0x09, &thread_start_address, sizeof(thread_start_address), NULL);

				if (((DWORD64)thread_start_address >= module_handle) && ((DWORD64)thread_start_address <= module_handle_end_address))
				{
					terminate_status = ::TerminateThread(thread_handle, 0);
				}

				CloseHandle(thread_handle);
			}
		}
	} while (Thread32Next(hThreadSnap, &te32));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	return terminate_status;
}

bool Tools::UnloadDll(HMODULE module_handle, HMODULE module_handle_end_address)
{
	bool status = false;
	if (module_handle != NULL)
	{
		this->TerminateThreadByModulehandle(GetCurrentProcessId(), (DWORD64)module_handle, (DWORD64)module_handle_end_address);
		status = ::FreeLibrary(module_handle);
	}
	else
		OutputDebugStringA("[GN]:Unloaddll模块为0");
	return status;
}


