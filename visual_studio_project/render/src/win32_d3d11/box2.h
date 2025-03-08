#include "win32_d3d11.h"


namespace render
{
    class box
    {
    public:
        box();
        ~box();
        void draw();

    private:
        ID3D11Device* device;
        ID3D11DeviceContext* device_context;

        ID3D11VertexShader* vertex_shader;
        ID3D11PixelShader* pixel_shader;

        static const char* vertex_shader_source;
        static const char* pixel_shader_source;

        ID3D11Buffer* vertex_buffer;
        ID3D11Buffer* index_buffer;

        ID3D11InputLayout* input_layout;
    };
}
