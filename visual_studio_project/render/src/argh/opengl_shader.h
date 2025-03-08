#pragma once


#include "renderer_shader.h"

#include "glad/glad.h"


namespace renderer
{
    class opengl_shader : public shader
    {
    public:
        opengl_shader(shader_desc desc);
        ~opengl_shader();

        GLuint get_id();

    private:
        void create(shader_desc desc);
        void destroy();

        bool check();

        static GLenum translate(shader_type st);

        GLuint id = 0;
        GLenum type;
    };
}
