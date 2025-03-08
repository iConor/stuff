#pragma once


#include "texture.h"


#include <d3d11.h>

namespace render
{
    class d3d11_texture : public texture
    {
    public:
        d3d11_texture(const texture_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_contexts);
        ~d3d11_texture();

        void bind() override;

        ID3D11ShaderResourceView* get_it();

    private:
        ID3D11Device*               m_pd3dDevice;
        ID3D11DeviceContext*        m_pd3dDeviceContext;


        ID3D11ShaderResourceView* texture_view;
    };
}
