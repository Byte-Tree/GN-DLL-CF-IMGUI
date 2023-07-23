#include "Draw.h"
//#include "../../DllMain.h"


Draw::Draw()
{
	DEVMODE dm;
	dm.dmSize = sizeof(DEVMODE);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
	this->cx = dm.dmPelsWidth;
	this->cy = dm.dmPelsHeight;
	this->screenwidth_real = GetSystemMetrics(SM_CXSCREEN);
	this->screenheight_real = GetSystemMetrics(SM_CYSCREEN);

}

Draw::~Draw()
{
}

bool Draw::InitImGui(IDXGISwapChain* pDxgiSwapChain)
{
	pDxgiSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&this->pd3d11device);
	this->pd3d11device->GetImmediateContext(&this->pd3d11devicecontext);

	DXGI_SWAP_CHAIN_DESC sd;
	pDxgiSwapChain->GetDesc(&sd);
	//HWND window = sd.OutputWindow;
	HWND window = FindWindow(L"Progman", L"Program Manager");

	ID3D11Texture2D* pBackBuffer;
	pDxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (pBackBuffer == NULL)
		return false;

	this->pd3d11device->CreateRenderTargetView(pBackBuffer, NULL, &this->prendertargetview);
	pBackBuffer->Release();
	this->old_window_proc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)Draw::OverlayWindowProc);
	////InitImGui();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	////io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	////io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(this->pd3d11device, this->pd3d11devicecontext);

	//设置ImGui字体
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\simhei.ttf", 14.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\simhei.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());

	return true;
}

void Draw::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView)
{
	return this->pd3d11devicecontext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

void Draw::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4])
{
	return pd3d11devicecontext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

//Overlay window proc
LRESULT CALLBACK Draw::OverlayWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	OutputDebugStringA("[GN]:窗口回调");

	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	//case WM_SIZE:
	//{
	//	OutputDebugStringA("[GN]:WM_SIZE");
	//	if (ce->Draw::GetD3D11Device() != NULL && wParam != SIZE_MINIMIZED)
	//	{
	//		ce->Draw::CleanupRenderTarget();
	//		ce->Draw::GetSwapChain()->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
	//		ce->Draw::CreateRenderTarget();
	//	}
	//	break;
	//}
	//case WM_SYSCOMMAND:
	//{
	//	if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
	//		return 0;
	//	break;
	//}
	//case WM_DESTROY:
	//	::PostQuitMessage(0);
	//	return 0;
	case WM_MOUSEMOVE:
	{
		OutputDebugStringA("[GN]:鼠标移动");
		break;
	}
	default:
		break;
	}
	//return ::CallWindowProc(draw->old_window_proc, hWnd, msg, wParam, lParam);
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

void Draw::SetImGuiMouse()
{
	//ImGuiIO& io = ImGui::GetIO();
	//POINT mousePosition;
	//::GetCursorPos(&mousePosition);
	//
	//////对应游戏窗口
	////io.MousePos.x = (float)mousePosition.x - this->Draw::windowrect.left;
	////io.MousePos.y = (float)mousePosition.y - this->Draw::windowrect.top - 26;
	//
	////全屏窗口
	//io.MousePos.x = (float)mousePosition.x;
	//io.MousePos.y = (float)mousePosition.y;
	//if (GetAsyncKeyState(VK_LBUTTON))io.MouseDown[0] = true;
	//else io.MouseDown[0] = false;

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.DisplaySize.x = this->cx;
	io.DisplaySize.y = this->cy;
	POINT info;
	GetCursorPos(&info);
	io.MousePos = { ((float)info.x / (float)screenwidth_real) * (float)this->cx,((float)info.y / (float)screenheight_real) * (float)this->cy };

	OutputDebugStringA_2Param("[GN]:io.x:%f,io.y:%f", io.MousePos.x, io.MousePos.y);

	if (GetAsyncKeyState(VK_LBUTTON))
		io.MouseDown[0] = true;
	else
		io.MouseDown[0] = false;
}

void Draw::Rendering()
{
	ImGui::Begin(u8"Test");

	ImGui::Text(u8"testtest...");

	ImGui::End();
}


