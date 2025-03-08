#include "win32_window.h"


#include "imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace platform
{
    win32_window::win32_window()
    {
        create();
    }


    win32_window::~win32_window()
    {
        destroy();
    }


    HWND win32_window::get_hwnd()
    {
        return hwnd;
    }


    void win32_window::create()
    {
        // FreeConsole();

        WNDCLASSEX wndclass_ex = { 0 };

        wndclass_ex.cbSize           = sizeof(WNDCLASSEX);
        wndclass_ex.style            = CS_CLASSDC;
        wndclass_ex.lpfnWndProc      = WindowProc;
        wndclass_ex.cbClsExtra       = 0L;
        wndclass_ex.cbWndExtra       = 0L;
        wndclass_ex.hInstance        = GetModuleHandle(NULL);
        wndclass_ex.hIcon            = NULL;
        wndclass_ex.hCursor          = LoadCursor(NULL, IDC_ARROW);
        wndclass_ex.hbrBackground    = NULL;
        wndclass_ex.lpszMenuName     = NULL;
        wndclass_ex.lpszClassName    = "ClassName";
        wndclass_ex.hIconSm          = NULL;

        RegisterClassEx(&wndclass_ex);

        RECT    rect        = { 0, 0, 1280, 720 };
        DWORD   style       = WS_OVERLAPPEDWINDOW;
        BOOL    menu        = FALSE;
        DWORD   style_ex    = 0L;

        AdjustWindowRectEx(&rect, style, menu, style_ex);

        hwnd = CreateWindowEx(
            style_ex,
            wndclass_ex.lpszClassName,
            "WindowName",
            style,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rect.right - rect.left,
            rect.bottom - rect.top,
            NULL,
            NULL,
            wndclass_ex.hInstance,
            NULL
        );
    }


    void win32_window::destroy()
    {
        DestroyWindow(hwnd);
        // TODO: Is it worth storing wndclass_ex, or is there another way?
        // UnregisterClass(wndclass_ex.lpszClassName, wndclass_ex.hInstance);
    }

    void win32_window::show()
    {
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);
    }


    bool win32_window::msgs()
    {
        bool received_quit = false;

        MSG msg;
        while(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            switch(msg.message)
            {
            case WM_QUIT:
                received_quit = true;
                break;
            default:
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                break;
            }
        }

        return received_quit;
    }
    // Forward declare message handler from imgui_impl_win32.cpp
    // extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK win32_window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
            return true;

        switch(uMsg)
        {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}
