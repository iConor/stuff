// #include "platform.h"
// #include "renderer.h"


#include "win32_window.h"
// #include "win32_opengl.h"
// #include "win32_d3d11.h"

// #include "opengl_render.h"
#include "d3d11_render.h"

// #include "box.h"
#include "box_mesh.h"

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
int main(int argc, char** argv)
{
    // platform::window* window = platform::window::load();
    // platform::render* render = platform::render::load(platform::render_api::OpenGL);
    platform::win32_window* window = new platform::win32_window();
    // platform::win32_d3d11* device = new platform::win32_d3d11(window->get_hwnd());

    platform::d3d11_render* render = new platform::d3d11_render();

    // TODO: vsync

    window->show();

    // box* cube = new box();
    box_mesh* cube = new box_mesh();

    cube->position(0.0f, -1.5f, -2.0f);
    cube->light(1.0f, 1.0f,  1.0f,
                2.5f, 5.0f, -0.5f);

    bool should_quit = false;
    while(!should_quit)
    {
        should_quit = window->msgs();


        render->clear(0.0f, 0.0f, 0.0f, 1.0f);

        cube->draw();

        // TODO: swap buffer
        // render->swap_buffers(); ????
        // device->swap_buffers(); ????
        // SwapBuffers(device->get_device_context()); // for opengl
        // g_pSwapChain->Present(g_bVsync, 0);
    }

    delete cube;

    delete render;
    // delete device;
    delete window;

    return 0;
}
