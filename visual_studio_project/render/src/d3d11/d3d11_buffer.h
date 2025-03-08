#pragma once


#include "buffer.h"


#include <d3d11.h>


namespace render
{
    class d3d11_buffer : public buffer
    {
    public:
        d3d11_buffer(const buffer_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_context);
        ~d3d11_buffer();

        void sub(const void* data) override;

        void bind_uniform_block(const int block_binding) override;

        ID3D11Buffer* get_it();
        int get_sz();

    private:
        ID3D11Device*               m_pd3dDevice;
        ID3D11DeviceContext*        m_pd3dDeviceContext;

        ID3D11Buffer*               m_pd3dBuffer;

        buffer_type type;
        int size;

        D3D11_BIND_FLAG translate(buffer_type bt);
    };
}
