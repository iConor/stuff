#include "chicago_cubes.h"

#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "stdio.h"


#define PX_WIDTH 1280
#define PX_HEIGHT 720

#define MAX_OFFSET 144

static float offset[MAX_OFFSET] = {};


void draw_top(float x, float y, float z, float half, float depth)
{
    // Near
    glVertex3f(x - half, y + half, z);
    glVertex3f(x + half, y + half, z);
    glVertex3f(x + half, y + half, z - depth);

    // Far
    glVertex3f(x + half, y + half, z - depth);
    glVertex3f(x - half, y + half, z - depth);
    glVertex3f(x - half, y + half, z);
}

void draw_bot(float x, float y, float z, float half, float depth)
{
    // Near
    glVertex3f(x + half, y - half, z);
    glVertex3f(x - half, y - half, z);
    glVertex3f(x - half, y - half, z - depth);

    // Far
    glVertex3f(x - half, y - half, z - depth);
    glVertex3f(x + half, y - half, z - depth);
    glVertex3f(x + half, y - half, z);
}

void draw_left(float x, float y, float z, float half, float depth)
{
    // Near
    glVertex3f(x - half, y - half, z);
    glVertex3f(x - half, y + half, z);
    glVertex3f(x - half, y + half, z - depth);

    // Far
    glVertex3f(x - half, y + half, z - depth);
    glVertex3f(x - half, y - half, z - depth);
    glVertex3f(x - half, y - half, z);
}

void draw_right(float x, float y, float z, float half, float depth)
{
    // Near
    glVertex3f(x + half, y + half, z);
    glVertex3f(x + half, y - half, z);
    glVertex3f(x + half, y - half, z - depth);
    //
    // Far
    glVertex3f(x + half, y - half, z - depth);
    glVertex3f(x + half, y + half, z - depth);
    glVertex3f(x + half, y + half, z);
}


void draw_cube(float x, float y, float z, float size)
{
    float half = size / 2.0f;

    float depth = 1.0f / 9.0f;

    float h = ((z + 1.15) * 1800.0f) + 180.0f;
    float s = 0.2f;
    float v = 0.8f;

    v3 color = hsv2rgb(h, s, v);
    // v3 color = { 0.6f, 0.3f, 0.4f };

    // printf("%f\n", h);

    glBegin(GL_TRIANGLES);

    // To make them cubes?

    glColor3f(color.r / 2.0f, color.g / 2.0f, color.b / 2.0f);
    draw_bot(x, y, z, half, depth);

    glColor3f(color.r / 1.75f, color.g / 1.75f, color.b / 1.75f);
    draw_left(x, y, z, half, depth);

    glColor3f(color.r / 1.5f, color.g / 1.5f, color.b / 1.5f);
    draw_right(x, y, z, half, depth);

    glColor3f(color.r / 1.25f, color.g / 1.25f, color.b / 1.25f);
    draw_top(x, y, z, half, depth);

    glColor3f(color.r, color.g, color.b);

    // Front

    // Top-left
    glVertex3f(x + half, y + half, z);
    glVertex3f(x - half, y + half, z);
    glVertex3f(x - half, y - half, z);

    // Bottom-right
    glVertex3f(x - half, y - half, z);
    glVertex3f(x + half, y - half, z);
    glVertex3f(x + half, y + half, z);

    glEnd();
}

void draw_cubes_move(float angle)
{
    float size = PX_HEIGHT / 9;

    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            float x = (float)i * size + size / 2.0f;
            float y = (float)j * size + size / 2.0f;

            int index = 9 * i + j;

            float z = SDL_sin(deg2rad(angle + offset[index])) / 10.0f - 1.15f;

            x -= PX_WIDTH / 2.0f;
            y -= PX_HEIGHT / 2.0f;

            draw_cube(x, y, z, size);
        }
    }
}


void generate_offsets()
{
    for(int i = 0; i < MAX_OFFSET; i++)
    {
        offset[i] = (float)(rand() % 3600) / 10.0f;
        // offset[i] = (float)(rand() % 10) / 100.0f;
    }
}



int main(int argc, char* argv[])
{
    int sdl_init = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

    if(sdl_init != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *sdl_window = SDL_CreateWindow("Window Title",
          SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          PX_WIDTH,
          PX_HEIGHT,
          SDL_WINDOW_OPENGL);

    if(sdl_window == NULL)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
    return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(sdl_window);

    if(gl_context == NULL)
    {
        SDL_Log("Unable to create GL context: %s", SDL_GetError());
        return 1;
    }

    int gl_current = SDL_GL_MakeCurrent(sdl_window, gl_context);

    if(gl_current != 0)
    {
        SDL_Log("Unable to make current: %s", SDL_GetError());
        return 1;
    }

    int gl_interval = SDL_GL_SetSwapInterval(1);

    if(gl_interval != 0)
    {
        SDL_Log("Unable to set swap interval: %s", SDL_GetError());
        return 1;
    }

    srand(time(NULL));

    glMatrixMode(GL_PROJECTION);

    float w = 2.0f / (float)PX_WIDTH;
    float h = 2.0f / (float)PX_HEIGHT;

    float projection[] =
    {
        w,  0,  0,  0,
        0,  h,  0,  0,
        0,  0, -3, -1,
        0,  0, -4,  0
    };
    glLoadMatrixf(projection);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    int frame = 0;

    generate_offsets();
    
    global_running =  true;
    while(global_running)
    {
        sdl_process_events();

        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        int progress = frame * 2;
        float degrees = (float)(progress % 360);
        float radians = deg2rad(degrees);
        draw_cubes_move(degrees);
        int ms = 33;

        ++frame;
        SDL_GL_SwapWindow(sdl_window);
        SDL_Delay(ms);
    }

    SDL_GL_DeleteContext(gl_context);

    SDL_DestroyWindow(sdl_window);

    SDL_Quit();

    return 0;
}

#include "chicago_cubes.cpp"
