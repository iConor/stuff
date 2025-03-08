#pragma once


namespace render
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
        // shader(const shader_desc& desc);
        // ~shader();
    };
}
