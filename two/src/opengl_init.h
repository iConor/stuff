#ifndef OPENGL_INIT_H
#define OPENGL_INIT_H


#ifdef _WIN32
#define LOAD_GL_FUNCTION(func) func = (fn_##func *)wglGetProcAddress(#func)
#else
#define LOAD_GL_FUNCTION(func) func = (fn_##func *)SDL_GL_GetProcAddress(#func)
#endif

#define DEFINE_GL_FUNCTION(retval, func, ...) typedef retval (fn_##func)(__VA_ARGS__); fn_##func * func



#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31

#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893

#define GL_STATIC_DRAW                    0x88E4

#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_INFO_LOG_LENGTH                0x8B84

typedef void GLvoid;
typedef unsigned int GLenum;
typedef float GLfloat;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLuint;
typedef unsigned char GLboolean;

typedef char GLchar;

typedef signed long int GLsizeiptr;


// Shaders
DEFINE_GL_FUNCTION(void, glAttachShader, GLuint, GLuint);
DEFINE_GL_FUNCTION(void, glCompileShader, GLuint);
DEFINE_GL_FUNCTION(GLuint, glCreateProgram, void);
DEFINE_GL_FUNCTION(GLuint, glCreateShader, GLenum);
DEFINE_GL_FUNCTION(void, glDeleteShader, GLuint);
DEFINE_GL_FUNCTION(void, glDetachShader, GLuint, GLuint);
DEFINE_GL_FUNCTION(GLint, glGetAttribLocation, GLuint, const GLchar*);
DEFINE_GL_FUNCTION(void, glGetProgramiv, GLuint, GLenum, GLint*);
DEFINE_GL_FUNCTION(void, glGetProgramInfoLog, GLuint, GLsizei, GLsizei*, GLchar*);
DEFINE_GL_FUNCTION(void, glGetShaderiv, GLuint, GLenum, GLint*);
DEFINE_GL_FUNCTION(void, glGetShaderInfoLog, GLuint, GLsizei, GLsizei*, GLchar*);
DEFINE_GL_FUNCTION(GLint, glGetUniformLocation, GLuint, const GLchar*);
DEFINE_GL_FUNCTION(void, glLinkProgram, GLuint);
DEFINE_GL_FUNCTION(void, glShaderSource, GLuint, GLsizei, const GLchar**, const GLint*);
DEFINE_GL_FUNCTION(GLint, glUniformMatrix4fv, GLint, GLsizei, GLboolean, const GLfloat*);
DEFINE_GL_FUNCTION(void, glUseProgram, GLuint);

// Buffer Objects
DEFINE_GL_FUNCTION(void, glBindBuffer, GLenum, GLuint);
DEFINE_GL_FUNCTION(void, glBufferData, GLenum, GLsizeiptr, const void*, GLenum);
DEFINE_GL_FUNCTION(void, glEnableVertexAttribArray, GLuint);
DEFINE_GL_FUNCTION(void, glGenBuffers, GLsizei, GLuint*);
DEFINE_GL_FUNCTION(void, glVertexAttribPointer, GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);

// Vertex Array Objects
DEFINE_GL_FUNCTION(void, glBindVertexArray, GLuint);
DEFINE_GL_FUNCTION(void, glGenVertexArrays, GLsizei, GLuint*);


bool opengl_init();


#endif /* OPENGL_INIT_H */
