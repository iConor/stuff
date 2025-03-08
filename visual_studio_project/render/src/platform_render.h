#pragma once


#include "platform_window.h"


namespace platform
{
    enum class render_api
    {
        OpenGL,
        Direct3D11,
    };

    class render
    {
    public:
        static render* load(render_api name);

        virtual void init(window* wndw) = 0;

        virtual void vsync(int enable) = 0; // vsync on/off 1/0
        virtual void clear() = 0;
        virtual void swap() = 0;

        render_api ra;
    };
}
