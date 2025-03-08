#pragma once


namespace renderer
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
        // buffer();
        // ~buffer();
    };
}
