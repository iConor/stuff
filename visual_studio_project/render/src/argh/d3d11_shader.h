#pragma once


#include <d3d11.h>

#include "renderer_shader.h"


namespace renderer
{
    class d3d11_shader : public shader
    {
    public:
        d3d11_shader(shader_desc desc);
        ~d3d11_shader();

    private:
        void create_vertex_shader(shader_desc desc);
        void create_fragment_shader(shader_desc desc);

        shader_type type;
        ID3DBlob* blob;
    };
}
