#include "gl_render_utils.cpp"


const char *vertex_shader_source =
    "#version 330 core\n"
    "in vec3 position;\n"
    "in vec3 color;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
    "out vec3 outColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * vec4(position, 1.0);\n"
    "   outColor = color;\n"
    "}\n";

const char *fragment_shader_source =
    "#version 330 core\n"
    "in vec3 outColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(outColor, 1.0);\n"
    "}\n";

static gl_program shader_program;
static GLint projection_uniform;
static GLint view_uniform;

static GLuint vertex_array;
static GLuint vertex_buffer;
static GLuint index_buffer;

static float vertex_data[] =
{
    -0.5f, -0.5f, 0.2f, 0.6f, 0.4f, 0.2f,
     0.5f, -0.5f, 0.2f, 0.2f, 0.4f, 0.6f,
     0.5f,  0.5f, 0.2f, 0.6f, 0.4f, 0.2f,
    -0.5f,  0.5f, 0.2f, 0.2f, 0.4f, 0.6f,
};

static int index_data[] =
{
    0, 1, 2, 2, 3, 0
};
static int num_indices = 6;

static float f = 100.0f;
static float n = 0.1f;
static float aspect = 16.0f / 9.0f;

static float projection_matrix[] =
{
    1.0f/aspect,  0.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,  0.0f,
    0.0f,  0.0f, -2.0f/(f-n),  -(f+n)/(f-n),
    0.0f,  0.0f,  0.0f,  1.0f,
};

static float view_matrix[] =
{
    1.0f,  0.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  1.0f,  0.0f,
    0.0f,  0.0f,  0.0f,  1.0f,
};

static void example_setup()
{
// Shader setup
    shader_program = gl_create_program(vertex_shader_source, fragment_shader_source);

    GLuint program = shader_program.id;

    projection_uniform = glGetUniformLocation(program, "projection");
    view_uniform = glGetUniformLocation(program, "view");

    GLint position_in = glGetAttribLocation(program, "position");
    GLint color_in = glGetAttribLocation(program, "color");

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
    glVertexAttribPointer(position_in, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(position_in);
    glVertexAttribPointer(color_in, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(color_in);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

// Unbind everything
    glUseProgram(0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

static void example_loop()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind the shaders and VAO
    glUseProgram(shader_program.id);
    glBindVertexArray(vertex_array);

    // Update the camera properties for the shaders
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, projection_matrix);
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, view_matrix);

    // Render!
    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);

    // Ubind the shaders and VAO
    glUseProgram(0);
    glBindVertexArray(0);
}
