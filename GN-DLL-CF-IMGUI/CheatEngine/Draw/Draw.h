#pragma once
#include "../../pch.h"
#include <dwmapi.h>
//direct
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#include <d3dx11.h>
#pragma comment(lib, "d3dx11.lib")
//ImGUi
#include "../../lmGui/imgui.h"
#include "../../lmGui/imgui_impl_dx9.h"
#include "../../lmGui/imgui_impl_win32.h"

#include "../Hook/HOOK.h"
#include "../Tools/Tools.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct _Direct9
{
	IDirect3D9* object = nullptr;							//创建一个D3D对象
	IDirect3DDevice9* device = nullptr;						//创建一个D3D设备
	D3DPRESENT_PARAMETERS params;							//创建一个D3D后台处理的类型
	IDirect3DStateBlock9* stateBlock = nullptr;
	ID3DXFont* fontSmall = nullptr;							//创建一个D3D绘制文本对象
	ID3DXLine* line = nullptr;								//创建一个D3D画线对象
	int fontSize = 17;										//设置字体大小
};

struct _Direct11
{
	ID3D11Device* pd3d11device = nullptr;
	ID3D11DeviceContext* pd3d11deviceContext = nullptr;
	IDXGISwapChain* pswapchain = nullptr;
	ID3D11RenderTargetView* mainrendertargetview = nullptr;
};


class Draw :public Tools
{
private:
	HWND game_window_handle = NULL;							//游戏窗口句柄
	HINSTANCE overlay_window_hinstance = 0;
	HWND overlay_window_handle = 0;
	_Direct9 direct9 = { nullptr };
	_Direct11 direct11 = { nullptr };

public:
	void SetDevice9(IDirect3DDevice9* p_device) { direct9.device = p_device; }
	HWND GetGameWindowHandle() { return game_window_handle; }
	void SetOverlayWindowHinstance(HINSTANCE hinstance) { overlay_window_hinstance = hinstance; }
	void SetGameWindowHandle(HWND hand) { game_window_handle = hand; }
	void SetOverlayWindowHandle(HWND hand) { overlay_window_handle = hand; }
	HWND GetOverlayWindowHandle() { return overlay_window_handle; }
	IDirect3DDevice9* GetD3D9Device() { return direct9.device; }
	ID3D11Device* GetD3D11Device() { return direct11.pd3d11device; }
	IDXGISwapChain* GetSwapChain() { return direct11.pswapchain; }

	static LRESULT CALLBACK OverlayWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static HRESULT CALLBACK Self_Present(IDirect3DDevice9* direct3ddevice9, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion);
	static HRESULT CALLBACK Self_SetViewport(IDirect3DDevice9* direct3ddevice9, CONST D3DVIEWPORT9* pViewport);
	static HRESULT CALLBACK Self_Reset(IDirect3DDevice9* direct3ddevice9, D3DPRESENT_PARAMETERS* pPresentationParameters);

public:
	inline_hook* setviewport_hook = nullptr;
	inline_hook* reset_hook = nullptr;

	ImU32 draw_color = D3DCOLOR_RGBA(0, 255, 0, 255);		//绘制颜色
	RECT windowrect, clientrect;
	int window_x = 0, window_y = 0, gamecent_x = 0, gamecent_y = 0, gameheight = 0, gamewidth = 0, gametop = 0, gameleft = 0;

	bool is_present_draw = true;
	bool show_menu = true;						//绘制菜单
	bool show_characterindex = false;			//人物渲染
	bool show_rectbox = false;					//显示方框
	bool show_health = false;					//显示血量
	bool show_c4 = false;						//显示雷包
	bool show_name = false;						//显示昵称
	bool show_crosshair = false;				//显示准心
	bool show_bone = false;						//显示骨骼
	bool show_userQQnumber = false;				//显示扣扣
	bool show_antenna = false;;					//显示天线
	bool show_teamate = false;					//显示队友
	bool show_previewray = false;				//预瞄射线
	bool show_trackrange = false;				//追踪范围

public:
	Draw();
	~Draw();
	void InitDirectAndHook(HWND hwnd);
	bool CreateOverlayWindow(const wchar_t* class_name, const wchar_t* title_name, bool inverse_screenshot);
	void InitImGui(HWND hwnd);
	void InitImGuiDx9(IDirect3DDevice9* direct3ddevice9);
	bool CreateDeviceD3D9(HWND hwnd);
	bool CreateDeviceD3D11(HWND hwnd);
	void CreateRenderTarget();
	void CleanupDeviceD3D11();
	void CleanupRenderTarget();
	void MoveOverlayWindow(HWND target_hwnd, HWND overlay_hwnd);
	void BegineDirect9();
	void EndDirect9();
	void BegineDirect11();
	void EndDirect11();
	void GetGameWindowRect();
	void SetImGuiMouse();
	void FillRectangle(float Left, float Top, float Width, float Height, float R, float G, float B, float A);
	void DrawCrossHair(RECT rect, float width, D3DCOLOR color);
	void DrawAntenna(RECT rect, int objx, int objy, int objw, int objh, D3DCOLOR color, float width);
	void DrawPreviewRay(RECT rect, int objx, int objy, int objw, int objh, bool side, D3DCOLOR color, float width);
	void DrawTrackRange(RECT rect, int range, D3DCOLOR color, float width);
	void MenuDraw();
	void MainFuncDraw();
	void HookMainFunc();

};



