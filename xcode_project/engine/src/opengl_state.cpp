#include "opengl_state.h"


void opengl_viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glViewport(x, y, width, height);
}


void opengl_depth_enable(GLuint enable)
{
    if(enable)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}


void opengl_depth_func(GLenum func)
{
    glDepthFunc(func);
}


// Determines whether the depth buffer can be written to
void opengl_depth_mask(GLboolean mask)
{
    glDepthMask(mask);
}


void opengl_stencil_enable(GLuint enable)
{
    if(enable)
    {
        glEnable(GL_STENCIL_TEST);
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
    }
}


void opengl_stencil_func(GLenum func, GLint ref, GLuint mask)
{
    glStencilFunc(func, ref, mask);
}


void opengl_stencil_mask(GLuint mask)
{
    glStencilMask(mask);
}


void opengl_stencil_op(GLenum sfail, GLenum dpfail, GLenum dppass)
{
    glStencilOp(sfail, dpfail, dppass);
}


void opengl_blend_enable(GLuint enable)
{
    if(enable)
    {
        glEnable(GL_BLEND);
    }
    else
    {
        glDisable(GL_BLEND);
    }
}


void opengl_blend_func(GLenum sfactor, GLenum dfactor)
{
    glBlendFunc(sfactor, dfactor);
}


void opengl_cull_enable(GLuint enable)
{
    if(enable)
    {
        glEnable(GL_CULL_FACE);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
}


void opengl_cull_face(GLenum mode)
{
    glCullFace(mode);
}


void opengl_cull_front(GLenum mode)
{
    glFrontFace(mode);
}


void opengl_wireframe_mode(GLuint enable)
{
    if(enable)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
