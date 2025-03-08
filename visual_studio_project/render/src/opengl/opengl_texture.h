#pragma once


#include "texture.h"


#include "glad/glad.h"


namespace render
{
    class opengl_texture : public texture
    {
    public:
        opengl_texture(const texture_desc& desc);
        ~opengl_texture();

        void bind() override;
    private:
        GLuint tex;
    };
}
