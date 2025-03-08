#pragma once


#include "glad/glad.h"


namespace render
{

    class shader
    {
    private:
        GLuint program;
        GLuint vertex_shader;
        GLuint fragment_shader;

    public:
        shader(const char* vertex_source, const char* fragment_source);
        ~shader();

        GLuint id();

    private:
        GLuint gl_create_shader(GLenum shader_type, const char* shader_source);
        void gl_create_program(const GLchar* vertex_source, const GLchar* fragment_source);
        void gl_destroy_program();

        bool gl_check_program(GLuint handle, const char* label);
        bool gl_check_shader(GLuint handle, const char* label);
    };


}
