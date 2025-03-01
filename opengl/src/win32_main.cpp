#include <windows.h>

#include "engine_types.h"

#include "win32_opengl_init.h"

// Example window
#include "example.cpp"

// Single compilation unit build
#include "win32_opengl_init.cpp"
#include "opengl_init.cpp"


static bool global_running;
static WINDOWPLACEMENT global_window_placement = { sizeof(global_window_placement) };


LRESULT CALLBACK win32_main_window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static void win32_process_messages();
static void win32_toggle_fullscreen(HWND hwnd);

static s64 win32_performance_counter();
static s64 win32_performance_frequency();

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
    WNDCLASSEXA window_class = {};

    window_class.cbSize = sizeof(WNDCLASSEXA);
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = win32_main_window_callback;
    window_class.hInstance = hInstance;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.lpszClassName = "Default Class Name";

    if(!RegisterClassExA(&window_class))
    {
        return -1; //TODO: win32_last_error("RegisterClassExA");
    }

    HWND window = CreateWindowExA(0L,
                                  window_class.lpszClassName,
                                  "Default Window Name",
                                  WS_OVERLAPPEDWINDOW,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  NULL,
                                  NULL,
                                  hInstance,
                                  NULL);

    if(!window)
    {
        return -1; //TODO: win32_last_error("CreateWindowExA");
    }

    HDC device_context = GetDC(window);
    win32_toggle_fullscreen(window);
    HGLRC render_context = win32_opengl_init(device_context);

    wglSwapIntervalEXT(1); // vsync on/off 1/0

    ShowWindow(window, SW_SHOW);

    example_setup();

    global_running = true;

    s64 performance_frequency = win32_performance_frequency();
    s64 last_counter = win32_performance_counter();
    while(global_running)
    {
        win32_process_messages();

        example_loop();

        SwapBuffers(device_context);

        s64 end_counter = win32_performance_counter();
        s64 elapsed_counter = end_counter - last_counter;
        last_counter = end_counter;
    }

    // TODO: Exit gracefully!
    // wglDeleteContext(render_context);
    // ReleaseDC(window, device_context);
    // DestroyWindow(window);
    // ExitProcess(0);

    return 0;
}

// WindowProc
LRESULT CALLBACK win32_main_window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch(uMsg)
    {
        case WM_CLOSE:
        case WM_DESTROY:
        {
            global_running = false;
        } break;

        case WM_SIZE:
        {
            RECT viewport;
            if(GetClientRect(hwnd, &viewport))
            {
                int width = viewport.right - viewport.left;
                int height = viewport.bottom - viewport.top;
                glViewport(0, 0, width, height);
            }
        } break;

        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC device_context = BeginPaint(hwnd, &paint);
            EndPaint(hwnd, &paint);
        } break;

        default:
        {
            result = DefWindowProcA(hwnd, uMsg, wParam, lParam);
        } break;
    }
    return result;
}


static void win32_process_messages()
{
    MSG msg;
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        switch(msg.message)
        {
            case WM_QUIT:
            {
                global_running = false;
            } break;

            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            {
                int vk_code = (int)msg.wParam;
                int vk_bits = (int)msg.lParam;

                bool alt_down = (vk_bits & (1 << 29)) != 0;
                bool was_down = (vk_bits & (1 << 30)) != 0;
                bool is_down = (vk_bits & (1 << 31)) == 0;

                if(is_down && !was_down)
                {
                    if(vk_code == VK_LBUTTON)
                    {
                    }
                    else if(vk_code == VK_RBUTTON)
                    {
                    }
                    else if(vk_code == VK_MBUTTON)
                    {
                    }
                    else if(vk_code == VK_ESCAPE)
                    {
                    }
                    else if(vk_code == VK_SPACE)
                    {
                    }
                    else if(vk_code == VK_LEFT)
                    {
                    }
                    else if(vk_code == VK_UP)
                    {
                    }
                    else if(vk_code == VK_RIGHT)
                    {
                    }
                    else if(vk_code == VK_DOWN)
                    {
                    }
                    else if(vk_code == 'A')
                    {
                    }
                    else if(vk_code == 'D')
                    {
                    }
                    else if(vk_code == 'E')
                    {
                    }
                    else if(vk_code == 'F')
                    {
                        win32_toggle_fullscreen(msg.hwnd);

                        RECT viewport;
                        if(GetClientRect(msg.hwnd, &viewport))
                        {
                            int w = viewport.right - viewport.left;
                            int h = viewport.bottom - viewport.top;
                            glViewport(0, 0, w, h);
                        }
                    }
                    else if(vk_code == 'Q')
                    {
                    }
                    else if(vk_code == 'S')
                    {
                    }
                    else if(vk_code == 'W')
                    {
                    }
                }

                if(vk_code == VK_F4 && alt_down)
                {
                    global_running = false;
                }
            } break;
            default:
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } break;
        }
    }
}

static s64 win32_performance_counter()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.QuadPart;
}

static s64 win32_performance_frequency()
{
    LARGE_INTEGER frequency;
    QueryPerformanceCounter(&frequency);
    return frequency.QuadPart;
}

static void win32_toggle_fullscreen(HWND hwnd)
{
    DWORD window_style = GetWindowLong(hwnd, GWL_STYLE);

    if(window_style & WS_OVERLAPPEDWINDOW)
    {
        HMONITOR monitor_handle = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);

        MONITORINFO monitor_info = {};
        monitor_info.cbSize = sizeof(monitor_info);

        BOOL got_monitor = GetMonitorInfo(monitor_handle, &monitor_info);
        BOOL got_window = GetWindowPlacement(hwnd, &global_window_placement);

        if(got_monitor && got_window)
        {
            SetWindowLong(hwnd, GWL_STYLE, window_style & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(hwnd, HWND_TOP,
                         monitor_info.rcMonitor.left,
                         monitor_info.rcMonitor.top,
                         monitor_info.rcMonitor.right - monitor_info.rcMonitor.left,
                         monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top,
                         SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }
    }
    else
    {
        SetWindowPlacement(hwnd, &global_window_placement);
        SetWindowLong(hwnd, GWL_STYLE, window_style | WS_OVERLAPPEDWINDOW);
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                     SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
}
