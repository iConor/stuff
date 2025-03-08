#pragma once


#include "program.h"


#include "glad/glad.h"


namespace render
{
    class opengl_program : public program
    {
    public:
        opengl_program(const program_desc& desc);
        ~opengl_program();

        void bind() override;
        void unbind() override;

        void bind_uniform_block(const int block_binding, const char* name) override;
        void bind_sampler(const int target, const char* name);

        void bind_vs_const_block(buffer* vs_cb) override;
        void bind_fs_const_block(buffer* fs_cb) override;
        void bind_texture(texture* rt) override;
        void bind_sampler(sampler* rs) override;
        void bind_layout(layout* lo) override;


    private:
        GLuint id;
    };
}
