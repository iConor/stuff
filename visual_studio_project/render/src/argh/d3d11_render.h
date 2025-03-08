#pragma once


#include "platform_render.h"


namespace platform
{
    class d3d11_render : public render
    {
    public:
        d3d11_render();
        ~d3d11_render();

        void clear(float r, float g, float b, float a);
        void cull();
        void depth();
    };
}
