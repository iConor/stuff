#pragma once


#include "renderer_texture.h"


namespace renderer
{
    class d3d11_texture : public texture
    {
    public:
        d3d11_texture(const char* filename);
        ~d3d11_texture();

        void bind() override;

    private:
        int width;
        int height;
    };
}
