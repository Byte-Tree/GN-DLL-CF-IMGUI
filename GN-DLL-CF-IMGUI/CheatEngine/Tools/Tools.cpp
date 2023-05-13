#include "Tools.h"


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
	OutputDebugStringA_1Param("[GN]:ģ���ַ��%p", modulehandle);
	////Ĩ��peͷ
	//PIMAGE_DOS_HEADER pdosheader = (PIMAGE_DOS_HEADER)modulehandle;									//Ĩȥz��־
	//pdosheader->e_magic = 0;																		//dosͷ�������peͷ
	//PIMAGE_NT_HEADERS pntheader = (PIMAGE_NT_HEADERS)((char*)modulehandle + pdosheader->e_lfanew);	//Ĩȥpe��־
	//pntheader->Signature = 0;
	ZeroMemory((PVOID)modulehandle, 1024);
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

	// ���ȵõ���ǰContext
	RtlCaptureContext(&Context);

	// ��ʼ�� UnwindHistoryTable������ṹ����Ҫ���ڶ�β���RUNTIME_FUNCTIONʱ�ӿ����Ч��
	RtlZeroMemory(&UnwindHistoryTable, sizeof(UNWIND_HISTORY_TABLE));

	// �����ѭ�����ǵõ����ö�ջ
	for (ULONG Frame = 0; ; Frame++)
	{
		// ��PE+ ��.pdata �����ҵ�������Ӧ��RuntimeFunction �ṹ
		// ֻ��Ҷ����û�д˽ṹ
		// �Ȳ����ú�������û���޸�ջָ�룬Ҳû��ʹ�� SEH �ĺ����ͽ�����Ҷ��������
		RuntimeFunction = RtlLookupFunctionEntry(Context.Rip, &ImageBase, &UnwindHistoryTable);
		RtlZeroMemory(&NvContext, sizeof(KNONVOLATILE_CONTEXT_POINTERS));
		if (!RuntimeFunction)
		{
			// ����û�еõ��ṹ�壬���ǵ�ǰ�õ���һ��Ҷ����
			// ��ʱRsp ֱ��ָ��Rip������Ҷ����ֻ����Call ��������ֻ����push eip ������Rsp += 8����
			Context.Rip = (ULONG64)(*(PULONG64)Context.Rsp);
			Context.Rsp += 8;
		}
		else
		{
			// ����չ�����õ����ö�ջ
			// ��һ��������ʾRip ���ں���û�й��˺ʹ�����
			// ������������չ���õ��ϲ���ö�ջ
			RtlVirtualUnwind(UNW_FLAG_NHANDLER, ImageBase, Context.Rip, RuntimeFunction, &Context, &HandlerData, &EstablisherFrame, &NvContext);
		}

		// û�еõ�Rip ���ǵ���ʧ��
		if (!Context.Rip)
		{
			//printf("û�еõ�Rip ���ǵ���ʧ��\n");
			break;
		}

		// չʾ�����Ϣ
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


