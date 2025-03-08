#pragma once


#include "program.h"

#include <d3d11.h>


namespace render
{
    class d3d11_program : public program
    {
    public:
        d3d11_program(const program_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_context);
        ~d3d11_program();

        void bind() override;
        void unbind() override;

        void bind_uniform_block(const int block_binding, const char* name) override;
        void bind_sampler(const int target, const char* name);

        void bind_vs_const_block(buffer* vs_cb) override;
        void bind_fs_const_block(buffer* fs_cb) override;
        void bind_texture(texture* rt) override;
        void bind_sampler(sampler* rs) override;
        void bind_layout(layout* lo) override;

    private:
        ID3D11Device*               m_pd3dDevice;
        ID3D11DeviceContext*        m_pd3dDeviceContext;


        ID3D11VertexShader* vertex_shader;
        ID3D11PixelShader* pixel_shader;


        ID3D11Buffer* vertex_constant_buffer;
        ID3D11Buffer* pixel_constant_buffer;


        ID3D11ShaderResourceView* texture_view;
        ID3D11SamplerState* texture_sampler;


        ID3DBlob* vertex_shader_blob;
        ID3D11InputLayout* input_layout;
    };
}
