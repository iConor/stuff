#pragma once


#include "shapes.h"

#include "render.h"


class box
{
public:
    box(render::core* core);
    box(render::core* core,
        float p_x, float p_y, float p_z,
        float r_x, float r_y, float r_z,
        float s_x, float s_y, float s_z,
        float c_r, float c_g, float c_b);
    ~box();

    void draw();

    void position(float x, float y, float z);
    void rotation(float x, float y, float z);
    void scale(float x, float y, float z);

    void color(float r, float g, float b);

    void light(float r, float g, float b,
               float x, float y, float z);

private:
    float pos_x, pos_y, pos_z;
    float rot_x, rot_y, rot_z;
    float sca_x, sca_y, sca_z;
    float col_r, col_g, col_b;

    float light_r, light_g, light_b;
    float light_x, light_y, light_z;

    void setup(float p_x, float p_y, float p_z,
               float r_x, float r_y, float r_z,
               float s_x, float s_y, float s_z,
               float c_r, float c_g, float c_b);

    render::core* render;

    render::object* ob;
    render::layout* lo;
    render::shader* vs;
    render::shader* fs;
    render::program* sp;
    render::buffer* vb;
    render::buffer* ib;
    render::buffer* vs_ub;
    render::buffer* fs_ub;
    render::texture* tx;
    render::sampler* ts;

    void init();

    static const render::layout_desc lo_desc[];

    static const char* vertex_shader_source;
    static const char* fragment_shader_source;

    static const float vertex_data[];
    static const int index_data[];
    static const int num_indices;

    vertex_uniform_block vs_uniform_data;
    fragment_uniform_block fs_uniform_data;

    camera camera;
};
