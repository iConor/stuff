#pragma once


namespace render
{
    struct texture_desc
    {
        int width;
        int height;
        void* data;
    };


    class texture
    {
    public:
        // texture(const texture_desc& desc);
        // ~texture();

        virtual void bind() = 0;
    };
}
