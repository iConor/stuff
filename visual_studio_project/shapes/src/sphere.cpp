#include "sphere.h"


#include "stb_image.h"

#include <string.h>

#include <cmath>



const render::layout_desc sphere::lo_desc[] =
{
    { "POSITION",   3 },
    // { "NORMAL", 3 },
    // { "TEXCOORD", 2 },
};


const char* sphere::vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 vertex;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec2 tex_uv;\n"
    "layout (std140) uniform VertexUniforms\n"
    "{\n"
    "   mat4 projection;\n"
    "   mat4 view;\n"
    "   vec4 position;\n"
    "   vec4 rotation;\n"
    "   vec4 scale;\n"
    "};\n"
    "out vec3 frag_position;\n"
    "out vec3 frag_normal;\n"
    "out vec2 frag_coords;\n"
    "mat3 rpy2mat(in vec3 rpy)\n"
    "{\n"
    "    vec3 rads = radians(rpy);\n"
    "    vec3 c = cos(rads);\n"
    "    vec3 s = sin(rads);\n"
    "    mat3 r = mat3(   1,    0,    0,\n"
    "                     0,  c.x, -s.x,\n"
    "                     0,  s.x,  c.x);\n"
    "    mat3 p = mat3( c.y,    0,  s.y,\n"
    "                     0,    1,    0,\n"
    "                  -s.y,    0,  c.y);\n"
    "    mat3 y = mat3( c.z, -s.z,    0,\n"
    "                   s.z,  c.z,    0,\n"
    "                     0,    0,    1);\n"
    "    return y * p * r;\n"
    "}\n"
    "void main()\n"
    "{\n"
    "   vec4 model = vec4(position.rgb + scale.rgb * (rpy2mat(rotation.rgb) * vertex), 1.0);\n"
    "   frag_position = model.rgb;\n"
    "   frag_normal = normal;\n"
    "   frag_coords = tex_uv;\n"
    "   gl_Position = projection * view * model;\n"
    "}\n";


// const char* sphere::vertex_shader_source =
//     "cbuffer VS_UNIFORMS // : register(b0)\n"
//     "{\n"
//     "   float4x4 proj;\n"
//     "   float4x4 view;\n"
//     "   float4   position;\n"
//     "   float4   rotation;\n"
//     "   float4   scale;\n"
//     "};\n"
//     "struct VS_INPUT\n"
//     "{\n"
//     "   float3 position : POSITION;\n"
//     // "   float3 normal   : NORMAL;\n"
//     // "   float2 texcoord : TEXCOORD;\n"
//     "};\n"
//     "struct VS_OUTPUT\n"
//     "{\n"
//     "   float4 posi : SV_POSITION;\n"
//     "   float4 position : POSITION;\n"
//     // "   float3 normal   : NORMAL;\n"
//     // "   float2 texcoord : TEXCOORD;\n"
//     "};\n"
//     "VS_OUTPUT main(VS_INPUT input)"
//     "{\n"
//     "   VS_OUTPUT output;\n"
//     "   float4 model    = position + scale * float4(input.position.xyz, 1.0f);\n"
//     "   output.posi = mul(proj, mul(view, model));\n"
//     "   output.position = model;\n"
//     // "   output.normal   = input.normal;\n"
//     // "   output.texcoord = input.texcoord;\n"
//     "   return output;\n"
//     "}\n";


const char* sphere::fragment_shader_source =
    "#version 330 core\n"
    "in vec3 frag_position;\n"
    "in vec3 frag_normal;\n"
    "in vec2 frag_coords;\n"
    "layout (std140) uniform FragmentUniforms\n"
    "{\n"
    "   vec4 tint_color;\n"
    "   vec4 light_color;\n"
    "   vec4 light_position;\n"
    "};\n"
    "uniform sampler2D texture_sampler;\n"
    "out vec4 frag_color;\n"
    "void main()\n"
    "{\n"
    "   vec3 eye = vec3(0.0, 0.0, 0.0);\n"
    "   vec3 norm = normalize(frag_normal);\n"
    "   vec3 light = normalize(light_position.rgb - frag_position);\n"
    "   vec3 refl = normalize(reflect(-light_position.rgb, norm));\n"
    "   vec3 view = normalize(eye - frag_position);\n"
    "   vec4 sample = texture(texture_sampler, frag_coords);"
    "   vec3 color = tint_color.rgb * sample.rgb * light_color.rgb;\n"
    "   vec3 ambient = color;\n"
    "   vec3 diffuse = color * max(dot(light, norm), 0.0);\n"
    "   vec3 specular = light_color.rgb * pow(max(dot(refl, view), 0.0), 32);\n"
    "   frag_color = vec4(0.1 * ambient + 0.9 * diffuse + 0.5 * specular, 1.0);\n"
    "   frag_color = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "}\n";


// const char* sphere::fragment_shader_source =
//     "sampler sampler0;\n"
//     "Texture2D texture0;\n"
//     "cbuffer PS_UNIFORMS\n"
//     "{\n"
//     "    float4 tint_color;\n"
//     "    float4 light_color;\n"
//     "    float4 light_position;\n"
//     "};\n"
//     "struct PS_INPUT\n"
//     "{\n"
//     "   float4 sv_position : SV_POSITION;\n"
//     "   float4 position : POSITION;\n"
//     // "   float3 normal   : NORMAL;\n"
//     // "   float2 texcoord : TEXCOORD;\n"
//     "};\n"
//     "float4 main(PS_INPUT input) : SV_TARGET\n"
//     "{\n"
//     // "   float3 eye = float3(0.0f, 0.0f, 0.0f);\n"
//     // "   float3 norm  = normalize(input.normal);\n"
//     // "   float3 light   = normalize(light_position - input.position);\n"
//     // "   float3 refl = normalize(reflect(-light_position, norm));\n"
//     // "   float3 view = normalize(eye - input.position);\n"
//     // "   float4 sample = texture0.Sample(sampler0, input.texcoord);\n"
//     // "   float3 color   = tint_color.xyz * light_color * sample.xyz;\n"
//     // "   float3 color   = tint_color.xyz * light_color;\n"
//     // "   float3 ambient = color;\n"
//     // "   float3 diffuse = color * max(dot(light, norm), 0.0f);\n"
//     // "   float3 specular = light_color * pow(max(dot(refl, view), 0.0), 32);\n"
//     // "   return float4(0.1f * ambient + 0.9f * diffuse + 0.5f * specular, 1.0f);\n"
//     "   return float4(1.0f, 1.0f, 1.0f, 1.0f);\n"
//     "}\n";


// const float sphere::vertex_data[] =
// {
//     -0.5f, -0.5f, 0.5f,      0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
//      0.5f, -0.5f, 0.5f,      0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
//      0.5f,  0.5f, 0.5f,      0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
//     -0.5f,  0.5f, 0.5f,      0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
//
//      0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
//      0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
//      0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
//      0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
//
//      0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
//     -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
//     -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
//      0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
//
//     -0.5f, -0.5f, -0.5f,    -1.0f,  1.0f,  0.0f,     0.0f,  0.0f,
//     -0.5f, -0.5f,  0.5f,    -1.0f,  1.0f,  0.0f,     1.0f,  0.0f,
//     -0.5f,  0.5f,  0.5f,    -1.0f,  1.0f,  0.0f,     1.0f,  1.0f,
//     -0.5f,  0.5f, -0.5f,    -1.0f,  1.0f,  0.0f,     0.0f,  1.0f,
//
//     -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
//      0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
//      0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
//     -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
//
//     -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
//      0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
//      0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
//     -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
// };


// const int sphere::index_data[] =
// {
//      0,  1,  2,
//      2,  3,  0,
//
//      4,  5,  6,
//      6,  7,  4,
//
//      8,  9, 10,
//     10, 11,  8,
//
//     12, 13, 14,
//     14, 15, 12,
//
//     16, 17, 18,
//     18, 19, 16,
//
//     20, 21, 22,
//     22, 23, 20,
// };
// const int sphere::num_indices = sizeof(index_data)/sizeof(index_data[0]);


sphere::sphere(render::core* core)
{
    render = core;
    setup(0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f,
          1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f);
    generate();
    init();
}


sphere::sphere(render::core* core,
         float p_x, float p_y, float p_z,
         float r_x, float r_y, float r_z,
         float s_x, float s_y, float s_z,
         float c_r, float c_g, float c_b)
{
    render = core;
    setup(p_x, p_y, p_z,
          r_x, r_y, r_z,
          s_x, s_y, s_z,
          c_r, c_g, c_b);
    generate();
    init();
}


sphere::~sphere()
{

}

void sphere::generate()
{
    float PI = acos(-1.0f);

    float radius = 0.5f;

// lat/long chunks
    float longitude_count = 48;
    float latitude_count = 24;

    float longitude_step = 2.0f * PI / longitude_count;
    float latitude_step = PI / latitude_count;

    // vertices
    for(int i = 0; i <= latitude_count; i++)
    {
        float latitude_angle =  (latitude_step * (float)i) - (PI / 2.0f);
        float xy = radius * cosf(latitude_angle);
        float z = radius * sinf(latitude_angle);

        for(int j = 0; j <= longitude_count; j++)
        {
            float longitude_angle = longitude_step * (float)j;

            float x = xy * cosf(longitude_angle);
            float y = xy * sinf(longitude_angle);

            vertex_data.push_back(x);
            vertex_data.push_back(y);
            vertex_data.push_back(z);
        }
    }

    // indices
    for(int i = 0; i < latitude_count; i++)
    {
        int p0 = i * ((int)longitude_count + 1);
        int p1 = p0 + (int)longitude_count + 1;

        for(int j = 0; j < longitude_count; j++)
        {
            if(i != 0)
            {
                index_data.push_back(p0);
                index_data.push_back(p0 + 1);
                index_data.push_back(p1 + 1);
            }

            if(i != (latitude_count - 1))
            {
                index_data.push_back(p0);
                index_data.push_back(p1 + 1);
                index_data.push_back(p1);
            }

            p0++;
            p1++;
        }
    }
}


void sphere::setup(float p_x, float p_y, float p_z,
                float r_x, float r_y, float r_z,
                float s_x, float s_y, float s_z,
                float c_r, float c_g, float c_b)
{
    position(p_x, p_y, p_z);
    rotation(r_x, r_y, r_z);
    scale(s_x, s_y, s_z);
    color(c_r, c_g, c_b);

    light(1.0f, 1.0f, 1.0f,
          0.0f, 0.0f, 0.0f);

    memcpy(&vs_uniform_data.proj, camera.projection_matrix, 16 * sizeof(float));
    memcpy(&vs_uniform_data.view, camera.view_matrix, 16 * sizeof(float));
}


void sphere::position(float x, float y, float z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;

    vs_uniform_data.position[0] = pos_x;
    vs_uniform_data.position[1] = pos_y;
    vs_uniform_data.position[2] = pos_z;
    vs_uniform_data.position[3] = 1.0f;
}


void sphere::rotation(float x, float y, float z)
{
    rot_x = x;
    rot_y = y;
    rot_z = z;

    vs_uniform_data.rotation[0] = rot_x;
    vs_uniform_data.rotation[1] = rot_y;
    vs_uniform_data.rotation[2] = rot_z;
    vs_uniform_data.rotation[3] = 1.0f;
}


void sphere::scale(float x, float y, float z)
{
    sca_x = x;
    sca_y = y;
    sca_z = z;

    vs_uniform_data.scale[0] = sca_x;
    vs_uniform_data.scale[1] = sca_y;
    vs_uniform_data.scale[2] = sca_z;
    vs_uniform_data.scale[3] = 1.0f;
}


void sphere::color(float r, float g, float b)
{
    col_r = r;
    col_g = g;
    col_b = b;

    fs_uniform_data.tint_color[0] = col_r;
    fs_uniform_data.tint_color[1] = col_g;
    fs_uniform_data.tint_color[2] = col_b;
    fs_uniform_data.tint_color[3] = 1.0f;
}


void sphere::light(float r, float g, float b,
                float x, float y, float z)
{
    light_r = r;
    light_g = g;
    light_b = b;

    fs_uniform_data.light_color[0] = light_r;
    fs_uniform_data.light_color[1] = light_g;
    fs_uniform_data.light_color[2] = light_b;
    fs_uniform_data.light_color[3] = 1.0f;

    light_x = x;
    light_y = y;
    light_z = z;

    fs_uniform_data.light_position[0] = light_x;
    fs_uniform_data.light_position[1] = light_y;
    fs_uniform_data.light_position[2] = light_z;
    fs_uniform_data.light_position[3] = 0.0f;
}


void sphere::init()
{
    render::shader_desc vs_desc = { render::shader_type::vertex, vertex_shader_source };
    vs = render->create_shader(vs_desc);

    render::shader_desc fs_desc = { render::shader_type::fragment, fragment_shader_source };
    fs = render->create_shader(fs_desc);

    render::program_desc sp_desc = { vs, fs };
    sp = render->create_program(sp_desc);



// TODO: static file loader
//////////////////////////////
    render::texture_desc tx_desc = {};
    // const char* filename = "E:\\dev\\scaling-potato\\bin\\Debug-x64\\platform\\wall.png";
    const char* filename = "\\\\BILL\\Users\\Public\\Public Games\\wall.png";

    int channels;
    stbi_set_flip_vertically_on_load(true);
    tx_desc.data = stbi_load(filename, &tx_desc.width, &tx_desc.height, &channels, 0);

    tx = render->create_texture(tx_desc);

    stbi_image_free(tx_desc.data);
////////////////////////////////////

    render::sampler_desc s_desc = {};
    ts = render->create_sampler(s_desc);


    ob = render->create_object();
    ob->bind();

    render::buffer_desc vb_desc = { render::buffer_type::vertex, (int)vertex_data.size() * sizeof(float), (void*)vertex_data.data() };
    vb = render->create_buffer(vb_desc);

    render::buffer_desc ib_desc = { render::buffer_type::index, (int)index_data.size() * sizeof(int), (void*)index_data.data() };
    ib = render->create_buffer(ib_desc);

    lo = render->create_layout(lo_desc, 1);

    render::buffer_desc vs_ub_desc = { render::buffer_type::uniform, sizeof(vs_uniform_data), &vs_uniform_data };
    vs_ub = render->create_buffer(vs_ub_desc);

    render::buffer_desc fs_ub_desc = { render::buffer_type::uniform, sizeof(fs_uniform_data), &fs_uniform_data };
    fs_ub = render->create_buffer(fs_ub_desc);


// TODO: these are very opengl goofy ass binds; after d3d11, clean them up
/////////////////////////////////

    // The D3D11 calls are shader-named and take pointers to the buffers and texture/sampler
    // objects. The best approach might be to pass all objects into the shader program in such
    // a way that they are bound to my abstraction for easy binding/setting by the pre-draw call
    // that binds the shader program.

    // If I can stuff all the miscellaneous actions into the shader program we can have
    // a good start to treating it as part of a material and having the render_object only
    // contain buffers and "material"/shader program sub-objects


    // NOTE:
    // So add the uniform strings to the uniform buffer descriptor or create a new descriptor
    // for binding these up to the shader program { vtx/frag_sdr, block_name_str }

    sp->bind_uniform_block(2, "VertexUniforms"); // VSSetConstantBuffers
    sp->bind_uniform_block(3, "FragmentUniforms"); // PSSetConstantBuffers
    sp->bind_sampler(0, "texture_sampler"); // PSSetSamplers, PSSetShaderResources???????

    vs_ub->bind_uniform_block(2);
    fs_ub->bind_uniform_block(3);


    // NOTE:
    // These are the d3d11 binding versions

    ob->bind_vbuf(vb);
    ob->bind_ibuf(ib);

    ob->bind_layout(lo);

    sp->bind_vs_const_block(vs_ub);
    sp->bind_fs_const_block(fs_ub);
    sp->bind_texture(tx);
    sp->bind_sampler(ts);
    sp->bind_layout(lo);

//////////////////////////////


    ob->unbind();
}


void sphere::draw()
{
    sp->bind();
    tx->bind();  // wrap up into sp??

    vs_ub->sub(&vs_uniform_data);
    fs_ub->sub(&fs_uniform_data);

    ob->bind();
    ob->draw(index_data.size()); // TODO: store indices inside object
    ob->unbind();
}
