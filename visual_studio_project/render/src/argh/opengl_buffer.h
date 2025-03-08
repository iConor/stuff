#pragma once


#include "renderer_buffer.h"

#include "glad/glad.h"


namespace renderer
{
    class opengl_buffer : public buffer
    {
    public:
        opengl_buffer(buffer_desc desc);
        ~opengl_buffer();

        GLuint get_id();
        void sub(void* data);

        void bind_uniform_block(const int block_binding);
    private:
        void create(buffer_desc desc);
        void destroy();

        static GLenum translate(buffer_type bt);


        GLuint id = 0;

        GLenum target;

        int size;
    };
}
