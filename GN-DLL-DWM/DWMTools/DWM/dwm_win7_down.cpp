#include "dwm.h"
#include <d3d10_1.h>
#include <d3d10.h>

#include "../../DllMain.h"

#define hr_fail_ret(ret) if(hr != S_OK){return ret;}
#define hr_fail_break if(hr != S_OK) {\
ERO_LOG("hr fail 0x%x",hr);\
break;\
}

namespace dwm
{
    namespace win7
    {
        char* hook_fun_address = 0;
        char* hook_fun_ori_address = 0;
        DWORD hook_fun_memory_proct = 0;

        namespace dx10
        {
            com_ptr<IDXGISwapChain> g_dxgiSwapChain;
            com_ptr<ID3D10Texture2D> g_back_buffer;
            com_ptr<ID3D10Device1>  g_d3dDevice;
            com_ptr<ID3D10RenderTargetView> g_mainRenderTargetView;
            com_ptr<ID3D10Texture2D>        g_AnitCaptureTexture2D;
            D3D10_TEXTURE2D_DESC back_buffer_desc;

            __int64 __fastcall my_present_hook(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8)
            {
                static bool init = false;
                if (!init)
                {
                    IDXGISwapChain* swap_chain = (IDXGISwapChain*)a1;
                    if (!draw->InitImGui(swap_chain))
                    {
                        OutputDebugStringA("[GN]:draw->InitImGui(): error!");
                    }
                    init = true;
                }

                //开始绘制
                ImGui_ImplDX11_NewFrame();
                //ImGui_ImplWin32_NewFrame((HWND)0);
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();

                //控制鼠标
                draw->SetImGuiMouse();

                //绘制
                draw->Rendering();

                //提交渲染
                ImGui::Render();
                draw->OMSetRenderTargets(1, &draw->prendertargetview, NULL);
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

                __int64 ret_val = ((decltype(my_present_hook)*)hook_fun_ori_address)(a1, a2, a3, a4, a5, a6, a7, a8);
                return ret_val;
            }
        };

        LONG WINAPI veh_handler(EXCEPTION_POINTERS* pExceptionInfo)
        {

            DWORD64 page_start = ((DWORD64)(hook_fun_address)) & 0xFFFFFFFFFFFFF000;
            DWORD64 page_end = page_start + 0x1000;

            LONG result;
            if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_GUARD_PAGE_VIOLATION) //捕获 PAGE_GUARD 异常
            {
                if ((pExceptionInfo->ContextRecord->Rip >= page_start) && (pExceptionInfo->ContextRecord->Rip <= page_end))
                {
                    if (pExceptionInfo->ContextRecord->Rip == (DWORD64)(hook_fun_address))
                    {
                        IUnknown* pObject = (IUnknown*)(pExceptionInfo->ContextRecord->Rcx);
                        {
                            char* table = *(char**)(pObject);
                            auto  cheat_table = LI_FN(VirtualAlloc)((LPVOID)0, (SIZE_T)0x200, MEM_COMMIT, PAGE_READWRITE);
                            memcpy(cheat_table, table, 0x200);
                            *(char**)(pObject) = (char*)cheat_table;
                            for (size_t i = 0; i < 0x200; i++)
                            {
                                if (((char**)cheat_table)[i] == hook_fun_address)
                                {
                                    ((char**)cheat_table)[i] = (char*)(&dx10::my_present_hook);
                                    hook_fun_ori_address = hook_fun_address;
                                    break;
                                }
                            }
                        }
                        return EXCEPTION_CONTINUE_EXECUTION;
                    }
                    pExceptionInfo->ContextRecord->EFlags |= 0x100;
                }
                result = EXCEPTION_CONTINUE_EXECUTION;
            }
            else if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP)
            {
                DWORD dwOld;
                LI_FN(VirtualProtect)((LPVOID)hook_fun_address, 1, hook_fun_memory_proct | PAGE_GUARD, &dwOld);
                result = EXCEPTION_CONTINUE_EXECUTION;
            }
            else
            {
                result = EXCEPTION_CONTINUE_SEARCH;
            }
            return result;
        }

        DWORD init(LPVOID parameter)
        {
            OutputDebugStringA("[GN]:DWM:WIN7");
            {
                GUID IID_IDXGIFactory = { 0x7b7166ec, 0x21c7, 0x44ae, 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 };

                com_ptr<IDXGIFactory> dxgiFactory;

                auto hr = LI_FN(CreateDXGIFactory)(IID_IDXGIFactory, &dxgiFactory);

                if (hr != S_OK) {
                    return 0;
                }

                com_ptr<IDXGIFactoryDWM> dxgiFactoryDWM;

                TEMP_GUID(IID_IDXGIFactoryDWM, 0x713F394E, 0x92CA, 0x47E7, 0xAB, 0x81, 0x11, 0x59, 0xC2, 0x79, 0x1E,
                    0x54);
                hr = dxgiFactory->QueryInterface(IID_IDXGIFactoryDWM, (void**)&dxgiFactoryDWM);

                if (hr != S_OK) {
                    return 0;
                }

                com_ptr<ID3D10Device1> d3d10Device;

                UINT createDeviceFlags = 0;
                createDeviceFlags |= D3D10_CREATE_DEVICE_BGRA_SUPPORT;
                hr = LI_FN(D3D10CreateDevice1)((IDXGIAdapter*)0, D3D10_DRIVER_TYPE_HARDWARE, (HMODULE)00,
                    createDeviceFlags,
                    D3D10_FEATURE_LEVEL_9_3, 0x20, &d3d10Device);

                if (hr != S_OK) {
                    return 0;
                }

                com_ptr<IDXGIDevice> dxgiDevice;
                GUID IID_IDXGIDevice = { 0x54ec77fa, 0x1377, 0x44e6, 0x8c, 0x32, 0x88, 0xfd, 0x5f, 0x44, 0xc8, 0x4c };
                hr = d3d10Device->QueryInterface(IID_IDXGIDevice, (void**)&dxgiDevice);
                if (hr != S_OK) {
                    return 0;
                }

                com_ptr<IDXGIAdapter> pAdapter;
                hr = dxgiDevice->GetAdapter(&pAdapter);
                if (hr != S_OK) {
                    return 0;
                }

                com_ptr<IDXGIOutput> pOutput;
                hr = pAdapter->EnumOutputs(0, &pOutput);
                if (hr != S_OK) {
                    return 0;
                }

                DXGI_SWAP_CHAIN_DESC sd;
                ZeroMemory(&sd, sizeof(sd));
                sd.BufferDesc.Width = 0;
                sd.BufferDesc.Width = 0;
                sd.BufferDesc.RefreshRate.Numerator = 0;
                sd.BufferDesc.RefreshRate.Denominator = 1;
                sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
                sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
                sd.SampleDesc.Count = 1;
                sd.SampleDesc.Quality = 0;
                sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER;
                sd.BufferCount = 3;
                sd.OutputWindow = nullptr;
                sd.Windowed = false;
                sd.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
                sd.Flags = DXGI_SWAP_CHAIN_FLAG_NONPREROTATED;

                com_ptr<IDXGISwapChainDWM> pSwapChainDWM;
                hr = dxgiFactoryDWM->CreateSwapChain(dxgiDevice.Get(), &sd, pOutput.Get(), &pSwapChainDWM);

                if (hr != S_OK) {
                    return 0;
                }

                uintptr_t* vtable = *(uintptr_t**)(pSwapChainDWM.Get());

                uintptr_t present_address = vtable[8];
                hook_fun_address = (char*)present_address;

                MEMORY_BASIC_INFORMATION mem_info;
                memset(&mem_info, 0, sizeof(mem_info));
                LI_FN(VirtualQuery)((LPCVOID)hook_fun_address, &mem_info, sizeof(mem_info));
                hook_fun_memory_proct = mem_info.Protect;

                PVOID veh_hanle = LI_FN(RtlAddVectoredExceptionHandler)(1, veh_handler);
                if (!veh_hanle) {
                    ERO_LOG("VEH ADD ERRO");
                }

                LI_FN(VirtualProtect)
                    ((LPVOID)hook_fun_address, 1, mem_info.Protect | PAGE_GUARD, &hook_fun_memory_proct);

                int frequency = 0;
                do {
                    frequency++;
                    LI_FN(Sleep)(16);
                } while (!hook_fun_ori_address && frequency < 60 * 60);

                LI_FN(VirtualProtect)((LPVOID)hook_fun_address, 1, mem_info.Protect, &hook_fun_memory_proct);
                LI_FN(RtlRemoveVectoredExceptionHandler)(veh_hanle);
            }
            return hook_fun_ori_address ? 1 : -1;
        }
    };
};



