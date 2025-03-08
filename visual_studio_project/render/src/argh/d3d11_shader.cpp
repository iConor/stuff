#include "d3d11_shader.h"


// TODO: nope nope nope
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler")


namespace renderer
{
    d3d11_shader::d3d11_shader(shader_desc desc)
    {
        switch(desc.type)
        {
            case shader_type::vertex:   create_vertex_shader(desc); break;
            case shader_type::fragment: create_fragment_shader(desc); break;
        }
    }


    d3d11_shader::~d3d11_shader()
    {
    }


    void d3d11_shader::create_vertex_shader(shader_desc desc)
    {
        D3DCompile(desc.source,
                   strlen(desc.source),
                   NULL,
                   NULL,
                   NULL,
                   "main",
                   "vs_5_0",
                   0,
                   0,
                   &blob,
                   NULL
        );
        // device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), NULL, &vertex_shader);
    }


    void d3d11_shader::create_fragment_shader(shader_desc desc)
    {
        D3DCompile(desc.source,
                   strlen(desc.source),
                   NULL,
                   NULL,
                   NULL,
                   "main",
                   "ps_5_0",
                   0,
                   0,
                   &blob,
                   NULL
        );
        // device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), NULL, &pixel_shader);
        // pixel_shader_blob->Release();
    }
}
