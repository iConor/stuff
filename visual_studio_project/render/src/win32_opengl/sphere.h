#pragma once


#include "shader.h"
#include <vector>


namespace render
{
    class sphere
    {
    public:
        sphere();
        sphere(float p_x, float p_y, float p_z,
               float r_x, float r_y, float r_z,
               float s_x, float s_y, float s_z,
               float c_r, float c_g, float c_b);
        ~sphere();

        void position(float x, float y, float z);
        void rotation(float x, float y, float z);
        void scale(float x, float y, float z);
        void color(float r, float g, float b);

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

        void layout_data();

        // Shader stuff
        shader* shader_program;

        GLuint vertex_array;    // VAO
        GLuint vertex_buffer;   // VBO
        GLuint index_buffer;    // EBO

        GLint projection_uniform;
        GLint view_uniform;
        GLint position_uniform;
        GLint rotation_uniform;
        GLint scale_uniform;
        GLint color_uniform;

        static const char* vertex_shader_source;
        static const char* fragment_shader_source;

        std::vector<float> vertex_data;
        std::vector<int> index_data;
    };

}
