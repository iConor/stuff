#include "opengl_buffer.h"


namespace renderer
{
    opengl_buffer::opengl_buffer(buffer_desc desc)
    {
        create(desc);
    }


    opengl_buffer::~opengl_buffer()
    {
        destroy();
    }


    void opengl_buffer::create(buffer_desc desc)
    {
        target = translate(desc.type);
        size = desc.size;

        glGenBuffers(1, &id);
        glBindBuffer(target, id);
        glBufferData(target, desc.size, nullptr, GL_STATIC_DRAW);
        glBufferSubData(target, 0, desc.size, desc.data);
        // glBindBuffer(target, 0);  // TODO: can't unbind this when attaching to a VAO
    }


    void opengl_buffer::destroy()
    {
        glDeleteBuffers(1, &id);
    }


    void opengl_buffer::sub(void* data)
    {
        glBindBuffer(target, id);
        glBufferSubData(target, 0, size, data);
        glBindBuffer(target, 0);
    }


    GLuint opengl_buffer::get_id()
    {
        return id;
    }


    GLenum opengl_buffer::translate(buffer_type type)
    {
        switch(type)
        {
            case buffer_type::vertex:   return GL_ARRAY_BUFFER;
            case buffer_type::index:    return GL_ELEMENT_ARRAY_BUFFER;
            case buffer_type::uniform:  return GL_UNIFORM_BUFFER;
        }
        return 0;
    }


    void opengl_buffer::bind_uniform_block(const int block_binding)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, block_binding, id);
    }
}
