#include <Windows.h>

#include "win32_opengl_init.h"

#include "render.h"


#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int win32_process_messages();

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
int main(int argc, char** argv)
{
    WNDCLASSEX wc = { 0 };

    wc.cbSize           = sizeof(WNDCLASSEX);
    wc.style            = CS_CLASSDC;
    wc.lpfnWndProc      = WindowProc;
    wc.cbClsExtra       = 0L;
    wc.cbWndExtra       = 0L;
    wc.hInstance        = GetModuleHandle(NULL);
    wc.hIcon            = NULL;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = "ClassName";
    wc.hIconSm          = NULL;

    RegisterClassEx(&wc);

    DWORD style = WS_OVERLAPPEDWINDOW;
    DWORD style_ex = 0L;

    RECT rect = { 0, 0, 1280, 720 };
    AdjustWindowRectEx(&rect, style, FALSE, style_ex);

    HWND hWnd = CreateWindowEx(
        style_ex,
        wc.lpszClassName,
        "WindowName",
        style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        wc.hInstance,
        NULL
        );


    HDC device_context = GetDC(hWnd);
    HGLRC render_context = win32_opengl_init(device_context);
    // Load generic (gl) functions
    // opengl_init();
    gladLoadGL();

    wglSwapIntervalEXT(1); // vsync on/off 1/0

// ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplOpenGL3_Init("#version 330");
////

    ShowWindow(hWnd, SW_SHOW);


    render::util::cull();
    render::util::depth();


    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);


    render::sphere* light = new render::sphere();
    render::box* cube = new render::box();
    render::dad_box* goober = new render::dad_box();

    ImVec4 light_position = ImVec4( 2.5f,  5.0f, -5.0f,  0.0f);
    ImVec4 light_rotation = ImVec4(90.0f,  0.0f,  0.0f,  0.0f);
    float light_scale = 0.5f;
    ImVec4 light_color = ImVec4(1.0f,  1.0f,  1.0f,  1.0f);
    bool light_edges = false;

    ImVec4 cube_position = ImVec4( 0.0f, -5.0f, -5.0f,  0.0f);
    ImVec4 cube_rotation = ImVec4( 0.0f,  0.0f,  0.0f,  0.0f);
    float cube_scale = 1.0f;
    ImVec4 cube_color = ImVec4(1.0f,  1.0f,  1.0f,  1.0f);
    bool cube_edges = false;

    ImVec4 goober_position = ImVec4( 7.5f, -2.5f, -10.0f,  0.0f);
    ImVec4 goober_rotation = ImVec4( 0.0f,  0.0f,   0.0f,  0.0f);
    float goober_scale = 1.0f;


    int should_quit = 0;
    while (should_quit == 0)
    {
        should_quit = win32_process_messages();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("That's no moon!");

            ImGui::BeginChild("background", ImVec2(200.0f, 60.0f));
            ImGui::Text("Background Color:");
            ImGui::ColorEdit3("", (float*)&clear_color);
            ImGui::EndChild();

            ImGui::BeginChild("light", ImVec2(200.0f, 180.0f));
            ImGui::Text("Light Properties:");
            ImGui::SliderFloat("Scale", &light_scale, 0.0f, 2.0f);
            ImGui::SliderFloat("X", &light_position.x, -10.0f, 10.0f);
            ImGui::SliderFloat("Y", &light_position.y, -10.0f, 10.0f);
            ImGui::SliderFloat("Z", &light_position.z, -20.0f,  0.0f);
            ImGui::ColorEdit3("Color", (float*)&light_color);
            ImGui::Checkbox("Edges", &light_edges);
            ImGui::EndChild();

            ImGui::BeginChild("cube", ImVec2(200.0f, 180.0f));
            ImGui::Text("Cube Properties:");
            ImGui::SliderFloat("Scale", &cube_scale, 0.0f, 2.0f);
            ImGui::SliderFloat("X", &cube_position.x, -10.0f, 10.0f);
            ImGui::SliderFloat("Y", &cube_position.y, -10.0f, 10.0f);
            ImGui::SliderFloat("Z", &cube_position.z, -20.0f,  0.0f);
            ImGui::ColorEdit3("Color", (float*)&cube_color);
            ImGui::Checkbox("Edges", &cube_edges);
            ImGui::EndChild();

            ImGui::BeginChild("goober", ImVec2(200.0f, 180.0f));
            ImGui::Text("Goober Properties:");
            ImGui::SliderFloat("Scale", &goober_scale, 0.0f, 2.0f);
            ImGui::SliderFloat("X", &goober_position.x, -10.0f, 10.0f);
            ImGui::SliderFloat("Y", &goober_position.y, -10.0f, 10.0f);
            ImGui::SliderFloat("Z", &goober_position.z, -20.0f,  0.0f);
            ImGui::EndChild();

            ImGui::Text("%.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);

            ImGui::End();
        }

        ImGui::Render();

        render::util::clear(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        light->position(light_position.x, light_position.y, light_position.z);
        light->rotation(light_rotation.x, light_rotation.y, light_rotation.z);
        light->scale(light_scale, light_scale, light_scale);
        light->color(light_color.x, light_color.y, light_color.z);

        if(light_edges)
        {
            light->draw_edges();
        }
        else
        {
            light->draw();
        }

        cube->position(cube_position.x, cube_position.y, cube_position.z);
        cube->rotation(cube_rotation.x, cube_rotation.y, cube_rotation.z);
        cube->scale(cube_scale, cube_scale, cube_scale);
        cube->color(cube_color.x, cube_color.y, cube_color.z);
        cube->light(light_color.x, light_color.y, light_color.z,
                    light_position.x, light_position.y, light_position.z);

        if(cube_edges)
        {
            cube->draw_edges();
        }
        else
        {
            cube->draw();
        }

        goober->position(goober_position.x, goober_position.y, goober_position.z);
        goober->rotation(goober_rotation.x, goober_rotation.y, goober_rotation.z);
        goober->scale(goober_scale, goober_scale, goober_scale);

        goober->draw();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SwapBuffers(device_context);
    }

    delete light;
    delete cube;
    delete goober;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // DestroyWindow(hWnd);
    // UnregisterClass(wc.lpszClassName, wc.hInstance);

    return should_quit;
}



// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if(ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg)
    {
        // Handles the close (X) button and ALT+F4
        case WM_CLOSE:
        {
            PostQuitMessage(0);
        } return 0;

        // default:
        // {
        //
        // } break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int win32_process_messages()
{
    int received_quit = 0;

    MSG msg;
    while (PeekMessage(&msg, NULL, 0L, 0L, PM_REMOVE))
    {
        switch (msg.message)
        {
            case WM_QUIT:
            {
                received_quit = -1; // exit code from PostQuitMessage
            } break;

            default:
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } break;
        }
    }

    return received_quit;
}
