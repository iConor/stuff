#include "platform.h"
#include "render.h"


#include "box.h"
#include "sphere.h"

#include "file.h"

#include "imgui.h"
// #include "imgui_impl_win32.h"
// #include "imgui_impl_dx11.h"
// #include "imgui_impl_opengl3.h"

// static platform::render_api api = platform::render_api::Direct3D11;
static platform::render_api api = platform::render_api::OpenGL;



int main(int argc, char** argv)
{
    platform::window* platform_window = platform::window::load();

    platform::render* platform_render = platform::render::load(api);

    platform_render->init(platform_window);

    render::core* render = render::core::load(platform_render);

// ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    render->ImGui_Init();
////

    platform_render->vsync(1);
    platform_window->show();

    render->depth();
    render->cull();


    box* cube = new box(render);
    sphere* bulb = new sphere(render);


    ImVec4 cube_position = ImVec4( 0.0f, -1.5f, -2.0f,  0.0f);
    float cube_scale = 1.0f;
    ImVec4 cube_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);


    ImVec4 bulb_position = ImVec4( 0.0f,  1.5f, -2.0f,  0.0f);
    float bulb_scale = 1.0f;
    ImVec4 bulb_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);





    bool should_quit = false;
    while(!should_quit)
    {
        should_quit = platform_window->msgs();
        platform_render->clear();


        render->ImGui_NewFrame();
        ImGui::NewFrame();


        ImGui::Begin("That's no moon!");

        ImGui::BeginChild("Bulb", ImVec2(200.0f, 180.0f));
        ImGui::Text("Bulb Properties:");
        ImGui::SliderFloat("Scale", &bulb_scale, 0.0f, 2.0f);
        ImGui::SliderFloat("X", &bulb_position.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Y", &bulb_position.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Z", &bulb_position.z, -20.0f,  0.0f);
        ImGui::ColorEdit3("Color", (float*)&bulb_color);
        ImGui::EndChild();

        ImGui::BeginChild("Cube", ImVec2(200.0f, 180.0f));
        ImGui::Text("Cube Properties:");
        ImGui::SliderFloat("Scale", &cube_scale, 0.0f, 2.0f);
        ImGui::SliderFloat("X", &cube_position.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Y", &cube_position.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Z", &cube_position.z, -20.0f,  0.0f);
        ImGui::ColorEdit3("Color", (float*)&cube_color);
        ImGui::EndChild();

        ImGui::Text("%.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);

        ImGui::End();


        ImGui::Render();


        bulb->position(bulb_position.x, bulb_position.y, bulb_position.z);
        bulb->scale(bulb_scale, bulb_scale, bulb_scale);
        bulb->color(bulb_color.x, bulb_color.y, bulb_color.z);
        // bulb->light(1.0f, 1.0f, 1.0f,
        //             bulb_position.x, bulb_position.y, bulb_position.z);
        bulb->draw();

        cube->position(cube_position.x, cube_position.y, cube_position.z);
        cube->scale(cube_scale, cube_scale, cube_scale);
        cube->color(cube_color.x, cube_color.y, cube_color.z);
        cube->light(bulb_color.x, bulb_color.y, bulb_color.z,
                    bulb_position.x, bulb_position.y, bulb_position.z);
        cube->draw();


        render->ImGui_RenderDrawData(ImGui::GetDrawData());

        platform_render->swap();
    }

    delete cube;
    delete bulb;

    render->ImGui_Shutdown();
    ImGui::DestroyContext();


    delete render;

    delete platform_render;
    delete platform_window;

    return 0;
}
