#include "chicago_cubes.h"

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

		if(mode == 0)
		{
			draw_cubes_move(degrees);
		}
		else if(mode == 1)
		{
			draw_cubes_stretch(degrees);
		}

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
