#include "d3d11_texture.h"


#include "stb_image.h"


namespace renderer
{
    d3d11_texture::d3d11_texture(const char* filename)
    {
        int channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* img = stbi_load(filename, &width, &height, &channels, 0);
        stbi_image_free(img);
    }


    d3d11_texture::~d3d11_texture()
    {
    }

    void d3d11_texture::bind()
    {
        width = 0;
    }
}
