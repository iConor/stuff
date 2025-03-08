#include "win32_render_opengl.h"

#include "win32_window.h"

#include "glad/glad.h"


#define DECLARE_GL_FUNCTION(retval, func, ...) typedef retval (fn_##func)(__VA_ARGS__); extern fn_##func* func
#define DEFINE_GL_FUNCTION(func) fn_##func* func = NULL;


#ifdef _WIN32
#define LOAD_GL_FUNCTION(func) func = (fn_##func *)wglGetProcAddress(#func)
#else
#define LOAD_GL_FUNCTION(func) func = (fn_##func *)SDL_GL_GetProcAddress(#func)
#endif


#define WGL_CONTEXT_MAJOR_VERSION_ARB               0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB               0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB                 0x2093
#define WGL_CONTEXT_FLAGS_ARB                       0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB                0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB                   0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB      0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB            0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB   0x00000002

#define ERROR_INVALID_VERSION_ARB                   0x2095
#define ERROR_INVALID_PROFILE_ARB                   0x2096

DECLARE_GL_FUNCTION(HGLRC, wglCreateContextAttribsARB, HDC, HGLRC, const int*);
DECLARE_GL_FUNCTION(BOOL, wglSwapIntervalEXT, int);

DEFINE_GL_FUNCTION(wglCreateContextAttribsARB);
DEFINE_GL_FUNCTION(wglSwapIntervalEXT);


namespace platform
{
    win32_render_opengl::win32_render_opengl()
    {
        ra = render_api::OpenGL;
    }


    win32_render_opengl::~win32_render_opengl()
    {

    }


    void win32_render_opengl::vsync(int enable)
    {
        wglSwapIntervalEXT(enable);
    }


    void win32_render_opengl::clear()
    {
        glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }


    void win32_render_opengl::swap()
    {
        SwapBuffers(dc);
    }


    void win32_render_opengl::init(window* wndw)
    {
        win32_window* window = static_cast<win32_window*>(wndw);

        hwnd = window->get_hwnd();

        dc = GetDC(hwnd);
        rc = win32_opengl_init(dc);

        gladLoadGL();
    }


    HGLRC win32_render_opengl::win32_opengl_init(HDC device_context)
    {
        HGLRC render_context = win32_opengl_create_context(device_context);

        // Load Windows-specific (wgl) functions
        LOAD_GL_FUNCTION(wglCreateContextAttribsARB);
        LOAD_GL_FUNCTION(wglSwapIntervalEXT);

        render_context = win32_opengl_escalate_context(device_context, render_context);

        return render_context;
    }


    // Creates an old-fashioned OpenGL rendering context
    HGLRC win32_render_opengl::win32_opengl_create_context(HDC device_context)
    {
        PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            24,                     // Color bits
            0, 0, 0, 0, 0, 0,
            8,                      // Alpha bits
            0,
            0,
            0, 0, 0, 0,
            32,                     // Depth bits
            8,                      // Stencil bits
            0,
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        int pixel_format = ChoosePixelFormat(device_context, &pfd);
        SetPixelFormat(device_context, pixel_format, &pfd);

        HGLRC render_context = wglCreateContext(device_context);
        wglMakeCurrent(device_context, render_context);

        return render_context;
    }


    // Creates a modern OpenGL rendering context
    HGLRC win32_render_opengl::win32_opengl_escalate_context(HDC device_context, HGLRC render_context)
    {
        int attrib_list[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,  // WGL_CONTEXT_DEBUG_BIT_ARB
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        HGLRC share_context = 0;
        HGLRC new_context = wglCreateContextAttribsARB(device_context, share_context, attrib_list);

        // If a new context was created, free the old context
        if(new_context)
        {
            wglMakeCurrent(device_context, new_context);
            wglDeleteContext(render_context);
            render_context = new_context;
        }

        return render_context;
    }
}
