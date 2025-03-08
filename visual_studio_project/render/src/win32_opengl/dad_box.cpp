#include "dad_box.h"

#include "camera.h"

// #include "windows.h"
// #include "gl/gl.h"


namespace render
{
const char* dad_box::vertex_shader_source =
    "#version 330 core\n"
    "in vec3 vertex;\n"
    "in vec3 color;\n"
    "uniform vec3 position;\n"
    "uniform vec3 rotation;\n"
    "uniform vec3 scale;\n"
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

const char* dad_box::fragment_shader_source =
    "#version 330 core\n"
    "in vec3 outColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(outColor, 1.0);\n"
    "}\n";


const float dad_box::vertex_data[] =
{
    -0.5f, -0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f,

     0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,

     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
};


const int dad_box::index_data[] =
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
const int dad_box::num_indices = sizeof(index_data)/sizeof(index_data[0]);


dad_box::dad_box()
{
    setup();

    pos_x = 0.0f;
    pos_y = 0.0f;
    pos_z = 0.0f;

    rot_x = 0.0f;
    rot_y = 0.0f;
    rot_z = 0.0f;

    sca_x = 1.0f;
    sca_y = 1.0f;
    sca_z = 1.0f;
}


dad_box::dad_box(float p_x, float p_y, float p_z,
                 float r_x, float r_y, float r_z,
                 float s_x, float s_y, float s_z)
{
    setup();

    pos_x = p_x;
    pos_y = p_y;
    pos_z = p_z;

    rot_x = r_x;
    rot_y = r_y;
    rot_z = r_z;

    sca_x = s_x;
    sca_y = s_y;
    sca_z = s_z;
}


dad_box::~dad_box()
{
    delete shader_program;
}


void dad_box::setup()
{
// Shader setup
    shader_program = new shader(vertex_shader_source, fragment_shader_source);

    GLuint program = shader_program->id();

    projection_uniform = glGetUniformLocation(program, "projection");
    view_uniform = glGetUniformLocation(program, "view");

    position_uniform = glGetUniformLocation(program, "position");
    rotation_uniform = glGetUniformLocation(program, "rotation");
    scale_uniform = glGetUniformLocation(program, "scale");

    GLint vertex_attrib = glGetAttribLocation(program, "vertex");
    GLint color_attrib = glGetAttribLocation(program, "color");

// Buffer setup
    glGenVertexArrays(1, &vertex_array);
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
// VAO
    glBindVertexArray(vertex_array);
// VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
// EBO (VIO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

// Interleave vertex positions and colors
    glVertexAttribPointer(vertex_attrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vertex_attrib);
    glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(color_attrib);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

// Unbind everything
    glUseProgram(0);
    glBindVertexArray(0);
}


void dad_box::draw()
{
    // Bind the shaders and VAO
    glUseProgram(shader_program->id());
    glBindVertexArray(vertex_array);

    // Update the camera properties
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, ex::camera::proj_mat());
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, ex::camera::view_mat());

    // Update the box properties
    glUniform3f(position_uniform, pos_x, pos_y, pos_z);
    glUniform3f(rotation_uniform, rot_x, rot_y, rot_z);
    glUniform3f(scale_uniform, sca_x, sca_y, sca_z);

    // Render!
    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);

    // Ubind the shaders and VAO
    glUseProgram(0);
    glBindVertexArray(0);
}


void dad_box::position(float x, float y, float z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;
}


void dad_box::rotation(float x, float y, float z)
{
    rot_x = x;
    rot_y = y;
    rot_z = z;
}


void dad_box::scale(float x, float y, float z)
{
    sca_x = x;
    sca_y = y;
    sca_z = z;
}


}
