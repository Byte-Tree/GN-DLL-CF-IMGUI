#include "CheatEngine.h"
#include "../DllMain/DllMain.h"


CheatEngine::CheatEngine(HINSTANCE hinstance)
{
	OutputDebugStringA_1Param("[GN]:%s", __FUNCTION__);

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

	////Set my driver class
	this->CheatEngine::driver = new Driver;
	this->CheatEngine::driver->SetProcessID(this->CheatEngineApi::GetCurrentProcessId());

	//Get game baseaddress
	this->Game::BaseAddressInit();

	//Set Exception Handler
	if (!gn_exception->InstallException(CheatEngine::NewExceptionHandler))
		exit(0);
	int ret = gn_exception->GN_Exception::SetHardWareBreakPoint(L"crossfire.exe", 0x455,
		/*0*/this->Game::GameBase.ACE_BASE64 + GlobalBaseFuncOffset,
		/*0*/Hitchaddress,
		/*0*/RedNameTrackAddress,
		/*0*/SilentTrackAddress);//视角追踪需要更新，不能用

	//////Clear Modulehandle Header
	////ce->CheatEngine::MemoryTools::WriteBytes((DWORD64)hinstance, temp_data, sizeof(temp_data));
	////Hide Dll Memory
	//if (!this->CheatEngine::driver->HideMemoryByVAD((ULONG64)this->self_module_handle, 0/*模块大小*/))
	//{
	//	OutputDebugStringA("[GN]:HideMemoryByVAD() error!");
	//	exit(0);
	//}
	//BYTE temp_data[1024] = { NULL };
	//for (int i = 0; i < 1024; i++)
	//	temp_data[i] = 0x05;
	//ce->CheatEngine::driver->WriteBytesByMDL((PVOID)hinstance, temp_data, sizeof(temp_data));

}

CheatEngine::~CheatEngine()
{

}

bool CheatEngine::ByPassCheck(PCONTEXT context)
{
	DWORD64 caller_address = ce->MemoryTools::ReadLong(context->Rsi);
	////绘制检测
	if ((caller_address > ce->Game::GameBase.Win32U) && (caller_address < ce->Game::GameBase.Win32UEnd))
		return true;
	if ((caller_address > ce->Game::GameBase.Gdi32) && (caller_address < ce->Game::GameBase.Gdi32End))
		return true;
	if ((caller_address > ce->Game::GameBase.D3D9) && (caller_address < ce->Game::GameBase.D3D9End))
		return true;

	//#if _REDBULLBRELEASE || _REDBULLBDEBUG
	//	////功能检测
	//	//DWORD64 callto_address = ce->MemoryTools::ReadLong(context->Rbx + 0x20);
	//	//if (caller_address == ce->CheatEngine::Game::GameBase.Cshell + 0x12C6890)
	//	//	return false;
	//	if ((caller_address > ce->Game::GameBase.Cross) && (caller_address < ce->Game::GameBase.CrossEndAddress))
	//		return true;
	//#endif
	return false;
}

void CheatEngine::InitHook()
{
	__int64* direct3ddevice9_table = (__int64*)*(__int64*)this->CheatEngine::Draw::GetD3D9Device();
	this->CheatEngine::Draw::setviewport_hook = new inline_hook(direct3ddevice9_table[47], (__int64)&Draw::Self_SetViewport, FALSE);
	this->CheatEngine::Draw::setviewport_hook->motify_address();
	this->CheatEngine::Draw::reset_hook = new inline_hook(direct3ddevice9_table[16], (__int64)&Draw::Self_Reset, FALSE);
	this->CheatEngine::Draw::reset_hook->motify_address();

}
