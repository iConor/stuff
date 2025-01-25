#include <stdio.h>


#include "gl_render_utils.h"


static bool gl_check_shader(GLuint handle, const char* label)
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

static bool gl_check_program(GLuint handle, const char* label)
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

static GLuint gl_create_shader(GLenum shader_type, const char* shader_source)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
#if RENDER_DEBUG
    gl_check_shader(shader);
#endif
    return shader;
}

gl_program gl_create_program(const GLchar* vertex_source, const GLchar* fragment_source)
{
    gl_program program = {};

    program.vertex_shader = gl_create_shader(GL_VERTEX_SHADER, vertex_source);
    program.fragment_shader = gl_create_shader(GL_FRAGMENT_SHADER, fragment_source);

    program.id = glCreateProgram();
    glAttachShader(program.id, program.vertex_shader);
    glAttachShader(program.id, program.fragment_shader);
    glLinkProgram(program.id);
#if RENDER_DEBUG
    gl_check_program(program.id);
#endif
    return program;
}

void gl_destroy_program(gl_program program)
{
    if(program.id)
    {
        if(program.vertex_shader)
        {
            glDetachShader(program.id, program.vertex_shader);
            program.vertex_shader = 0;
        }

        if(program.fragment_shader)
        {
            glDetachShader(program.id, program.fragment_shader);
            program.fragment_shader = 0;
        }

        program.id = 0;
    }
}
