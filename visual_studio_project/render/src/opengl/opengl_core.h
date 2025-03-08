#pragma once


#include "core.h"

#include "win32_render_opengl.h"


#include <windows.h>

namespace render
{
    class opengl_core : public core
    {
    public:
        opengl_core(platform::render* pr);
        ~opengl_core();

////////////////////////////////////////////////////////////////////////////////

        buffer* create_buffer(const buffer_desc& desc) override;
        void release_buffer(buffer* bye) override;

        layout* create_layout(const layout_desc* desc, int count) override;
        void release_layout(layout* bye) override;

        program* create_program(const program_desc& desc) override;
        void release_program(program* bye) override;

        sampler* create_sampler(const sampler_desc& desc) override;
        void release_sampler(sampler* bye) override;

        shader* create_shader(const shader_desc& desc) override;
        void release_shader(shader* bye) override;

        texture* create_texture(const texture_desc& desc) override;
        void release_texture(texture* bye) override;


        object* create_object() override;
        void release_object(object* bye) override;

////////////////////////////////////////////////////////////////////////////////

        void depth() override;
        void cull() override;
        void clear(float r, float g, float b, float a) override;

////////////////////////////////////////////////////////////////////////////////

        void ImGui_Init() override;
        void ImGui_NewFrame() override;
        void ImGui_RenderDrawData(ImDrawData* draw_data) override;
        void ImGui_Shutdown() override;

    private:
        HWND hwnd;

    };
}
