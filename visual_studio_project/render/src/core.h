#pragma once


#include "buffer.h"
#include "layout.h"
#include "program.h"
#include "sampler.h"
#include "shader.h"
#include "texture.h"

#include "object.h"



#include "platform_render.h"


#include "imgui.h"


namespace render
{
    class core
    {
    public:
        static core* load(platform::render* pr);


        // TODO:
        // context
        // command buffer
        // render pass
        // render target
        // pipeline (layout/state)
        // finish migrating platform render layer


// Object Instantiation (Allocation, etc.)
////////////////////////////////////////////////////////////////////////////////

        virtual buffer* create_buffer(const buffer_desc& desc) = 0;
        virtual void release_buffer(buffer* bye) = 0;

        virtual layout* create_layout(const layout_desc* desc, int count) = 0;
        virtual void release_layout(layout* bye) = 0;

        virtual program* create_program(const program_desc& desc) = 0;
        virtual void release_program(program* bye) = 0;

        virtual sampler* create_sampler(const sampler_desc& desc) = 0;
        virtual void release_sampler(sampler* bye) = 0;

        virtual shader* create_shader(const shader_desc& desc) = 0;
        virtual void release_shader(shader* bye) = 0;

        virtual texture* create_texture(const texture_desc& desc) = 0;
        virtual void release_texture(texture* bye) = 0;

        // TODO: Aggregate object (already holds VAO)
        virtual object* create_object() = 0;
        virtual void release_object(object* bye) = 0;

////////////////////////////////////////////////////////////////////////////////


// Global State
////////////////////////////////////////////////////////////////////////////////

        virtual void depth() = 0; // TODO: DepthStencil State/Target/View
        virtual void cull() = 0;  // TODO: Rasterizer State

////////////////////////////////////////////////////////////////////////////////


// TODO: Finish migrating platform stuff
////////////////////////////////////////////////////////////////////////////////

        virtual void clear(float r, float g, float b, float a) = 0;

////////////////////////////////////////////////////////////////////////////////


// ImGui Town
////////////////////////////////////////////////////////////////////////////////

        virtual void ImGui_Init() = 0;
        virtual void ImGui_NewFrame() = 0;
        virtual void ImGui_RenderDrawData(ImDrawData* draw_data) = 0;
        virtual void ImGui_Shutdown() = 0;


////////////////////////////////////////////////////////////////////////////////
    };
}
