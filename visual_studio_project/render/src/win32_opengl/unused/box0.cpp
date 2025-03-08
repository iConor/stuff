#include "box.h"

#include "camera.h"

// #include "windows.h"
// #include "gl/gl.h"


namespace render
{
const char* box::vertex_shader_source =
    "#version 330 core\n"
    "in vec3 vertex;\n"
    "uniform vec3 position;\n"
    "uniform vec3 rotation;\n"
    "uniform vec3 scale;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
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
    "   vec4 model = vec4(position + scale * (rpy2mat(rotation) * vertex), 1.0);\n"
    "   gl_Position = projection * view * model;\n"
    "}\n";

const char* box::fragment_shader_source =
    "#version 330 core\n"
    "uniform vec3 tint_color;\n"
    "uniform vec3 light_color;\n"
    "uniform vec3 light_position;\n"
    "out vec4 frag_color;\n"
    "void main()\n"
    "{\n"
    "   vec3 color = tint_color * light_color;\n"
    "   vec3 ambient = color;\n"
    "   vec3 diffuse = color;\n"
    "   vec3 specular = color;\n"
    "   frag_color = vec4(0.1 * ambient + 0.0 * diffuse + 0.0 * specular, 1.0);\n"
    "}\n";

const float box::vertex_data[] =
{
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
};

const int box::index_data[] =
{
    0, 1, 2,    2, 3, 0,
    1, 6, 5,    5, 2, 1,
    6, 7, 4,    4, 5, 6,
    7, 0, 3,    3, 4, 7,
    3, 2, 5,    5, 4, 3,
    7, 6, 1,    1, 0, 7,
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
    delete shader_program;
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
    color_uniform = glGetUniformLocation(program, "tint_color");
    light_color_uniform = glGetUniformLocation(program, "light_color");
    light_position_uniform = glGetUniformLocation(program, "light_position");
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    // EBO (VIO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);
    // Layout
    glVertexAttribPointer(vertex_attrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vertex_attrib);
    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void box::draw()
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
    glUniform3f(light_color_uniform, light_r, light_g, light_b);
    glUniform3f(light_position_uniform, light_x, light_y, light_z);

    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);

    glUseProgram(0);
    glBindVertexArray(0);
}


void box::draw_edges()
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


void box::position(float x, float y, float z)
{
    pos_x = x;
    pos_y = y;
    pos_z = z;
}


void box::rotation(float x, float y, float z)
{
    rot_x = x;
    rot_y = y;
    rot_z = z;
}


void box::scale(float x, float y, float z)
{
    sca_x = x;
    sca_y = y;
    sca_z = z;
}


void box::color(float r, float g, float b)
{
    col_r = r;
    col_g = g;
    col_b = b;
}


void box::light(float r, float g, float b,
                float x, float y, float z)
{
    light_r = r;
    light_g = g;
    light_b = b;

    light_x = x;
    light_y = y;
    light_z = z;
}


}
