#include "dwm.h"

#include <d3d11.h>
#define OutputDebugStringA_1Param(fmt,var) {CHAR sOut[256];CHAR sfmt[50];sprintf_s(sfmt,"%s%s","",fmt);sprintf_s(sOut,(sfmt),var);OutputDebugStringA(sOut);}
#define hr_fail_ret(ret) if(hr != S_OK){return ret;}
#define hr_fail_break if(hr != S_OK) {\
ERO_LOG("hr fail 0x%x",hr);\
break;\
}


namespace dwm
{
    namespace win10
    {

        char* hook_fun_address = 0;
        char* hook_fun_ori_address = 0;
        DWORD hook_fun_memory_proct = 0;

        namespace dx11
        {
            com_ptr<IDXGISwapChain>         g_dxgiSwapChain;
            com_ptr<ID3D11Texture2D>        g_back_buffer;
            com_ptr<ID3D11Device>           g_d3dDevice;
            com_ptr<ID3D11DeviceContext>    g_d3dDeviceContext;
            com_ptr<ID3D11RenderTargetView> g_mainRenderTargetView;
            com_ptr<ID3D11Texture2D>        g_AnitCaptureTexture2D;
            D3D11_TEXTURE2D_DESC            back_buffer_desc;

            __int64 __fastcall my_present_hook(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8)
            {

                static bool init = false;
                if (!init)
                {
                    do
                    {
                        IDXGISwapChain* swap_chain = (IDXGISwapChain*)a1;

                        auto hr = 0;

                        com_ptr<ID3D11Device> d3dDevice;

                        TEMP_GUID(IID_ID3D11Device, 0xdb6f6ddb, 0xac77, 0x4e88, 0x82, 0x53, 0x81, 0x9d, 0xf9, 0xbb, 0xf1, 0x40);
                        hr = swap_chain->GetDevice(IID_ID3D11Device, &d3dDevice);

                        hr_fail_break;

                        com_ptr<ID3D11DeviceContext> d3dDeviceContext;
                        d3dDevice->GetImmediateContext(&d3dDeviceContext);


                        TEMP_GUID(IID_ID3D11Texture2D, 0x6f15aaf2, 0xd208, 0x4e89, 0x9a, 0xb4, 0x48, 0x95, 0x35, 0xd3, 0x4f, 0x9c);

                        hr = swap_chain->GetBuffer(0, IID_ID3D11Texture2D, &g_back_buffer);

                        hr_fail_break;


                        g_back_buffer->GetDesc(&back_buffer_desc);

                        MSG_LOG("width %d , height %d", back_buffer_desc.Width, back_buffer_desc.Height);

                        com_ptr<ID3D11RenderTargetView> main_render_target_view;

                        hr = d3dDevice->CreateRenderTargetView(g_back_buffer.Get(), NULL, &main_render_target_view);

                        //hr_fail_break;
                        //
                        //{
                        //    D3D11_TEXTURE2D_DESC desc;
                        //    memset(&desc, 0x00, sizeof(desc));
                        //    g_back_buffer->GetDesc(&desc);
                        //    hr = d3dDevice->CreateTexture2D(&desc, 0, &(g_AnitCaptureTexture2D));
                        //    hr_fail_break;
                        //}
                        //
                        //g_dxgiSwapChain.Attach(swap_chain);
                        //g_d3dDevice.Attach(d3dDevice.Get());
                        //g_d3dDeviceContext.Attach(d3dDeviceContext.Get());
                        //
                        //if (!IImDataRender::GetInstance(0xD3D11)->Init(g_dxgiSwapChain.Get())) {
                        //    break;
                        //}
                        //
                        //if (!draw::init()) {
                        //    break;
                        //}
                        //
                        //g_mainRenderTargetView = main_render_target_view;
                        //
                        //MSG_LOG("direct 11 init success");
                        
                        init = true;
                    } while (false);
                }

                //if (init)
                //{
                //    g_d3dDeviceContext->CopyResource(g_AnitCaptureTexture2D.Get(), g_back_buffer.Get());
                //
                //    g_d3dDeviceContext->OMSetRenderTargets(1, g_mainRenderTargetView.GetAddressOf(), NULL);
                //
                //    draw::draw_call();
                //}
                /* if (!bypass::CanPresent() && init) {
                     g_d3dDeviceContext->CopyResource(g_back_buffer.Get(), g_AnitCaptureTexture2D.Get());
                 }*/
                //
                 //OutputDebugStringA("[GN]:my present hook ...");

                OutputDebugStringA("[GN]:present循环");

                __int64 ret_val = ((decltype(my_present_hook)*)hook_fun_ori_address)(a1, a2, a3, a4, a5, a6, a7, a8);

                //if (init) {
                //    g_d3dDeviceContext->CopyResource(g_back_buffer.Get(), g_AnitCaptureTexture2D.Get());
                //}

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
                if ((pExceptionInfo->ContextRecord->Rip >= page_start) && (pExceptionInfo->ContextRecord->Rip <= page_end)) {

                    if (pExceptionInfo->ContextRecord->Rip == (DWORD64)(hook_fun_address)) {
                        IUnknown* pObject = (IUnknown*)(pExceptionInfo->ContextRecord->Rcx);

                        {
                            char* table = *(char**)(pObject);
                            auto  cheat_table =
                                LI_FN(VirtualAlloc)((LPVOID)0, (SIZE_T)0x200, MEM_COMMIT, PAGE_READWRITE);
                            memcpy(cheat_table, table, 0x200);
                            *(char**)(pObject) = (char*)cheat_table;
                            for (size_t i = 0; i < 0x200; i++)
                            {
                                if (((char**)cheat_table)[i] == hook_fun_address)
                                {
                                    OutputDebugStringA_1Param("[GN]:present Hook地址:%p", hook_fun_address);
                                    ((char**)cheat_table)[i] = (char*)(&dx11::my_present_hook);
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
            OutputDebugStringA("[GN]:DWM:WIN10");
            {

                TEMP_GUID(IID_IDXGIFactory, 0x7b7166ec, 0x21c7, 0x44ae, 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69);

                com_ptr<IDXGIFactory> dxgiFactory;

                auto hr = LI_FN(CreateDXGIFactory)(IID_IDXGIFactory, &dxgiFactory);

                hr_fail_ret(-1);

                TEMP_GUID(IID_IDXGIFactoryDWM8, 0x1DDD77AA, 0x9A4Au, 0x4CC8, 0x9Eu, 0x55, 0x98u, 0xC1u, 0x96u, 0xBAu,
                    0xFCu, 0x8Fu);

                com_ptr<IDXGIFactoryDWM8> dxgiFactoryDWM8;

                hr = dxgiFactory->QueryInterface(IID_IDXGIFactoryDWM8, (void**)&dxgiFactoryDWM8);

                hr_fail_ret(-1);

                com_ptr<ID3D11Device>        d3dDevice;
                com_ptr<ID3D11DeviceContext> d3dDeviceContext;

                UINT createDeviceFlags = 0;
                createDeviceFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;
                D3D_FEATURE_LEVEL featureLevelArray[] = { (D3D_FEATURE_LEVEL)0xb100/*D3D_FEATURE_LEVEL_11_1*/, D3D_FEATURE_LEVEL_11_0,
                                                         D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };

                hr = LI_FN(D3D11CreateDevice)((IDXGIAdapter*)NULL, D3D_DRIVER_TYPE_HARDWARE, (HMODULE)NULL,
                    createDeviceFlags, (CONST D3D_FEATURE_LEVEL*) & featureLevelArray, 4, 7,
                    &d3dDevice, (D3D_FEATURE_LEVEL*)0,
                    &d3dDeviceContext);

                hr_fail_ret(-1);

                TEMP_GUID(IID_IDXGIDevice, 0x54ec77fa, 0x1377, 0x44e6, 0x8c, 0x32, 0x88, 0xfd, 0x5f, 0x44, 0xc8, 0x4c);
                com_ptr<IDXGIDevice> dxgiDevice;

                hr = d3dDevice->QueryInterface(IID_IDXGIDevice, (void**)&dxgiDevice);

                hr_fail_ret(-1);

                com_ptr<IDXGIAdapter> pAdapter;

                hr = dxgiDevice->GetAdapter(&pAdapter);

                hr_fail_ret(-1);

                com_ptr<IDXGIOutput> pOutput;

                hr = pAdapter->EnumOutputs(0, &pOutput);

                hr_fail_ret(-1);

                DXGI_SWAP_CHAIN_DESC1 pSwapChainDesc1;
                memset(&pSwapChainDesc1, 0, sizeof(pSwapChainDesc1));

                pSwapChainDesc1.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                char* temp = (char*)&(pSwapChainDesc1.Format);
                *(int*)(temp + 0x08) = 1;
                *(int*)(temp + 0x0c) = 0;
                *(int*)(temp + 0x10) = 0x20;
                *(int*)(temp + 0x14) = 2;
                *(int*)(temp + 0x1c) = 4;
                *(int*)(temp + 0x24) = 2;

                DXGI_SWAP_CHAIN_FULLSCREEN_DESC pSwapChainFullScreenDesc1;

                memset(&pSwapChainFullScreenDesc1, 0, sizeof(pSwapChainFullScreenDesc1));
                pSwapChainFullScreenDesc1.Windowed = 1;

                com_ptr<IDXGISwapChainDWM8> SwapChainDWM8;

                hr = dxgiFactoryDWM8->CreateSwapChainDWM(dxgiDevice.Get(), &pSwapChainDesc1, &pSwapChainFullScreenDesc1,
                    pOutput.Get(), &SwapChainDWM8);

                hr_fail_ret(-1);

                uintptr_t* vtable = *(uintptr_t**)(SwapChainDWM8.Get());

                constexpr size_t present_vt_index[3] = { 23, 16, 8 };
                for (size_t i = 0; i < 3; i++) {
                    uintptr_t present_address = vtable[present_vt_index[i]];

                    hook_fun_address = (char*)present_address;
                    OutputDebugStringA_1Param("[GN]:循环次数：%d", i);

                    MEMORY_BASIC_INFORMATION mem_info;
                    memset(&mem_info, 0, sizeof(mem_info));
                    LI_FN(VirtualQuery)((LPCVOID)hook_fun_address, &mem_info, sizeof(mem_info));
                    hook_fun_memory_proct = mem_info.Protect;

                    PVOID veh_hanle = LI_FN(RtlAddVectoredExceptionHandler)(1, veh_handler);
                    if (!veh_hanle) {
                        ERO_LOG("veh erro");
                        break;
                    }

                    LI_FN(VirtualProtect)
                        ((LPVOID)hook_fun_address, 1, mem_info.Protect | PAGE_GUARD, &hook_fun_memory_proct);

                    int frequency = 0;
                    do {
                        frequency++;
                        LI_FN(Sleep)(16);
                    } while (!hook_fun_ori_address && frequency < 60 * 10);

                    LI_FN(VirtualProtect)((LPVOID)hook_fun_address, 1, mem_info.Protect, &hook_fun_memory_proct);
                    LI_FN(RtlRemoveVectoredExceptionHandler)(veh_hanle);

                    if (hook_fun_ori_address) {
                        break;
                    }
                }
            }
            return hook_fun_ori_address ? 1 : -1;
        }
    };
};


