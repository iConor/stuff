#include "d3d11_shader_program.h"


namespace renderer
{
    d3d11_shader_program::d3d11_shader_program(shader_program_desc desc)
    {
        vertex_shader = desc.vertex;
        fragment_shader = desc.fragment;
    }


    d3d11_shader_program::~d3d11_shader_program()
    {
    }


    void d3d11_shader_program::bind()
    {
    }
}
