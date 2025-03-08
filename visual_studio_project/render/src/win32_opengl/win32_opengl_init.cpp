#include "win32_opengl_init.h"


DEFINE_GL_FUNCTION(wglCreateContextAttribsARB);
DEFINE_GL_FUNCTION(wglSwapIntervalEXT);


HGLRC win32_opengl_init(HDC device_context)
{
    HGLRC render_context = win32_opengl_create_context(device_context);

    // Load Windows-specific (wgl) functions
    LOAD_GL_FUNCTION(wglCreateContextAttribsARB);
    LOAD_GL_FUNCTION(wglSwapIntervalEXT);

    render_context = win32_opengl_escalate_context(device_context, render_context);

    return render_context;
}


// Creates an old-fashioned OpenGL rendering context
HGLRC win32_opengl_create_context(HDC device_context)
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
HGLRC win32_opengl_escalate_context(HDC device_context, HGLRC render_context)
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
