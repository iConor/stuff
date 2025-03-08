#pragma once


namespace renderer
{
    enum class shader_type
    {
        unknown,
        vertex,
        fragment,
    };

    struct shader_desc
    {
        shader_type type;
        const char* source;
    };

    class shader
    {
    public:
        // shader();
        // ~shader();
    };
}
