#pragma once


#include "shader.h"


#include "glad/glad.h"


namespace render
{
    class opengl_shader : public shader
    {
    public:
        opengl_shader(const shader_desc& desc);
        ~opengl_shader();

        GLuint get_id();
    private:
        shader_type type;
        GLuint id;

        static GLenum translate(shader_type st);
    };
}
