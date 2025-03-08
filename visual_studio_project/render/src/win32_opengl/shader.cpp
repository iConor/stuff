#include "shader.h"

#include <stdio.h>


namespace render
{

shader::shader(const GLchar* vertex_source, const GLchar* fragment_source)
{
    gl_create_program(vertex_source, fragment_source);
}


shader::~shader()
{
    gl_destroy_program();
}


GLuint shader::id()
{
    return program;
}


GLuint shader::gl_create_shader(GLenum shader_type, const char* shader_source)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
#if RENDER_DEBUG
    gl_check_shader(shader);
#endif
    return shader;
}


void shader::gl_create_program(const GLchar* vertex_source, const GLchar* fragment_source)
{
    vertex_shader = gl_create_shader(GL_VERTEX_SHADER, vertex_source);
    fragment_shader = gl_create_shader(GL_FRAGMENT_SHADER, fragment_source);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
#if RENDER_DEBUG
    gl_check_program(program);
#endif
}


bool shader::gl_check_shader(GLuint handle, const char* label)
{
    GLint status = 0;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    if((GLboolean)status != GL_TRUE)
    {
        fprintf(stderr, "ERROR: (check_shader) %s", label);
    }
    else
    {
        fprintf(stderr, "INFO: (check_shader) %s", label);
    }

    GLint log_length = 0;
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 0)
    {
        char* buffer = new char[log_length];
        glGetShaderInfoLog(handle, log_length, NULL, (GLchar*)buffer);
        fprintf(stderr, "%s", buffer);
        delete buffer;
    }

    fprintf(stderr, "\n");

    return (GLboolean)status == GL_TRUE;
}


bool shader::gl_check_program(GLuint handle, const char* label)
{
    GLint status = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    if((GLboolean)status != GL_TRUE)
    {
        fprintf(stderr, "ERROR: (check_program) %s", label);
    }
    else
    {
        fprintf(stderr, "INFO: (check_program) %s", label);
    }

    GLint log_length = 0;
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 0)
    {
        char* buffer = new char[log_length];
        glGetProgramInfoLog(handle, log_length, NULL, (GLchar*)buffer);
        fprintf(stderr, "%s", buffer);
        delete buffer;
    }

    fprintf(stderr, "\n");

    return (GLboolean)status == GL_TRUE;
}


void shader::gl_destroy_program()
{
    if(program)
    {
        if(vertex_shader)
        {
            glDetachShader(program, vertex_shader);
            vertex_shader = 0;
        }

        if(fragment_shader)
        {
            glDetachShader(program, fragment_shader);
            fragment_shader = 0;
        }

        program = 0;
    }
}


}
