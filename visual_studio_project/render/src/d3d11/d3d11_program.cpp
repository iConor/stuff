#include "d3d11_program.h"


#include "d3d11_buffer.h"
#include "d3d11_texture.h"
#include "d3d11_sampler.h"
#include "d3d11_layout.h"



#include "d3d11_shader.h"


namespace render
{
    d3d11_program::d3d11_program(const program_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        m_pd3dDevice = device;
        m_pd3dDeviceContext = device_context;

        auto vs = static_cast<d3d11_shader*>(desc.vertex);
        vertex_shader = vs->get_vs();
        vertex_shader_blob = vs->get_blob();

        auto fs = static_cast<d3d11_shader*>(desc.fragment);
        pixel_shader = fs->get_fs();
    }


    d3d11_program::~d3d11_program()
    {
    }


    void d3d11_program::bind()
    {
        m_pd3dDeviceContext->IASetInputLayout(input_layout);


        m_pd3dDeviceContext->VSSetShader(vertex_shader, NULL, 0);
        m_pd3dDeviceContext->VSSetConstantBuffers(0, 1, &vertex_constant_buffer);
        m_pd3dDeviceContext->PSSetShader(pixel_shader, NULL, 0);
        m_pd3dDeviceContext->PSSetConstantBuffers(0, 1, &pixel_constant_buffer);
        m_pd3dDeviceContext->PSSetSamplers(0, 1, &texture_sampler);
        m_pd3dDeviceContext->PSSetShaderResources(0, 1, &texture_view);
    }


    void d3d11_program::unbind()
    {

    }


    void d3d11_program::bind_uniform_block(const int block_binding, const char* block_name)
    {

    }


    void d3d11_program::bind_sampler(const int target, const char* name)
    {

    }


    void d3d11_program::bind_vs_const_block(buffer* vs_cb)
    {
        auto vcb = static_cast<d3d11_buffer*>(vs_cb);
        vertex_constant_buffer = vcb->get_it();
    }


    void d3d11_program::bind_fs_const_block(buffer* fs_cb)
    {
        auto fcb = static_cast<d3d11_buffer*>(fs_cb);
        pixel_constant_buffer = fcb->get_it();
    }


    void d3d11_program::bind_texture(texture* rt)
    {
        auto tv = static_cast<d3d11_texture*>(rt);
        texture_view = tv->get_it();
    }


    void d3d11_program::bind_sampler(sampler* rs)
    {
        auto ts = static_cast<d3d11_sampler*>(rs);
        texture_sampler = ts->get_it();
    }


    void d3d11_program::bind_layout(layout* lo)
    {
        auto layout = static_cast<d3d11_layout*>(lo);
        D3D11_INPUT_ELEMENT_DESC* ied = layout->get_it();
        int count = layout->get_ct();

        // ID3D11InputLayout* input_layout;
        m_pd3dDevice->CreateInputLayout(ied, count, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), &input_layout);
    }

}
