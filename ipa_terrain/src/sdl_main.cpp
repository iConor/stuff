#include <SDL.h>
#include <glad/glad.h>
#include <glad.c>

#include <stdio.h>

#include <glm/glm.hpp>

#include "ipa_glm.h"
#include "ipa_imgui.cpp"

#include "render.h"
#include "terrain.cpp"





int main(int, char**)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Decide GL+GLSL versions
    const char* glsl_version = "#version 330";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    const int WIDTH = current.w;
    const int HEIGHT = current.h;
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    bool err = gladLoadGL() == 0;
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // specific
    const int VERTEX_VECTOR_SIZE = 3;
    const int VERTEX_COLOR_SIZE = 3;

    const int VERTEX_SIZE = VERTEX_VECTOR_SIZE + VERTEX_COLOR_SIZE;

    const int VERTICES_PER_SIDE = 11;
    const int VERTICES_PER_MAP = VERTICES_PER_SIDE * VERTICES_PER_SIDE;

    const int VERTEX_DATA_SIZE = VERTEX_SIZE * VERTICES_PER_MAP;

    const int GRIDS_PER_SIDE = VERTICES_PER_SIDE - 1;
    const int GRIDS_PER_MAP = GRIDS_PER_SIDE * GRIDS_PER_SIDE;

    const int TRIANGLES_PER_MAP = GRIDS_PER_MAP * 2;

    const int INDEX_DATA_SIZE = TRIANGLES_PER_MAP * 3;


    const float GRID_SIZE = 0.25f;


    float vertex_data[VERTEX_DATA_SIZE] = {};
    unsigned int index_data[INDEX_DATA_SIZE] = {};

    generate_vertices(vertex_data, GRIDS_PER_SIDE, GRID_SIZE);
    generate_indices(index_data, GRIDS_PER_SIDE);

    unsigned int program = create_program(vertex_shader_source, fragment_shader_source);
    int projection_uniform = glGetUniformLocation(program, "projection");
    int view_uniform = glGetUniformLocation(program, "view");

    glEnable(GL_DEPTH_TEST);


// vao
    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

// vbo
    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

// vio
    unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

// detach all
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    bool show_debug = false;
    bool use_glm = true;

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.6f, 0.9f, 0.9f, 1.0f);

    float pitch = 0.0f;
    float yaw = 0.0f;
    v4 pos = {};

    bool key_w = false;
    bool key_s = false;
    bool key_r = false;
    bool key_f = false;
    bool key_a = false;
    bool key_d = false;
    bool key_q = false;
    bool key_e = false;

    float translate = 0.0f;



    float fovy = 45.0f;
    float aspect = (float)WIDTH / (float)HEIGHT;
    float near = 0.1f;
    float far = 100.0f;
    glm::mat4 projection_matrix = perspective(use_glm, fovy, aspect, near, far);


    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
            if (event.type == SDL_KEYUP && event.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                show_debug = !show_debug;
            if(event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_W)
                    key_w = event.key.state == SDL_PRESSED;
                if (event.key.keysym.scancode == SDL_SCANCODE_A)
                    key_a = event.key.state == SDL_PRESSED;
                if (event.key.keysym.scancode == SDL_SCANCODE_S)
                    key_s = event.key.state == SDL_PRESSED;
                if (event.key.keysym.scancode == SDL_SCANCODE_D)
                    key_d = event.key.state == SDL_PRESSED;
                if (event.key.keysym.scancode == SDL_SCANCODE_Q)
                    key_q = event.key.state == SDL_PRESSED;
                if (event.key.keysym.scancode == SDL_SCANCODE_E)
                    key_e = event.key.state == SDL_PRESSED;
                if (event.key.keysym.scancode == SDL_SCANCODE_R)
                    key_r = event.key.state == SDL_PRESSED;
                if (event.key.keysym.scancode == SDL_SCANCODE_F)
                    key_f = event.key.state == SDL_PRESSED;
            }
        }

        float adjustment = 0.01f;
        v4 delta_pos = {};
        if(key_w)
            delta_pos.z -= adjustment;
        if(key_a)
            delta_pos.x -= adjustment;
        if(key_s)
            delta_pos.z += adjustment;
        if(key_d)
            delta_pos.x += adjustment;
        if(key_q)
            yaw -= adjustment;
        if(key_e)
            yaw += adjustment;
        if(key_r)
            pitch -= adjustment;
        if(key_f)
            pitch += adjustment;

            pos += delta_pos;


        glm::mat4 view_matrix = camera(use_glm, translate, pitch, yaw);



        // Clear the screen
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Attach
        glUseProgram(program);
        glBindVertexArray(vertex_array);
        // Update
        glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, &projection_matrix[0][0]);
        glUniformMatrix4fv(view_uniform, 1, GL_FALSE, &view_matrix[0][0]);
        // Render
        glDrawElements(GL_TRIANGLES, INDEX_DATA_SIZE, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        if(show_debug)
        {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(window);
            ImGui::NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            // if (show_demo_window)
            //     ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            // {
            //     static float f = 0.0f;
            //     static int counter = 0;
            //
            //     ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            //
            //     ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            //     ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            //     ImGui::Checkbox("Another Window", &show_another_window);
            //
            //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //     ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            //
            //     if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            //         counter++;
            //     ImGui::SameLine();
            //     ImGui::Text("counter = %d", counter);
            //
            //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            //     ImGui::End();
            // }

            // 3. Show another simple window.
            // if (show_another_window)
            // {
            //     ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            //     ImGui::Text("Hello from another window!");
            //     if (ImGui::Button("Close Me"))
            //         show_another_window = false;
            //     ImGui::End();
            // }

            ImGui::Begin("Debug");

            if(ImGui::Checkbox("use_glm", &use_glm))
            {
                projection_matrix = perspective(use_glm, fovy, aspect, near, far);
            }

            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            ImGui::SliderFloat("translate", &translate, 0.0f, 5.0f);

            ImGui::End();

            // Rendering
            ImGui::Render();
            SDL_GL_MakeCurrent(window, gl_context);
            // glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
            // glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            // glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        }

        // yaw += 0.01f;
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
