#include "../../pch.h"
#include "../../DllMain/DllMain.h"


//Overlay window proc
LRESULT CALLBACK Draw::OverlayWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	//	return true;
	switch (msg)
	{
	case WM_SIZE:
	{
		OutputDebugStringA("[GN]:WM_SIZE");
		if (ce->Draw::GetD3D11Device() != NULL && wParam != SIZE_MINIMIZED)
		{
			ce->Draw::CleanupRenderTarget();
			ce->Draw::GetD3D11SwapChain()->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			ce->Draw::CreateRenderTarget();
		}
		break;
	}
	case WM_SYSCOMMAND:
	{
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	}
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

//Game window proc
LRESULT CALLBACK CheatEngine::SelfGameWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
	{
		//ce->Draw::MoveOverlayWindow(ce->CheatEngine::Draw::GetGameWindowHandle(), ce->Draw::GetOverlayWindowHandle());
		ce->Draw::GetGameWindowRect();
		break;
	}
	case WM_SIZE:
	{
		//ce->Draw::MoveOverlayWindow(ce->CheatEngine::Draw::GetGameWindowHandle(), ce->Draw::GetOverlayWindowHandle());
		ce->Draw::GetGameWindowRect();
		break;
	}
	case WM_MOVE:
	{
		//ce->Draw::MoveOverlayWindow(ce->CheatEngine::Draw::GetGameWindowHandle(), ce->Draw::GetOverlayWindowHandle());
		ce->Draw::GetGameWindowRect();
		break;
	}
	//case WM_MOUSEMOVE:
	//{
	//	ce->Draw::GetGameWindowRect();
	//	break;
	//}
	case WM_KEYDOWN:
	{
		ce->CheatEngine::GameKeyCallBack(wParam, lParam);
		break;
	}
	case WM_SYSCOMMAND:
	{
		ce->CheatEngine::GameCombinationKeyCallBack(wParam, lParam);
		break;
	}
	default:
		break;
	}

	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	return CallWindowProc(ce->CheatEngine::Game::original_proc, hWnd, msg, wParam, lParam);
}

//Game keyboard proc
void CheatEngine::GameKeyCallBack(WPARAM wParam, LPARAM lParam)
{
	if (wParam == VK_HOME)
		this->Draw::show_menu = !this->Draw::show_menu;
}

//Game combination keyboard proc
void CheatEngine::GameCombinationKeyCallBack(WPARAM wParam, LPARAM lParam)
{

}

//Self present api
HRESULT CALLBACK Draw::Self_Present(IDirect3DDevice9* direct3ddevice9, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion)
{
	static bool first_call = false;
	if (!first_call)
	{
		first_call = true;
		ce->CheatEngine::Draw::SetDevice9(direct3ddevice9);
		ce->CheatEngine::Draw::InitImGuiDx9(direct3ddevice9);
		ce->CheatEngine::InitHook();
		ce->CheatEngine::original_proc = (WNDPROC)SetWindowLongPtr(ce->CheatEngine::GetGameWindowHandle(), GWLP_WNDPROC, (LONG_PTR)CheatEngine::SelfGameWindowProc);
	}

	ce->CheatEngine::Draw::BegineDirect9();
	ce->CheatEngine::Draw::MenuDraw();
	ce->CheatEngine::Draw::MainFuncDraw();
	ce->CheatEngine::Draw::EndDirect9();

	return S_OK;
}

//Self DrawIndexedPrimitive api
HRESULT CALLBACK Draw::Self_DrawIndexedPrimitive(IDirect3DDevice9* direct3ddevice9, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	ce->Draw::drawindexedprimitive_hook->restore_address();

	if (ce->Draw::show_characterindex)
	{
		IDirect3DVertexBuffer9* pStreamData = NULL;
		UINT iOffsetInBytes, iStride;
		if (direct3ddevice9->GetStreamSource(0, &pStreamData, &iOffsetInBytes, &iStride) == D3D_OK)
		{
			pStreamData->Release();
			DWORD Value = 0;
			if (iStride == 40 || iStride == 44 || iStride == 48 || iStride == 68 || iStride == 72)
			{
				direct3ddevice9->GetRenderState(D3DRS_ZENABLE, &Value);
				direct3ddevice9->SetRenderState((D3DRENDERSTATETYPE)7, 0);
			}
		}
	}

	HRESULT result = direct3ddevice9->DrawIndexedPrimitive(Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
	ce->Draw::drawindexedprimitive_hook->motify_address();
	return result;
}

//Self SetViewport api
HRESULT CALLBACK Draw::Self_SetViewport(IDirect3DDevice9* direct3ddevice9, CONST D3DVIEWPORT9* pViewport)
{
	ce->CheatEngine::Draw::setviewport_hook->restore_address();

	HRESULT result = direct3ddevice9->SetViewport(pViewport);

	//GetWindowRect(, &g_WindRect);   //获取游戏窗口矩形
	ce->Draw::clientrect.left = (int)pViewport->X;
	ce->Draw::clientrect.right = (int)pViewport->Width;
	ce->Draw::clientrect.top = (int)pViewport->Y;
	ce->Draw::clientrect.bottom = (int)pViewport->Height;

	ce->Draw::gameheight = ce->Draw::clientrect.bottom;
	ce->Draw::gamewidth = ce->Draw::clientrect.right;
	ce->Draw::gamecent_x = (int)pViewport->Width / 2;
	ce->Draw::gamecent_y = (int)pViewport->Height / 2;

	ce->CheatEngine::Draw::setviewport_hook->motify_address();
	return result;
}

//Self Reset api
HRESULT CALLBACK Draw::Self_Reset(IDirect3DDevice9* direct3ddevice9, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ce->CheatEngine::reset_hook->restore_address();

	ImGui_ImplDX9_InvalidateDeviceObjects();

	printf("设备已重置...\n");

	HRESULT result = direct3ddevice9->Reset(pPresentationParameters);

	ImGui_ImplDX9_CreateDeviceObjects();

	ce->CheatEngine::reset_hook->motify_address();
	return result;
}

//Self GetBuffer api
HRESULT CALLBACK Draw::Self_GetBuffer(IDXGISwapChain* pSwapChain, UINT Buffer, REFIID riid, void** ppSurface)
{
	ce->CheatEngine::Draw::getbuffer_hook->restore_address();

	HRESULT result = ce->CheatEngine::Draw::m_OriginalGetBufferPoint(pSwapChain, Buffer, riid, ppSurface);

	OutputDebugStringA("[GN]:游戏调用GetBuffer...\n");

	ce->CheatEngine::Draw::getbuffer_hook->motify_address();
	return result;
}

//Vector exception handler Old...
LONG WINAPI CheatEngine::ExceptionHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
	//hardware breakpoint
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	{
		if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->mdr1)
		{
			if (ce->CheatEngine::ByPassCheck(ExceptionInfo->ContextRecord))
			{
				ExceptionInfo->ContextRecord->Rip = gn_exception->mdr1 + 0x07;
				OutputDebugStringA("[GN]:Pass Base...");
				return EXCEPTION_CONTINUE_EXECUTION;
			}
			else
			{
				ExceptionInfo->ContextRecord->Rip = gn_exception->mdr1 + 0x04;
				//OutputDebugStringA("[GN]:Doing Base...");
				return EXCEPTION_CONTINUE_EXECUTION;
			}
		}
		//绘制挂接
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->mdr2)
		{
			CheatEngine::Self_Present((IDirect3DDevice9*)ExceptionInfo->ContextRecord->Rcx, NULL, NULL, NULL, NULL);
			ExceptionInfo->ContextRecord->R9 = 0;
			ExceptionInfo->ContextRecord->R8 = 0;
			ExceptionInfo->ContextRecord->Rdx = 0;
			ExceptionInfo->ContextRecord->Rip = gn_exception->mdr2 + 0x08;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//红名追踪hook
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->mdr3)
		{
			ce->CheatEngine::Game::HookRedNameTrackFunc(ExceptionInfo->ContextRecord->Rcx, ExceptionInfo->ContextRecord->Rbp);

			//*(__int64*)(ExceptionInfo->ContextRecord->Rsp + 0x18) = ExceptionInfo->ContextRecord->R8;
			//*(__int64*)(ExceptionInfo->ContextRecord->Rsp + 0x10) = ExceptionInfo->ContextRecord->Rdx;
			//*(__int64*)(ExceptionInfo->ContextRecord->Rsp + 0x08) = ExceptionInfo->ContextRecord->Rcx;
			//ExceptionInfo->ContextRecord->Rip = gn_exception->mdr3 + 0x0F;

			*(__int64*)(ExceptionInfo->ContextRecord->Rsp + 0x18) = ExceptionInfo->ContextRecord->R8;
			ExceptionInfo->ContextRecord->Rip = gn_exception->mdr3 + 0x05;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//视角追踪
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->mdr4)
		{
			if (ce->CheatEngine::Game::silence_track)
			{
				if (ce->CheatEngine::Game::silence_track_switch)
				{
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm0, &ce->CheatEngine::Game::m_silence_track_coordinates.y, sizeof(float));
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm1, &ce->CheatEngine::Game::m_silence_track_coordinates.x, sizeof(float));
				}
				else
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm1, &ExceptionInfo->ContextRecord->Xmm3, sizeof(float));
			}
			else
				RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm1, &ExceptionInfo->ContextRecord->Xmm3, sizeof(float));
			ExceptionInfo->ContextRecord->Rip = gn_exception->mdr4 + 0x03;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}
	//software breakpoint
	else if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT)
	{
		//crossfireBase驱动
		if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint1)
		{
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint1 + 0x0527;
			OutputDebugStringA("[GN]:跳过CrossfireBase检测驱动");
			return EXCEPTION_CONTINUE_EXECUTION;
		}
#if _REDBULLBRELEASE || _REDBULLBDEBUG
		//ATS_CRC
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint2)
		{
			//printf("原始R8:%p\n", ExceptionInfo->ContextRecord->R8);
			//ExceptionInfo->ContextRecord->R8 = *(BYTE*)ExceptionInfo->ContextRecord->Rdx;
			//printf("修改后R8:%p\n", ExceptionInfo->ContextRecord->R8);
			//printf("\n");
			DWORD thread_id = GetCurrentThreadId();
			printf("ats1当前线程：%d\n", thread_id);
			SuspendThread(GetCurrentThread());
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint2 + 0x03;
			return EXCEPTION_CONTINUE_SEARCH;
		}
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint3)
		{
			DWORD thread_id = GetCurrentThreadId();
			printf("ats2当前线程：%d\n", thread_id);
			SuspendThread(GetCurrentThread());
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint3 + 0x03;
			return EXCEPTION_CONTINUE_SEARCH;
		}
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint4)
		{
			DWORD thread_id = GetCurrentThreadId();
			printf("ats3当前线程：%d\n", thread_id);
			SuspendThread(GetCurrentThread());
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint4 + 0x03;
			return EXCEPTION_CONTINUE_SEARCH;
		}
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint5)
		{
			DWORD thread_id = GetCurrentThreadId();
			printf("ats4当前线程：%d\n", thread_id);
			SuspendThread(GetCurrentThread());
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint5 + 0x03;
			return EXCEPTION_CONTINUE_SEARCH;
		}
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint17)
		{
			DWORD thread_id = GetCurrentThreadId();
			printf("ats5当前线程：%d\n", thread_id);
			SuspendThread(GetCurrentThread());
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint17 + 0x03;
			return EXCEPTION_CONTINUE_SEARCH;
		}
		//范围追踪
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint6)
		{
			if (ce->Game::range_track)
			{
				if (ce->MemoryTool::ReadInt(ExceptionInfo->ContextRecord->Rdx + 0x16C) == ce->Game::range_track_position)
				{
					float temp = 0.0f, write = 0.0f;
					RtlCopyMemory(&temp, &ExceptionInfo->ContextRecord->Xmm2, sizeof(float));
					write = temp - ce->Game::range_track_value;
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm2, &write, sizeof(float));

					temp = 0.0f; write = 0.0f;
					RtlCopyMemory(&temp, &ExceptionInfo->ContextRecord->Xmm1, sizeof(float));
					write = temp - ce->Game::range_track_value;
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm1, &write, sizeof(float));

					temp = 0.0f; write = 0.0f;
					RtlCopyMemory(&temp, &ExceptionInfo->ContextRecord->Xmm0, sizeof(float));
					write = temp - ce->Game::range_track_value;
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm0, &write, sizeof(float));
				}
			}
			RtlCopyMemory((PVOID)(ExceptionInfo->ContextRecord->Rdx + 0x08), &ExceptionInfo->ContextRecord->Xmm2, sizeof(float));
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint6 + 0x05;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint7)
		{
			if (ce->Game::range_track)
			{
				if (ce->MemoryTool::ReadInt(ExceptionInfo->ContextRecord->Rdx + 0x16C) == ce->Game::range_track_position)
				{
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm2, &ce->Game::range_track_value, sizeof(float));
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm1, &ce->Game::range_track_value, sizeof(float));
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm0, &ce->Game::range_track_value, sizeof(float));
				}
			}
			float xmm2 = 0;
			RtlCopyMemory(&xmm2, &ExceptionInfo->ContextRecord->Xmm2, sizeof(float));
			xmm2 = xmm2 + *(float*)(ExceptionInfo->ContextRecord->Rdx + 0x194);
			RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm2, &xmm2, sizeof(float));
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint7 + 0x08;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint8)
		{
			if (ce->Game::range_track)
			{
				if (ce->MemoryTool::ReadInt(ExceptionInfo->ContextRecord->Rax + 0x16C) == ce->Game::range_track_position)
				{
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm0, &ce->Game::range_track_value, sizeof(float));
					float xmm0 = 0;
					xmm0 = ce->Game::range_track_value * ce->Game::range_track_value;
					RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm0, &xmm0, sizeof(float));
				}
			}
			RtlCopyMemory((PVOID)(ExceptionInfo->ContextRecord->Rsp + 0x2C), &ExceptionInfo->ContextRecord->Xmm0, sizeof(float));
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint8 + 0x06;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//静步加速
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint9)
		{
			RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm0, &ce->Game::static_acceleration_value, sizeof(float));
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint9 + 0x08;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//下蹲加速
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint10)
		{
			RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm0, &ce->Game::squat_acceleration_value, sizeof(float));
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint10 + 0x08;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//零秒换弹
		else if ((ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint11) || (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID)gn_exception->software_breakpoint12))
		{
			if (ce->Game::zero_second_reload)
			{
				if (ce->MemoryTool::ReadInt(ce->MemoryTool::ReadLong(ce->Game::GameBase.CharacterBase) + CurrentWeaponOffset) != 2)
					ExceptionInfo->ContextRecord->Rdx = 2;
				else
					ExceptionInfo->ContextRecord->Rdx = *(int*)(ExceptionInfo->ContextRecord->R14 + ZeroSecondAmmunitionChangeOffset);
			}
			else
				ExceptionInfo->ContextRecord->Rdx = *(int*)(ExceptionInfo->ContextRecord->R14 + ZeroSecondAmmunitionChangeOffset);
			//判断跳转地址
			if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID)gn_exception->software_breakpoint11)
				ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint11 + 0x07;
			else
				ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint12 + 0x07;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//空格飞天
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint13)
		{
			if (ce->Game::space_fly)
			{
				if (GetAsyncKeyState(VK_SPACE) != 0)
					ExceptionInfo->ContextRecord->Rax = 1151067676;
				else
					ExceptionInfo->ContextRecord->Rax = *(int*)(ExceptionInfo->ContextRecord->Rdx + SpaceflyOffset);
			}
			else
				ExceptionInfo->ContextRecord->Rax = *(int*)(ExceptionInfo->ContextRecord->Rdx + SpaceflyOffset);
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint13 + 0x06;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//卡不掉血
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint14)
		{
			if (ce->Game::no_blood_loss)
			{
				float t = 0.0f;
				RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm1, &t, sizeof(float));
			}
			*(__int64*)(ExceptionInfo->ContextRecord->Rsp + 0x08) = ExceptionInfo->ContextRecord->Rbx;
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint14 + 0x05;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//子弹午后
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint15)
		{
			static int start_value = 0.0f, old_value = 3212836864;
			if (ce->Game::no_backseat)
				RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm8, &start_value, sizeof(float));
			else
				RtlCopyMemory(&ExceptionInfo->ContextRecord->Xmm8, &old_value, sizeof(float));
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint15 + 0x09;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//武器连发
		else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint16)
		{
			if (ce->Game::weapon_fire)
				*(BYTE*)(ExceptionInfo->ContextRecord->Rsi + WeaponFireOffset) = (BYTE)0x00;
			else
				*(BYTE*)(ExceptionInfo->ContextRecord->Rsi + WeaponFireOffset) = (BYTE)0x01;
			ExceptionInfo->ContextRecord->Rip = gn_exception->software_breakpoint16 + 0x07;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
#endif
	}
	//set breakpoint
	else
	{
		ExceptionInfo->ContextRecord->Dr0 = gn_exception->mdr1;
		ExceptionInfo->ContextRecord->Dr1 = gn_exception->mdr2;
		ExceptionInfo->ContextRecord->Dr2 = gn_exception->mdr3;
		ExceptionInfo->ContextRecord->Dr3 = gn_exception->mdr4;
		return EXCEPTION_CONTINUE_SEARCH;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

//Vector exception handler
LONG WINAPI CheatEngine::NewExceptionHandler(PEXCEPTION_RECORD ExceptionRecord, PCONTEXT context)
{
	//hardware breakpoint
	if (ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	{
		if (ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->mdr1)
		{
			if (ce->CheatEngine::ByPassCheck(context))
			{
				context->Rip = gn_exception->mdr1 + 0x07;
				//ACE-Base64.dll + 815844 - 48 89 47 08 -	mov[rdi + 08], rax
				//ACE-Base64.dll + 815848 - FF 53 20 -		call qword ptr[rbx + 20]	//跳过执行
				//ACE-Base64.dll + 81584B - 48 8B 1B -		mov rbx, [rbx]
				
				//OutputDebugStringA("[GN]:Pass Base...");
				return EXCEPTION_CONTINUE_EXECUTION;
			}
			else
			{
				context->Rip = gn_exception->mdr1 + 0x04;
				//OutputDebugStringA("[GN]:Doing Base...");
				return EXCEPTION_CONTINUE_EXECUTION;
			}
		}
		//绘制挂接
		else if (ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->mdr2)
		{
			//OutputDebugStringA("[GN]:绘制挂接...");
			CheatEngine::Self_Present((IDirect3DDevice9*)context->Rcx, NULL, NULL, NULL, NULL);
			context->R9 = 0;
			context->R8 = 0;
			context->Rdx = 0;
			context->Rip = gn_exception->mdr2 + 0x08;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//红名追踪hook
		else if (ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->mdr3)
		{
			ce->CheatEngine::Game::HookRedNameTrackFunc(context->Rcx, context->Rbp);

			//*(__int64*)(ExceptionInfo->ContextRecord->Rsp + 0x18) = ExceptionInfo->ContextRecord->R8;
			//*(__int64*)(ExceptionInfo->ContextRecord->Rsp + 0x10) = ExceptionInfo->ContextRecord->Rdx;
			//*(__int64*)(ExceptionInfo->ContextRecord->Rsp + 0x08) = ExceptionInfo->ContextRecord->Rcx;
			//ExceptionInfo->ContextRecord->Rip = gn_exception->mdr3 + 0x0F;

			*(__int64*)(context->Rsp + 0x18) = context->R8;
			context->Rip = gn_exception->mdr3 + 0x05;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		//视角追踪
		else if (ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->mdr4)
		{
			if (ce->CheatEngine::Game::silence_track)
			{
				if (ce->CheatEngine::Game::silence_track_switch)
				{
					if (ce->Game::m_locking_pawn != 0)
					{
						if (ce->CheatEngine::Game::silence_track_switch)
						{
							//crossfire.exe + 235330 - 48 83 EC 28 -		sub rsp, 28
							//crossfire.exe + 235334 - 0F28 C2 -			movaps xmm0, xmm2			//写y坐标
							//crossfire.exe + 235337 - 4C 8B CA -			mov r9, rdx
							//crossfire.exe + 23533A - F3 0F10 54 24 50 -	movss xmm2, [rsp + 50]
							//crossfire.exe + 235340 - 0F28 CB -			movaps xmm1, xmm3			//Hook点 | 写x坐标
							//crossfire.exe + 235343 - E8 D817FEFF -		call TracFuncion()
							RtlCopyMemory(&context->Xmm0, &ce->CheatEngine::Game::m_silence_track_coordinates.y, sizeof(float));
							RtlCopyMemory(&context->Xmm1, &ce->CheatEngine::Game::m_silence_track_coordinates.x, sizeof(float));
						}
						else
							context->Xmm1 = context->Xmm3;
					}
					else
						context->Xmm1 = context->Xmm3;
				}
				else
					context->Xmm1 = context->Xmm3;
			}
			else
				context->Xmm1 = context->Xmm3;
			context->Rip = gn_exception->mdr4 + 0x03;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		else
		{
			context->Dr0 = gn_exception->mdr1;
			context->Dr1 = gn_exception->mdr2;
			context->Dr2 = gn_exception->mdr3;
			context->Dr3 = gn_exception->mdr4;
			return EXCEPTION_CONTINUE_SEARCH;
		}
	}
	//software breakpoint
	else if (ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT)
	{
		if (ExceptionRecord->ExceptionAddress == (PVOID64)gn_exception->software_breakpoint1)
		{
			if (ce->CheatEngine::Game::no_backseat)
			{
				float func_value = 0.0f;

				RtlCopyMemory(&context->Xmm8, &func_value, sizeof(float));
			}
			else
			{
				float old_value = -1.0f;

				RtlCopyMemory(&context->Xmm8, &old_value, sizeof(float));
			}

			context->Rip = gn_exception->software_breakpoint1 + 0x09;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}
	return EXCEPTION_CONTINUE_SEARCH;
}



