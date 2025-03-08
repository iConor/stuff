#pragma once


#include "shader.h"
#include "texture.h"


namespace render
{
    class box
    {
    public:
        box();
        box(float p_x, float p_y, float p_z,
            float r_x, float r_y, float r_z,
            float s_x, float s_y, float s_z,
            float c_r, float c_g, float c_b);
        ~box();

        void position(float x, float y, float z);
        void rotation(float x, float y, float z);
        void scale(float x, float y, float z);
        void color(float r, float g, float b);

        void light(float r, float g, float b,
                   float x, float y, float z);

        void draw();
        void draw_edges();

    private:
        void setup(float p_x, float p_y, float p_z,
                   float r_x, float r_y, float r_z,
                   float s_x, float s_y, float s_z,
                   float c_r, float c_g, float c_b);

        float pos_x, pos_y, pos_z;
        float rot_x, rot_y, rot_z;
        float sca_x, sca_y, sca_z;
        float col_r, col_g, col_b;

        float light_r, light_g, light_b;
        float light_x, light_y, light_z;

// Mesh
        static const float vertex_data[];
        static const int index_data[];
        static const int num_indices;

        GLuint vertex_array;    // VAO
        GLuint vertex_buffer;   // VBO
        GLuint index_buffer;    // EBO

// Shader
        static const char* vertex_shader_source;
        static const char* fragment_shader_source;

        shader* shader_program;

        GLint projection_uniform;
        GLint view_uniform;

        GLint position_uniform;
        GLint rotation_uniform;
        GLint scale_uniform;

        GLint texture_uniform;
        GLint color_uniform;
        GLint light_color_uniform;
        GLint light_position_uniform;
        // Texture Sampling
        texture* texture_thingie;
    };

}
