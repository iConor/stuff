#include "box_mesh.h"


#include <string.h>


#include "d3d11_buffer.h"
#include "d3d11_layout.h"
#include "d3d11_shader.h"
#include "d3d11_shader_program.h"
#include "d3d11_texture.h"


float f = 10.0f;
float n = 0.1f;
float aspect = 16.0f / 9.0f;


// OpenGL
// float projection_matrix[] =
// {
//     1.0f/aspect,  0.0f,  0.0f,  0.0f,
//     0.0f,  1.0f,  0.0f,  0.0f,
//     0.0f,  0.0f,  f/(f-n),  -1.0f,
//     0.0f,  0.0f,  (f*n)/(f-n),  0.0f,
// };


// Direct3D
float projection_matrix[] =
{
    1.0f/aspect,  0.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  f/(n-f), -1.0f ,
    0.0f,  0.0f,  (f*n)/(n-f),  0.0f,
};


float view_matrix[] =
{
     1.0f,  0.0f,  0.0f,  0.0f,
     0.0f,  1.0f,  0.0f,  0.0f,
     0.0f,  0.0f,  1.0f,  0.0f,
     0.0f,  0.0f,  0.0f,  1.0f,
};


// GLSL
// const char* box_mesh::vertex_shader_source =
//     "#version 330 core\n"
//     "layout (location = 0) in vec3 vertex;\n"
//     "layout (location = 1) in vec3 normal;\n"
//     "layout (location = 2) in vec2 tex_uv;\n"
//     "layout (std140) uniform VertexUniforms\n"
//     "{\n"
//     "   mat4 projection;\n"
//     "   mat4 view;\n"
//     "   vec4 position;\n"
//     "   vec4 rotation;\n"
//     "   vec4 scale;\n"
//     "};\n"
//     "out vec3 frag_position;\n"
//     "out vec3 frag_normal;\n"
//     "out vec2 frag_coords;\n"
//     "mat3 rpy2mat(in vec3 rpy)\n"
//     "{\n"
//     "    vec3 rads = radians(rpy);\n"
//     "    vec3 c = cos(rads);\n"
//     "    vec3 s = sin(rads);\n"
//     "    mat3 r = mat3(   1,    0,    0,\n"
//     "                     0,  c.x, -s.x,\n"
//     "                     0,  s.x,  c.x);\n"
//     "    mat3 p = mat3( c.y,    0,  s.y,\n"
//     "                     0,    1,    0,\n"
//     "                  -s.y,    0,  c.y);\n"
//     "    mat3 y = mat3( c.z, -s.z,    0,\n"
//     "                   s.z,  c.z,    0,\n"
//     "                     0,    0,    1);\n"
//     "    return y * p * r;\n"
//     "}\n"
//     "void main()\n"
//     "{\n"
//     "   vec4 model = vec4(position.rgb + scale.rgb * (rpy2mat(rotation.rgb) * vertex), 1.0);\n"
//     "   frag_position = model.rgb;\n"
//     "   frag_normal = normal;\n"
//     "   frag_coords = tex_uv;\n"
//     "   gl_Position = projection * view * model;\n"
//     "}\n";


// GLSL
// const char* box_mesh::fragment_shader_source =
//     "#version 330 core\n"
//     "in vec3 frag_position;\n"
//     "in vec3 frag_normal;\n"
//     "in vec2 frag_coords;\n"
//     "layout (std140) uniform FragmentUniforms\n"
//     "{\n"
//     "   vec4 tint_color;\n"
//     "   vec4 light_color;\n"
//     "   vec4 light_position;\n"
//     "};\n"
//     "uniform sampler2D texture_sampler;\n"
//     "out vec4 frag_color;\n"
//     "void main()\n"
//     "{\n"
//     "   vec3 eye = vec3(0.0, 0.0, 0.0);\n"
//     "   vec3 norm = normalize(frag_normal);\n"
//     "   vec3 light = normalize(light_position.rgb - frag_position);\n"
//     "   vec3 refl = normalize(reflect(-light_position.rgb, norm));\n"
//     "   vec3 view = normalize(eye - frag_position);\n"
//     "   vec4 sample = texture(texture_sampler, frag_coords);"
//     "   vec3 color = tint_color.rgb * sample.rgb * light_color.rgb;\n"
//     "   vec3 ambient = color;\n"
//     "   vec3 diffuse = color * max(dot(light, norm), 0.0);\n"
//     "   vec3 specular = light_color.rgb * pow(max(dot(refl, view), 0.0), 32);\n"
//     "   frag_color = vec4(0.1 * ambient + 0.9 * diffuse + 0.5 * specular, 1.0);\n"
//     "}\n";


// HLSL
const char* box_mesh::vertex_shader_source =
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

// HLSL Pixel Shader
const char* box_mesh::fragment_shader_source =
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


const float box_mesh::vertex_data[] =
{
    -0.5f, -0.5f, 0.5f,      0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
     0.5f, -0.5f, 0.5f,      0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
     0.5f,  0.5f, 0.5f,      0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
    -0.5f,  0.5f, 0.5f,      0.0f,  0.0f,  1.0f,     0.0f,  1.0f,

     0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,

     0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     0.0f,  1.0f,

    -0.5f, -0.5f, -0.5f,    -1.0f,  1.0f,  0.0f,     0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,    -1.0f,  1.0f,  0.0f,     1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,    -1.0f,  1.0f,  0.0f,     1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,    -1.0f,  1.0f,  0.0f,     0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     0.0f,  1.0f,

    -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
};


const int box_mesh::index_data[] =
{
     0,  1,  2,
     2,  3,  0,

     4,  5,  6,
     6,  7,  4,

     8,  9, 10,
    10, 11,  8,

    12, 13, 14,
    14, 15, 12,

    16, 17, 18,
    18, 19, 16,

    20, 21, 22,
    22, 23, 20,
};
const int box_mesh::num_indices = sizeof(index_data)/sizeof(index_data[0]);


box_mesh::box_mesh()
{
    setup(0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f,
          1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f);

    create();
}


box_mesh::box_mesh(float p_x, float p_y, float p_z,
                   float r_x, float r_y, float r_z,
                   float s_x, float s_y, float s_z,
                   float c_r, float c_g, float c_b)
{
    setup(p_x, p_y, p_z,
          r_x, r_y, r_z,
          s_x, s_y, s_z,
          c_r, c_g, c_b);

    create();
}


box_mesh::~box_mesh()
{
    delete vertex_buffer;
    delete index_buffer;
    delete layout;
    delete shader_program;
    delete texture;
}


void box_mesh::setup(float p_x, float p_y, float p_z,
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

    memcpy(&vs_uniform_data.proj, projection_matrix, sizeof(projection_matrix));
    memcpy(&vs_uniform_data.view, view_matrix, sizeof(view_matrix));
}

// GLuint VAO;

void box_mesh::create()
{
    // Shader
    renderer::shader_desc vs_desc = { renderer::shader_type::vertex, vertex_shader_source };
    renderer::shader* vertex_shader = new renderer::d3d11_shader(vs_desc);

    renderer::shader_desc fs_desc = { renderer::shader_type::fragment, fragment_shader_source };
    renderer::shader* fragment_shader = new renderer::d3d11_shader(fs_desc);

    renderer::shader_program_desc sp_desc = { vertex_shader, fragment_shader };
    shader_program = new renderer::d3d11_shader_program(sp_desc);

    texture = new renderer::d3d11_texture("E:\\dev\\scaling-potato\\bin\\Debug-x64\\platform\\wall.png");
    // texture = new renderer::d3d11_texture("\\\\BILL\\Users\\Public\\Public Games\\wall.png");


// Buffers
    renderer::buffer_desc vb_desc = { renderer::buffer_type::vertex, sizeof(vertex_data), vertex_data };
    vertex_buffer = new renderer::d3d11_buffer(vb_desc);

    renderer::buffer_desc ib_desc = { renderer::buffer_type::index, sizeof(index_data), index_data };
    index_buffer = new renderer::d3d11_buffer(ib_desc);

// Layout
    // TODO: This should be static constant data
    renderer::layout_desc l_desc[] =
    {
        { "NORMAL",   3 },
        { "POSITION", 3 },
        { "TEXCOORD", 2 },
    };
    layout = new renderer::d3d11_layout(l_desc, 3);

    renderer::buffer_desc vs_ub_desc = { renderer::buffer_type::uniform, sizeof(vs_uniform_data), &vs_uniform_data };
    vs_uniform_buffer = new renderer::d3d11_buffer(vs_ub_desc);

    renderer::buffer_desc fs_ub_desc = { renderer::buffer_type::uniform, sizeof(fs_uniform_data), &fs_uniform_data };
    fs_uniform_buffer = new renderer::d3d11_buffer(fs_ub_desc);


    renderer::d3d11_shader_program* sp = static_cast<renderer::d3d11_shader_program*>(shader_program);
    // sp->bind_uniform_block(0, "VertexUniforms");
    // sp->bind_uniform_block(1, "FragmentUniforms");
    // sp->bind_sampler(0, "texture_sampler");

    renderer::d3d11_buffer* vs_ub = static_cast<renderer::d3d11_buffer*>(vs_uniform_buffer);
    // vs_ub->bind_uniform_block(0);

    renderer::d3d11_buffer* fs_ub = static_cast<renderer::d3d11_buffer*>(fs_uniform_buffer);
    // fs_ub->bind_uniform_block(1);

}


void box_mesh::draw()
{
    // TODO: bind things
    // texture
    // texture->bind();
    //  v_buffer
    // i_buffer
    // layout?????
    shader_program->bind();

    renderer::d3d11_buffer* vs_ub = static_cast<renderer::d3d11_buffer*>(vs_uniform_buffer);
    vs_ub->sub(&vs_uniform_data);

    renderer::d3d11_buffer* fs_ub = static_cast<renderer::d3d11_buffer*>(fs_uniform_buffer);
    fs_ub->sub(&fs_uniform_data);



////

    // TODO: Uniform buffer!

////

    // TODO: should go on the aggregate render object
    // glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);

}


void box_mesh::position(float x, float y, float z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;

    vs_uniform_data.position[0] = pos_x;
    vs_uniform_data.position[1] = pos_y;
    vs_uniform_data.position[2] = pos_z;
    vs_uniform_data.position[3] = 1.0f;
}


void box_mesh::rotation(float x, float y, float z)
{
    rot_x = x;
    rot_y = y;
    rot_z = z;

    vs_uniform_data.rotation[0] = rot_x;
    vs_uniform_data.rotation[1] = rot_y;
    vs_uniform_data.rotation[2] = rot_z;
    vs_uniform_data.rotation[3] = 1.0f;
}


void box_mesh::scale(float x, float y, float z)
{
    sca_x = x;
    sca_y = y;
    sca_z = z;

    vs_uniform_data.scale[0] = sca_x;
    vs_uniform_data.scale[1] = sca_y;
    vs_uniform_data.scale[2] = sca_z;
    vs_uniform_data.scale[3] = 1.0f;
}


void box_mesh::color(float r, float g, float b)
{
    col_r = r;
    col_g = g;
    col_b = b;

    fs_uniform_data.tint_color[0] = col_r;
    fs_uniform_data.tint_color[1] = col_g;
    fs_uniform_data.tint_color[2] = col_b;
    fs_uniform_data.tint_color[3] = 1.0f;
}


void box_mesh::light(float r, float g, float b,
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
