#include "texture.h"


#include "stb_image.h"
#include <stdio.h>

namespace render
{
    texture::texture(const char* filename)
    {
        glGenTextures(1, &tx);
        glBindTexture(GL_TEXTURE_2D, tx);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* img = stbi_load(filename, &width, &height, &channels, 0);
        if(img)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(img);
    }


    texture::~texture()
    {
    }


    unsigned int texture::id()
    {
        return tx;
    }
}
