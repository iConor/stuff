#pragma once


#include "glad/glad.h"



// render::texture* tex = new render::texture("E:\\dev\\scaling-potato\\bin\\Debug-x64\\platform\\wall.jpg");



namespace render
{
    class texture
    {
    public:
        texture(const char* filename);
        ~texture();

        unsigned int id();
    private:
        int width;
        int height;
        unsigned int tx;
    };
}
