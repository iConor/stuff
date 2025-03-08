#include "sphere.h"

#include "camera.h"

// #include "windows.h"
// #include "gl/gl.h"

#include <cmath>

namespace render
{
const char* sphere::vertex_shader_source =
    "#version 330 core\n"
    "in vec3 vertex;\n"
    "uniform vec3 position;\n"
    "uniform vec3 rotation;\n"
    "uniform vec3 scale;\n"
    "uniform vec3 color;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
    "out vec3 outColor;\n"
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
    "   gl_Position = projection * view * vec4(position + scale * (rpy2mat(rotation) * vertex), 1.0);\n"
    "   outColor = color;\n"
    "}\n";

const char* sphere::fragment_shader_source =
    "#version 330 core\n"
    "in vec3 outColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(outColor, 1.0);\n"
    "}\n";


sphere::sphere()
{
    setup(0.0f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f,
          1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f);
}


sphere::sphere(float p_x, float p_y, float p_z,
               float r_x, float r_y, float r_z,
               float s_x, float s_y, float s_z,
               float c_r, float c_g, float c_b)
{

    setup(p_x, p_y, p_z,
          r_x, r_y, r_z,
          s_x, s_y, s_z,
          c_r, c_g, c_b);
}


sphere::~sphere()
{
    delete shader_program;
}


void sphere::layout_data()
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

    layout_data();

// Shader setup
    shader_program = new shader(vertex_shader_source, fragment_shader_source);
    GLuint program = shader_program->id();
    // Camera
    projection_uniform = glGetUniformLocation(program, "projection");
    view_uniform = glGetUniformLocation(program, "view");
    // Transform
    position_uniform = glGetUniformLocation(program, "position");
    rotation_uniform = glGetUniformLocation(program, "rotation");
    scale_uniform = glGetUniformLocation(program, "scale");
    // Color
    color_uniform = glGetUniformLocation(program, "color");
    // Vertices
    GLint vertex_attrib = glGetAttribLocation(program, "vertex");

// Buffer setup
    glGenVertexArrays(1, &vertex_array);
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    // VAO
    glBindVertexArray(vertex_array);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertex_data.size() * sizeof(float)), vertex_data.data(), GL_STATIC_DRAW);
    // EBO (VIO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(index_data.size() * sizeof(int)), index_data.data(), GL_STATIC_DRAW);
    // Layout
    glVertexAttribPointer(vertex_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vertex_attrib);
    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void sphere::draw()
{
    glUseProgram(shader_program->id());
    glBindVertexArray(vertex_array);

    // Camera
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, ex::camera::proj_mat());
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, ex::camera::view_mat());
    // Transform
    glUniform3f(position_uniform, pos_x, pos_y, pos_z);
    glUniform3f(rotation_uniform, rot_x, rot_y, rot_z);
    glUniform3f(scale_uniform, sca_x, sca_y, sca_z);
    // Color
    glUniform3f(color_uniform, col_r, col_g, col_b);

    glDrawElements(GL_TRIANGLES, (GLsizei)index_data.size(), GL_UNSIGNED_INT, 0);

    glUseProgram(0);
    glBindVertexArray(0);
}


void sphere::draw_edges()
{
    draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float r = col_r;
    float g = col_g;
    float b = col_b;

    col_r = 0.0f;
    col_g = 0.0f;
    col_b = 0.0f;

    draw();

    col_r = r;
    col_g = g;
    col_b = b;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void sphere::position(float x, float y, float z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;
}


void sphere::rotation(float x, float y, float z)
{
    rot_x = x;
    rot_y = y;
    rot_z = z;
}


void sphere::scale(float x, float y, float z)
{
    sca_x = x;
    sca_y = y;
    sca_z = z;
}


void sphere::color(float r, float g, float b)
{
    col_r = r;
    col_g = g;
    col_b = b;
}

}
