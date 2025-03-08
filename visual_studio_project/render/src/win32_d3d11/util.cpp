#include "util.h"


namespace render
{
    void util::clear(float r, float g, float b, float a)
    {
        float clear_color = { r, g, b, a };

        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
    }
}
