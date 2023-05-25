#include "Game.h"
#include "../../DllMain/DllMain.h"
#include "../../sdk/sdk.h"			//ltbasedefs.h 注释了第1167和1168行得以编译通过


Game::Game()
{

}

Game::~Game()
{

}

void Game::BaseAddressInit()
{
	//OutputDebugStringA_1Param("[GN]:%s", __FUNCTION__);
	MODULEINFO ModuleInfo = { 0 };
	this->GameBase.Cshell = (unsigned __int64)ce->CheatEngineApi::GetModuleHandleA("cshell_x64.dll");
	GetModuleInformation(ce->CheatEngineApi::GetCurrentProcess(), ce->CheatEngineApi::GetModuleHandleA("cshell_x64.dll"), &ModuleInfo, sizeof(MODULEINFO));
	this->GameBase.CshellEndAddress = ((__int64)ModuleInfo.lpBaseOfDll + ModuleInfo.SizeOfImage);
	if (this->GameBase.Cshell == 0)
	{
		MessageBox(NULL, L"数据读取出错，即将退出游戏", L"温馨提示", 0);
		exit(0);
	}
	this->GameBase.CrossFireBase = (__int64)ce->CheatEngineApi::GetModuleHandleA("crossfireBase.dll");
	this->GameBase.Cross = (unsigned __int64)GetModuleHandle(L"crossfire.exe");
	GetModuleInformation(ce->CheatEngineApi::GetCurrentProcess(), ce->CheatEngineApi::GetModuleHandleA("crossfire.exe"), &ModuleInfo, sizeof(MODULEINFO));
	this->GameBase.CrossEndAddress = ((__int64)ModuleInfo.lpBaseOfDll + ModuleInfo.SizeOfImage);
	this->GameBase.Win32U = (unsigned __int64)GetModuleHandle(L"win32u.dll");
	GetModuleInformation(ce->CheatEngineApi::GetCurrentProcess(), ce->CheatEngineApi::GetModuleHandleA("win32u.dll"), &ModuleInfo, sizeof(MODULEINFO));
	this->GameBase.Win32UEnd = ((__int64)ModuleInfo.lpBaseOfDll + ModuleInfo.SizeOfImage);
	this->GameBase.Gdi32 = (unsigned __int64)GetModuleHandle(L"gdi32.dll");
	GetModuleInformation(ce->CheatEngineApi::GetCurrentProcess(), ce->CheatEngineApi::GetModuleHandleA("gdi32.dll"), &ModuleInfo, sizeof(MODULEINFO));
	this->GameBase.Gdi32End = ((__int64)ModuleInfo.lpBaseOfDll + ModuleInfo.SizeOfImage);
	this->GameBase.D3D9 = (unsigned __int64)GetModuleHandle(L"d3d9.dll");
	GetModuleInformation(ce->CheatEngineApi::GetCurrentProcess(), ce->CheatEngineApi::GetModuleHandleA("d3d9.dll"), &ModuleInfo, sizeof(MODULEINFO));
	this->GameBase.D3D9End = ((__int64)ModuleInfo.lpBaseOfDll + ModuleInfo.SizeOfImage);
	this->GameBase.dxgi = (unsigned __int64)GetModuleHandle(L"dxgi.dll");
	GetModuleInformation(ce->CheatEngineApi::GetCurrentProcess(), ce->CheatEngineApi::GetModuleHandleA("dxgi.dll"), &ModuleInfo, sizeof(MODULEINFO));
	this->GameBase.dxgiEnd = ((__int64)ModuleInfo.lpBaseOfDll + ModuleInfo.SizeOfImage);
	this->GameBase.CrossFireBase = (unsigned __int64)GetModuleHandle(L"crossfireBase.dll");
	this->GameBase.TerSafe = (unsigned __int64)GetModuleHandle(L"tersafe.dll");
	this->GameBase.ACE_PBC_GAME64 = (unsigned __int64)GetModuleHandle(L"ACE-PBC-Game64.dll");
	GetModuleInformation(ce->CheatEngineApi::GetCurrentProcess(), ce->CheatEngineApi::GetModuleHandleA("ACE-PBC-Game64.dll"), &ModuleInfo, sizeof(MODULEINFO));
	this->GameBase.ACE_PBC_GAME64End = ((__int64)ModuleInfo.lpBaseOfDll + ModuleInfo.SizeOfImage);
	this->GameBase.ACE_BASE64 = (unsigned __int64)GetModuleHandle(L"ACE-Base64.dll");
	this->GameBase.ACE_ATS64 = (unsigned __int64)GetModuleHandle(L"ACE-ATS64.dll");
	this->GameBase.ACE_DFS64 = (unsigned __int64)GetModuleHandle(L"ACE-DFS64.dll");
	this->GameBase.ACE_CSI64 = (unsigned __int64)GetModuleHandle(L"ACE-CSI64.dll");
	this->GameBase.ACE_Tips64 = (unsigned __int64)GetModuleHandle(L"ACE-Tips64.dll");
	this->GameBase.ACE_DRV64 = (unsigned __int64)GetModuleHandle(L"ACE-Drv64.dll");
	this->GameBase.ACE_GDP64 = (unsigned __int64)GetModuleHandle(L"ACE-GDP64.dll");
	GetModuleInformation(ce->CheatEngineApi::GetCurrentProcess(), ce->CheatEngineApi::GetModuleHandleA("ACE-GDP64.dll"), &ModuleInfo, sizeof(MODULEINFO));
	this->GameBase.ACE_GDP64End = ((__int64)ModuleInfo.lpBaseOfDll + ModuleInfo.SizeOfImage);
	this->GameBase.ACE_GDPServer64 = (unsigned __int64)GetModuleHandle(L"ACE-GDPServer64.dll");
	this->GameBase.SGuard64 = (unsigned __int64)GetModuleHandle(L"SGuardAgent64.dll");
	this->GameBase.MatrixBase = Mtrix;
	this->GameBase.ArraySize = ArraySizeOffset;
	this->GameBase.BarrierBaseAddress = BarrierOffset;
	this->GameBase.PlayerArray = this->GameBase.Cshell + PlayerArrayBaseAddress;										//玩家数组
	this->GameBase.ModeAddress = this->GameBase.Cshell + ModelOffset;													//判断模式
	this->GameBase.ModeAddress2 = this->GameBase.Cshell + ModelOffset2;													//模式基址2
	this->GameBase.CharacterBase = this->MemoryTools::ReadLong(this->GameBase.PlayerArray) + CharacterBaseOffset;
	this->GameBase.SelfAddress = this->MemoryTools::ReadLong(this->GameBase.PlayerArray) + SelfAddressOffset;
	this->GameBase.CharacterData = this->MemoryTools::ReadLong(this->GameBase.PlayerArray) + CharacterDataOffset;		//人物数据 敌人地址 OBJECT
	this->GameBase.IsInGame = this->GameBase.CharacterBase + IsInGameOffset;
	this->GameBase.PersonalPerspective = this->GameBase.CharacterBase - PersonalPerspectiveOffset;						//人称视角
	this->GameBase.UnlimitedPainting = this->GameBase.Cshell + UnlimitedPaintingBaseAddress;							//无限喷漆
	this->GameBase.SpaceContinuousJump = this->GameBase.Cshell + SpaceContinuousJumpOffset;								//空格连跳
	this->GameBase.SelfPosition = this->GameBase.Cshell + SelfPositionOffset;											//自己位置
	//this->GameBase.ContractingLabel = this->GameBase.Cshell + ContractingLabelOffset;									//发包标签
	//this->GameBase.CLTClient = this->GameBase.Cross + CLTClientOffset;													//CLTClient
	//g_LTClient = (CLTClient*)this->Game::GameBase.CLTClient;
	//g_CommonLT = g_LTClient->Common();
	this->GameBase.ThousandTimesTheRateOfFire[0] = this->GameBase.Cshell + NewThousandTimesTheRateOfFireBaseAddress;
	this->GameBase.ThousandTimesTheRateOfFire[1] = this->GameBase.Cshell + OldThousandTimesTheRateOfFireBaseAddress;
	this->GameBase.ActionBaseAddress[0] = this->GameBase.Cshell + CharacterUpperBodyActionBaseAddress;
	this->GameBase.ActionBaseAddress[1] = this->GameBase.Cshell + CharacterLowerBodyActionBaseAddress;
	this->GameBase.NewThrowALittle = this->GameBase.Cshell + NewThrowALittleBaseAddress;
	this->GameBase.OldThrowALittle = this->GameBase.Cshell + OldThrowALittleBaseAddres;
	this->GameBase.RangeTrackBase = this->GameBase.Cshell + RangeTrackBaseAddress;
	this->GameBase.InfiniteBackpack = this->GameBase.Cshell + InfiniteBackpackBaseAddress;
	this->GameBase.InfiniteShield = this->GameBase.Cshell + InfiniteShieldBaseAddress;
	this->GameBase.IgnoreSmokeAddress = this->GameBase.Cshell + IgnoreSmokeBaseAddress;
	this->GameBase.DisconnectTeleportAddress[0] = this->GameBase.Cshell + NewDisconnectTeleportBaseAddress;
	this->GameBase.DisconnectTeleportAddress[1] = this->GameBase.Cshell + OldDisconnectTeleportBaseAddress;
	this->GameBase.RadarAddress[0] = this->GameBase.Cshell + RadarOffsetOne;				//雷达透视1
	this->GameBase.RadarAddress[1] = this->GameBase.Cshell + RadarOffsetTwo;				//雷达透视2
	this->GameBase.RadarAddress[2] = this->GameBase.Cshell + RadarOffsetThree;				//雷达透视3
	ZeroMemory(this->GameBase.WeaponNameValue, sizeof(this->GameBase.WeaponNameValue));		//刀距名字清零操作

	////自杀函数
	//OriginalKillSelfPoint = (OriginalKillSelfStruct)(this->GameBase.Cshell + KillSelfFuncOffset);
	////范围增伤函数
	//GameRangeCallPoint = (GameRangeCallStruct)(this->GameBase.Cshell + RangeTrackFuncOffset);
	//
	////空格连跳Hook
	//this->GameBase.HookFunc.SpaceJumpHookAddress = this->GameBase.Cshell + SpaceJumpHookOffset;
	//this->GameBase.HookFunc.SpaceJumpHookRetAddress = this->GameBase.Cshell + SpaceJumpHookRetOffset;
	////静步加速Hook
	//this->GameBase.HookFunc.StaticAccelerationHookAddress = this->GameBase.Cshell + StaticAccelerationHookOffset;
	//this->GameBase.HookFunc.StaticAccelerationHookRetAddress = this->GameBase.Cshell + StaticAccelerationHookRetOffset;
	////下蹲加速Hook
	//this->GameBase.HookFunc.SquatAccelerationHookAddress = this->GameBase.Cshell + SquatAccelerationHookOffset;
	//this->GameBase.HookFunc.SquatAccelerationHookRetAddress = this->GameBase.Cshell + SquatAccelerationHookRetOffset;
	////静态无后Hook
	//this->GameBase.HookFunc.BulletWithoutBackSeatHookAddress = this->GameBase.Cshell + BulletWithoutBackSeatHookOffset;
	//this->GameBase.HookFunc.BulletWithoutBackSeatHookRetAddress = this->GameBase.Cshell + BulletWithoutBackSeatHookRetOffset;
	////左键千刀Hook
	//this->GameBase.HookFunc.LeftKnifeHookAddress = this->GameBase.Cshell + LeftKnifeHookOffset;
	//this->GameBase.HookFunc.LeftKnifeHookRetAddress = this->GameBase.Cshell + LeftKnifeHookRetOffset;
	////右键千刀Hook
	//this->GameBase.HookFunc.RightKnifeHookAddress = this->GameBase.Cshell + RightKnifeHookOffset;
	//this->GameBase.HookFunc.RightKnifeHookRetAddress = this->GameBase.Cshell + RightKnifeHookRetOffset;
	//this->GameBase.HookFunc.RightKnifeCallAddress = this->GameBase.Cshell + RightKnifeCallOffset;
	////零秒换弹新图Hook
	//this->GameBase.HookFunc.ZeroBulletChange_NewMapHookAddress = this->GameBase.Cshell + ZeroBulletChange_NewMapHookOffset;
	//this->GameBase.HookFunc.ZeroBulletChange_NewMapHookRetAddress = this->GameBase.Cshell + ZeroBulletChange_NewMapHookRetOffset;
	////零秒换弹旧图Hook
	//this->GameBase.HookFunc.ZeroBulletChange_OldMapHookAddress = this->GameBase.Cshell + ZeroBulletChange_OldMapHookOffset;
	//this->GameBase.HookFunc.ZeroBulletChange_OldMapHookRetAddress = this->GameBase.Cshell + ZeroBulletChange_OldMapHookRetOffset;
	////人物穿墙Hook
	//this->GameBase.HookFunc.ThroughTheWallHookAddress = this->GameBase.Cshell + ThroughTheWallHookOffset;
	//this->GameBase.HookFunc.ThroughTheWallHookRetAddress = this->GameBase.Cshell + ThroughTheWallHookRetOffset;
	//
	////弹道追踪基址
	//this->GameBase.BallisticBaseSite[0] = this->GameBase.Cshell + BallisticBaseSiteOne;
	//this->GameBase.BallisticBaseSite[1] = this->GameBase.Cshell + BallisticBaseSiteTwo;
	//this->GameBase.BallisticBaseSite[2] = this->GameBase.Cshell + BallisticBaseSiteThree;
	//this->GameBase.BallisticBaseSite[3] = this->GameBase.Cshell + BallisticBaseSiteFour;
	//this->GameBase.BallisticBaseSite[4] = this->GameBase.Cshell + PursuitBallisticBaseSiteOne;
	//this->GameBase.BallisticBaseSite[5] = this->GameBase.Cshell + PursuitBallisticBaseSiteTwo;
	//this->GameBase.BallisticBaseSite[6] = this->GameBase.Cshell + PersonalBallisticBaseSiteOne;
	//this->GameBase.BallisticBaseSite[7] = this->GameBase.Cshell + PersonalBallisticBaseSiteTwo;
	//
	////静默追踪基址
	//this->GameBase.SilentTrackBaseAddress[0] = this->GameBase.Cshell + SilentTrackNewMapAddress;	//新图静默追踪
	//this->GameBase.SilentTrackBaseAddress[1] = this->GameBase.Cshell + SilentTrackOldMapAddress;	//旧图静默追踪

	//处理ACE
	this->Game::ByPassACE();
//#if _REDBULLBRELEASE || _REDBULLBDEBUG
//	//处理错误代码
//	this->Game::PassErrorCode();
//#endif
}

void Game::ByPassACE()
{
	//this->Game::ACE_Base();
	//this->Game::ACE_ATS();
	//this->Game::ACE_CSI();
	this->Game::ACE_PBC();

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Game::PassThread, NULL, NULL, NULL);
}

void Game::ACE_Base()
{

}

void Game::ACE_ATS()
{
	//while (true)
	//{
	//	if (this->Game::GameBase.ACE_ATS64)
	//	{
	//		if (this->MemoryTools::ReadLong(this->Game::GameBase.ACE_ATS64 + ATSGetCurrentProcessOffset) == (__int64)&GetCurrentProcess)
	//		{
	//			this->Game::driver->WriteLong(this->Game::GameBase.ACE_ATS64 + ATSGetCurrentProcessOffset, (__int64)&Self_GetCurrentProcess);
	//			if (this->MemoryTools::ReadLong(this->Game::GameBase.ACE_ATS64 + ATSGetCurrentProcessOffset) == (__int64)&Self_GetCurrentProcess)
	//				break;
	//		}
	//		else
	//		{
	//			MessageBoxA(NULL, "检测到ATS需要更新，请联系管理员更新后再使用！", "警告", MB_OK);
	//			exit(-1);
	//		}
	//	}
	//	else
	//		this->Game::GameBase.ACE_ATS64 = (__int64)GetModuleHandleA("ACE-ATS64.dll");
	//}

	while (true)
	{
		if (this->Game::GameBase.ACE_ATS64)
		{
			//crc
			//if (this->MemoryTools::ReadLong(this->Game::GameBase.ACE_ATS64 + ATSGetModuleInformationOffset) == (__int64)GetProcAddress(GetModuleHandleA("PSAPI.dll"), "GetModuleInformation"))
			//{
			//	this->Game::driver->WriteLong(this->Game::GameBase.ACE_ATS64 + ATSGetModuleInformationOffset, (__int64)&Self_GetModuleInformation);
			//	this->Game::driver->WriteLong(this->Game::GameBase.ACE_ATS64 + ATSGetModuleHandleAOffset, (__int64)&Self_GetModuleHandleA);
			//	break;
			//}
			//else
			//{
			//	MessageBoxA(NULL, "检测到ATS需要更新，请联系管理员更新后再使用！", "警告", MB_OK);
			//	exit(-1);
			//}
		}
		else
			this->Game::GameBase.ACE_ATS64 = (__int64)GetModuleHandleA("ace-ats64.dll");
	}
}

void Game::ACE_PBC()
{
	////Pass Kill Enemy
	//DWORD64 kill_enemy_function_address = this->Game::GameBase.Cshell + PassKillEnemyOffset;
	//DWORD64 original_kill_enemy_function_address = this->Game::GameBase.Cshell + OriginalKillEnemyFunctionOffset;

	////DWORD64 rax = ReadLong(kill_enemy_function_address);		//mov rax,[cshell_x64.dll+2A873C8]
	////DWORD64 rcx = ReadLong(rax + 0x260);						// - mov rcx,[rax+00000260]
	////rcx = ReadLong(rcx + 0x588);								//mov rcx,[rcx+00000588]
	////rax = ReadLong(rcx);										//mov rax,[rcx]
	////DWORD64 caller_address = rax + 0x48;						//call qword ptr [rax+48]
	//DWORD64 caller_address = this->MemoryTools::ReadLong(this->MemoryTools::ReadLong(this->MemoryTools::ReadLong(this->MemoryTools::ReadLong(kill_enemy_function_address) + 0x260) + 0x588) + 0x0) + 0x48;
	//OutputDebugStringA_2Param("[GN]:caller_address：%p,value:%p\n", caller_address, this->MemoryTools::ReadLong(caller_address));
	//while (true)
	//{
	//	this->MemoryTools::WriteLong(caller_address, original_kill_enemy_function_address);
	//	if (this->MemoryTools::ReadLong(caller_address) == original_kill_enemy_function_address)
	//		break;
	//	Sleep(5);
	//}

}

void Game::ACE_CSI()
{
	//while (true)
	//{
	//	if (this->Game::GameBase.ACE_CSI64)
	//	{
	//		if (this->MemoryTools::ReadLong(this->Game::GameBase.ACE_CSI64 + CSIGetClassNameWOffset) == (__int64)GetProcAddress(GetModuleHandleA("USER32.dll"), "GetClassNameW"))
	//		{
	//			//this->Game::driver->WriteLong(this->Game::GameBase.ACE_CSI64 + CSIEnumWindowsOffset, (__int64)&Self_EnumWindows);
	//			//this->Game::driver->WriteLong(this->Game::GameBase.ACE_CSI64 + CSIEnumChildWindowsOffset, (__int64)&Self_EnumChildWindows);
	//			this->Game::driver->WriteLong(this->Game::GameBase.ACE_CSI64 + CSIGetClassNameWOffset, (__int64)&HookAPI::GetClassNameW);
	//			break;
	//		}
	//		else
	//		{
	//			MessageBoxA(NULL, "检测到CSI需要更新，请联系管理员更新后再使用！", "警告", MB_OK);
	//			exit(-1);
	//		}
	//	}
	//	else
	//		this->Game::GameBase.ACE_CSI64 = (__int64)GetModuleHandleA("ACE-CSI64.dll");
	//}
}

void Game::PassThread()
{
	//while (true)
	//{
	//	////动态
	//	//if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "237d"))
	//	//	OutputDebugStringA("[GN]:SuspendThreadByTag() 237d error\n");
	//	//if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "2681"))
	//	//	OutputDebugStringA("[GN]:SuspendThreadByTag() 2681 error\n");
	//	//if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "512a"))
	//	//	OutputDebugStringA("[GN]:SuspendThreadByTag() 512a error\n");
	//	//if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "38e7"))
	//	//	OutputDebugStringA("[GN]:SuspendThreadByTag() 38e7 error\n");
	//	//if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "914c"))
	//	//	OutputDebugStringA("[GN]:SuspendThreadByTag() 914c error\n");
	//	//if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "a4ef"))
	//	//	OutputDebugStringA("[GN]:SuspendThreadByTag() a4ef error\n");
	//	//if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "5832"))
	//	//	OutputDebugStringA("[GN]:SuspendThreadByTag() 5832 error\n");
	//	//if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "5c27"))
	//	//	OutputDebugStringA("[GN]:SuspendThreadByTag() 5c27 error\n");
	//	////ACE-Base64.dll线程中倒数第三个线程
	//	if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "b00c"))
	//		OutputDebugStringA("[GN]:SuspendThreadByTag() 9e00 error\n");
	//	//PBC-Game
	//	if (!ce->CheatEngine::Tools::SuspendThreadByTag(GetCurrentProcessId(), "a560"))
	//		OutputDebugStringA("[GN]:SuspendThreadByTag() a560 error\n");
	//	//PBC-Game断链后的线程
	//	ce->CheatEngine::Tools::SuspendThreadByNoModulehandle(GetCurrentProcessId());
	//	
	//	//Pass Kill Enemy
	//	DWORD64 kill_enemy_function_address = ce->Game::GameBase.Cshell + PassKillEnemyOffset;
	//	DWORD64 original_kill_enemy_function_address = ce->Game::GameBase.Cshell + OriginalKillEnemyFunctionOffset;
	//	DWORD64 caller_address = ce->MemoryTools::ReadLong(ce->MemoryTools::ReadLong(ce->MemoryTools::ReadLong(ce->MemoryTools::ReadLong(kill_enemy_function_address) + 0x260) + 0x588) + 0x0) + 0x48;
	//	if (ce->MemoryTools::ReadLong(caller_address) != original_kill_enemy_function_address)
	//		//ce->MemoryTools::WriteLong(caller_address, original_kill_enemy_function_address);
	//		ce->CheatEngine::driver->WriteLongByMDL((PVOID)caller_address, original_kill_enemy_function_address);
	//
	//	Sleep(2000);
	//}
}

void Game::PassErrorCode()
{
	this->MemoryTools::WriteVecBytes(this->Game::GameBase.Cshell + Code1_2One, { 0xF3,0x0F,0x59,0x05,0x54,0x15,0x9D,0x01 });
	this->MemoryTools::WriteVecBytes(this->Game::GameBase.Cshell + Code193One, { 0x90,0x90,0x90,0x90,0x90,0x90 });
	this->MemoryTools::WriteVecBytes(this->Game::GameBase.Cshell + Code193Two, { 0x90,0x90,0x90,0x90,0x90,0x90 });
	this->MemoryTools::WriteVecBytes(this->Game::GameBase.Cshell + Code193Three, { 0x90,0x90,0x90,0x90,0x90,0x90 });
	this->MemoryTools::WriteVecBytes(this->Game::GameBase.Cshell + Code143One, { 0x90,0x90,0x90,0x90,0x90,0x90 });
	this->MemoryTools::WriteVecBytes(this->Game::GameBase.Cshell + Code143Two, { 0x90,0x90,0x90,0x90,0x90,0x90 });
}

BOOL Game::WorldToScreen2(m_D3DCoordinate view_, D3DXVECTOR2* RetCoordinates)
{
	D3DXVECTOR3 Pos, Bos;
	BYTE view[64] = { NULL }, projection[64] = { NULL }, viewPort[64] = { NULL };
	BYTE World[64] = { 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63 };
	Pos.x = view_.x;
	Pos.y = view_.z;
	Pos.z = view_.y;
	memcpy(&viewPort, reinterpret_cast<void*>(this->GameBase.MatrixBase), 64);
	memcpy(&view, reinterpret_cast<void*>((this->GameBase.MatrixBase - 128)), 64);
	memcpy(&projection, reinterpret_cast<void*>((this->GameBase.MatrixBase - 64)), 64);
	D3DXVec3Project(&Bos, &Pos, (D3DVIEWPORT9*)&viewPort, (D3DXMATRIX*)&projection, (D3DXMATRIX*)&view, (D3DXMATRIX*)&World);
	if (Bos.z > 1)
		return false;
	RetCoordinates->x = Bos.x;
	RetCoordinates->y = Bos.y;
	return true;
}

BOOL Game::WorldToScreen(m_D3DCoordinate EnemyCoordinates, m_D3DCoordinate* RetCoordinates)
{
	BYTE view[64] = { NULL }, projection[64] = { NULL }, viewPort[64] = { NULL };
	BYTE World[64] = { 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63 };
	D3DXVECTOR3	vScreen, Pos2, PlayerPos;
	__int64 ss = this->GameBase.MatrixBase;
	PlayerPos.x = EnemyCoordinates.x;
	PlayerPos.y = EnemyCoordinates.z;
	PlayerPos.z = EnemyCoordinates.y;
	memcpy(&viewPort, (const void*)(this->GameBase.MatrixBase), 64);
	memcpy(&view, (const void*)(this->GameBase.MatrixBase - 128), 64);
	memcpy(&projection, (const void*)(this->GameBase.MatrixBase - 64), 64);
	D3DXVec3Project(&vScreen, &PlayerPos, (D3DVIEWPORT9*)&viewPort, (D3DXMATRIX*)&projection, (D3DXMATRIX*)&view, (D3DXMATRIX*)&World);
	if (vScreen.z > 1)
		return FALSE;
	RetCoordinates->x = vScreen.x;
	RetCoordinates->y = vScreen.y;
	return TRUE;
}

//是否在游戏
bool Game::IsInGaming()
{
	if (this->MemoryTools::ReadInt(this->GameBase.IsInGame) != (int)1)
		return FALSE;
	else
		return TRUE;
}

//取自己位置
int Game::GetSelfPosition()
{
	return this->MemoryTools::ReadLong((this->MemoryTools::ReadLong(this->GameBase.PlayerArray) + SelfAddressOffset)) + 1;
	//return this->MemoryTools::ReadLong((this->MemoryTools::ReadLong(this->GameBase.PlayerArray) + SelfAddressOffset));
}

//取人物数量
int Game::GetCharacterNumber()
{
	//int pattern_address = this->MemoryTools::ReadInt(this->GameBase.JudgmentMode);
	//if (pattern_address == 1 || pattern_address == 2 || pattern_address == 46 || pattern_address == 40 || pattern_address == 35 || pattern_address == 22 || pattern_address == 3 || pattern_address == 7 || pattern_address == 6 || pattern_address == 9 || pattern_address == 10 || pattern_address == 16 || pattern_address == 20 || pattern_address == 48 || pattern_address == 25 || pattern_address == 54)
	//	return 8;//普通赛
	//if (pattern_address == 15)//战场
	//	return 5;//战场
	//if (pattern_address == 5 || pattern_address == 12 || pattern_address == 14 || pattern_address == 17 || pattern_address == 19 || pattern_address == 47)//' 生化丨小丑丨暗影（感染）
	//	return 30;//' 生化丨小丑丨暗影（感染）
	//if (pattern_address == 41 || pattern_address == 47)
	//	return 14;
	//if (pattern_address == 4 || pattern_address == 36 || pattern_address == 41)//个人
	//	return 16;
	//if (pattern_address == 11 || pattern_address == 24 || pattern_address == 31)
	//	return 4;//挑战
	//if (pattern_address == 32 || pattern_address == 26 || pattern_address == 28)
	//	return 8;//人机
	//return 8;

	__int64 mode_address = this->MemoryTools::ReadInt(this->GameBase.ModeAddress);
	if (mode_address == 41 || mode_address == 47 || mode_address == 4 || mode_address == 36 || mode_address == 49)//个人
		return 16;//个人
	if (mode_address == 14 || mode_address == 12 || mode_address == 5 || mode_address == 17 || mode_address == 19 || mode_address == 47)//生化丨小丑丨暗影（感染
		return 30;//个人
	return 8;
}

//取自己坐标数据
void Game::GetSelfData(m_D3DCoordinate* RetData)
{
	__int64 PrimaryOffset = 0;
	PrimaryOffset = this->MemoryTools::ReadLong((this->MemoryTools::ReadLong(this->GameBase.PlayerArray) + 72));
	if (PrimaryOffset != 0)
	{
		RetData->x = this->MemoryTools::ReadFloat((PrimaryOffset + 160));
		RetData->z = this->MemoryTools::ReadFloat((PrimaryOffset + 164));
		RetData->y = this->MemoryTools::ReadFloat((PrimaryOffset + 168));
	}
}

//取敌人坐标
bool Game::GetEnemyCoordinate(__int64 id, m_D3DCoordinate* b)
{
	__int64 CoordinateAddress = 0;//Coordinates地址
	CoordinateAddress = this->Game::MemoryTools::ReadLong(((id - 1) * GameBase.ArraySize + GameBase.CharacterData));
	if (CoordinateAddress > 0)
	{
		b->x = this->Game::MemoryTools::ReadFloat(CoordinateAddress + PlayerXCoordinateOffset);
		b->y = this->Game::MemoryTools::ReadFloat(CoordinateAddress + PlayerYCoordinateOffset);
		b->z = this->Game::MemoryTools::ReadFloat(CoordinateAddress + PlayerZCoordinateOffset);
		return TRUE;
	}
	return FALSE;
}

//取生化状态
bool Game::GetBiochemicalModel(int SelfPosition, int PlayerPosition)
{
	__int64 SelfCamp, PlayerCamp;//本人阵营 玩家阵营
	SelfCamp = this->MemoryTools::ReadLong(this->MemoryTools::ReadLong(this->GameBase.PlayerArray) + BiochemicalOffset + (SelfPosition - 1) * this->GameBase.ArraySize);
	PlayerCamp = this->MemoryTools::ReadLong(this->MemoryTools::ReadLong(this->GameBase.PlayerArray) + BiochemicalOffset + (PlayerPosition - 1) * this->GameBase.ArraySize);
	if (PlayerCamp > 0)
		return this->MemoryTools::ReadByte(SelfCamp + BiochemicalCampOffset) != this->MemoryTools::ReadByte(PlayerCamp + BiochemicalCampOffset);
	return FALSE;
}

//取自己生存
__int64 Game::GetSelfLive()
{
	return this->MemoryTools::ReadLong((this->GameBase.CharacterBase - SelfLiveOffset));
}

//取敌人昵称
char* Game::GetEnemyName(__int64 id)
{
	return this->MemoryTools::ReadChar(((this->GameBase.CharacterData + 10) + ((id - 1) * this->GameBase.ArraySize)));
}

//取敌人生存
bool Game::GetEnemyLive(__int64 id)
{
	__int64 Plaply_INFOx = 0;	//敌人基址
	Plaply_INFOx = this->MemoryTools::ReadLong((this->GameBase.CharacterData + 24) + (id - 1) * this->GameBase.ArraySize);
	if (Plaply_INFOx == NULL)
		return FALSE;
	if (this->MemoryTools::ReadByte(Plaply_INFOx + EnemyLiveOffset) == (BYTE)0)
		return TRUE;
	return FALSE;
}

//取玩家QQ号
int Game::GetUserQQNumber(int id)
{
	return this->MemoryTools::ReadInt(((this->GameBase.CharacterData + UserQQNumberOffset) + ((id - 1) * this->GameBase.ArraySize)));
}

//取人物血量
__int64 Game::GetCharacterBlood(__int64 id)
{
	return this->MemoryTools::ReadLong(((this->GameBase.CharacterData + 68) + ((id - 1) * this->GameBase.ArraySize)));
}

//是否雷包
bool Game::IsC4(int id)
{
	if (this->MemoryTools::ReadByte(((this->GameBase.CharacterData + 40) + ((id - 1) * this->GameBase.ArraySize))) == 0x1)
		return TRUE;
	else
		return FALSE;
}

//取当前武器ID
int Game::GetCurrentWeaponID()
{
	return this->MemoryTools::ReadInt(this->MemoryTools::ReadLong(this->GameBase.CharacterBase) + CurrentWeaponIDOffset);
}

//判断地图
LPCSTR Game::JudgeMentMap()
{
	//map_baseaddress
	DWORD64 map_baseaddress = this->Game::MemoryTools::ReadLong(this->Game::MemoryTools::ReadLong(this->Game::MemoryTools::ReadLong(this->Game::MemoryTools::ReadLong(this->Game::GameBase.ModeAddress2) + 0x10) + 0x108) + 2);
	if (map_baseaddress != 0)
	{
		if (map_baseaddress == 3619486395)
			return "当前地图->机甲迷城";
		if (map_baseaddress == 3872518331)
			return "当前地图->火焰山";
		if (map_baseaddress == 2830870468)
			return "当前地图->魔花研究所";
		if (map_baseaddress == 2832527049)
			return "当前地图->深渊冰龙之巢";
		if (map_baseaddress == 3586124240)
			return "当前地图->虚空裂缝";
		if (map_baseaddress == 3418939070)
			return "当前地图->巨人城";
		if (map_baseaddress == 4038850993)
			return "当前地图->冰火遗迹";
		if (map_baseaddress == 3737043664)
			return "当前地图->新巨人城废墟";
		if (map_baseaddress == 4056542934)
			return "当前地图->诸神竞技场";
		if (map_baseaddress == 3082987972)
			return "当前地图->末路狂飙";
		if (map_baseaddress == 3418939070)
			return "当前地图->巨人城";
		if (map_baseaddress == 2868303808)
			return "当前地图->雷霆塔";
		if (map_baseaddress == 4039367099)
			return "当前地图->毁灭都市";
		if (map_baseaddress == 3636720073)
			return "当前地图->神秘营地";
		if (map_baseaddress == 3586697668)
			return "当前地图->末日剧场";
		if (map_baseaddress == 4223066061)
			return "当前地图->瓦尔基里";
		if (map_baseaddress == 2933305035)
			return "当前地图->水之城";
		if (map_baseaddress == 4240701630)
			return "当前地图->绝命之谷";
		if (map_baseaddress == 3083787982)
			return "当前地图->无畏战舰";
		if (map_baseaddress == 3922446022)
			return "当前地图->破碎之都";
		if (map_baseaddress == 3803836362)
			return "当前地图->曙光战舰";
		if (map_baseaddress == 3790790334)
			return "当前地图->巨蜥峡谷";
		if (map_baseaddress == 3066156234)
			return "当前地图->试炼岛：逆袭";
	}
	else
		return "当前地图->未知地图";
}

//追踪范围
void Game::TrackingRange(m_D3DCoordinate Data, int Target, int gamewidth, int gameheight)
{
	int DrawWidth, DrawHeight, Distance;//画出宽度 画出高度 距离
	ScreenCoordinates AimingAngle;//瞄准角度
	DrawWidth = Data.x;
	DrawHeight = Data.y;
	AimingAngle.X = gamewidth / 2 - this->track_range + this->track_range / 5.5;
	AimingAngle.Y = gameheight / 2 - this->track_range + this->track_range / 5.5;
	AimingAngle.H = this->track_range * 2 - this->track_range / 3;
	AimingAngle.W = this->track_range * 2 - this->track_range / 3;
	Distance = sqrt((DrawWidth - gamewidth / 2) * (DrawWidth - gamewidth / 2) + (DrawHeight - gameheight / 2) * (DrawHeight - gameheight / 2));
	if (DrawWidth > AimingAngle.X && DrawHeight < AimingAngle.X + AimingAngle.W)
	{
		if (DrawHeight > AimingAngle.Y && DrawHeight < AimingAngle.Y + AimingAngle.H)
		{
			if (this->m_locking_pawn == 0)
			{
				this->m_locking_pawn = Target;
				this->m_lastdistance = Distance;
			}
			else if (Distance < this->m_lastdistance)
				this->m_locking_pawn = Target;
		}
	}
}

//计算敌人距离
int Game::CalulateEnemyDistance(m_D3DCoordinate self_coordinate, m_D3DCoordinate enemy_coordinate)
{
	m_D3DCoordinate disparity = { NULL };
	disparity.x = self_coordinate.x * -1 - enemy_coordinate.x * -1;
	disparity.y = self_coordinate.y - enemy_coordinate.y;
	disparity.z = self_coordinate.z - enemy_coordinate.z;
	return sqrt(disparity.x * disparity.x + disparity.y * disparity.y + disparity.z * disparity.z) / 100;
}

//计算距离
void Game::CalculateDistance(m_D3DCoordinate ScreenCoordinates, __int64 EnemyID, __int64 BoneID, int gamecent_x, int gamecent_y)
{
	int CurrentDistance;
	if (this->m_recentdistance == 0)
	{
		this->m_recentdistance = pow(pow(ScreenCoordinates.x - gamecent_x, 2) + pow(ScreenCoordinates.y - gamecent_y, 2), 0.5);
		this->m_locking_pawn = EnemyID;
		this->m_locking_bone_id = BoneID;
		return;
	}
	CurrentDistance = pow(pow(ScreenCoordinates.x - gamecent_x, 2) + pow(ScreenCoordinates.y - gamecent_y, 2), 0.5);
	if (CurrentDistance < this->m_recentdistance)
	{
		this->m_recentdistance = CurrentDistance;
		this->m_locking_pawn = EnemyID;
		this->m_locking_bone_id = BoneID;
	}
}

//判断障碍
BOOL Game::IsVisible(m_D3DCoordinate SelfPos, m_D3DCoordinate TargetPos)
{
	memset(&this->Query, 0, sizeof(_IntersectQuery));
	memset(&this->Info, 0, sizeof(_IntersectInfo));
	this->Query.m_FromX = SelfPos.x;
	this->Query.m_FromY = SelfPos.z;
	this->Query.m_FromZ = SelfPos.y;
	this->Query.m_ToX = TargetPos.x;
	this->Query.m_ToY = TargetPos.z;
	this->Query.m_ToZ = TargetPos.y;
	return !((bool(__fastcall*)(IntersectQuery&, IntersectInfo*))this->GameBase.BarrierBaseAddress)(this->Query, &this->Info);
}

//鼠标移动
void Game::MouseAimbot(m_D3DCoordinate Output, int gamecent_x, int gamecent_y, int gamewidth, int gameheight)
{
	float TargetX = 0, TargetY = 0, Frevise;
	Frevise = (float)0.3;
	if (Output.x != 0)
	{
		if (Output.x > gamecent_x)
		{
			TargetX = -(gamecent_x - Output.x);
			TargetX = TargetX / this->Game::aim_speed;
			if (TargetX + gamecent_x + 1 > gamewidth)
				TargetX = 0;
			if (TargetX < 1 && TargetX > Frevise)
				TargetX = 1;
		}
		if (Output.x < gamecent_x)
		{
			TargetX = Output.x - gamecent_x;
			TargetX = TargetX / this->Game::aim_speed;
			if (TargetX + gamecent_x - 1 < 0)
				TargetX = 0;
			if (TargetX > -1 && TargetX < Frevise)
				TargetX = -1;
		}
	}
	if (Output.y != 0)
	{
		if (Output.y > gamecent_y)
		{
			TargetY = -(gamecent_y - Output.y);
			TargetY = TargetY / this->Game::aim_speed;
			if (TargetY + gamecent_y + 1 > gameheight)
				TargetY = 0;
			if (TargetY<1 && TargetY>Frevise)
				TargetY = 1;
		}
		if (Output.y < gamecent_y)
		{
			TargetY = Output.y - gamecent_y;
			TargetY = TargetY / this->Game::aim_speed;
			if (TargetY + gamecent_y - 1 < 0)
				TargetY = 0;
			if (TargetY > -1 && TargetY < Frevise)
				TargetY = -1;
		}
	}
	mouse_event(1, TargetX, TargetY, 3.2, 3.2);
}

//自瞄算法
m_D3DCoordinate Game::AutomaticAimingAlgorithm(m_D3DCoordinate EnemyCoordinates)
{
	BYTE World[64] = { 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63 };
	BYTE view[64], projection[64], viewPort[64];
	D3DXVECTOR3 vScreen, Pos2, PlayerPos, abcd;
	double Distance = 0, Multiple_x = 0;
	PlayerPos.x = EnemyCoordinates.x;
	PlayerPos.y = EnemyCoordinates.z + 18.8;
	PlayerPos.z = EnemyCoordinates.y;

	memcpy(&viewPort, (const void*)(this->GameBase.MatrixBase), 64);
	memcpy(&view, (const void*)(this->GameBase.MatrixBase - 128), 64);
	memcpy(&projection, (const void*)(this->GameBase.MatrixBase - 64), 64);

	D3DXVec3Project(&vScreen, &PlayerPos, (D3DVIEWPORT9*)&viewPort, (D3DXMATRIX*)&projection, (D3DXMATRIX*)&view, (D3DXMATRIX*)&World);
	EnemyCoordinates.x = vScreen.x;
	EnemyCoordinates.y = vScreen.y;
	EnemyCoordinates.z = vScreen.z;
	return EnemyCoordinates;
}

//追踪算法
m_D3DCoordinate Game::VectorToRotation(m_D3DCoordinate SelfCoordinates, m_D3DCoordinate b)
{
	float m_pi = (float)3.1415926535;
	double X_gap, Y_gap, Z_gap, X_angle, Y_angle, AdjacentEdge, OppositeSide;
	m_D3DCoordinate LockingCoordinates, EnemyCoordinates;
	EnemyCoordinates = b;
	X_gap = SelfCoordinates.x * -1 - EnemyCoordinates.x * -1;
	Y_gap = SelfCoordinates.y - EnemyCoordinates.y;
	Z_gap = SelfCoordinates.z - EnemyCoordinates.z - 24;
	if (X_gap == 0 && Y_gap < 0)
		X_angle = 0;
	else if (X_gap == 0 && Y_gap > 0)
		X_angle = 180;
	else if (X_gap > 0 && Y_gap == 90)
		X_angle = 90;
	else if (X_gap < 0 && Y_gap == 0)
		X_angle = 270;
	else if (X_gap > 0 && Y_gap < 0)
	{
		OppositeSide = Y_gap;
		AdjacentEdge = X_gap;
		X_angle = atan(OppositeSide / AdjacentEdge) * 180 / m_pi + 90;
	}
	else if (X_gap < 0 && Y_gap < 0)
	{
		OppositeSide = X_gap;
		AdjacentEdge = Y_gap;
		X_angle = 360 - atan(OppositeSide / AdjacentEdge) * 180 / m_pi;
	}
	else if (X_gap > 0 && Y_gap > 0)
	{
		OppositeSide = Y_gap;
		AdjacentEdge = X_gap;
		X_angle = atan(OppositeSide / AdjacentEdge) * 180 / m_pi + 90;
	}
	else if (X_gap < 0 && Y_gap>0)
	{
		OppositeSide = X_gap;
		AdjacentEdge = Y_gap;
		X_angle = 180 - atan(OppositeSide / AdjacentEdge) * 180 / m_pi;
	}
	else
		X_angle = 0;
	Y_angle = atan(Z_gap / sqrt(Y_gap * Y_gap + X_gap * X_gap)) * 180 / m_pi;
	LockingCoordinates.x = X_angle * m_pi / 180;
	LockingCoordinates.y = Y_angle * m_pi / 180;
	LockingCoordinates.z = 0;
	return LockingCoordinates;
}

//随机位置
int Game::RandomPosition()
{
	srand(time(0));
	int ret = rand() % 13;
	if (ret == 6)
		return ret = ret + (rand() % 10);
	else if (ret == 11)
		return ret = ret + (rand() % 4);
	else if (ret == 7)
		return ret = ret + (rand() % 2);
	else
		return ret;
	////2
	//srand(time(0));
	//int ret = rand() % 13;
	//if (ret == 6)
	//	ret = this->Game::RandomPosition();
	//else
	//	return ret;
	////1
	//for (int i = 0; i < 5; i++)
	//{
	//	return rand() % 13;
	//}
	//return 0;
}

//修改弹道
void Game::ModifyTrajectory()
{
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[0], { 0x80,0x00,0x00,0x00 });//128 普通模式Y    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[1], { 0x84,0x00,0x00,0x00 });//132 普通模式X    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[2], { 0x80,0x00,0x00,0x00 });//128 特殊模式Y    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[3], { 0x84,0x00,0x00,0x00 });//132 特殊模式X    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[4], { 0x80,0x00,0x00,0x00 });//128 特殊模式Y    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[5], { 0x84,0x00,0x00,0x00 });//132 特殊模式X    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[6], { 0x80,0x00,0x00,0x00 });//128 特殊模式Y	
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[7], { 0x84,0x00,0x00,0x00 });//132 特殊模式X     
}

//还原弹道
void Game::ReductionTrajectory()
{
	////Drv.WriteInt(this->GameBase.BallisticBaseSite[0], 2120);//普通模式Y     
	////Drv.WriteInt(this->GameBase.BallisticBaseSite[1], 2124);//普通模式X     
	////Drv.WriteInt(this->GameBase.BallisticBaseSite[2], 2120);//特殊模式Y     
	////Drv.WriteInt(this->GameBase.BallisticBaseSite[3], 2124);//特殊模式X     
	////Drv.WriteInt(this->GameBase.BallisticBaseSite[4], 2120);//特殊模式Y     
	////Drv.WriteInt(this->GameBase.BallisticBaseSite[5], 2124);//特殊模式X     
	////Drv.WriteInt(this->GameBase.BallisticBaseSite[6], 2120);//特殊模式Y     
	////Drv.WriteInt(this->GameBase.BallisticBaseSite[7], 2124);//特殊模式X      

	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[0], { 0x48,0x08,0x00,0x00 });//2120 普通模式Y    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[1], { 0x4C,0x08,0x00,0x00 });//2124 普通模式X    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[2], { 0x48,0x08,0x00,0x00 });//2120 特殊模式Y    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[3], { 0x4C,0x08,0x00,0x00 });//2124 特殊模式X    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[4], { 0x48,0x08,0x00,0x00 });//2120 特殊模式Y    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[5], { 0x4C,0x08,0x00,0x00 });//2124 特殊模式X    
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[6], { 0x48,0x08,0x00,0x00 });//2120 特殊模式Y	 
	//Drv.WriteVecByte(this->GameBase.BallisticBaseSite[7], { 0x4C,0x08,0x00,0x00 });//2124 特殊模式X     

	////WriteVecBytes(this->GameBase.BallisticBaseSite[0], { 0x00,0x00,0x08,0x48 });//2120 普通模式Y    
	////WriteVecBytes(this->GameBase.BallisticBaseSite[1], { 0x00,0x00,0x08,0x4C });//2124 普通模式X    
	////WriteVecBytes(this->GameBase.BallisticBaseSite[2], { 0x00,0x00,0x08,0x48 });//2120 特殊模式Y    
	////WriteVecBytes(this->GameBase.BallisticBaseSite[3], { 0x00,0x00,0x08,0x4C });//2124 特殊模式X    
	////WriteVecBytes(this->GameBase.BallisticBaseSite[4], { 0x00,0x00,0x08,0x48 });//2120 特殊模式Y    
	////WriteVecBytes(this->GameBase.BallisticBaseSite[5], { 0x00,0x00,0x08,0x4C });//2124 特殊模式X    
	////WriteVecBytes(this->GameBase.BallisticBaseSite[6], { 0x00,0x00,0x08,0x48 });//2120 特殊模式Y	
	////WriteVecBytes(this->GameBase.BallisticBaseSite[7], { 0x00,0x00,0x08,0x4C });//2124 特殊模式X     
}

//追踪部署
void Game::TrackDeployment(m_D3DCoordinate AimCoordinates)
{
	m_D3DCoordinate MuzzleAmplitude;//枪口幅度
	__int64 BaseAddress = this->MemoryTools::ReadLong(this->GameBase.CharacterBase);
	//WriteFloat2((BaseAddress + 0x80), AimCoordinates.y);	//128
	//WriteFloat2((BaseAddress + 0x84), AimCoordinates.x);	//132

	MuzzleAmplitude.y = this->MemoryTools::ReadFloat(BaseAddress + MouseYOffset);
	MuzzleAmplitude.x = this->MemoryTools::ReadFloat(BaseAddress + MouseXOffset);
	//Drv.WriteFloat((PVOID)(BaseAddress + 0x80), AimCoordinates.y - MuzzleAmplitude.y);	//128
	//Drv.WriteFloat((PVOID)(BaseAddress + 0x84), AimCoordinates.x - MuzzleAmplitude.x);	//132
	////WriteFloat2((BaseAddress + 0x80), AimCoordinates.y - MuzzleAmplitude.y);	//128
	////WriteFloat2((BaseAddress + 0x84), AimCoordinates.x - MuzzleAmplitude.x);	//132
}

//取骨骼坐标
bool Game::GetBoneCoordinate(__int64 ID, m_D3DCoordinate* Deposit, __int64 Position)
{
	__int64 EnemyBaseAddress, Coordinate;
	EnemyBaseAddress = this->MemoryTools::ReadLong((((ID - 1) * this->GameBase.ArraySize) + this->GameBase.CharacterData));
	if (EnemyBaseAddress > 0)
	{
		//ReadLong
		Coordinate = this->MemoryTools::ReadLong((EnemyBaseAddress + BoneOffset));
		if (Coordinate != 0)
		{
			Coordinate = (Coordinate + (0x0C + (0x40 * Position)));
			Deposit->x = this->MemoryTools::ReadFloat(Coordinate);
			Deposit->z = this->MemoryTools::ReadFloat((Coordinate + 0x10));
			Deposit->y = this->MemoryTools::ReadFloat((Coordinate + 0x20));
			return TRUE;
		}
	}
	else
		return FALSE;
}

//绘制骨骼
void Game::DrawBone(int Addr, int color, int LineSize)
{
	m_D3DCoordinate Head = { NULL }, Neck = { NULL }, LeftArm = { NULL }, LeftElbow = { NULL }, LeftHand = { NULL }, RightArm = { NULL },
		RightElbow = { NULL }, RightHand = { NULL }, Pelvis = { NULL }, LeftLeg = { NULL }, LeftKnee = { NULL }, LeftFoot = { NULL },
		RightLeg = { NULL }, RightKnee = { NULL }, RightFoot = { NULL };
	m_D3DCoordinate HeadO = { NULL }, NeckO = { NULL }, LeftArmO = { NULL }, LeftElbowO = { NULL }, LeftHandO = { NULL }, RightArmO = { NULL },
		RightElbowO = { NULL }, RightHandO = { NULL }, PelvisO = { NULL }, LeftLegO = { NULL }, LeftKneeO = { NULL }, LeftFootO = { NULL },
		RightLegO = { NULL }, RightKneeO = { NULL }, RightFootO = { NULL };
	if (this->GetBoneCoordinate(Addr, &Pelvis, 3))
	{
		this->GetBoneCoordinate(Addr, &Neck, 5);	Neck.z = Neck.z + 2;
		this->GetBoneCoordinate(Addr, &Head, 6);	Head.z = Head.z + 10;
		this->GetBoneCoordinate(Addr, &LeftArm, 8);	this->GetBoneCoordinate(Addr, &LeftElbow, 9);	this->GetBoneCoordinate(Addr, &LeftHand, 10);
		this->GetBoneCoordinate(Addr, &RightArm, 15); this->GetBoneCoordinate(Addr, &RightElbow, 16); this->GetBoneCoordinate(Addr, &RightHand, 17);
		this->GetBoneCoordinate(Addr, &LeftLeg, 21); this->GetBoneCoordinate(Addr, &LeftKnee, 22);	this->GetBoneCoordinate(Addr, &LeftFoot, 23);
		this->GetBoneCoordinate(Addr, &RightLeg, 25); this->GetBoneCoordinate(Addr, &RightKnee, 26);	this->GetBoneCoordinate(Addr, &RightFoot, 27);
	}
	if (this->WorldToScreen(Head, &HeadO))
	{
		if (this->WorldToScreen(Neck, &NeckO))
		{
			if (this->WorldToScreen(Pelvis, &PelvisO))
			{
				if (this->WorldToScreen(LeftArm, &LeftArmO))
				{
					if (this->WorldToScreen(LeftElbow, &LeftElbowO))
					{
						if (this->WorldToScreen(LeftHand, &LeftHandO))
						{
							if (this->WorldToScreen(RightArm, &RightArmO))
							{
								if (this->WorldToScreen(RightElbow, &RightElbowO))
								{
									if (this->WorldToScreen(RightHand, &RightHandO))
									{
										if (this->WorldToScreen(LeftLeg, &LeftLegO))
										{
											if (this->WorldToScreen(LeftKnee, &LeftKneeO))
											{
												if (this->WorldToScreen(LeftFoot, &LeftFootO))
												{
													if (this->WorldToScreen(RightLeg, &RightLegO))
													{
														if (this->WorldToScreen(RightKnee, &RightKneeO))
														{
															if (this->WorldToScreen(RightFoot, &RightFootO))
															{
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(PelvisO.x, PelvisO.y), ImVec2(HeadO.x, HeadO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(NeckO.x, NeckO.y), ImVec2(LeftArmO.x, LeftArmO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftArmO.x, LeftArmO.y), ImVec2(LeftElbowO.x, LeftElbowO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftElbowO.x, LeftElbowO.y), ImVec2(LeftHandO.x, LeftHandO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(NeckO.x, NeckO.y), ImVec2(RightArmO.x, RightArmO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightArmO.x, RightArmO.y), ImVec2(RightElbowO.x, RightElbowO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightElbowO.x, RightElbowO.y), ImVec2(RightHandO.x, RightHandO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(PelvisO.x, PelvisO.y), ImVec2(LeftLegO.x, LeftLegO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftLegO.x, LeftLegO.y), ImVec2(LeftKneeO.x, LeftKneeO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftKneeO.x, LeftKneeO.y), ImVec2(LeftFootO.x, LeftFootO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(PelvisO.x, PelvisO.y), ImVec2(RightLegO.x, RightLegO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightLegO.x, RightLegO.y), ImVec2(RightKneeO.x, RightKneeO.y), color, LineSize);
																ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightKneeO.x, RightKneeO.y), ImVec2(RightFootO.x, RightFootO.y), color, LineSize);
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

//静默追踪功能
void Game::WriteSilenceTrack(m_D3DCoordinate aim_coordinates)
{
	this->m_silence_track_coordinates.x = aim_coordinates.x;
	this->m_silence_track_coordinates.y = aim_coordinates.y;
}

//无限喷漆开关
void Game::UnlimitedPaintingSwitch()
{
	this->MemoryTools::WriteInt(GameBase.UnlimitedPainting, 256);
}

//修改刀距
bool Game::ChangeKnifeDistance(float KnifeWieldingDistance, float TapSpeed, float HitSpeed, float TapRange, float HitRange)
{
	__int64 Offset;//Offset
	__int64 WeaponType;//武器类型
	__int64 WeaponNumber[2];//武器序号
	this->GameBase.KnifeDistanceBase = this->MemoryTools::ReadLong(this->GameBase.CharacterBase);
	WeaponType = this->MemoryTools::ReadLong(this->GameBase.KnifeDistanceBase + CurrentWeaponOffset);
	//WeaponNumber[0] = this->MemoryTools::ReadLong(this->GameBase.Cshell + WeaponNumberBaseAddressOne);					//武器序列
	//WeaponNumber[1] = this->MemoryTools::ReadLong(WeaponNumber[0] + WeaponNumberBaseAddressTwo);
	WeaponNumber[1] = this->GetCurrentWeaponID();																		//武器序列
	this->GameBase.WeaponNumber = WeaponNumber[1] * WeaponNumberArray;													//武器序号2
	//printf("this->GameBase.WeaponNumber:%p\n", this->GameBase.WeaponNumber);
	this->GameBase.KnifeDistanceBase = this->MemoryTools::ReadLong(this->GameBase.Cshell + KnifeDistanceBaseAddress);	//刀距基址|武器基址
	if (WeaponType == 2)
	{
		if (!this->GameBase.KnifeIsChanged)
		{
			Offset = this->MemoryTools::ReadLong(this->GameBase.KnifeDistanceBase + this->GameBase.WeaponNumber);
			this->GameBase.KnifeDistancePassACEAddress = Offset;
			//printf("Offset:%p\n", Offset);
			sprintf_s(this->GameBase.WeaponNameValue, "%s", this->MemoryTools::ReadChar(Offset + WeaponNameOffset));		//武器名字
			if (!this->FirstCallKnifeDistance)
			{
				if (strcmp(this->GameBase.LastWeaponNameValue, this->GameBase.WeaponNameValue) != 0)					//判断当前武器不是上次修改武器时返回失败
				{
					printf("修改失败！请切换到上一个近战武器点击还原后再修改.\n");
					return FALSE;
				}
			}
			this->GameBase.TapDistanceValue[0] = this->MemoryTools::ReadFloat(Offset + TapWieldingDistanceOffsetOne);	//轻击挥刀距离一
			this->GameBase.TapDistanceValue[1] = this->MemoryTools::ReadFloat(Offset + TapWieldingDistanceOffsetTwo);	//轻击挥刀距离二
			this->GameBase.TapSpeedValue[0] = this->MemoryTools::ReadFloat(Offset + TapSpeedOffsetOne);					//轻击速度一
			this->GameBase.TapSpeedValue[1] = this->MemoryTools::ReadFloat(Offset + TapSpeedOffsetTwo);					//轻击速度二
			this->GameBase.TapRangeValue[0] = this->MemoryTools::ReadFloat(Offset + TapRangeOffsetOne);					//轻击范围一
			this->GameBase.TapRangeValue[1] = this->MemoryTools::ReadFloat(Offset + TapRangeOffsetTwo);					//轻击范围二
			this->GameBase.HitDistanceValue = this->MemoryTools::ReadFloat(Offset + HitDistanceOffset);					//重击挥刀距离
			this->GameBase.HitSpeedValue = this->MemoryTools::ReadFloat(Offset + HitSpeedOffset);						//重击速度
			this->GameBase.HitRangeValue = this->MemoryTools::ReadFloat(Offset + HitRangeOffset);						//重击范围
			this->GameBase.KnifeMarkDistanceValue = this->MemoryTools::ReadFloat(Offset + KnifeMarkDistanceOffset);		//刀痕距离
			sprintf_s(this->GameBase.LastWeaponNameValue, "%s", this->MemoryTools::ReadChar(Offset + WeaponNameOffset));	//上一个武器名字
			printf("当前近战武器名称：%s\n", this->GameBase.WeaponNameValue);

			this->MemoryTools::WriteFloat(Offset + TapWieldingDistanceOffsetOne, KnifeWieldingDistance);					//轻击挥刀距离一
			this->MemoryTools::WriteFloat(Offset + TapWieldingDistanceOffsetTwo, KnifeWieldingDistance);					//轻击挥刀距离二
			this->MemoryTools::WriteFloat(Offset + HitDistanceOffset, KnifeWieldingDistance);							//重击挥刀距离
			this->MemoryTools::WriteFloat(Offset + KnifeMarkDistanceOffset, KnifeWieldingDistance);						//刀痕距离
			this->MemoryTools::WriteFloat(Offset + TapSpeedOffsetOne, TapSpeed);											//轻击速度一
			this->MemoryTools::WriteFloat(Offset + TapSpeedOffsetTwo, TapSpeed);											//轻击速度二
			this->MemoryTools::WriteFloat(Offset + TapRangeOffsetOne, TapRange);											//轻击范围一
			this->MemoryTools::WriteFloat(Offset + TapRangeOffsetTwo, TapRange);											//轻击范围二
			this->MemoryTools::WriteFloat(Offset + HitSpeedOffset, HitSpeed);											//重击速度
			this->MemoryTools::WriteFloat(Offset + HitRangeOffset, HitRange);											//重击范围
			this->GameBase.KnifeIsChanged = TRUE;																		//确认修改刀距
			FirstCallKnifeDistance = FALSE;
			return TRUE;
		}
		else
		{
			printf("请先还原上一把武器再修改.\n");
			return FALSE;
		}
	}
	else
		return FALSE;
}

//还原刀距
bool Game::ReductionKnifeDistance()
{
	__int64 Offset;//Offset
	__int64 WeaponType;//武器类型
	__int64 WeaponNumber[2];//武器序号
	char CurrentWeaponTemp[MAX_PATH] = { NULL };//当前武器缓存
	this->GameBase.KnifeDistanceBase = this->MemoryTools::ReadLong(this->GameBase.CharacterBase);
	WeaponType = this->MemoryTools::ReadLong(this->GameBase.KnifeDistanceBase + CurrentWeaponOffset);
	//WeaponNumber[0] = this->MemoryTools::ReadLong(this->GameBase.Cshell + WeaponNumberBaseAddressOne);
	//WeaponNumber[1] = this->MemoryTools::ReadLong(WeaponNumber[0] + WeaponNumberBaseAddressTwo);
	WeaponNumber[1] = this->GetCurrentWeaponID();			//武器序列
	this->GameBase.WeaponNumber = WeaponNumber[1] * WeaponNumberArray;//武器序号2
	this->GameBase.KnifeDistanceBase = this->MemoryTools::ReadLong(this->GameBase.Cshell + KnifeDistanceBaseAddress);
	if (WeaponType == 2)
	{
		if (this->GameBase.KnifeIsChanged)
		{
			Offset = this->MemoryTools::ReadLong(this->GameBase.KnifeDistanceBase + this->GameBase.WeaponNumber);
			sprintf_s(CurrentWeaponTemp, "%s", this->MemoryTools::ReadChar(Offset + 0xE));		//获取当前武器
			if (strcmp(CurrentWeaponTemp, this->GameBase.WeaponNameValue) != 0)		//判断当前武器不是上次修改武器时返回失败
			{
				printf("还原失败！请切换到上一个近战武器再点击还原.\n");
				return FALSE;
			}
			this->MemoryTools::WriteFloat(Offset + TapWieldingDistanceOffsetOne, this->GameBase.TapDistanceValue[0]);	//轻击挥刀距离一
			this->MemoryTools::WriteFloat(Offset + TapWieldingDistanceOffsetTwo, this->GameBase.TapDistanceValue[1]);	//轻击挥刀距离二
			this->MemoryTools::WriteFloat(Offset + HitDistanceOffset, this->GameBase.HitDistanceValue);					//重击挥刀距离
			this->MemoryTools::WriteFloat(Offset + TapSpeedOffsetOne, this->GameBase.TapSpeedValue[0]);					//轻击速度一
			this->MemoryTools::WriteFloat(Offset + TapSpeedOffsetTwo, this->GameBase.TapSpeedValue[1]);					//轻击速度二
			this->MemoryTools::WriteFloat(Offset + TapRangeOffsetOne, this->GameBase.TapRangeValue[0]);					//轻击范围一
			this->MemoryTools::WriteFloat(Offset + TapRangeOffsetTwo, this->GameBase.TapRangeValue[1]);					//轻击范围二
			this->MemoryTools::WriteFloat(Offset + KnifeMarkDistanceOffset, this->GameBase.KnifeMarkDistanceValue);		//刀痕距离
			this->MemoryTools::WriteFloat(Offset + HitSpeedOffset, this->GameBase.HitSpeedValue);						//重击速度
			this->MemoryTools::WriteFloat(Offset + HitRangeOffset, this->GameBase.HitRangeValue);						//重击范围
			this->GameBase.KnifeIsChanged = FALSE;													//确认还原刀距
			FirstCallKnifeDistance = TRUE;
			return TRUE;
		}
		else
		{
			printf("未修改刀距，请先修改数据后再还原.\n");
			return FALSE;
		}
	}
	return FALSE;
}

//瞬移追敌功能
void Game::TeleportToTrackTheEnemyFunc(DWORD id)
{
	m_D3DCoordinate TempCoordinate = { NULL };
	if (GetEnemyCoordinate(id, &TempCoordinate))
	{
		__int64 Offset = this->Game::MemoryTools::ReadLong(this->Game::MemoryTools::ReadLong(GameBase.CharacterBase) + MapOffset);
		this->Game::MemoryTools::WriteFloat(Offset + PlayerXCoordinateOffset, TempCoordinate.x);
		this->Game::MemoryTools::WriteFloat(Offset + PlayerYCoordinateOffset, TempCoordinate.y);
		this->Game::MemoryTools::WriteFloat(Offset + PlayerZCoordinateOffset, TempCoordinate.z + 130.0f);
	}
}

//空格连跳功能
void Game::SpaceContinuousJumpFunc()
{
	if (this->Game::spacecontinuousjump)
		this->Game::MemoryTools::WriteInt(this->Game::GameBase.SpaceContinuousJump, 0);
}

//红名追踪功能
void Game::HookRedNameTrackFunc(__int64 pointer, __int64 judgement_pointer)
{
	m_D3DCoordinate self_coordinates = { NULL }, aiming_coordinate = { NULL };
	this->Game::GetSelfData(&self_coordinates);
	if (this->Game::m_locking_pawn != 0)
	{
		if (this->Game::GetEnemyLive(this->Game::m_locking_pawn))
		{
			if ((this->Game::aim_hotkey == AIM_HOTKEY_MOUSE_LEFT && GetAsyncKeyState(VK_LBUTTON) != 0) || (this->Game::aim_hotkey == AIM_HOTKEY_MOUSE_RIGHT && GetAsyncKeyState(VK_RBUTTON) != 0) || (this->Game::aim_hotkey == AIM_HOTKEY_KEYBOARD_ALT && GetAsyncKeyState(18) != 0))
			{
				if (this->Game::redname_track)
				{
					if (this->MemoryTools::ReadInt(judgement_pointer + 0x14) != 7 && this->MemoryTools::ReadInt(pointer + 0x24) == 7)
					{
						if (this->Game::judgementbarrier)
						{
							if (this->Game::GetBoneCoordinate(this->Game::m_locking_pawn, &aiming_coordinate, (bool)this->Game::aim_position ? 6 : this->Game::RandomPosition()))
							{
								if (this->Game::IsVisible(self_coordinates, aiming_coordinate))//障碍判断
								{
									this->MemoryTools::WriteFloat(pointer + 0x0C, aiming_coordinate.x);
									this->MemoryTools::WriteFloat(pointer + 0x10, aiming_coordinate.z + 18.9);
									this->MemoryTools::WriteFloat(pointer + 0x14, aiming_coordinate.y);
								}
							}
						}
						else
						{
							if (this->Game::GetBoneCoordinate(this->Game::m_locking_pawn, &aiming_coordinate, (bool)this->Game::aim_position ? 6 : this->Game::RandomPosition()))
							{
								this->MemoryTools::WriteFloat(pointer + 0x0C, aiming_coordinate.x);
								this->MemoryTools::WriteFloat(pointer + 0x10, aiming_coordinate.z + 18.9);
								this->MemoryTools::WriteFloat(pointer + 0x14, aiming_coordinate.y);
							}
						}
					}
				}
			}
			else
				this->Game::m_locking_pawn = 0;
		}
		else
			this->Game::m_locking_pawn = 0;
	}
}

//二叉树
bool Game::TraversingBinaryTree(__int64 object, std::vector<__int64>* pvector)
{
	if (!object)
		return false;
	DWORD64 tree_head = this->Game::MemoryTools::ReadLong(object);
	DWORD64 tree_left = this->Game::MemoryTools::ReadLong(tree_head);
	pvector->clear();
	while (tree_left != tree_head)
	{
		pvector->push_back(tree_left);
		DWORD64 tree_right = this->Game::MemoryTools::ReadLong(tree_left + 16);
		if (tree_right == 0)
			return false;
		if (this->Game::MemoryTools::ReadByte(tree_right + 25) != 0)
		{
			tree_right = this->Game::MemoryTools::ReadLong(tree_left + 8);
			if (this->Game::MemoryTools::ReadByte(tree_right + 25) == 0)
			{
				do
				{
					if (this->Game::MemoryTools::ReadLong(tree_right + 16) != tree_left)
						break;
					tree_left = tree_right;
					tree_right = this->Game::MemoryTools::ReadLong(tree_right + 8);
					if (tree_right == 0)
						return false;
				} while (this->Game::MemoryTools::ReadByte(tree_right + 25) == 0);
			}
			tree_left = tree_right;
		}
		else
		{
			DWORD64 old_tree = this->Game::MemoryTools::ReadLong(tree_right);
			tree_left = tree_right;
			if (this->Game::MemoryTools::ReadByte(old_tree + 25) == 0)
			{
				do
				{
					tree_right = this->Game::MemoryTools::ReadLong(old_tree);
					tree_left = old_tree;
					old_tree = tree_right;
					if (tree_right == 0)
						return false;
				} while (this->Game::MemoryTools::ReadByte(tree_right + 25) == 0);
			}
		}
	}
	return pvector->size() != 0;
}

//二叉树遍历怪物
void Game::TraverseMonsterArray()
{
	std::vector<__int64> monster_list, temp_monster_list;
	monster_list.clear();
	__int64 treeObj = this->Game::MemoryTools::ReadLong(this->Game::MemoryTools::ReadLong(this->Game::GameBase.PlayerArray) + 0x3C818) + 16;
	if (this->Game::TraversingBinaryTree(treeObj, &temp_monster_list))
	{
		for (int i = 0; i < (int)temp_monster_list.size(); i++)
		{
			__int64 monster_pointer = this->Game::MemoryTools::ReadLong(temp_monster_list[i] + 40);
			if (monster_pointer && this->Game::MemoryTools::ReadLong(monster_pointer + 208) != 0 && this->Game::MemoryTools::ReadByte(monster_pointer + 564) == 0)
			{
				monster_list.push_back(monster_pointer);
				this->Game::SendSecKillPacket(&monster_list);
			}
		}
	}
}

//发送秒杀怪物封包
void Game::SendSecKillPacket(std::vector<__int64>* pmonster_list)
{
	std::vector<__int64> monster_list = *pmonster_list;
	if (pmonster_list->size() > 0)
	{
		DWORD self_position = this->Game::MemoryTools::ReadInt(this->Game::MemoryTools::ReadLong(this->Game::GameBase.PlayerArray) + 0x289);
		DWORD monster_point = this->Game::MemoryTools::ReadInt(this->Game::MemoryTools::ReadLong(monster_list[monster_list.size() - 1] + 0xD0) + 0x154);
		//怪物血量
		DWORD64 monster_health = this->Game::MemoryTools::ReadInt(this->Game::MemoryTools::ReadLong(this->Game::MemoryTools::ReadLong(monster_point + 0x160) + 8) + 0x17E4C);
		//游戏时间
		int game_time = (int)this->Game::MemoryTools::ReadFloat(this->Game::MemoryTools::ReadLong(this->Game::GameBase.CharacterBase) + 0x4A4);
		LTVector pos_self = { (float)3343077376,(float)3343077376,(float)3343077376 };
		LTVector pos_enemy = { (float)3454954280,(float)3454954280,(float)3454954280 };
		//if (self_position == 8)
		//	self_position = 0; 
		ILTMessage_Write* msg;
		//破坏者秒杀
		if (this->Game::destroyer_seckill)
		{
			if (g_CommonLT->CreateMessage(msg) == LT_OK)
			{
				int id = 0;
				msg->AddRef();
				int label = msg->AddCout(this->Game::GameBase.ContractingLabel);
				msg->WriteBits(0x25, 16);
				msg->WriteBits(0xB27AD5F7, 5);
				msg->WriteBits(label, 8);												//Write48Cout
				msg->WriteBits(0x76C, 32);
				msg->WriteBits(0, 1);
				msg->WriteBits(0, 32);
				msg->WriteBits(0, 32);
				msg->WriteBits(0, 1);
				msg->WriteBits(msg->Size() * (label + id), 0x8);						//Write48Imul
				g_LTClient->SendToServer(msg->Read(), 1);
				msg->Release();
			}
			if (g_CommonLT->CreateMessage(msg) == LT_OK)
			{
				int weapon_id = this->Game::GetCurrentWeaponID();
				msg->AddRef();
				int label = msg->AddCout(this->Game::GameBase.ContractingLabel);
				msg->WriteBits(0x3F, 16);
				msg->WriteBits(0xB27AD5F7, 5);
				msg->WriteBits(label, 8);
				msg->WriteData(&pos_self, 0x60);
				msg->WriteData(&pos_enemy, 0x60);
				msg->WriteBits(weapon_id, 16);
				msg->WriteBits(0, 1);
				msg->WriteBits(0, 8);
				msg->WriteBits(0, 8);
				msg->WriteBits(msg->Size() * (label + weapon_id), 0x8);
				g_LTClient->SendToServer(msg->Read(), 1);
				msg->Release();
			}
			if (g_CommonLT->CreateMessage(msg) == LT_OK)
			{
				int weapon_id = this->Game::GetCurrentWeaponID() + 1;
				msg->AddRef();
				msg->WriteBits(0x122, 16);
				msg->WriteBits(0xB27AD5F7, 5);
				msg->WriteBits(0, 8);
				if (this->Game::is_average)
					msg->WriteBits(8, 8);
				//msg->WriteBits(index, 8);//index指定人ID
				else
					msg->WriteBits(self_position, 8);
				msg->WriteBits(1, 8);
				msg->Writeuint16(monster_point);
				if (this->Game::GetCurrentWeaponID() == 0x1394)
					msg->WriteBits(0x3E9, 16);
				else
					msg->WriteBits(0x259, 16);
				msg->WriteBits(-1, 8);
				msg->WriteBits(weapon_id, 16);
				LTVector pos_enemy1 = Read<LTVector>(this->Game::MemoryTools::ReadLong(monster_list[monster_list.size() - 1] + 0xD0) + 0x194);
				msg->WriteCompLTVector(pos_enemy1);
				g_LTClient->SendToServer(msg->Read(), 1);
				msg->Release();
			}
		}
		//爆裂者秒杀
		if (this->Game::breakers_seckill)
		{
			if (g_CommonLT->CreateMessage(msg) == LT_OK)
			{
				int id = 0;
				msg->AddRef();
				int label = msg->AddCout(GameBase.ContractingLabel);
				msg->WriteBits(0x71B, 16);
				msg->WriteBits(0xB27AD5F7, 5);
				msg->WriteBits(label, 8);
				msg->WriteBits(1, 1);
				msg->WriteBits(id, 8);
				msg->WriteBits((id + label) * msg->Size(), 8);
				g_LTClient->SendToServer(msg->Read(), 1);
				msg->Release();
			}
			if (g_CommonLT->CreateMessage(msg) == LT_OK)
			{
				int id = 0;
				msg->AddRef();
				int label = msg->AddCout(GameBase.ContractingLabel);
				msg->WriteBits(0x71B, 16);
				msg->WriteBits(0xB27AD5F7, 5);
				msg->WriteBits(label, 8);
				msg->WriteBits(0, 1);
				msg->WriteBits(id, 8);
				msg->WriteBits((id + label) * msg->Size(), 8);
				g_LTClient->SendToServer(msg->Read(), 1);
				msg->Release();
			}
			if (g_CommonLT->CreateMessage(msg) == LT_OK)
			{
				int weapon_id = this->Game::GetCurrentWeaponID();
				msg->AddRef();
				int label = msg->AddCout(GameBase.ContractingLabel);
				msg->WriteBits(0x431, 16);
				msg->WriteBits(0xB27AD5F7, 5);
				msg->WriteBits(label, 8);
				msg->WriteData(&pos_self, 0x60);
				msg->WriteData(&pos_enemy, 0x60);
				msg->WriteBits(weapon_id, 16);
				msg->WriteBits((weapon_id + label) * msg->Size(), 8);
				g_LTClient->SendToServer(msg->Read(), 1);
				msg->Release();
			}
			if (g_CommonLT->CreateMessage(msg) == LT_OK)
			{
				int weapon_id = this->Game::GetCurrentWeaponID() + 1;//原来的代码
				msg->AddRef();
				msg->WriteBits(0x122, 16);
				msg->WriteBits(0xB27AD5F7, 5);
				msg->WriteBits(0, 8);
				if (this->Game::is_average)
					msg->WriteBits(8, 8);
				//msg->WriteBits(index, 8);//修改index指定人选分数
				else
					msg->WriteBits(self_position, 8);
				msg->WriteBits(1, 8);
				msg->Writeuint16(monster_point);
				msg->WriteBits(0xDA4, 16);
				msg->WriteBits(-1, 8);
				msg->WriteBits(weapon_id, 16);
				LTVector pos_enemy1 = Read<LTVector>(this->Game::MemoryTools::ReadLong(monster_list[monster_list.size() - 1] + 0xD0) + 0x194);
				msg->WriteCompLTVector(pos_enemy1);
				g_LTClient->SendToServer(msg->Read(), 1);
				msg->Release();
			}
		}
		//全图吸怪
		if (this->Game::absorb_monster)
		{
			if (g_CommonLT->CreateMessage(msg) == LT_OK)
			{
				msg->WriteBits(685, 0x10);
				msg->WriteBits(monster_point, 0x10);
				msg->WriteData(&pos_self, 0x60);
				msg->WriteData(&pos_enemy, 0x60);
				g_LTClient->SendToServer(msg->Read(), 1);
			}
		}
		//无视错误代码
		if (g_CommonLT->CreateMessage(msg) == LT_OK)
		{
			msg->WriteBits(413, 16);
			msg->WriteBits(0xB2995A77, 5);
			msg->WriteBits(0, 8);
			msg->WriteBits(0, 8);
			msg->WriteBits(1, 1);
			msg->WriteBits(0, 8);
			g_LTClient->SendToServer(msg->Read(), 1);
		}

		////162检测包
		//if (g_CommonLT->CreateMessage(msg) == LT_OK)
		//{
		//	msg->AddRef();
		//	msg->WriteBits(702, 0x10);
		//	g_LTClient->SendToServer(msg->Read(), 1);
		//	msg->Release();
		//}
		pmonster_list->pop_back();			//清空数组
		Sleep(this->Game::seckill_speed);	//秒杀速度
	}
}

//发送封包
void Game::SendPacket()
{
	if (this->IsInGaming())
	{
		ILTMessage_Write* msg;
		//无视飞天瞬移错误代码
		if (g_CommonLT->CreateMessage(msg) == LT_OK)
		{
			msg->WriteBits(413, 16);
			msg->WriteBits(0xB2995A77, 5);
			msg->WriteBits(0, 8);
			msg->WriteBits(0, 8);
			msg->WriteBits(1, 1);
			msg->WriteBits(0, 8);
			g_LTClient->SendToServer(msg->Read(), 1);
		}
		////包
		//if (g_CommonLT->CreateMessage(msg) == LT_OK)
		//{
		//	msg->AddRef();
		//	msg->WriteBits(702, 0x10);
		//	g_LTClient->SendToServer(msg->Read(), 1);
		//	msg->Release();
		//}
	}
}

//void 飞镖秒杀(DWORD 本人ID, DWORD 目标ID, ULONG64 击杀目标, int 武器类型, int HostCreateTime, D3DXVECTOR3 Pos)
//{
//	ILTMessage_Write* Msg;
//	if (!g_CommonLT->CreateMessage(Msg)) {
//		Msg->AddRef();
//		Msg->WriteBits(0x2FC, 0x10);
//		Msg->WriteBits(0xB27AD5F7, 0x5);
//		Msg->WriteBits(0x0, 0x8);
//		Msg->WriteBits(本人ID, 0x8);
//		Msg->WriteBits(目标ID, 0x8);
//		Msg->WriteBits(0x100, 0x10);//伤害
//		Msg->WriteObject((HOBJECT)击杀目标);
//		Msg->WriteBits(1, 0x8);//击打骨骼类型
//		Msg->WriteBits(0, 0x8);
//		Msg->WriteBits(武器类型, 0x10);//武器ID
//		Msg->WriteCompLTVector(Pos);//敌人坐标
//		Msg->WriteBits(0, 0x1);//是否是AI
//		Msg->WriteBits(0, 0x1);//是否为物体
//		Msg->WriteBits(HostCreateTime, 0x20);//不知道啥玩意
//		Msg->WriteBits(0, 0x20);//击打类型
//		Msg->WriteBits(0, 0x1);//是否重击
//		Msg->WriteBits(0, 0x8);
//		g_LTClient->SendToServer(Msg->Read(), 1);
//		Msg->Release();
//	}
//}



