#pragma once


#include <windows.h>
#include "platform_window.h"


namespace platform
{
    class win32_window : public window
    {
    public:
        win32_window();
        ~win32_window();

        void show() override;
        bool msgs() override;

        HWND get_hwnd();

    private:
        void create() override;
        void destroy() override;

        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        HWND hwnd;
    };
}
