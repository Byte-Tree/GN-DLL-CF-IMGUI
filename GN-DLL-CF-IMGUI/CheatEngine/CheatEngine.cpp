#include "CheatEngine.h"
#include "../DllMain/DllMain.h"
#include "../NetVerification/网络验证.h"


CheatEngine::CheatEngine(HINSTANCE hinstance)
{
	OutputDebugStringA_2Param("[GN]:%s-> 模块地址：%p", __FUNCTION__, hinstance);

	////打开控制台
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);

	//Save Modulehandle
	this->self_module_handle = hinstance;
	ce = this;

	//Find game windowhandle and set game windowhandle
	while (this->Draw::GetGameWindowHandle() == NULL)
	{
		this->Draw::SetGameWindowHandle(this->CheatEngineApi::FindWindowA("CrossFire", "穿越火线"));
	}
	
	DWORD game_pid = 0;
	this->CheatEngineApi::GetWindowThreadProcessId(this->CheatEngine::GetGameWindowHandle(), &game_pid);
	this->CheatEngine::SetGameProcessId(game_pid);
	
	//Set my driver class
	this->CheatEngine::driver = new Driver;
	this->CheatEngine::driver->SetProcessID(this->CheatEngineApi::GetCurrentProcessId());
	
	//Get game baseaddress
	this->Game::BaseAddressInit();
	
	//Set Exception Handler
	if (!gn_exception->InstallException("TKD604E537253H51289E138A1BE4588D", CheatEngine::NewExceptionHandler))
		exit(-1);
	int ret = gn_exception->GN_Exception::SetHardWareBreakPoint(L"crossfire.exe", 0x455,
		/*0*/this->Game::GameBase.ACE_BASE64 + GlobalBaseFuncOffset,
		/*0*/Hitchaddress,
		0/*RedNameTrackAddress*/,
		0/*SilentTrackAddress*/);
	this->CheatEngine::SetSoftWareBreakPoint();
	
	//Clear Modulehandle Header
	ZeroMemory(hinstance, 1024);
	
	//////Hide Dll Memory
	////if (!this->CheatEngine::driver->HideMemoryByVAD((ULONG64)this->self_module_handle, 0/*模块大小*/))
	////{
	////	OutputDebugStringA("[GN]:HideMemoryByVAD() error!");
	////	exit(0);
	////}
	//////BYTE temp_data[1024] = { NULL };
	//////for (int i = 0; i < 1024; i++)
	//////	temp_data[i] = 0x05;
	//////ce->CheatEngine::driver->WriteBytesByMDL((PVOID)hinstance, temp_data, sizeof(temp_data));

}

CheatEngine::~CheatEngine()
{

}

bool CheatEngine::ByPassCheck(PCONTEXT context)
{
	DWORD64 caller_address = this->MemoryTools::ReadLong(context->Rsi);
	DWORD64 callto_address = this->MemoryTools::ReadLong(context->Rbx + 0x20);

	//绘制检测
	if ((caller_address > this->Game::GameBase.Win32U) && (caller_address < this->Game::GameBase.Win32UEnd))
		return true;
	if ((caller_address > this->Game::GameBase.Gdi32) && (caller_address < this->Game::GameBase.Gdi32End))
		return true;
	if ((caller_address > this->Game::GameBase.D3D9) && (caller_address < this->Game::GameBase.D3D9End))
		return true;

	//////////功能检测
	////////DWORD64 callto_address = ce->MemoryTools::ReadLong(context->Rbx + 0x20);
	////////if (caller_address == ce->CheatEngine::Game::GameBase.Cshell + 0x12C6890)
	////////	return false;
	////////if ((caller_address > ce->Game::GameBase.Cshell) && (caller_address < ce->Game::GameBase.CshellEndAddress))
	////////{
	////////	////判断是否击杀函数
	////////	//if (caller_address != ce->CheatEngine::Game::GameBase.Cshell + 0x13004E0)
	////////	//	return true;
	////////	return true;
	////////}
	//////if ((caller_address > ce->Game::GameBase.Cross) && (caller_address < ce->Game::GameBase.CrossEndAddress))
	//////	return true;
	//if (caller_address == this->Game::GameBase.Cshell + 0x12F34C0)
	//{
	//	DWORD64 callto_address = this->MemoryTools::ReadLong(context->Rbx + 0x20);
	//	if (callto_address == this->GameBase.ACE_PBC_GAME64 + 0x4DFE0)
	//	{
	//		OutputDebugStringA_1Param("[GN]:地址:%p", callto_address);
	//		return true;
	//	}
	//	if (callto_address == this->GameBase.ACE_PBC_GAME64 + 0x52820)
	//	{
	//		OutputDebugStringA_1Param("[GN]:地址:%p", callto_address);
	//		return true;
	//	}
	//	if (callto_address < 0x700000000000)
	//	{
	//		OutputDebugStringA_1Param("[GN]:地址:%p", callto_address);
	//		return true;
	//	}
	//	return false;
	//}
	//if (caller_address == this->Game::GameBase.Cshell + 0xACA640)
	//	return true;
	
	////处理后无异常 162
	//if (caller_address == this->Game::GameBase.Cshell + 0x12F34C0)
	//{
	//	////if ((callto_address > this->GameBase.ACE_PBC_GAME64) && (callto_address < this->GameBase.ACE_PBC_GAME64End))
	//	////	return false;
	//	////else if ((callto_address > this->GameBase.ACE_GDP64) && (callto_address < this->GameBase.ACE_GDP64End))
	//	////	return false;
	//	//
	//	////第一计数器
	//	//if (callto_address == (this->GameBase.PassReadNameTrack + 0x3F18))
	//	//{
	//	//	DWORD64 count1_address = this->GameBase.PassReadNameTrack + 0x4C7F;
	//	//	if (this->CheatEngine::MemoryTools::ReadByte(count1_address) == 0x80)
	//	//	{
	//	//		DWORD64 p_passaddress = count1_address + this->CheatEngine::MemoryTools::ReadInt(count1_address + 0x02) + 7;
	//	//		OutputDebugStringA_2Param("[GN]:计算出count1地址：%p，值：%d", p_passaddress, this->Game::MemoryTools::ReadInt(p_passaddress));
	//	//		this->Game::MemoryTools::WriteInt(p_passaddress, 0);
	//	//	}
	//	//}
	//	////第二计数器
	//	//else if (callto_address == (this->GameBase.PassReadNameTrack + 0x4BA5))
	//	//{
	//	//	DWORD64 count2_address = this->GameBase.PassReadNameTrack + 0x4000;
	//	//	if (this->CheatEngine::MemoryTools::ReadByte(count2_address) == 0x80)
	//	//	{
	//	//		DWORD64 p_passaddress = count2_address + this->CheatEngine::MemoryTools::ReadInt(count2_address + 0x02) + 7;
	//	//		OutputDebugStringA_2Param("[GN]:计算出count2地址：%p，值：%d", p_passaddress, this->Game::MemoryTools::ReadInt(p_passaddress));
	//	//		this->Game::MemoryTools::WriteInt(p_passaddress, 0);
	//	//	}
	//	//}
	//	//else
	//	//	return false;
	//	return false;
	//}
	//else
	//{
	//	//处理其他钩子
	//	if ((callto_address > this->GameBase.ACE_GDP64) && (callto_address < this->GameBase.ACE_GDP64End))
	//		return false;
	//	else if ((callto_address > this->GameBase.ACE_PBC_GAME64) && (callto_address < this->GameBase.ACE_PBC_GAME64End))
	//		return false;
	//	else
	//		return true;
	//}

	return false;
}

void CheatEngine::InitHook()
{
	__int64* direct3ddevice9_table = (__int64*)*(__int64*)this->CheatEngine::Draw::GetD3D9Device();
	//this->CheatEngine::Draw::setviewport_hook = new inline_hook(direct3ddevice9_table[47], (__int64)&Draw::Self_SetViewport, FALSE);
	//this->CheatEngine::Draw::setviewport_hook->motify_address();
	//this->CheatEngine::Draw::reset_hook = new inline_hook(direct3ddevice9_table[16], (__int64)&Draw::Self_Reset, FALSE);
	//this->CheatEngine::Draw::reset_hook->motify_address();
	//this->CheatEngine::Draw::drawindexedprimitive_hook = new inline_hook(direct3ddevice9_table[82], (__int64)&Draw::Self_DrawIndexedPrimitive, FALSE);
	//this->CheatEngine::Draw::drawindexedprimitive_hook->motify_address();

	//if (this->CheatEngine::Draw::CreateDeviceD3D11(this->GetGameWindowHandle()))
	//{
	//	__int64* SwapChainTable = (__int64*)*(__int64*)this->CheatEngine::Draw::GetD3D11SwapChain();
	//	OutputDebugStringA_1Param("[GN]:GetBuffer地址：%p", SwapChainTable[1]);
	//	this->CheatEngine::Draw::m_OriginalGetBufferPoint = (OriginalGetBufferStruct)SwapChainTable[1];
	//	this->CheatEngine::Draw::getbuffer_hook = new inline_hook(SwapChainTable[1], (__int64)&Draw::Self_GetBuffer, FALSE);
	//	this->CheatEngine::Draw::getbuffer_hook->motify_address();
	//}

	//this->CheatEngine::IsBadReadPtr_hook = new inline_hook((long long)&IsBadReadPtr, (__int64)&CheatEngine::Self_IsBadReadPtr, FALSE);
	//this->CheatEngine::IsBadReadPtr_hook->motify_address();
	//
	//DWORD64 sendto_address = (DWORD64)GetProcAddress(GetModuleHandle(L"ws2_32.dll"), "sendto");
	//OutputDebugStringA_1Param("[GN]:SendTo地址：%p", sendto_address);
	//this->CheatEngine::SendTo_hook = new inline_hook(sendto_address, (__int64)&CheatEngine::Self_SendTo, FALSE);
	//this->CheatEngine::SendTo_hook->motify_address();
	
	DWORD64 send_address = (DWORD64)GetProcAddress(GetModuleHandle(L"ws2_32.dll"), "send");
	//OutputDebugStringA_1Param("[GN]:Send地址：%p", send_address);
	this->CheatEngine::Send_hook = new inline_hook(send_address, (__int64)&CheatEngine::Self_Send, FALSE);
	this->CheatEngine::Send_hook->motify_address();

}

void CheatEngine::SetSoftWareBreakPoint()
{
	gn_exception->software_breakpoint1 = this->CheatEngine::Game::GameBase.Cshell + BulletWithoutBackSeatHookOffset;

}

