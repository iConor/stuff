#include "box.h"


#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler")


namespace render
{
const char* box::vertex_shader_source =
    "struct VS_OUTPUT\n"
    "{\n"
    "   float4 position : SV_POSITION;\n"
    "   float4 color : COLOR;\n"
    "};\n"
    "VS_OUTPUT main(float3 position : POSITION)"
    "{\n"
    "   VS_OUTPUT output;\n"
    "   output.position = float4(position.xyz, 1.0f);\n"
    "   output.color = float4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "   return output;\n"
    "}\n";


const char* box::pixel_shader_source =
    "float4 main(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET\n"
    "{\n"
    "   return color;\n"
    "}\n";


    box::box()
    {
        float vertices[] =
        {
            -0.5f, -0.5f,  0.0f,
             0.5f, -0.5f,  0.0f,
             0.5f,  0.5f,  0.0f,
            -0.5f,  0.5f,  0.0f,
        };

        unsigned int indices[]
        {
            0, 1, 2,
            2, 3, 0
        };

    // Get Handles
        device = d3d11_get_device();
        device_context = d3d11_get_device_context();

    // Create Shaders
        ID3DBlob* vertex_shader_blob;
        D3DCompile(vertex_shader_source,
                   strlen(vertex_shader_source),
                   NULL,
                   NULL,
                   NULL,
                   "main",
                   "vs_5_0",
                   0,
                   0,
                   &vertex_shader_blob,
                   NULL
        );

        ID3DBlob* pixel_shader_blob;
        D3DCompile(pixel_shader_source,
                   strlen(pixel_shader_source),
                   NULL,
                   NULL,
                   NULL,
                   "main",
                   "ps_5_0",
                   0,
                   0,
                   &pixel_shader_blob,
                   NULL
        );

        device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), NULL, &vertex_shader);
        device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), NULL, &pixel_shader);

        device_context->VSSetShader(vertex_shader, NULL, 0);
        device_context->PSSetShader(pixel_shader, NULL, 0);

        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        device->CreateInputLayout(layout, 1, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), &input_layout);
        device_context->IASetInputLayout(input_layout);

        D3D11_BUFFER_DESC vb_desc = { 0 };

        vb_desc.ByteWidth               = sizeof(vertices);
        vb_desc.Usage                   = D3D11_USAGE_DYNAMIC;
        vb_desc.BindFlags               = D3D11_BIND_VERTEX_BUFFER;
        vb_desc.CPUAccessFlags          = D3D11_CPU_ACCESS_WRITE;
        vb_desc.MiscFlags               = 0;
        // vb_desc.StructureByteStride     = 8 * sizeof(float);

        device->CreateBuffer(&vb_desc, NULL, &vertex_buffer);

        D3D11_MAPPED_SUBRESOURCE vb_sub;
        device_context->Map(vertex_buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &vb_sub);
        memcpy(vb_sub.pData, vertices, sizeof(vertices));
        device_context->Unmap(vertex_buffer, NULL);

        D3D11_BUFFER_DESC ib_desc = { 0 };

        ib_desc.ByteWidth               = sizeof(indices);
        ib_desc.Usage                   = D3D11_USAGE_DYNAMIC;
        ib_desc.BindFlags               = D3D11_BIND_VERTEX_BUFFER;
        ib_desc.CPUAccessFlags          = D3D11_CPU_ACCESS_WRITE;
        ib_desc.MiscFlags               = 0;
        // ib_desc.StructureByteStride     = 8 * sizeof(float);

        device->CreateBuffer(&ib_desc, NULL, &index_buffer);

        D3D11_MAPPED_SUBRESOURCE ib_sub;
        device_context->Map(index_buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ib_sub);
        memcpy(ib_sub.pData, indices, sizeof(indices));
        device_context->Unmap(index_buffer, NULL);
    }

    box::~box()
    {

    }

    void box::draw()
    {
        UINT stride = 3 * sizeof(float);
        UINT offset = 0;
        device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
        device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);
        device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // device_context->Draw(3, 0);
        int IndexCount = 6; // I think
        int StartIndexLocation = 0; // offset into index array?
        int BaseVertexLocation = 0; // offset into vertex array?
        device_context->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
    }
}
