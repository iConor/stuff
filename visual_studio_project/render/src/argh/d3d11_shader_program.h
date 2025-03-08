#pragma once


#include <d3d11.h>


#include "renderer_shader_program.h"


namespace renderer
{
    class d3d11_shader_program : public shader_program
    {
    public:
        d3d11_shader_program(shader_program_desc desc);
        ~d3d11_shader_program();

        void bind() override;

    private:

        shader* vertex_shader;
        shader* fragment_shader;

        // ID3D11VertexShader* vertex_shader;
        // ID3D11PixelShader*  fragment_shader;


        int id;
    };
}
