#include "core.h"


#include "opengl/opengl_core.h"
#include "d3d11/d3d11_core.h"


namespace render
{
    // core::core()
    // {
    // }
    //
    //
    // core::~core()
    // {
    // }


    core* core::load(platform::render* pr)
    {
        switch(pr->ra)
        {
            case platform::render_api::OpenGL:        return new opengl_core(pr);
            case platform::render_api::Direct3D11:    return new d3d11_core(pr);
        }
        return nullptr;
    }
}
