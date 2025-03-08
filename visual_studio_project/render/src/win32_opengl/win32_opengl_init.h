#ifndef WIN32_OPENGL_INIT_H
#define WIN32_OPENGL_INIT_H


#include <windows.h>


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

HGLRC win32_opengl_init(HDC device_context);
HGLRC win32_opengl_create_context(HDC device_context);
HGLRC win32_opengl_escalate_context(HDC device_context, HGLRC render_context);

#endif /* WIN32_OPENGL_INIT_H */
