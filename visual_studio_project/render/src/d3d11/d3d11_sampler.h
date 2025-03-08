#pragma once


#include "sampler.h"

#include <d3d11.h>

namespace render
{
    class d3d11_sampler : public sampler
    {
    public:
        d3d11_sampler(const sampler_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_context);
        ~d3d11_sampler();


        ID3D11SamplerState* get_it();

    private:
        ID3D11Device*               m_pd3dDevice;
        ID3D11DeviceContext*        m_pd3dDeviceContext;


        ID3D11SamplerState* texture_sampler;
    };
}
