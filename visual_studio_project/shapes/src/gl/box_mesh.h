#pragma once

#include "renderer_buffer.h"
#include "renderer_layout.h"
#include "renderer_shader.h"
#include "renderer_shader_program.h"
#include "renderer_texture.h"



struct vertex_uniform_block
{
    // Camera
    float proj[16];
    float view[16];
    // Object
    float position[4];
    float rotation[4];
    float scale[4];
};

struct fragment_uniform_block
{
    // Object
    float tint_color[4];
    // Lights
    float light_color[4];
    float light_position[4];
};


class box_mesh
{
public:
    box_mesh();
    box_mesh(float p_x, float p_y, float p_z,
             float r_x, float r_y, float r_z,
             float s_x, float s_y, float s_z,
             float c_r, float c_g, float c_b);
    ~box_mesh();

    void position(float x, float y, float z);
    void rotation(float x, float y, float z);
    void scale(float x, float y, float z);
    void color(float r, float g, float b);

    void light(float r, float g, float b,
               float x, float y, float z);

    void draw();

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

    void create();

// Buffer Data
    static const float vertex_data[];
    static const int index_data[];
    static const int num_indices;
// Shader Data
    static const char* vertex_shader_source;
    static const char* fragment_shader_source;

// Render Objects
    renderer::buffer* vertex_buffer;
    renderer::buffer* index_buffer;
    renderer::layout* layout;
    renderer::shader_program* shader_program;
    renderer::texture* texture;

// Converting to constant buffers for the uniforms

    vertex_uniform_block vs_uniform_data;
    fragment_uniform_block fs_uniform_data;

    renderer::buffer* vs_uniform_buffer;
    renderer::buffer* fs_uniform_buffer;

    // TODO: separate out the constant buffers
    // renderer::buffer* camera_buffer;
    // renderer::buffer* light_buffer;

};
