#include "win32_d3d11.h"


static IDXGISwapChain*          g_pSwapChain            = NULL;

static ID3D11Device*            g_pd3dDevice            = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext     = NULL;
static ID3D11RenderTargetView*  g_pd3dRenderTargetView  = NULL;

static ID3D11RasterizerState*   g_pRasterizerState      = NULL;
static ID3D11DepthStencilState* g_pDepthStencilState    = NULL;

static ID3D11Texture2D*         g_pDepthStencilTexture  = NULL;
static ID3D11DepthStencilView*  g_pDepthStencilView     = NULL;


static int g_bVsync = 1; // on/off 1/0


bool d3d11_init(HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC swap_chain = { 0 };

    swap_chain.BufferDesc.Width     = 0;
    swap_chain.BufferDesc.Height    = 0;
    swap_chain.BufferDesc.RefreshRate.Numerator     = 60;
    swap_chain.BufferDesc.RefreshRate.Denominator   = 1;
    swap_chain.BufferDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
    // swap_chain.BufferDesc.ScanlineOrdering  = 0;
    // swap_chain.BufferDesc.Scaling           = 0;

    swap_chain.SampleDesc.Count     = 1;
    swap_chain.SampleDesc.Quality   = 0;

    swap_chain.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain.BufferCount  = 2;
    swap_chain.OutputWindow = hwnd;
    swap_chain.Windowed     = TRUE;
    swap_chain.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain.Flags        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

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
        &swap_chain,
        &g_pSwapChain,
        &g_pd3dDevice,
        &feature_level,
        &g_pd3dDeviceContext
    );

    if( result != S_OK )
        return false;

    d3d11_create_render_target();


    D3D11_RASTERIZER_DESC r_desc = { 0 };

    r_desc.FillMode                 = D3D11_FILL_SOLID;
    r_desc.CullMode                 = D3D11_CULL_BACK;
    r_desc.FrontCounterClockwise    = TRUE;
    r_desc.DepthBias                = 0;
    r_desc.DepthBiasClamp           = 0.0f;
    r_desc.SlopeScaledDepthBias     = 0.0f;
    r_desc.DepthClipEnable          = TRUE;
    r_desc.ScissorEnable            = FALSE;
    r_desc.MultisampleEnable        = FALSE;
    r_desc.AntialiasedLineEnable    = FALSE;

    g_pd3dDevice->CreateRasterizerState(&r_desc, &g_pRasterizerState);
    g_pd3dDeviceContext->RSSetState(g_pRasterizerState);


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
    //
    // ds_desc.BackFace.StencilFailOp          = D3D11_STENCIL_OP_KEEP;
    // ds_desc.BackFace.StencilDepthFailOp     = D3D11_STENCIL_OP_KEEP;
    // ds_desc.BackFace.StencilPassOp          = D3D11_STENCIL_OP_KEEP;
    // ds_desc.BackFace.StencilFunc            = D3D11_COMPARISON_ALWAYS;

    g_pd3dDevice->CreateDepthStencilState(&ds_desc, &g_pDepthStencilState);
    g_pd3dDeviceContext->OMSetDepthStencilState(g_pDepthStencilState, 0);


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

    g_pd3dDevice->CreateTexture2D(&ds_tex_desc, NULL, &g_pDepthStencilTexture);


    D3D11_DEPTH_STENCIL_VIEW_DESC ds_view_desc = { 0 };

    ds_view_desc.Format             = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    ds_view_desc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
    // ds_view_desc.Flags              = ;
    ds_view_desc.Texture2D.MipSlice = 0;

    g_pd3dDevice->CreateDepthStencilView(g_pDepthStencilTexture, &ds_view_desc, &g_pDepthStencilView);

    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_pd3dRenderTargetView, g_pDepthStencilView);


    D3D11_VIEWPORT view = { 0 };

    view.TopLeftX   = 0;
    view.TopLeftY   = 0;
    view.Width      = 1280;
    view.Height     = 720;
    view.MinDepth   = 0.0f;
    view.MaxDepth   = 1.0f;

    g_pd3dDeviceContext->RSSetViewports(1, &view);

    return true;
}


void d3d11_exit()
{
    d3d11_destroy_render_target();
    if( g_pSwapChain )          { g_pSwapChain->Release();          g_pSwapChain = NULL; }
    if( g_pd3dDeviceContext )   { g_pd3dDeviceContext->Release();   g_pd3dDeviceContext = NULL; }
    if( g_pd3dDevice )          { g_pd3dDevice->Release();          g_pd3dDevice = NULL; }
}


void d3d11_create_render_target()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pd3dRenderTargetView);
    pBackBuffer->Release();

    // g_pd3dDeviceContext->OMSetRenderTargets(1, &g_pd3dRenderTargetView, NULL);
}


void d3d11_destroy_render_target()
{
    if ( g_pd3dRenderTargetView ) { g_pd3dRenderTargetView->Release(); g_pd3dRenderTargetView = NULL; }
}


void d3d11_vsync(int enable)
{
    g_bVsync = enable;
}


void d3d11_clear(float* color)
{
    g_pd3dDeviceContext->ClearRenderTargetView(g_pd3dRenderTargetView, color);
    g_pd3dDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}


void d3d11_swap()
{
    g_pSwapChain->Present(g_bVsync, 0);
}


ID3D11Device* d3d11_get_device()
{
    return g_pd3dDevice;
}


ID3D11DeviceContext* d3d11_get_device_context()
{
    return g_pd3dDeviceContext;
}
