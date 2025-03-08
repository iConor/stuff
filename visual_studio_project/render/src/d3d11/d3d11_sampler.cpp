#include "d3d11_sampler.h"


namespace render
{
    d3d11_sampler::d3d11_sampler(const sampler_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        m_pd3dDevice = device;
        m_pd3dDeviceContext = device_context;


        D3D11_SAMPLER_DESC sampler_desc = { 0 };

        sampler_desc.Filter             = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampler_desc.AddressU           = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressV           = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressW           = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.MipLODBias         = 0.0f;
        // sampler_desc.MaxAnisotropy      = ;
        sampler_desc.ComparisonFunc     = D3D11_COMPARISON_ALWAYS;//GREATER_EQUAL;
        // sampler_desc.BorderColor        = ;
        sampler_desc.MinLOD             = 0.0f;
        sampler_desc.MaxLOD             = 0.0f;

        device->CreateSamplerState(&sampler_desc, &texture_sampler);
    }


    d3d11_sampler::~d3d11_sampler()
    {
    }

    ID3D11SamplerState* d3d11_sampler::get_it()
    {
        return texture_sampler;
    }
}
