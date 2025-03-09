#include "opengl_shader.h"


#include <stdio.h>

#include "engine_types.h"
#include "engine_vector.h"
#include "engine_matrix.h"


GLuint opengl_create_shader(GLenum shader_type, const char* shader_source)
{
    GLuint shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &shader_source, nullptr);
    glCompileShader(shader);

    GLint compile_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE)
    {
        const GLsizei MAX_LENGTH = 1024;
        GLsizei length = 0;
        GLchar info_log[MAX_LENGTH];
        glGetShaderInfoLog(shader, MAX_LENGTH, &length, info_log);

        printf("glCompileShader failed: %s\n", info_log);

        // TODO: Is this the best way to handle this error?
        glDeleteShader(shader);
        shader = 0;
    }

    return shader;
}


GLuint opengl_create_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    GLint link_status;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if(link_status != GL_TRUE)
    {
        const GLsizei MAX_LENGTH = 1024;
        GLsizei length = 0;
        GLchar info_log[MAX_LENGTH];
        glGetProgramInfoLog(program, MAX_LENGTH, &length, info_log);

        printf("glLinkProgram failed: %s\n", info_log);

        // TODO: Is this the best way to handle this error?
        glDeleteProgram(program);
        program = 0;
    }

    return program;
}


GLuint opengl_create_shader_program(char* vertex_source, char* fragment_source)
{
    GLuint vertex_shader =  opengl_create_shader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader =  opengl_create_shader(GL_FRAGMENT_SHADER, fragment_source);

    GLuint shader_program = opengl_create_program(vertex_shader, fragment_shader);

    return shader_program;
}


void opengl_bind_shader(GLuint program)
{
    glUseProgram(program);
}


void opengl_uniform_s32(GLuint program, const char* name, s32 value)
{
    GLint location = glGetUniformLocation(program, name);
    glUniform1i(location, value);
}


void opengl_uniform_u32(GLuint program, const char* name, u32 value)
{
    GLint location = glGetUniformLocation(program, name);
    glUniform1ui(location, value);
}


void opengl_uniform_f32(GLuint program, const char* name, f32 value)
{
    GLint location = glGetUniformLocation(program, name);
    glUniform1f(location, value);
}


void opengl_uniform_v3f(GLuint program, const char* name, v3f value)
{
    GLint location = glGetUniformLocation(program, name);
    glUniform3fv(location, 1, value.e);
}


void opengl_uniform_m4f(GLuint program, const char* name, m4f value)
{
    GLint location = glGetUniformLocation(program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, value.e);
}
