#pragma once


#include "platform_render.h"


namespace platform
{
    class opengl_render : public render
    {
    public:
        opengl_render();
        ~opengl_render();

        void clear(float r, float g, float b, float a);
        void cull();
        void depth();
    };
}
