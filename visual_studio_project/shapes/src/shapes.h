#pragma once


class camera
{
public:
    static const float f;
    static const float n;
    static const float aspect;

    static const float projection_matrix[];
    static const float view_matrix[];
};


struct vertex_uniform_block
{
    // Camera
    float proj[16];
    float view[16];
    // Object
    float position[4];
    float rotation[4];
    float scale[4];
};


struct fragment_uniform_block
{
    // Object
    float tint_color[4];
    // Lights
    float light_color[4];
    float light_position[4];
};
