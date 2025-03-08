#include "opengl_texture.h"


#include "stb_image.h"


namespace renderer
{
    opengl_texture::opengl_texture(const char* filename)
    {
        create(filename);
    }


    opengl_texture::~opengl_texture()
    {
        destroy();
    }


    void opengl_texture::create(const char* filename)
    {
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // TODO: Handle channels. Assuming RGBA/(4 channels) for now (it matches my test pngs)
        int channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* img = stbi_load(filename, &width, &height, &channels, 0);
        if(img)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(img);
    }


    void opengl_texture::destroy()
    {

    }


    GLuint opengl_texture::get_id()
    {
        return tex;
    }


    void opengl_texture::bind()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
    }
}
