#include "opengl_render.h"


#include "glad/glad.h"


namespace platform
{
    opengl_render::opengl_render()
    {
        cull();
        depth();
    }


    opengl_render::~opengl_render()
    {
    }

    void opengl_render::clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    void opengl_render::cull()
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

    }

    void opengl_render::depth()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1.0f);
    }
}
