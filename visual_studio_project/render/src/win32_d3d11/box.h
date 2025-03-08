#include "win32_d3d11.h"


namespace render
{
    struct vertex_constant_block
    {
        // Camera
        float proj[4][4];
        float view[4][4];
        // Object
        float position[4];
        float rotation[4];
        float scale[4];
    };

    struct pixel_constant_block
    {
        // Object
        float tint_color[4];
        // Lights
        float light_color[4];
        float light_position[4];
    };

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

// Renderer
        ID3D11Device* device;
        ID3D11DeviceContext* device_context;

// Mesh
        static const float vertex_data[];
        static const unsigned int index_data[];
        static const int num_indices;

        ID3D11Buffer* vertex_buffer;
        ID3D11Buffer* index_buffer;

// Shader
        static const char* vertex_shader_source;
        static const char* pixel_shader_source;

        ID3D11VertexShader* vertex_shader;
        ID3D11PixelShader* pixel_shader;
        // Constants/Uniforms
        vertex_constant_block vertex_constant_data;
        pixel_constant_block pixel_constant_data;

        ID3D11Buffer* vertex_constant_buffer;
        ID3D11Buffer* pixel_constant_buffer;

        ID3D11InputLayout* input_layout;
        // Texture Sampling
        ID3D11ShaderResourceView* texture_view;
        ID3D11SamplerState* texture_sampler;
    };
}
