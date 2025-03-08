#include "d3d11_core.h"


#include "d3d11_buffer.h"
#include "d3d11_layout.h"
#include "d3d11_program.h"
#include "d3d11_sampler.h"
#include "d3d11_shader.h"
#include "d3d11_texture.h"

#include "d3d11_object.h"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


namespace render
{
    d3d11_core::d3d11_core(platform::render* pr)
    {
        platform::win32_render_d3d11* pr_ = static_cast<platform::win32_render_d3d11*>(pr);

        hwnd = pr_->hwnd;

        m_pSwapChain = pr_->m_pSwapChain;
        m_pd3dDevice = pr_->m_pd3dDevice;
        m_pd3dDeviceContext = pr_->m_pd3dDeviceContext;

        m_pd3dRenderTargetView = pr_->m_pd3dRenderTargetView;

        m_pDepthStencilState = pr_->m_pDepthStencilState;
        m_pDepthStencilTexture = pr_->m_pDepthStencilTexture;
        m_pDepthStencilView = pr_->m_pDepthStencilView;


// TODO: generic viewport
        D3D11_VIEWPORT view = { 0 };

        view.TopLeftX   = 0;
        view.TopLeftY   = 0;
        view.Width      = 1280;
        view.Height     = 720;
        view.MinDepth   = 0.0f;
        view.MaxDepth   = 1.0f;

        m_pd3dDeviceContext->RSSetViewports(1, &view);
    }


    d3d11_core::~d3d11_core()
    {
    }


    buffer* d3d11_core::create_buffer(const buffer_desc& desc)
    {
        return new d3d11_buffer(desc, m_pd3dDevice, m_pd3dDeviceContext);
    }


    void d3d11_core::release_buffer(buffer* bye)
    {
        delete bye;
    }



    layout* d3d11_core::create_layout(const layout_desc* desc, int count)
    {
        return new d3d11_layout(desc, count, m_pd3dDevice, m_pd3dDeviceContext);
    }


    void d3d11_core::release_layout(layout* bye)
    {
        delete bye;
    }



    program* d3d11_core::create_program(const program_desc& desc)
    {
        return new d3d11_program(desc, m_pd3dDevice, m_pd3dDeviceContext);
    }


    void d3d11_core::release_program(program* bye)
    {
        delete bye;
    }



    sampler* d3d11_core::create_sampler(const sampler_desc& desc)
    {
        return new d3d11_sampler(desc, m_pd3dDevice, m_pd3dDeviceContext);
    }


    void d3d11_core::release_sampler(sampler* bye)
    {
        delete bye;
    }



    shader* d3d11_core::create_shader(const shader_desc& desc)
    {
        return new d3d11_shader(desc, m_pd3dDevice, m_pd3dDeviceContext);
    }


    void d3d11_core::release_shader(shader* bye)
    {
        delete bye;
    }



    texture* d3d11_core::create_texture(const texture_desc& desc)
    {
        return new d3d11_texture(desc, m_pd3dDevice, m_pd3dDeviceContext);
    }


    void d3d11_core::release_texture(texture* bye)
    {
        delete bye;
    }


    object* d3d11_core::create_object()
    {
        return new d3d11_object(m_pd3dDevice, m_pd3dDeviceContext);
    }


    void d3d11_core::release_object(object* bye)
    {
        delete bye;
    }


    void d3d11_core::depth()
    {
        // TODO: move over from platform
    }


    void d3d11_core::cull()
    {
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

        m_pd3dDevice->CreateRasterizerState(&r_desc, &m_pRasterizerState);
        m_pd3dDeviceContext->RSSetState(m_pRasterizerState);
    }


    void d3d11_core::clear(float r, float g, float b, float a)
    {
        float color[] = { r, g, b, a };

        m_pd3dDeviceContext->ClearRenderTargetView(m_pd3dRenderTargetView, color);
        m_pd3dDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }



    ////////////////////////////////////////////////////////////////////////////////

    void d3d11_core::ImGui_Init()
    {
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(m_pd3dDevice, m_pd3dDeviceContext);
    }


    void d3d11_core::ImGui_NewFrame()
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
    }


    void d3d11_core::ImGui_RenderDrawData(ImDrawData* draw_data)
    {
        ImGui_ImplDX11_RenderDrawData(draw_data);
    }


    void d3d11_core::ImGui_Shutdown()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
    }
}
