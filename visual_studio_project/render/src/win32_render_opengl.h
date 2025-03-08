#pragma once


#include "platform_render.h"

#include <windows.h>


namespace platform
{
    class win32_render_opengl : public render
    {
    public:
        win32_render_opengl();
        ~win32_render_opengl();

        void init(window* wndw) override;

        void vsync(int enable) override;
        void clear() override;
        void swap() override;

        HWND hwnd;
    private:
        HDC dc;
        HGLRC rc;

        HGLRC win32_opengl_init(HDC device_context);
        HGLRC win32_opengl_create_context(HDC device_context);
        HGLRC win32_opengl_escalate_context(HDC device_context, HGLRC render_context);
    };
}
