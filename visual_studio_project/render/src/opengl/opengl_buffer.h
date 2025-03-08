#pragma once


#include "buffer.h"


#include "glad/glad.h"


namespace render
{
    class opengl_buffer : public buffer
    {
    public:
        opengl_buffer(const buffer_desc& desc);
        ~opengl_buffer();

        void sub(const void* data) override;

        void bind_uniform_block(const int block_binding) override;

    private:
        buffer_type type;
        int size;

        GLuint id;
        GLenum target;

        GLenum translate(buffer_type bt);
    };
}
