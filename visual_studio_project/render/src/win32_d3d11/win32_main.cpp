#include "windows.h"

#include "win32_d3d11.h"
// #include "win32_opengl.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
// #include "imgui_impl_opengl3.h"

#include "box.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void ImGui_Demo(bool* show_demo_window, bool* show_another_window, ImVec4* clear_color);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    WNDCLASSEX wndclass_ex = { 0 };

    wndclass_ex.cbSize           = sizeof(WNDCLASSEX);
    wndclass_ex.style            = CS_CLASSDC;
    wndclass_ex.lpfnWndProc      = WindowProc;
    wndclass_ex.cbClsExtra       = 0L;
    wndclass_ex.cbWndExtra       = 0L;
    wndclass_ex.hInstance        = GetModuleHandle(NULL);
    wndclass_ex.hIcon            = NULL;
    wndclass_ex.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wndclass_ex.hbrBackground    = NULL;
    wndclass_ex.lpszMenuName     = NULL;
    wndclass_ex.lpszClassName    = "ClassName";
    wndclass_ex.hIconSm          = NULL;

    RegisterClassEx(&wndclass_ex);

    RECT    rect        = { 0, 0, 1280, 720 };
    DWORD   style       = WS_OVERLAPPEDWINDOW;
    BOOL    menu        = FALSE;
    DWORD   style_ex    = 0L;

    AdjustWindowRectEx(&rect, style, menu, style_ex);

    HWND hwnd = CreateWindowEx(
        style_ex,
        wndclass_ex.lpszClassName,
        "WindowName",
        style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        wndclass_ex.hInstance,
        NULL
    );

    if(!d3d11_init(hwnd))
    {
        d3d11_exit();
        UnregisterClass(wndclass_ex.lpszClassName, wndclass_ex.hInstance);
        return 1;
    }
    // if(!opengl_init())
    // {
    //     UnregisterClass(wndclass_ex.lpszClassName, wndclass_ex.hInstance);
    //     return 1;
    // }

    d3d11_vsync(1);
    // opengl_vsync(1);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(d3d11_get_device(), d3d11_get_device_context());
    // const char* glsl_version = "#version 330";
    // ImGui_ImplOpenGL3_Init(glsl_version); //

    // ImGui Demo State
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

    render::box* light = new render::box();
    render::box* cube = new render::box();

    ImVec4 light_position = ImVec4( 2.5f,  2.5f, -5.0f,  0.0f);
    ImVec4 light_color    = ImVec4( 1.0f,  1.0f,  1.0f,  1.0f);

    ImVec4 cube_position = ImVec4( 0.0f, -2.5f, -5.0f,  0.0f);
    ImVec4 cube_color    = ImVec4( 1.0f,  1.0f,  1.0f,  1.0f);

    bool running = true;
    while(running)
    {
        MSG msg;
        while(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            switch(msg.message)
            {
            case WM_QUIT:
                running = false;
                break;
            default:
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                break;
            }
        }

        ImGui_ImplDX11_NewFrame();
        // ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // ImGui_Demo(&show_demo_window, &show_another_window, &clear_color);

        ImGui::Begin("That's no moon!");

        ImGui::BeginChild("background", ImVec2(200.0f, 60.0f));
        ImGui::Text("Background Color:");
        ImGui::ColorEdit3("", (float*)&clear_color);
        ImGui::EndChild();

        ImGui::BeginChild("light", ImVec2(200.0f, 180.0f));
        ImGui::Text("Light Properties:");
        // ImGui::SliderFloat("Scale", &light_scale, 0.0f, 2.0f);
        ImGui::SliderFloat("X", &light_position.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Y", &light_position.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Z", &light_position.z, -20.0f,  0.0f);
        ImGui::ColorEdit3("Color", (float*)&light_color);
        // ImGui::Checkbox("Edges", &light_edges);
        ImGui::EndChild();

        ImGui::BeginChild("cube", ImVec2(200.0f, 180.0f));
        ImGui::Text("Cube Properties:");
        // ImGui::SliderFloat("Scale", &cube_scale, 0.0f, 2.0f);
        ImGui::SliderFloat("X", &cube_position.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Y", &cube_position.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Z", &cube_position.z, -20.0f,  0.0f);
        ImGui::ColorEdit3("Color", (float*)&cube_color);
        // ImGui::Checkbox("Edges", &cube_edges);
        ImGui::EndChild();

        ImGui::Text("%.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);

        ImGui::End();

        ImGui::Render();

        d3d11_clear((float*)&clear_color);
        // opengl_clear((float*)&clear_color);


        light->light(light_color.x, light_color.y, light_color.z,
                     light_position.x, light_position.y, light_position.z + 1.0f);

        light->position(light_position.x, light_position.y, light_position.z);
        light->color(light_color.x, light_color.y, light_color.z);
        light->draw();



        cube->position(cube_position.x, cube_position.y, cube_position.z);
        cube->color(cube_color.x, cube_color.y, cube_color.z);
        cube->light(light_color.x, light_color.y, light_color.z,
                    light_position.x, light_position.y, light_position.z);
        cube->draw();

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        d3d11_swap();
        // opengl_swap();
    }

    ImGui_ImplDX11_Shutdown();
    // ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    delete light;
    delete cube;

    d3d11_exit();
    // opengl_exit();

    DestroyWindow(hwnd);
    UnregisterClass(wndclass_ex.lpszClassName, wndclass_ex.hInstance);

    return 0;
}


// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    switch(uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void ImGui_Demo(bool* show_demo_window, bool* show_another_window, ImVec4* clear_color)
{
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (*show_demo_window)
        ImGui::ShowDemoWindow(show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (*show_another_window)
    {
        ImGui::Begin("Another Window", show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            *show_another_window = false;
        ImGui::End();
    }
}
