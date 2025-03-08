#include "box.h"

// TODO: nope nope nope
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler")

#include "stb_image.h"

namespace render
{


float f = 100.0f;
float n = 0.1f;
float aspect = 16.0f / 9.0f;

// vertex_constant_block box::vertex_constant_data =
// {
//     {
//
//         { 1.0f/aspect,  0.0f,  0.0f,  0.0f},
//         { 0.0f,  1.0f,  0.0f,  0.0f},
//         { 0.0f,  0.0f,  f/(n-f), -1.0f },
//         { 0.0f,  0.0f,  (f*n)/(n-f),  0.0f},
//     },
//     {
//         {  1.0f,  0.0f,  0.0f,  0.0f },
//         {  0.0f,  1.0f,  0.0f,  0.0f },
//         {  0.0f,  0.0f,  1.0f,  0.0f },
//         {  0.0f,  0.0f,  0.0f,  1.0f },
//     },
//     {  0.0f,  0.0f,  0.0f, 0.0f },
//     {  0.0f,  0.0f,  0.0f, 1.0f },
//     {  1.0f,  1.0f,  1.0f, 1.0f },
// };
//
//
// pixel_constant_block box::pixel_constant_data =
// {
//     {  1.0f,  1.0f,  1.0f,  1.0f },
//     {  1.0f,  1.0f,  1.0f,  1.0f },
//     {  0.0f,  0.0f,  0.0f,  0.0f }
// };


const char* box::vertex_shader_source =
    "cbuffer VS_UNIFORMS // : register(b0)\n"
    "{\n"
    "   float4x4 proj;\n"
    "   float4x4 view;\n"
    "   float4   position;\n"
    "   float4   rotation;\n"
    "   float4   scale;\n"
    "};\n"
    "struct VS_INPUT\n"
    "{\n"
    "   float3 position : POSITION;\n"
    "   float3 normal   : NORMAL;\n"
    "   float2 texcoord : TEXCOORD;\n"
    "};\n"
    "struct VS_OUTPUT\n"
    "{\n"
    "   float4 posi : SV_POSITION;\n"
    "   float4 position : POSITION;\n"
    "   float3 normal   : NORMAL;\n"
    "   float2 texcoord : TEXCOORD;\n"
    "};\n"
    "VS_OUTPUT main(VS_INPUT input)"
    "{\n"
    "   VS_OUTPUT output;\n"
    "   float4 model    = position + scale * float4(input.position.xyz, 1.0f);\n"
    "   output.posi = mul(proj, mul(view, model));\n"
    "   output.position = model;\n"
    "   output.normal   = input.normal;\n"
    "   output.texcoord = input.texcoord;\n"
    "   return output;\n"
    "}\n";


const char* box::pixel_shader_source =
    "sampler sampler0;\n"
    "Texture2D texture0;\n"
    "cbuffer PS_UNIFORMS\n"
    "{\n"
    "    float4 tint_color;\n"
    "    float4 light_color;\n"
    "    float4 light_position;\n"
    "};\n"
    "struct PS_INPUT\n"
    "{\n"
    "   float4 sv_position : SV_POSITION;\n"
    "   float4 position : POSITION;\n"
    "   float3 normal   : NORMAL;\n"
    "   float2 texcoord : TEXCOORD;\n"
    "};\n"
    "float4 main(PS_INPUT input) : SV_TARGET\n"
    "{\n"
    "   float3 eye = float3(0.0f, 0.0f, 0.0f);\n"
    "   float3 norm  = normalize(input.normal);\n"
    "   float3 light   = normalize(light_position - input.position);\n"
    "   float3 refl = normalize(reflect(-light_position, norm));\n"
    "   float3 view = normalize(eye - input.position);\n"
    "   float4 sample = texture0.Sample(sampler0, input.texcoord);\n"
    "   float3 color   = tint_color.xyz * light_color * sample.xyz;\n"
    "   float3 ambient = color;\n"
    "   float3 diffuse = color * max(dot(light, norm), 0.0f);\n"
    "   float3 specular = light_color * pow(max(dot(refl, view), 0.0), 32);\n"
    "   return float4(0.1f * ambient + 0.9f * diffuse + 0.5f * specular, 1.0f);\n"
    "}\n";


const float box::vertex_data[] =
{
// Front
    -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
// Right
     0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
// Back
     0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
// Left
    -0.5f, -0.5f, -0.5f,    -1.0f,  1.0f,  0.0f,     0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,    -1.0f,  1.0f,  0.0f,     1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    -1.0f,  1.0f,  0.0f,     1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,    -1.0f,  1.0f,  0.0f,     0.0f,  1.0f,
// Top
    -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
// Bottom
    -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
};


const unsigned int box::index_data[] =
{
     0,  1,  2,
     2,  3,  0,
     // 0,  3,  2,
     // 2,  1,  0,

     4,  5,  6,
     6,  7,  4,
     // 4,  7,  6,
     // 6,  5,  4,

     8,  9, 10,
    10, 11,  8,

    12, 13, 14,
    14, 15, 12,

    16, 17, 18,
    18, 19, 16,

    20, 21, 22,
    22, 23, 20,
};
const int box::num_indices = sizeof(index_data)/sizeof(index_data[0]);


box::box()
{
    setup(0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f,
          1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f);
}


box::box(float p_x, float p_y, float p_z,
         float r_x, float r_y, float r_z,
         float s_x, float s_y, float s_z,
         float c_r, float c_g, float c_b)
{
    setup(p_x, p_y, p_z,
          r_x, r_y, r_z,
          s_x, s_y, s_z,
          c_r, c_g, c_b);
}


box::~box()
{

}


void box::setup(float p_x, float p_y, float p_z,
                float r_x, float r_y, float r_z,
                float s_x, float s_y, float s_z,
                float c_r, float c_g, float c_b)
{
    pos_x = p_x;
    pos_y = p_y;
    pos_z = p_z;

    rot_x = r_x;
    rot_y = r_y;
    rot_z = r_z;

    sca_x = s_x;
    sca_y = s_y;
    sca_z = s_z;

    col_r = c_r;
    col_g = c_g;
    col_b = c_b;

    light_r = 1.0f;
    light_g = 1.0f;
    light_b = 1.0f;

    light_x = 0.0f;
    light_y = 0.0f;
    light_z = 0.0f;

    vertex_constant_data =
    {
        {

            { 1.0f/aspect,  0.0f,  0.0f,  0.0f},
            { 0.0f,  1.0f,  0.0f,  0.0f},
            { 0.0f,  0.0f,  f/(n-f), -1.0f },
            { 0.0f,  0.0f,  (n*f)/(n-f),  0.0f},
        },
        {
            {  1.0f,  0.0f,  0.0f,  0.0f },
            {  0.0f,  1.0f,  0.0f,  0.0f },
            {  0.0f,  0.0f,  1.0f,  0.0f },
            {  0.0f,  0.0f,  0.0f,  1.0f },
        },
        {  0.0f,  0.0f,  0.0f, 0.0f },
        {  0.0f,  0.0f,  0.0f, 1.0f },
        {  1.0f,  1.0f,  1.0f, 1.0f },
    };


    pixel_constant_data =
    {
        {  1.0f,  1.0f,  1.0f,  1.0f },
        {  1.0f,  1.0f,  1.0f,  1.0f },
        {  0.0f,  0.0f,  0.0f,  0.0f }
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
    device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), NULL, &vertex_shader);

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
    device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), NULL, &pixel_shader);
    // pixel_shader_blob->Release();

// Vertex Layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0,                 D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0,  6 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    device->CreateInputLayout(layout, 3, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), &input_layout);
    // vertex_shader_blob->Release();

// Vertex Buffer
    D3D11_BUFFER_DESC vb_desc = { 0 };

    vb_desc.ByteWidth               = sizeof(vertex_data);
    vb_desc.Usage                   = D3D11_USAGE_DYNAMIC;
    vb_desc.BindFlags               = D3D11_BIND_VERTEX_BUFFER;
    vb_desc.CPUAccessFlags          = D3D11_CPU_ACCESS_WRITE;
    vb_desc.MiscFlags               = 0;
    // vb_desc.StructureByteStride     = 8 * sizeof(float);

    device->CreateBuffer(&vb_desc, NULL, &vertex_buffer);

    D3D11_MAPPED_SUBRESOURCE vb_sub;
    device_context->Map(vertex_buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &vb_sub);
    memcpy(vb_sub.pData, vertex_data, sizeof(vertex_data));
    device_context->Unmap(vertex_buffer, NULL);

// Index Buffer
    D3D11_BUFFER_DESC ib_desc = { 0 };

    ib_desc.ByteWidth               = sizeof(index_data);
    ib_desc.Usage                   = D3D11_USAGE_DYNAMIC;
    ib_desc.BindFlags               = D3D11_BIND_VERTEX_BUFFER;
    ib_desc.CPUAccessFlags          = D3D11_CPU_ACCESS_WRITE;
    ib_desc.MiscFlags               = 0;
    // ib_desc.StructureByteStride     = 8 * sizeof(float);

    device->CreateBuffer(&ib_desc, NULL, &index_buffer);

    D3D11_MAPPED_SUBRESOURCE ib_sub;
    device_context->Map(index_buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ib_sub);
    memcpy(ib_sub.pData, index_data, sizeof(index_data));
    device_context->Unmap(index_buffer, NULL);

// Vertex Constant Buffer
    D3D11_BUFFER_DESC vertex_cb_desc = { 0 };

    vertex_cb_desc.ByteWidth               = sizeof(vertex_constant_block);
    vertex_cb_desc.Usage                   = D3D11_USAGE_DYNAMIC;
    vertex_cb_desc.BindFlags               = D3D11_BIND_CONSTANT_BUFFER;
    vertex_cb_desc.CPUAccessFlags          = D3D11_CPU_ACCESS_WRITE;
    vertex_cb_desc.MiscFlags               = 0;
    // vertex_cb_desc.StructureByteStride     = 16 * sizeof(float);

    device->CreateBuffer(&vertex_cb_desc, NULL, &vertex_constant_buffer);

// Pixel Constant Buffer
    D3D11_BUFFER_DESC pixel_cb_desc = { 0 };

    pixel_cb_desc.ByteWidth               = sizeof(pixel_constant_block);
    pixel_cb_desc.Usage                   = D3D11_USAGE_DYNAMIC;
    pixel_cb_desc.BindFlags               = D3D11_BIND_CONSTANT_BUFFER;
    pixel_cb_desc.CPUAccessFlags          = D3D11_CPU_ACCESS_WRITE;
    pixel_cb_desc.MiscFlags               = 0;
    // pixel_cb_desc.StructureByteStride     = 16 * sizeof(float);

    device->CreateBuffer(&pixel_cb_desc, NULL, &pixel_constant_buffer);


    // const char* filename = "E:\\dev\\scaling-potato\\bin\\Debug-x64\\platform\\wall.png";
    const char* filename = "\\\\BILL\\Users\\Public\\Public Games\\wall.png";

    int width;
    int height;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* img = stbi_load(filename, &width, &height, &channels, 0);
    if(img)
    {
        ID3D11Texture2D* pTexture = NULL;

        D3D11_TEXTURE2D_DESC tex_desc = { 0 };

        tex_desc.Width              = width;
        tex_desc.Height             = height;
        tex_desc.MipLevels          = 1;
        tex_desc.ArraySize          = 1;
        tex_desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
        // tex_desc.Format             = DXGI_FORMAT_UNKNOWN;
        tex_desc.SampleDesc.Count   = 1;
        // tex_desc.SampleDesc.Quality = ;
        tex_desc.Usage              = D3D11_USAGE_DEFAULT;
        tex_desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
        // tex_desc.CPUAccessFlags     = 0;
        // tex_desc.MiscFlags          = ;

        D3D11_SUBRESOURCE_DATA tex_sub = { 0 };

        tex_sub.pSysMem = img;
        tex_sub.SysMemPitch = tex_desc.Width * 4;
        tex_sub.SysMemSlicePitch = 0;

        device->CreateTexture2D(&tex_desc, &tex_sub, &pTexture);

        D3D11_SHADER_RESOURCE_VIEW_DESC view_desc = { 0 };

        view_desc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
        view_desc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
        view_desc.Texture2D.MostDetailedMip = 0;
        view_desc.Texture2D.MipLevels       = tex_desc.MipLevels;

        device->CreateShaderResourceView(pTexture, &view_desc, &texture_view);

        pTexture->Release();

        D3D11_SAMPLER_DESC sampler_desc = { 0 };

        sampler_desc.Filter             = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampler_desc.AddressU           = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressV           = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressW           = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.MipLODBias         = 0.0f;
        // sampler_desc.MaxAnisotropy      = ;
        sampler_desc.ComparisonFunc     = D3D11_COMPARISON_ALWAYS;//GREATER_EQUAL;
        // sampler_desc.BorderColor        = ;
        sampler_desc.MinLOD             = 0.0f;
        sampler_desc.MaxLOD             = 0.0f;

        device->CreateSamplerState(&sampler_desc, &texture_sampler);
    }
    stbi_image_free(img);
}


void box::draw()
{
    // Constants
    D3D11_MAPPED_SUBRESOURCE vertex_cb_sub;
    device_context->Map(vertex_constant_buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &vertex_cb_sub);
    memcpy(vertex_cb_sub.pData, &vertex_constant_data, sizeof(vertex_constant_data));
    device_context->Unmap(vertex_constant_buffer, NULL);

    D3D11_MAPPED_SUBRESOURCE pixel_cb_sub;
    device_context->Map(pixel_constant_buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &pixel_cb_sub);
    memcpy(pixel_cb_sub.pData, &pixel_constant_data, sizeof(pixel_constant_data));
    device_context->Unmap(pixel_constant_buffer, NULL);

// Buffers
    device_context->IASetInputLayout(input_layout);
    UINT stride = 8 * sizeof(float);
    UINT offset = 0;
    device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
    device_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);

// Shaders
    device_context->VSSetShader(vertex_shader, NULL, 0);
    device_context->VSSetConstantBuffers(0, 1, &vertex_constant_buffer);
    device_context->PSSetShader(pixel_shader, NULL, 0);
    device_context->PSSetConstantBuffers(0, 1, &pixel_constant_buffer);
    device_context->PSSetSamplers(0, 1, &texture_sampler);
    device_context->PSSetShaderResources(0, 1, &texture_view);

// Draw
    device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    int IndexCount = 36; // num_indices; // I think
    int StartIndexLocation = 0; // offset into index array?
    int BaseVertexLocation = 0; // offset into vertex array?
    device_context->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}


void box::draw_edges()
{
    // ID3D11Device* device = d3d11_get_device();
    // ID3D11DeviceContext* device_context = d3d11_get_device_context();

}


void box::position(float x, float y, float z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;

    vertex_constant_data.position[0] = x;
    vertex_constant_data.position[1] = y;
    vertex_constant_data.position[2] = z;
}


void box::rotation(float x, float y, float z)
{
    rot_x = x;
    rot_y = y;
    rot_z = z;

    vertex_constant_data.rotation[0] = x;
    vertex_constant_data.rotation[1] = y;
    vertex_constant_data.rotation[2] = z;
}


void box::scale(float x, float y, float z)
{
    sca_x = x;
    sca_y = y;
    sca_z = z;

    vertex_constant_data.scale[0] = x;
    vertex_constant_data.scale[1] = y;
    vertex_constant_data.scale[2] = z;
}


void box::color(float r, float g, float b)
{
    col_r = r;
    col_g = g;
    col_b = b;

    pixel_constant_data.tint_color[0] = r;
    pixel_constant_data.tint_color[1] = g;
    pixel_constant_data.tint_color[2] = b;
}


void box::light(float r, float g, float b,
                float x, float y, float z)
{
    light_r = r;
    light_g = g;
    light_b = b;

    pixel_constant_data.light_color[0] = r;
    pixel_constant_data.light_color[1] = g;
    pixel_constant_data.light_color[2] = b;

    light_x = x;
    light_y = y;
    light_z = z;

    pixel_constant_data.light_position[0] = x;
    pixel_constant_data.light_position[1] = y;
    pixel_constant_data.light_position[2] = z;
}


}
