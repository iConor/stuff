#include "d3d11_shader.h"

// TODO: nope nope nope
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler")


namespace render
{
    d3d11_shader::d3d11_shader(const shader_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        m_pd3dDevice = device;
        m_pd3dDeviceContext = device_context;

        type = desc.type;

        if(type == shader_type::vertex)
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
                       &shader_blob,
                       NULL
            );
            device->CreateVertexShader(shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), NULL, &vertex_shader);
        }
        else if(type == shader_type::fragment)
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
                       &shader_blob,
                       NULL
            );
            device->CreatePixelShader(shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), NULL, &pixel_shader);
        }
    }


    d3d11_shader::~d3d11_shader()
    {
        shader_blob->Release();
    }


    ID3D11VertexShader* d3d11_shader::get_vs()
    {
        return vertex_shader;
    }


    ID3D11PixelShader* d3d11_shader::get_fs()
    {
        return pixel_shader;
    }


    ID3DBlob* d3d11_shader::get_blob()
    {
        return shader_blob;
    }
}
