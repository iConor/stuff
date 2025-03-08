#pragma once


namespace render
{
    enum class buffer_type
    {
        unknown,
        vertex,
        index,
        uniform,
    };


    struct buffer_desc
    {
        buffer_type type;
        int size;
        const void* data;
    };


    class buffer
    {
    public:
        // buffer(const buffer_desc& desc);
        // ~buffer();

        virtual void sub(const void* data) = 0;

        virtual void bind_uniform_block(const int block_binding) = 0;
    };
}
