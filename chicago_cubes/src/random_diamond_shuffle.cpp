#include "chicago_cubes.h"


#include "stdlib.h"
#include "time.h"
#include "math.h"


#define PX_WIDTH 1280
#define PX_HEIGHT 720


void draw_diamond(float x, float y, float z, float size)
{
    float half = size;

    float h = (float)(rand() % 360);
    float s = 0.2f;
    float v = 0.8f;

    v3 color = hsv2rgb(h, s, v);

    glBegin(GL_TRIANGLES);

    glColor3f(color.r, color.g, color.b);

    glVertex3f(x - half, y, z);
    glVertex3f(x, y - half, z);
    glVertex3f(x + half, y, z);

    glVertex3f(x + half, y, z);
    glVertex3f(x, y + half, z);
    glVertex3f(x - half, y, z);

    glEnd();
}

void draw_diamonds(float angle)
{
    float size = PX_HEIGHT / 9;

    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            float x = (float)i * size + size / 2.0f;
            float y = (float)j * size + size / 2.0f;

            float z = (float)(rand() % 10) / 100.0f - 1.15f;

            x -= PX_WIDTH / 2.0f;
            y -= PX_HEIGHT / 2.0f;

            x *= SDL_cos(angle);
            y *= SDL_sin(angle);

            draw_diamond(x, y, z, size);
        }
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

    for(int frame = 0; frame < 360; frame++)
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        float degrees = (float)(frame % 360);
        float radians = deg2rad(degrees);
        draw_diamonds(radians);
        int ms = 33;

        SDL_GL_SwapWindow(sdl_window);
        SDL_Delay(ms);
    }

    SDL_GL_DeleteContext(gl_context);

    SDL_DestroyWindow(sdl_window);

    SDL_Quit();

    return 0;
}

#include "chicago_cubes.cpp"
