#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H


#include "glad/glad.h"

#include "engine_types.h"


GLuint opengl_create_shader_program(char* vertex_source, char* fragment_source);

GLuint opengl_create_shader(GLenum shader_type, const char* shader_source);
GLuint opengl_create_program(GLuint vertex_shader, GLuint fragment_shader);

void opengl_bind_shader(GLuint program);

void opengl_uniform_s32(GLuint program, const char* name, s32 value);
void opengl_uniform_u32(GLuint program, const char* name, u32 value);
void opengl_uniform_f32(GLuint program, const char* name, f32 value);

void opengl_uniform_v3f(GLuint program, const char* name, v3f value);
void opengl_uniform_m4f(GLuint program, const char* name, m4f value);


#endif /* OPENGL_SHADER_H */
