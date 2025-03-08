#include "opengl_buffer.h"


namespace render
{
    opengl_buffer::opengl_buffer(const buffer_desc& desc)
    {
        type = desc.type;
        size = desc.size;

        target = translate(type);

        glGenBuffers(1, &id);
        glBindBuffer(target, id);
        glBufferData(target, size, nullptr, GL_STATIC_DRAW);
        if(desc.data)
        {
            glBufferSubData(target, 0, size, desc.data);
        }
        // glBindBuffer(target, 0);  // TODO: can't unbind this when attaching to a VAO
    }


    opengl_buffer::~opengl_buffer()
    {
        glDeleteBuffers(1, &id);
    }


    void opengl_buffer::sub(const void* data)
    {
        glBindBuffer(target, id);
        glBufferSubData(target, 0, size, data);
        glBindBuffer(target, 0);
    }


    GLenum opengl_buffer::translate(buffer_type bt)
    {
        switch(bt)
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
