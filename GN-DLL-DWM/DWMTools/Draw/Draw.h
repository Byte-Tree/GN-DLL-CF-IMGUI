#pragma once
#include "../../pch.h"

#include <dwmapi.h>
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#include <d3dx11.h>
#pragma comment(lib, "d3dx11.lib")

#include "../../lmGui/imgui.h"
#include "../../lmGui/imgui_impl_dx11.h"
#include "../../lmGui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


class Draw
{
private:
	ID3D11Device* pd3d11device;
	ID3D11DeviceContext* pd3d11devicecontext;

	int cx = 0, cy = 0;
	int screenwidth_real = 0, screenheight_real = 0;

public:
	ID3D11RenderTargetView* prendertargetview;
	void OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView);
	void ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4]);
	ID3D11RenderTargetView* GetD3D11RenderTargetView() { return this->prendertargetview; }

	WNDPROC old_window_proc = NULL;
	static LRESULT CALLBACK OverlayWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	Draw();
	~Draw();
	bool InitImGui(IDXGISwapChain* pDxgiSwapChain);
	void SetImGuiMouse();
	void Rendering();

};


