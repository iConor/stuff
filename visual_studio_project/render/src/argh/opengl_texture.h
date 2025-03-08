#pragma once


#include "renderer_texture.h"


#include "glad/glad.h"


namespace renderer
{
    class opengl_texture : public texture
    {
    public:
        opengl_texture(const char* filename);
        ~opengl_texture();

        void bind() override;

        GLuint get_id();

    private:
        void create(const char* filename);
        void destroy();

        int width;
        int height;

        GLuint tex;
    };
}
