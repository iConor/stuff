#include "ipa_math.h"
#include "ipa_vector.h"
#include "ipa_matrix.h"


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
            float rando = (float)(rand() % 25) / 100.0f;;
            vertex_data[index++] = (side * x) - offset; // x
            vertex_data[index++] = (side * y) - offset; // y
            vertex_data[index++] = -1.0f + rando; // z

            // float h = (float)(rand() % 3600) / 10.0f;
            // float s = 0.2f;
            // float v = 0.8f;
            // v3 color = hsv2rgb(h, s, v);

            v3 color = V3(0.1f + rando * 2.0f, 0.5f + rando * 2.0f, 0.2f + rando * 2.0f);

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

// make color flat for low poly
const char *vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "uniform mat4 projection;"
    "uniform mat4 view;"
    "out vec3 ourColor;"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view  * vec4(position, 1.0);\n"
    "   ourColor = color;\n"
    "}\n";

// make color flat for low poly
const char *fragment_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n";
