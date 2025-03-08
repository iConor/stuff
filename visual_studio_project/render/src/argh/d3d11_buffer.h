#pragma once


#include <d3d11.h>


#include "renderer_buffer.h"


namespace renderer
{
    class d3d11_buffer : public buffer
    {
    public:
        d3d11_buffer(buffer_desc desc);
        ~d3d11_buffer();

        void sub(const void* data);

    private:
        int size;

        UINT translate(buffer_type type);

        ID3D11Buffer* buffer;
    };
}
