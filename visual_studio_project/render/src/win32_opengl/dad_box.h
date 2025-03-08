#pragma once


#include "shader.h"


namespace render
{
    class dad_box
    {
    public:
        dad_box();
        dad_box(float p_x, float p_y, float p_z,
                float r_x, float r_y, float r_z,
                float s_x, float s_y, float s_z);
        ~dad_box();


        void position(float x, float y, float z);
        void rotation(float x, float y, float z);
        void scale(float x, float y, float z);


        void draw();

    private:
        void setup();
        // Box properties
        float pos_x, pos_y, pos_z;
        float rot_x, rot_y, rot_z;
        float sca_x, sca_y, sca_z;


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


        static const char* vertex_shader_source;
        static const char* fragment_shader_source;

        static const float vertex_data[];
        static const int index_data[];
        static const int num_indices;
    };

}
