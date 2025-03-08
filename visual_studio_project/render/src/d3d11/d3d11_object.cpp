#include "d3d11_object.h"


#include "d3d11_buffer.h"

// TODO:    The render_object is the aggregate object for _things_ that can be show on screen.
//          In OpenGL it holds the VAO id and seems like it should hold most other per-object
//          state, like shader programs. That looks most equivalent to PSO in D3D12 and there
//          will likely be something analogous in Vulkan. So, for now, the render_object for
//          D3D11 will best be served by working towards emulating a PSO. The PSO descriptor
//          struct's reference page is linked below becuase it shows what objects are linked
//          together to form a PSO.
//
// https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_graphics_pipeline_state_desc



//NOTE: D3D11 Pipeline Stages
// IA:  Input-Assembler
// VS:  Vertex Shader
// HS:  Hull Shader
// TS:  Tessellator
// DS:  Domain Shader
// GS:  Geometry Shader
// SO:  Stream Output
// RS:  Rasterizer
// PS:  Pixel Shader
// OM:  Output Merger


namespace render
{
    d3d11_object::d3d11_object(ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        m_pd3dDevice = device;
        m_pd3dDeviceContext = device_context;
    }



    void d3d11_object::bind_vbuf(buffer* vb)
    {
        auto v = static_cast<d3d11_buffer*>(vb);
        vertex_buffer = v->get_it();
    }


    void d3d11_object::bind_ibuf(buffer* ib)
    {
        auto i = static_cast<d3d11_buffer*>(ib);
        index_buffer = i->get_it();
        index_count = i->get_sz();
    }


    void d3d11_object::bind_layout(layout* lo)
    {
        auto lay = static_cast<d3d11_layout*>(lo);
        layout_stride = lay->get_stride();
    }


    d3d11_object::~d3d11_object()
    {
    }


    void d3d11_object::bind()
    {
        // TODO: Handle PSO here and non-PSO in draw? The VS and PS are handled in the shader program for now

    // IA
        // m_pd3dDeviceContext->IASetInputLayout(input_layout);
        // UINT stride = 8 * sizeof(float);
        // UINT offset = 0;
        // m_pd3dDeviceContext->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
        // m_pd3dDeviceContext->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);
    // VS
        // device_context->VSSetShader(vertex_shader, NULL, 0);
        // device_context->VSSetConstantBuffers(0, 1, &vertex_constant_buffer);
    // RS
    // PS
        // device_context->PSSetShader(pixel_shader, NULL, 0);
        // device_context->PSSetConstantBuffers(0, 1, &pixel_constant_buffer);
        // device_context->PSSetSamplers(0, 1, &texture_sampler);
        // device_context->PSSetShaderResources(0, 1, &texture_view);
    // OM




    }


    void d3d11_object::unbind()
    {

    }


    void d3d11_object::draw(int count)
    {
        // TODO: Non-PSO (GraphicsCommandList) calls should be handled outside of bind(),
        // either here or at a wider scope than an individual object

        // IASetIndexBuffer
        // IASetVertexBuffers
        // SOSetTargets
        // OMSetRenderTargets
        // RSSetViewports
        // RSSetScissorRects
        // OMSetBlendFactor
        // OMSetStencilRef
        // IASetPrimitiveTopology  -- DONE


        // TODO:
        // TODO:
        // TODO:
        // The fix for the broken meshes is to set the stride appropriately.


        UINT stride = layout_stride * sizeof(float);
        UINT offset = 0;
        m_pd3dDeviceContext->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
        m_pd3dDeviceContext->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);


        m_pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        int IndexCount = count; // num_indices; // I think
        int StartIndexLocation = 0; // offset into index array?
        int BaseVertexLocation = 0; // offset into vertex array?
        m_pd3dDeviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
    }
}
