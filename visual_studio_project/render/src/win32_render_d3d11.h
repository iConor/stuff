#pragma once


#include "platform_render.h"

#include <d3d11.h>


namespace platform
{
    class win32_render_d3d11 : public render
    {
    public:
        win32_render_d3d11();
        ~win32_render_d3d11();

        void init(window* wndw) override;

        void vsync(int enable) override;
        void clear() override;
        void swap() override;

    // private:
        HWND hwnd;

        int                         m_bVsync;

        IDXGISwapChain*             m_pSwapChain;
        ID3D11Device*               m_pd3dDevice;
        ID3D11DeviceContext*        m_pd3dDeviceContext;

        ID3D11RenderTargetView*     m_pd3dRenderTargetView;

        ID3D11DepthStencilState*    m_pDepthStencilState;
        ID3D11Texture2D*            m_pDepthStencilTexture;
        ID3D11DepthStencilView*     m_pDepthStencilView;
    };
}
