#include "platform_render.h"


#include "win32_render_opengl.h"
#include "win32_render_d3d11.h"


namespace platform
{
    render* render::load(render_api name)
    {
        switch(name)
        {
            case render_api::OpenGL:        return new win32_render_opengl();
            case render_api::Direct3D11:    return new win32_render_d3d11();
        }
        return nullptr;
    }
}
