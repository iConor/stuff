#ifndef CHICAGO_CUBES_H

#ifdef __APPLE__

#include <SDL2/SDL.h>
#include "OpenGL/gl.h"

#else // Windows

#include <SDL.h>
#include <windows.h>
#include <GL/gl.h>

#endif


union v3
{
    struct
    {
        float x;
        float y;
        float z;
    };
    struct
    {
        float r;
        float g;
        float b;
    };
    struct
    {
        float h;
        float s;
        float v;
    };
};


float deg2rad(float degrees);
v3 hsv2rgb(float h, float s, float v);


static bool global_running;

static void sdl_process_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            global_running = false;
        }
        else if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            global_running = false;
        }
    }
}


#define CHICAGO_CUBES_H
#endif
