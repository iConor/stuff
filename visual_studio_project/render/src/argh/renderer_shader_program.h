#pragma once


#include "renderer_shader.h"


namespace renderer
{
    struct shader_program_desc
    {
        shader* vertex;
        shader* fragment;
    };

    class shader_program
    {
    public:
        // shader_program();
        // ~shader_program();

        virtual void bind() = 0;
    };
}
