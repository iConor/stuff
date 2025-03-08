#include "win32_render_d3d11.h"

#include "win32_window.h"


namespace platform
{
    win32_render_d3d11::win32_render_d3d11()
    {
        ra = render_api::Direct3D11;
    }


    win32_render_d3d11::~win32_render_d3d11()
    {
    }


    void win32_render_d3d11::vsync(int enable)
    {
        m_bVsync = enable;
    }


    void win32_render_d3d11::clear()
    {
        float color[] = { 0.0f, 0.0f, 0.5f, 1.0f };

        m_pd3dDeviceContext->ClearRenderTargetView(m_pd3dRenderTargetView, color);
        m_pd3dDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }


    void win32_render_d3d11::swap()
    {
        m_pSwapChain->Present(m_bVsync, 0);
    }


    void win32_render_d3d11::init(window* wndw)
    {
        win32_window* window = static_cast<win32_window*>(wndw);
        hwnd = window->get_hwnd();

        m_bVsync = 1;

////
        DXGI_SWAP_CHAIN_DESC sc_desc = { 0 };

        sc_desc.BufferDesc.Width     = 0;
        sc_desc.BufferDesc.Height    = 0;
        sc_desc.BufferDesc.RefreshRate.Numerator     = 60;
        sc_desc.BufferDesc.RefreshRate.Denominator   = 1;
        sc_desc.BufferDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
        // sc_desc.BufferDesc.ScanlineOrdering  = 0;
        // sc_desc.BufferDesc.Scaling           = 0;

        sc_desc.SampleDesc.Count     = 1;
        sc_desc.SampleDesc.Quality   = 0;

        sc_desc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sc_desc.BufferCount  = 2;
        sc_desc.OutputWindow = hwnd;
        sc_desc.Windowed     = TRUE;
        sc_desc.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
        sc_desc.Flags        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        UINT flags = 0; // D3D11_CREATE_DEVICE_DEBUG;
        D3D_FEATURE_LEVEL feature_priority[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };

        D3D_FEATURE_LEVEL feature_level;
        HRESULT result = D3D11CreateDeviceAndSwapChain(
            NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            flags,
            feature_priority,
            sizeof(feature_priority) / sizeof(feature_priority[0]),
            D3D11_SDK_VERSION,
            &sc_desc,
            &m_pSwapChain,
            &m_pd3dDevice,
            &feature_level,
            &m_pd3dDeviceContext
        );

        // if( result != S_OK )
        //     return false;

//// create_render_target
        ID3D11Texture2D* pBackBuffer;
        m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pd3dRenderTargetView);
        pBackBuffer->Release();

//// depth/stencil state
        D3D11_DEPTH_STENCIL_DESC ds_desc = { 0 };

        ds_desc.DepthEnable                     = TRUE;
        ds_desc.DepthWriteMask                  = D3D11_DEPTH_WRITE_MASK_ALL;
        ds_desc.DepthFunc                       = D3D11_COMPARISON_LESS_EQUAL;
        ds_desc.StencilEnable                   = FALSE;
        ds_desc.StencilReadMask                 = D3D11_DEFAULT_STENCIL_READ_MASK;
        ds_desc.StencilWriteMask                = D3D11_DEFAULT_STENCIL_WRITE_MASK;

        // ds_desc.FrontFace.StencilFailOp         = D3D11_STENCIL_OP_KEEP;
        // ds_desc.FrontFace.StencilDepthFailOp    = D3D11_STENCIL_OP_KEEP;
        // ds_desc.FrontFace.StencilPassOp         = D3D11_STENCIL_OP_KEEP;
        // ds_desc.FrontFace.StencilFunc           = D3D11_COMPARISON_ALWAYS;

        // ds_desc.BackFace.StencilFailOp          = D3D11_STENCIL_OP_KEEP;
        // ds_desc.BackFace.StencilDepthFailOp     = D3D11_STENCIL_OP_KEEP;
        // ds_desc.BackFace.StencilPassOp          = D3D11_STENCIL_OP_KEEP;
        // ds_desc.BackFace.StencilFunc            = D3D11_COMPARISON_ALWAYS;

        m_pd3dDevice->CreateDepthStencilState(&ds_desc, &m_pDepthStencilState);
        m_pd3dDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 0);

//// depth/stencil buffer
        D3D11_TEXTURE2D_DESC ds_tex_desc = { 0 };

        ds_tex_desc.Width              = 1280;
        ds_tex_desc.Height             = 720;
        ds_tex_desc.MipLevels          = 1;
        ds_tex_desc.ArraySize          = 1;
        ds_tex_desc.Format             = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
        // ds_tex_desc.Format             = ;
        ds_tex_desc.SampleDesc.Count   = 1;
        ds_tex_desc.SampleDesc.Quality = 0;
        ds_tex_desc.Usage              = D3D11_USAGE_DEFAULT;
        ds_tex_desc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
        ds_tex_desc.CPUAccessFlags     = 0;
        ds_tex_desc.MiscFlags          = 0;

        m_pd3dDevice->CreateTexture2D(&ds_tex_desc, NULL, &m_pDepthStencilTexture);


        D3D11_DEPTH_STENCIL_VIEW_DESC ds_view_desc = { 0 };

        ds_view_desc.Format             = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
        ds_view_desc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
        // ds_view_desc.Flags              = ;
        ds_view_desc.Texture2D.MipSlice = 0;

        m_pd3dDevice->CreateDepthStencilView(m_pDepthStencilTexture, &ds_view_desc, &m_pDepthStencilView);

        m_pd3dDeviceContext->OMSetRenderTargets(1, &m_pd3dRenderTargetView, m_pDepthStencilView);
    }
}
