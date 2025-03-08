#pragma once


#include "shader.h"


#include <d3d11.h>

namespace render
{
    class d3d11_shader : public shader
    {
    public:
        d3d11_shader(const shader_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_context);
        ~d3d11_shader();

        ID3D11VertexShader* get_vs();
        ID3D11PixelShader* get_fs();
        ID3DBlob* get_blob();

    private:
        ID3D11Device*               m_pd3dDevice;
        ID3D11DeviceContext*        m_pd3dDeviceContext;

        ID3DBlob* shader_blob;

        shader_type type;
        // Either or...
        ID3D11VertexShader* vertex_shader = nullptr;
        ID3D11PixelShader* pixel_shader = nullptr;
    };
}
