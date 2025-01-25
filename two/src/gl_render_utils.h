#ifndef GL_RENDER_UTILS_H
#define GL_RENDER_UTILS_H


struct gl_program
{
    unsigned int id;
    unsigned int vertex_shader;
    unsigned int geometry_shader;
    unsigned int fragment_shader;
};

gl_program gl_create_program(const char* vertex_source, const char* fragment_source);
void gl_destroy_program(gl_program program);


#endif /* RENDER_H */
