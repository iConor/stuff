#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H


#include "engine_types.h"


#include <iostream>


typedef struct
{
    s32 width;
    s32 height;
    s32 channels;
    u8* data;
} texture;


void load_texture(texture* tex, const char* filename);
void free_texture(texture* tex);


u32 texture_from_file(std::string pathname, std::string filename);

#endif /* ENGINE_TEXTURE_H */
