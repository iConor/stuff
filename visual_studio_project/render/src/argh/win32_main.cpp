#include "win32_window.h"

// #include "imgui.h"
// #include "imgui_impl_win32.h"
// #include "imgui_impl_dx11.h"
// // #include "imgui_impl_opengl3.h"


// void ImGui_Demo(bool* show_demo_window, bool* show_another_window, ImVec4* clear_color);

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
int main(int argc, char** argv)
{
    platform::window* window = new platform::win32_window();

////
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    //
    // ImGui::StyleColorsDark();
    //
    // ImGui_ImplWin32_Init(hwnd);
    // // ImGui_ImplDX11_Init(d3d11_get_device(), d3d11_get_device_context());
    // // const char* glsl_version = "#version 330";
    // // ImGui_ImplOpenGL3_Init(glsl_version); //
    //
    // bool show_demo_window = false;
    // bool show_another_window = false;
    // ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
////

    window->show();

    bool should_quit = false;

    while(!should_quit)
    {
        should_quit = window->msgs();

    ////
        // ImGui_ImplDX11_NewFrame();
        // // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplWin32_NewFrame();
        // ImGui::NewFrame();
        //
        // ImGui_Demo(&show_demo_window, &show_another_window, &clear_color);
        //
        // ImGui::Render();
    ////


    ////
        // ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        // // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ////
    }

////
    // ImGui_ImplDX11_Shutdown();
    // // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplWin32_Shutdown();
    // ImGui::DestroyContext();
////


    return 0;
}





// void ImGui_Demo(bool* show_demo_window, bool* show_another_window, ImVec4* clear_color)
// {
//     // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
//     if (*show_demo_window)
//         ImGui::ShowDemoWindow(show_demo_window);
//
//     // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
//     {
//         static float f = 0.0f;
//         static int counter = 0;
//
//         ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//         ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//         ImGui::Checkbox("Demo Window", show_demo_window);      // Edit bools storing our window open/close state
//         ImGui::Checkbox("Another Window", show_another_window);
//
//         ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//         ImGui::ColorEdit3("clear color", (float*)clear_color); // Edit 3 floats representing a color
//
//         if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//             counter++;
//         ImGui::SameLine();
//         ImGui::Text("counter = %d", counter);
//
//         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//         ImGui::End();
//     }
//
//     // 3. Show another simple window.
//     if (*show_another_window)
//     {
//         ImGui::Begin("Another Window", show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//         ImGui::Text("Hello from another window!");
//         if (ImGui::Button("Close Me"))
//             *show_another_window = false;
//         ImGui::End();
//     }
// }
