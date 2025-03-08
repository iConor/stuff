#include "opengl_object.h"


namespace render
{
    opengl_object::opengl_object()
    {
        glGenVertexArrays(1, &vao);
    }


    opengl_object::~opengl_object()
    {
        glDeleteVertexArrays(1, &vao);
    }


    void opengl_object::bind()
    {
        glBindVertexArray(vao);
    }


    void opengl_object::unbind()
    {
        glBindVertexArray(0);
    }


    void opengl_object::bind_vbuf(buffer* vb)
    {
    }


    void opengl_object::bind_ibuf(buffer* ib)
    {
    }


    void opengl_object::bind_layout(layout* lo)
    {

    }


    void opengl_object::draw(int count)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }
}
