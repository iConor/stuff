#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#include "lib_vector.h"
#include "lib_matrix.h"

#include "color.cpp"
#include "terrain.cpp"

#include "render.h"

static int WIDTH = 1280;
static int HEIGHT = 720;


const char *vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "uniform mat4 projection;"
    "uniform mat4 view;"
    "flat out vec3 ourColor;"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view  * vec4(position, 1.0);\n"
    "   ourColor = color;\n"
    "}\n";

const char *fragment_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "flat in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n";

float deg2rad(float degrees)
{
    float radians = 0.0f;

    float convert = M_PI / 180.0f;

    radians = degrees * convert;

    return radians;
}
v3 hsv2rgb(float h, float s, float v)
{
    v3 out = {};

    float chroma = s * v;
    float hprime = h / 60.0f;

    float xfactor = chroma * (1.0f - fabsf(fmodf(hprime, 2.0f) - 1.0f));

    float m = v - chroma;

    out.r += m;
    out.g += m;
    out.b += m;

    if(0.0f <= hprime && hprime <= 1.0f)
    {
        out.r += chroma;
        out.g += xfactor;
    }
    else if(hprime <= 2.0f)
    {
        out.r += xfactor;
        out.g += chroma;
    }
    else if(hprime <= 3.0f)
    {
        out.g += chroma;
        out.b += xfactor;
    }
    else if(hprime <= 4.0f)
    {
        out.g += xfactor;
        out.b += chroma;
    }
    else if(hprime <= 5.0f)
    {
        out.r += xfactor;
        out.b += chroma;
    }
    else if(hprime <= 6.0f)
    {
        out.r += chroma;
        out.b += xfactor;
    }

    return out;
}
static void generate_vertices(float *vertex_data, int grid, float side)
{
    float offset = (float)grid * side / 2.0f;
    int max_vertex = grid + 1;

    srand(time(NULL));

    int index = 0;
    for(int y = 0; y < max_vertex; y++)
    {
        for(int x = 0; x < max_vertex; x++)
        {
            vertex_data[index++] = (side * x) - offset; // x
            vertex_data[index++] = (side * y) - offset; // y
            vertex_data[index++] = -1.0f; // z

            float h = (float)(rand() % 3600) / 10.0f;
            float s = 0.2f;
            float v = 0.8f;

            v3 color = hsv2rgb(h, s, v);

            vertex_data[index++] = color.r;
            vertex_data[index++] = color.g;

            vertex_data[index++] = color.b;
        }
    }
}


static void generate_indices(unsigned int *index_data, int grid)
{
    int base;
    int stride = grid + 1;

    int index = 0;
    for(int y = 0; y < grid; y++)
    {
        base = y * stride;

        for(int x = 0; x < grid; x++)
        {
            index_data[index++] = base;
            index_data[index++] = base + 1;
            index_data[index++] = base + 1 + stride;

            index_data[index++] = base + 1 + stride;
            index_data[index++] = base + stride;
            index_data[index++] = base;

            ++base;
        }
    }
}

static void print_vertices(float* vertex_data, int vertices)
{
    int index = 0;
    for(int i = 0; i < vertices; i++)
    {
        float a = vertex_data[index++];
        float b = vertex_data[index++];
        float c = vertex_data[index++];
        float d = vertex_data[index++];
        float e = vertex_data[index++];
        float f = vertex_data[index++];
        printf("x: %f, y: %f, z: %f\nr: %f, g: %f, b: %f\n\n", a, b, c, d, e, f);
    }
}

static void print_indices(unsigned int* index_data, int indices)
{
    int index = 0;
    for(int i = 0; i < indices; i++)
    {
        printf("%d\n", index_data[index++]);
    }
}


struct kbd_input
{
    int w_key;
    int a_key;
    int s_key;
    int d_key;

    v2 mouse;
};

static kbd_input process_input(GLFWwindow* window)
{
    kbd_input input = {};

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        input.w_key = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        input.a_key = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        input.s_key = 1;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        input.d_key = 1;
    }

    double pos_x;
    double pos_y;
    glfwGetCursorPos(window, &pos_x, &pos_y);
    input.mouse.x = (float)pos_x;
    input.mouse.y = (float)pos_y;

    return input;
}


int main(int argc, char* argv[])
{
// glfw
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello OpenGL", NULL, NULL);
    if(!window)
    {
        puts("Failed to create the window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // TODO: Am I to be error?

// glew
    if(glewInit() != GLEW_OK)
    {
        puts("Failed to initialize GLEW");
        glfwTerminate();
        return -1;
    }

// specific
    const int VERTEX_VECTOR_SIZE = 3;
    const int VERTEX_COLOR_SIZE = 3;

    const int VERTEX_SIZE = VERTEX_VECTOR_SIZE + VERTEX_COLOR_SIZE;

    const int VERTICES_PER_SIDE = 11;
    const int VERTICES_PER_MAP = VERTICES_PER_SIDE * VERTICES_PER_SIDE;

    const int VERTEX_DATA_SIZE = VERTEX_SIZE * VERTICES_PER_MAP;

    const int GRIDS_PER_SIDE = VERTICES_PER_SIDE - 1;
    const int GRIDS_PER_MAP = GRIDS_PER_SIDE * GRIDS_PER_SIDE;

    const int TRIANGLES_PER_MAP = GRIDS_PER_MAP * 2;

    const int INDEX_DATA_SIZE = TRIANGLES_PER_MAP * 3;

    float vertex_data[VERTEX_DATA_SIZE] = {};
    unsigned int index_data[INDEX_DATA_SIZE] = {};

    const float GRID_SIZE = 0.25f;

    generate_vertices(vertex_data, GRIDS_PER_SIDE, GRID_SIZE);
    // flatten_colors(vertex_data, GRIDS_PER_SIDE);

    generate_indices(index_data, GRIDS_PER_SIDE);
    // print_vertices(vertex_data, 25);
    // print_indices(index_data, INDEX_DATA_SIZE);

    unsigned int program = create_program(vertex_shader_source, fragment_shader_source);

// vao
    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

// vbo
    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

// vio
    unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

// detach all
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    float camera_mps = 0.025f;
    float mouse_sensitivity = 0.000625f;

///////////////////////////////////////////////////////////////

    float aspect_ratio = (float)WIDTH / (float)HEIGHT;
    float field_of_view = 45.0f;
    float focal_length = tanf(deg2rad(field_of_view / 2.0f));
    float near_plane = 0.1f;
    float far_plane = 100.0f;

    float m00 = focal_length;
    float m11 = focal_length * aspect_ratio;
    float m22 = (far_plane + near_plane) / (near_plane - far_plane);
    float m23 = 2.0f * far_plane * near_plane / (near_plane - far_plane);

    float projection_matrix[] =
    {
         m00, 0.0f,  0.0f,  0.0f,
        0.0f,  m11,  0.0f,  0.0f,
        0.0f, 0.0f,  m22,    m23,
        0.0f, 0.0f, -1.0f,  0.0f,
    };

    int projection_uniform = glGetUniformLocation(program, "projection");
    int view_uniform = glGetUniformLocation(program, "view");

    kbd_input old_input = process_input(window);

    float yaw = 0.0f;
    float pitch = 0.0f;

    v4 camera_pos = {};

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        kbd_input input = process_input(window);

        v2 mouse_delta = old_input.mouse - input.mouse;
        mouse_delta *= mouse_sensitivity;

        yaw += mouse_delta.x;
        pitch += mouse_delta.y;

        // gimbal lock esta no bueno
        if(pitch > 89.0f)
        {
            pitch = 89.0f;
        }
        else if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }

        v4 camera_delta = {};

        if(input.w_key)
        {
            camera_delta.z -= camera_mps;
        }
        if(input.a_key)
        {
            camera_delta.x -= camera_mps;
        }
        if(input.s_key)
        {
            camera_delta.z += camera_mps;
        }
        if(input.d_key)
        {
            camera_delta.x += camera_mps;
        }

        float cx = cosf(pitch);
        float sx = sinf(pitch);
        float cy = cosf(yaw);
        float sy = sinf(yaw);

        m4 rotation_matrix =
        {
               cy, sx*sy, cx*sy, 0.0f,
             0.0f,    cx,   -sx, 0.0f,
              -sy, sx*cy, cx*cy, 0.0f,
             0.0f,  0.0f,  0.0f, 1.0f,
        };


        camera_delta = rotation_matrix * camera_delta;
        camera_pos += camera_delta;

        v4 camera_shift = rotation_matrix * camera_pos;

        m4 view_matrix = rotation_matrix;
        view_matrix.m[0][3] = camera_shift.x;
        view_matrix.m[1][3] = camera_shift.y;
        view_matrix.m[2][3] = camera_shift.z;


        old_input = input;

        // glDrawArrays(GL_TRIANGLES, 0, vertex_count);

        // glPointSize(20);
        // glLineWidth(2);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawElements(GL_TRIANGLES, INDEX_DATA_SIZE, GL_UNSIGNED_INT, 0);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

// set thing to update and render
        glUseProgram(program);
        glBindVertexArray(vertex_array);
// update
        glUniformMatrix4fv(projection_uniform, 1, GL_TRUE, projection_matrix);
        glUniformMatrix4fv(view_uniform, 1, GL_TRUE, view_matrix.e);
// and render
        glDrawElements(GL_TRIANGLES, INDEX_DATA_SIZE, GL_UNSIGNED_INT, 0);

// frame end
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);

    glfwTerminate();
    return 0;
}
