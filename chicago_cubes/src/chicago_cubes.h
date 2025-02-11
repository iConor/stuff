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


#define PX_WIDTH 1280
#define PX_HEIGHT 720

#define MAX_OFFSET 144

static bool global_running;
static float offset[MAX_OFFSET] = {};


float deg2rad(float degrees);
v3 hsv2rgb(float h, float s, float v);
void sdl_process_events();

void generate_offsets();

void draw_cube(float x, float y, float z, float size);
void draw_prism(float x, float y, float z, float size);
void draw_square(float x, float y, float z, float size);

void draw_cubes_move(float angle);
void draw_cubes_stretch(float angle);
void draw_squares();

void draw_diamond(float x, float y, float z, float size);

void draw_diamond_mats();
void draw_diamond_shuffle(float angle);


#define CHICAGO_CUBES_H
#endif
