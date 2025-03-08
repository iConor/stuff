#include "d3d11_render.h"


namespace platform
{
    d3d11_render::d3d11_render()
    {
    }


    d3d11_render::~d3d11_render()
    {
    }


    void d3d11_render::clear(float r, float g, float b, float a)
    {
        float clear_color[] = { r, g, b, a };

        // g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        // g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);

        // g_pd3dDeviceContext->ClearRenderTargetView(g_pd3dRenderTargetView, color);
        // g_pd3dDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }


    void d3d11_render::cull()
    {
        // set in rasterizer
    }


    void d3d11_render::depth()
    {
        // gotta create a depthstencil state, texture, view...
    }


}
