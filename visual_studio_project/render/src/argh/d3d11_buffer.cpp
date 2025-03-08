#include "d3d11_buffer.h"


namespace renderer
{
    d3d11_buffer::d3d11_buffer(buffer_desc desc)
    {
        size = desc.size;


        D3D11_BUFFER_DESC d3d11_desc = { 0 };

        d3d11_desc.ByteWidth               = desc.size;
        d3d11_desc.Usage                   = D3D11_USAGE_DYNAMIC;
        d3d11_desc.BindFlags               = translate(desc.type);
        d3d11_desc.CPUAccessFlags          = D3D11_CPU_ACCESS_WRITE;
        d3d11_desc.MiscFlags               = 0;
        // d3d11_desc.StructureByteStride     = ;

        // TODO: How to handle device and context pointers?
        // device->CreateBuffer(&d3d11_desc, NULL, &buffer);

        sub(desc.data);
    }


    d3d11_buffer::~d3d11_buffer()
    {
    }


    void d3d11_buffer::sub(const void* data)
    {
        // D3D11_MAPPED_SUBRESOURCE sub;
        // device_context->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &sub);
        // memcpy(sub.pData, data, size);
        // device_context->Unmap(buffer, NULL);
    }


    UINT d3d11_buffer::translate(buffer_type type)
    {
        switch(type)
        {
            case buffer_type::vertex:   return D3D11_BIND_VERTEX_BUFFER;
            case buffer_type::index:    return D3D11_BIND_INDEX_BUFFER;
            case buffer_type::uniform:  return D3D11_BIND_CONSTANT_BUFFER;
        }
        return 0;

    }
}
