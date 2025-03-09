#include "engine_texture.h"

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"




void load_texture(texture* tex, const char* filename)
{
    int width;
    int height;
    int channels_in_file;

    stbi_set_flip_vertically_on_load(true);

    int desired_channels = 4;
    unsigned char* data = stbi_load(filename, &width, &height, &channels_in_file, desired_channels);


    if(data)
    {
        tex->width = width;
        tex->height = height;
        //    TODO: Error checking
        //    if(channels_in_file == desired_channels)
        tex->channels = desired_channels;

        tex->data = data;
    }
}


void free_texture(texture* tex)
{
    tex->width = 0;
    tex->height = 0;
    tex->channels = 0;

    stbi_image_free(tex->data);
}


u32 texture_from_file(std::string directory, std::string filename)
{
    GLuint texture_id;

    std::string path = directory + '/' + filename;

    texture tx;
    load_texture(&tx, path.c_str());

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tx.width, tx.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tx.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free_texture(&tx);

    return texture_id;
}
