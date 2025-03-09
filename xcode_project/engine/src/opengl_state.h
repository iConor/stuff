#ifndef OPENGL_STATE_H
#define OPENGL_STATE_H


#include "glad/glad.h"


void opengl_viewport(GLint x, GLint y, GLsizei width, GLsizei height);

void opengl_depth_enable(GLuint enable);
void opengl_depth_func(GLenum func);
void opengl_depth_mask(GLboolean enable);

void opengl_stencil_enable(GLuint enable);
void opengl_stencil_func(GLenum func, GLint ref, GLuint mask);
void opengl_stencil_mask(GLuint mask);
void opengl_stencil_op(GLenum sfail, GLenum dpfail, GLenum dppass);

void opengl_blend_enable(GLuint enable);
void opengl_blend_func(GLenum sfactor, GLenum dfactor);

void opengl_cull_enable(GLuint enable);
void opengl_cull_face(GLenum mode);
void opengl_cull_front(GLenum mode);

void opengl_wireframe_mode(GLuint enable);


#endif /* OPENGL_STATE_H */
