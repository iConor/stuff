#include "d3d11_buffer.h"


namespace render
{
    d3d11_buffer::d3d11_buffer(const buffer_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        m_pd3dDevice = device;
        m_pd3dDeviceContext = device_context;

        type = desc.type;
        size = desc.size;

// TODO: move init to its own function so constructor args and stored pointers are separated for clarity and faster bug detection
        D3D11_BUFFER_DESC d3d11_desc = { 0 };

        d3d11_desc.ByteWidth               = size;
        d3d11_desc.Usage                   = D3D11_USAGE_DYNAMIC;
        d3d11_desc.BindFlags               = translate(type);
        d3d11_desc.CPUAccessFlags          = D3D11_CPU_ACCESS_WRITE;
        d3d11_desc.MiscFlags               = 0;
        // vb_desc.StructureByteStride     = 8 * sizeof(float);

        m_pd3dDevice->CreateBuffer(&d3d11_desc, NULL, &m_pd3dBuffer);

        if(desc.data)
        {
            sub(desc.data);
        }
    }


    d3d11_buffer::~d3d11_buffer()
    {
    }


    void d3d11_buffer::sub(const void* data)
    {
        D3D11_MAPPED_SUBRESOURCE map_sub;
        m_pd3dDeviceContext->Map(m_pd3dBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &map_sub);
        memcpy(map_sub.pData, data, size);
        m_pd3dDeviceContext->Unmap(m_pd3dBuffer, NULL);
    }


    D3D11_BIND_FLAG d3d11_buffer::translate(buffer_type bt)
    {
        switch(type)
        {
            case buffer_type::vertex:   return D3D11_BIND_VERTEX_BUFFER;
            case buffer_type::index:    return D3D11_BIND_INDEX_BUFFER;
            case buffer_type::uniform:  return D3D11_BIND_CONSTANT_BUFFER;
        }
        return D3D11_BIND_VERTEX_BUFFER; // return 0; // TODO: best way to detect/report or avoid this error?
    }


    void d3d11_buffer::bind_uniform_block(const int block_binding)
    {

    }


    ID3D11Buffer* d3d11_buffer::get_it()
    {
        return m_pd3dBuffer;
    }


    int d3d11_buffer::get_sz()
    {
        return size;
    }
}
