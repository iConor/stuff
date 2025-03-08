#pragma once


#include "renderer_shader_program.h"

#include "glad/glad.h"


namespace renderer
{
    class opengl_shader_program : public shader_program
    {
    public:
        opengl_shader_program(shader_program_desc desc);
        ~opengl_shader_program();

        void bind() override;

        GLuint get_id();

        void bind_uniform_block(const int block_binding, const char* block_name);
        void bind_sampler(const int target, const char* name);

    private:
        void create(shader_program_desc desc);
        void destroy();

        // bool check();

        GLuint id = 0;
    };
}
