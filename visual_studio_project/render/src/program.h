#pragma once


#include "buffer.h"
#include "texture.h"
#include "sampler.h"
#include "layout.h"

#include "shader.h"


namespace render
{
    struct program_desc
    {
        shader* vertex;
        shader* fragment;
    };


    class program
    {
    public:
        // program(const program_desc& desc);
        // ~program();

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void bind_uniform_block(const int block_binding, const char* block_name) = 0;
        virtual void bind_sampler(const int target, const char* name) = 0;

        virtual void bind_vs_const_block(buffer* vs_cb) = 0;
        virtual void bind_fs_const_block(buffer* fs_cb) = 0;
        virtual void bind_texture(texture* rt) = 0;
        virtual void bind_sampler(sampler* rs) = 0;
        virtual void bind_layout(layout* lo) = 0;
    };
}
