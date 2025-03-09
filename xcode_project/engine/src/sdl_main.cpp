#include <SDL2/SDL.h>

#include "glad/glad.h"

#include "sdl_platform.h"

#include "opengl_clear.h"
#include "opengl_shader.h"
#include "opengl_state.h"

#include "assimp_model.h"


#include "engine_types.h"
#include "engine_texture.h"
#include "engine_matrix.h"

#include "engine_model.h"
#include "engine_shapes.h"


static int window_width = 1280;
static int window_height = 720;


bool sdl_process_events();

// Camera state
static f32 camera_speed = 0.005f;
static v3f camera_pos = V3(0.0f, 0.0f, 10.0f);
static v3f camera_dir = V3(0.0f, 0.0f, -1.0f);
static v3f camera_up  = V3(0.0f, 1.0f, 0.0f);

static f32 mouse_speed = 0.1f; // mouse_sensitivity

static float yaw = -90.0f;
static float pitch = 0.0f;
// Camera state

static bool moving_forward = false;
static bool moving_backward = false;
static bool moving_left = false;
static bool moving_right = false;
static bool moving_up = false;
static bool moving_down = false;

//static const f32 cube_vertices[] =
//{
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//};


//static const s32 cube_indices[] =
//{
//     0,  1,  2,
//     3,  4,  5,
//     6,  7,  8,
//     9, 10, 11,
//    12, 13, 14,
//    15, 16, 17,
//    18, 19, 20,
//    21, 22, 23,
//    24, 25, 26,
//    27, 28, 29,
//    30, 31, 32,
//    33, 34, 35,
//};




int main(int argc, char** argv)
{
    SDL_Window* sdl_window;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
                        | SDL_GL_CONTEXT_DEBUG_FLAG);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    sdl_window = SDL_CreateWindow("SDL Window",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  window_width,
                                  window_height,
                                  SDL_WINDOW_OPENGL);

    if(!sdl_window)
    {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_GLContext sdl_gl_context = SDL_GL_CreateContext(sdl_window);
    SDL_GL_MakeCurrent(sdl_window, sdl_gl_context);

    SDL_GL_SetSwapInterval(1); // vsync

    if(!gladLoadGL())
    {
        printf("gladLoadGL failed.");
        return 1;
    }

    opengl_viewport(0, 0, window_width, window_height);

    opengl_depth_enable(1);
    opengl_depth_func(GL_LESS);


    // render transparent objects back to front
    // distance = length(object.position - camera.position)
    // iterate from largest to small distance
    opengl_blend_enable(1);
    opengl_blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    opengl_cull_enable(1);
    opengl_cull_face(GL_BACK);
    opengl_cull_front(GL_CCW); // default

    opengl_wireframe_mode(0);


    char* basic_light_vs_source = sdl_read_entire_file("basic_light.vert");
    char* basic_light_fs_source = sdl_read_entire_file("basic_light.frag");
    GLuint basic_light_shader = opengl_create_shader_program(basic_light_vs_source, basic_light_fs_source);

    char* basic_object_vs_source = sdl_read_entire_file("basic_object.vert");
    char* basic_object_fs_source = sdl_read_entire_file("basic_object.frag");
    GLuint basic_object_shader = opengl_create_shader_program(basic_object_vs_source, basic_object_fs_source);

    model_data sphere_model;
    generate_sphere(&sphere_model, 36, 18);

    model_data cylinder_model;
    generate_cylinder(&cylinder_model, 36, 1.0f, 2.0f);


    m4f model = identity();
    m4f view;
    m4f projection = perspective(0.7535f, ((f32)window_width)/((f32)window_height), 0.1f, 100.0f);

    u64 new_count = SDL_GetPerformanceCounter();
    u64 old_count = new_count;
    u64 count_frequency = SDL_GetPerformanceFrequency();


    bool done = false;
    while(!done)
    {
        u64 elapsed_count = new_count - old_count;
        f32 elapsed_time = ((f32)(elapsed_count * 1000)) / ((f32)count_frequency);

        if(moving_forward)
        {
            camera_pos += elapsed_time * camera_speed * camera_dir;
        }
        if(moving_backward)
        {
            camera_pos -= elapsed_time * camera_speed * camera_dir;
        }
        if(moving_left)
        {
            camera_pos -= elapsed_time * camera_speed * normalize(cross(camera_dir, camera_up));
        }
        if(moving_right)
        {
            camera_pos += elapsed_time * camera_speed * normalize(cross(camera_dir, camera_up));
        }
        if(moving_up)
        {
            camera_pos += elapsed_time * camera_speed * normalize(cross(normalize(cross(camera_dir, camera_up)), camera_dir));
        }
        if(moving_down)
        {
            camera_pos -= elapsed_time * camera_speed * normalize(cross(normalize(cross(camera_dir, camera_up)), camera_dir));
        }


        done = sdl_process_events();

        view = look_at(camera_pos, camera_pos + camera_dir, camera_up);

        opengl_clear();

// Lights
        opengl_bind_shader(basic_light_shader);

        opengl_uniform_m4f(basic_light_shader, "view", view);
        opengl_uniform_m4f(basic_light_shader, "projection", projection);

        // Point Lights
//        model = translation(0.0f, 0.0f, 0.0f);
//        opengl_uniform_m4f(basic_light_shader, "model", model);
//        draw_model(&sphere_model, basic_light_shader);
//        model = translation(0.0f, 0.0f, 0.0f);
//        opengl_uniform_m4f(basic_light_shader, "model", model);
//        draw_model(&sphere_model, basic_light_shader);
//        model = translation(0.0f, 0.0f, 0.0f);
//        opengl_uniform_m4f(basic_light_shader, "model", model);
//        draw_model(&sphere_model, basic_light_shader);
//        model = translation(0.0f, 0.0f, 0.0f);
//        opengl_uniform_m4f(basic_light_shader, "model", model);
//        draw_model(&sphere_model, basic_light_shader);

        // Directional Light
        model = translation(0.0f, 0.0f, 0.0f);
        opengl_uniform_m4f(basic_light_shader, "model", model);
        draw_model(&cylinder_model, basic_light_shader);

// Objects
        opengl_bind_shader(basic_object_shader);

        opengl_uniform_m4f(basic_object_shader, "view", view);
        opengl_uniform_m4f(basic_object_shader, "projection", projection);

        model = translation(1.0f, 0.0f, 0.0f);
        opengl_uniform_m4f(basic_object_shader, "model", model);
        draw_model(&sphere_model, basic_object_shader);

//        model = translation(0.0f, 0.0f, 0.0f);
//        opengl_uniform_m4f(basic_object_shader, "model", model);
//        draw_model(&cylinder_model, basic_object_shader);



        SDL_GL_SwapWindow(sdl_window);
        old_count = new_count;
        new_count = SDL_GetPerformanceCounter();
    }

    SDL_GL_DeleteContext(sdl_gl_context);

    SDL_DestroyWindow(sdl_window);
    SDL_Quit();

    return 0;
}


bool sdl_process_events()
{
    bool done_yet = false;

    SDL_Event sdl_event;
    while(SDL_PollEvent(&sdl_event))
    {
        switch(sdl_event.type)
        {
            case SDL_QUIT:
                done_yet = true;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                // TODO: Time stepping movement and continous movement (fix key repeat stutter)
                if(sdl_event.key.keysym.scancode == SDL_SCANCODE_W)
                {
                    if(sdl_event.key.state == SDL_PRESSED)
                    {
                        moving_forward = true;
                    }
                    else
                    {
                        moving_forward = false;
                    }
                }
                else if(sdl_event.key.keysym.scancode == SDL_SCANCODE_S)
                {
                    if(sdl_event.key.state == SDL_PRESSED)
                    {
                        moving_backward = true;
                    }
                    else
                    {
                        moving_backward = false;
                    }
                }
                else if(sdl_event.key.keysym.scancode == SDL_SCANCODE_A)
                {
                    if(sdl_event.key.state == SDL_PRESSED)
                    {
                        moving_left = true;
                    }
                    else
                    {
                        moving_left = false;
                    }
                }
                else if(sdl_event.key.keysym.scancode == SDL_SCANCODE_D)
                {
                    if(sdl_event.key.state == SDL_PRESSED)
                    {
                        moving_right = true;
                    }
                    else
                    {
                        moving_right = false;
                    }
                }
                else if(sdl_event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                {
                    if(sdl_event.key.state == SDL_PRESSED)
                    {
                        moving_up = true;
                    }
                    else
                    {
                        moving_up = false;
                    }
                }
                else if(sdl_event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
                {
                    if(sdl_event.key.state == SDL_PRESSED)
                    {
                        moving_down = true;
                    }
                    else
                    {
                        moving_down = false;
                    }
                }
                else if(sdl_event.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    if(sdl_event.key.state == SDL_PRESSED) // sdl_event.key.keysym.mod & KMOD_SHIFT &&
                    {
                        SDL_bool mouse_mode = SDL_GetRelativeMouseMode();
                        if(mouse_mode == SDL_TRUE)
                        {
                            SDL_SetRelativeMouseMode(SDL_FALSE);
                        }
                        else
                        {
                            SDL_SetRelativeMouseMode(SDL_TRUE);
                        }
                    }
                }
                break;
            case SDL_MOUSEMOTION:

                v2f mouse_pos = V2(sdl_event.motion.xrel, sdl_event.motion.yrel);

                v2f offset = mouse_speed * (mouse_pos);

                yaw += offset.x;
                pitch -= offset.y;

                if(pitch > 89.0f)
                {
                    pitch = 89.0f;
                }
                else if(pitch < -89.0f)
                {
                    pitch = -89.0f;
                }

                v3f dir;
                dir.x = cosf(radians(yaw)) * cosf(radians(pitch));
                dir.y = sinf(radians(pitch));
                dir.z = sinf(radians(yaw)) * cosf(radians(pitch));

                camera_dir = normalize(dir);
                break;

        }
    }
    return done_yet;
}
