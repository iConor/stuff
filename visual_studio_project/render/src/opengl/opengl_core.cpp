#include "opengl_core.h"


#include "opengl_buffer.h"
#include "opengl_layout.h"
#include "opengl_program.h"
#include "opengl_sampler.h"
#include "opengl_shader.h"
#include "opengl_texture.h"

#include "opengl_object.h"

#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"


namespace render
{
    opengl_core::opengl_core(platform::render* pr)
    {
        platform::win32_render_opengl* pr_ = static_cast<platform::win32_render_opengl*>(pr);
        hwnd = pr_->hwnd;
    }


    opengl_core::~opengl_core()
    {
    }


    buffer* opengl_core::create_buffer(const buffer_desc& desc)
    {
        return new opengl_buffer(desc);
    }


    void opengl_core::release_buffer(buffer* bye)
    {
        delete bye;
    }



    layout* opengl_core::create_layout(const layout_desc* desc, int count)
    {
        return new opengl_layout(desc, count);
    }


    void opengl_core::release_layout(layout* bye)
    {
        delete bye;
    }



    program* opengl_core::create_program(const program_desc& desc)
    {
        return new opengl_program(desc);
    }


    void opengl_core::release_program(program* bye)
    {
        delete bye;
    }



    sampler* opengl_core::create_sampler(const sampler_desc& desc)
    {
        return new opengl_sampler(desc);
    }


    void opengl_core::release_sampler(sampler* bye)
    {
        delete bye;
    }



    shader* opengl_core::create_shader(const shader_desc& desc)
    {
        return new opengl_shader(desc);
    }


    void opengl_core::release_shader(shader* bye)
    {
        delete bye;
    }



    texture* opengl_core::create_texture(const texture_desc& desc)
    {
        return new opengl_texture(desc);
    }


    void opengl_core::release_texture(texture* bye)
    {
        delete bye;
    }


    object* opengl_core::create_object()
    {
        return new opengl_object();
    }


    void opengl_core::release_object(object* bye)
    {
        delete bye;
    }


    void opengl_core::depth()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1.0f);
    }


    void opengl_core::cull()
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }


    void opengl_core::clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }


    ////////////////////////////////////////////////////////////////////////////////

    void opengl_core::ImGui_Init()
    {
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplOpenGL3_Init("#version 330");
    }


    void opengl_core::ImGui_NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
    }


    void opengl_core::ImGui_RenderDrawData(ImDrawData* draw_data)
    {
        ImGui_ImplOpenGL3_RenderDrawData(draw_data);
    }


    void opengl_core::ImGui_Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplWin32_Shutdown();
    }
}
