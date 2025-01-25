#include "opengl_init.h"


bool opengl_init()
{
    // Shaders
    LOAD_GL_FUNCTION(glAttachShader);
    LOAD_GL_FUNCTION(glCompileShader);
    LOAD_GL_FUNCTION(glCreateProgram);
    LOAD_GL_FUNCTION(glCreateShader);
    LOAD_GL_FUNCTION(glDeleteShader);
    LOAD_GL_FUNCTION(glDetachShader);
    LOAD_GL_FUNCTION(glGetAttribLocation);
    LOAD_GL_FUNCTION(glGetProgramiv);
    LOAD_GL_FUNCTION(glGetProgramInfoLog);
    LOAD_GL_FUNCTION(glGetShaderiv);
    LOAD_GL_FUNCTION(glGetShaderInfoLog);
    LOAD_GL_FUNCTION(glGetUniformLocation);
    LOAD_GL_FUNCTION(glLinkProgram);
    LOAD_GL_FUNCTION(glShaderSource);
    LOAD_GL_FUNCTION(glUniformMatrix4fv);
    LOAD_GL_FUNCTION(glUseProgram);

    // Buffer Objects
    LOAD_GL_FUNCTION(glBindBuffer);
    LOAD_GL_FUNCTION(glBufferData);
    LOAD_GL_FUNCTION(glEnableVertexAttribArray);
    LOAD_GL_FUNCTION(glGenBuffers);
    LOAD_GL_FUNCTION(glVertexAttribPointer);

    // Vertex Array Objects
    LOAD_GL_FUNCTION(glBindVertexArray);
    LOAD_GL_FUNCTION(glGenVertexArrays);

    return glCreateProgram != NULL;
}
