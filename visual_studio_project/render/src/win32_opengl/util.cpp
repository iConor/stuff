#include "util.h"

#include "glad/glad.h"

// #include "windows.h"
// #include "gl/gl.h"

namespace render
{
    void util::clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }


    void util::cull()
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    void util::depth()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1.0f);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
