#include "opengl_init.h"


#ifdef _WIN32
#include "Windows.h"
#endif


// Shaders
DEFINE_GL_FUNCTION(glAttachShader);
DEFINE_GL_FUNCTION(glCompileShader);
DEFINE_GL_FUNCTION(glCreateProgram);
DEFINE_GL_FUNCTION(glCreateShader);
DEFINE_GL_FUNCTION(glDeleteShader);
DEFINE_GL_FUNCTION(glDetachShader);
DEFINE_GL_FUNCTION(glGetAttribLocation);
DEFINE_GL_FUNCTION(glGetProgramiv);
DEFINE_GL_FUNCTION(glGetProgramInfoLog);
DEFINE_GL_FUNCTION(glGetShaderiv);
DEFINE_GL_FUNCTION(glGetShaderInfoLog);
DEFINE_GL_FUNCTION(glGetUniformLocation);
DEFINE_GL_FUNCTION(glLinkProgram);
DEFINE_GL_FUNCTION(glShaderSource);
DEFINE_GL_FUNCTION(glUniform3f);
DEFINE_GL_FUNCTION(glUniformMatrix4fv);
DEFINE_GL_FUNCTION(glUseProgram);

// Buffer Objects
DEFINE_GL_FUNCTION(glBindBuffer);
DEFINE_GL_FUNCTION(glBufferData);
DEFINE_GL_FUNCTION(glEnableVertexAttribArray);
DEFINE_GL_FUNCTION(glGenBuffers);
DEFINE_GL_FUNCTION(glVertexAttribPointer);

// Vertex Array Objects
DEFINE_GL_FUNCTION(glBindVertexArray);
DEFINE_GL_FUNCTION(glGenVertexArrays);


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
    LOAD_GL_FUNCTION(glUniform3f);
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
