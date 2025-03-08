#pragma once


#include "core.h"


#include "win32_render_d3d11.h"


namespace render
{
    class d3d11_core : public core
    {
    public:
        d3d11_core(platform::render* pr);
        ~d3d11_core();

////////////////////////////////////////////////////////////////////////////////

        buffer* create_buffer(const buffer_desc& desc) override;
        void release_buffer(buffer* bye) override;

        layout* create_layout(const layout_desc* desc, int count) override;
        void release_layout(layout* bye) override;

        program* create_program(const program_desc& desc) override;
        void release_program(program* bye) override;

        sampler* create_sampler(const sampler_desc& desc) override;
        void release_sampler(sampler* bye) override;

        shader* create_shader(const shader_desc& desc) override;
        void release_shader(shader* bye) override;

        texture* create_texture(const texture_desc& desc) override;
        void release_texture(texture* bye) override;


        object* create_object() override;
        void release_object(object* bye) override;

////////////////////////////////////////////////////////////////////////////////

        void depth() override;
        void cull() override;
        void clear(float r, float g, float b, float a) override;

////////////////////////////////////////////////////////////////////////////////

        void ImGui_Init() override;
        void ImGui_NewFrame() override;
        void ImGui_RenderDrawData(ImDrawData* draw_data) override;
        void ImGui_Shutdown() override;



////////////////////////////////////////////////////////////////////////////////
// TODO: this is bad, don't leave it

    // copy of platform renderer for temp initialization
    private:
        HWND hwnd;

        int                         m_bVsync;

// TEMP: globals to mimic opengl for now
        IDXGISwapChain*             m_pSwapChain;
        ID3D11Device*               m_pd3dDevice;
        ID3D11DeviceContext*        m_pd3dDeviceContext;

        ID3D11RenderTargetView*     m_pd3dRenderTargetView;

        ID3D11DepthStencilState*    m_pDepthStencilState;
        ID3D11Texture2D*            m_pDepthStencilTexture;
        ID3D11DepthStencilView*     m_pDepthStencilView;

////////////////////////////////////////////////////////////////////////////////

        ID3D11RasterizerState*   m_pRasterizerState;

    };
}
