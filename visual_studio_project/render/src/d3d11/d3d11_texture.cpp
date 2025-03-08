#include "d3d11_texture.h"


namespace render
{
    d3d11_texture::d3d11_texture(const texture_desc& desc, ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        m_pd3dDevice = device;
        m_pd3dDeviceContext = device_context;


        ID3D11Texture2D* pTexture = NULL;

        D3D11_TEXTURE2D_DESC tex_desc = { 0 };

        tex_desc.Width              = desc.width;
        tex_desc.Height             = desc.height;
        tex_desc.MipLevels          = 1;
        tex_desc.ArraySize          = 1;
        tex_desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
        // tex_desc.Format             = DXGI_FORMAT_UNKNOWN;
        tex_desc.SampleDesc.Count   = 1;
        // tex_desc.SampleDesc.Quality = ;
        tex_desc.Usage              = D3D11_USAGE_DEFAULT;
        tex_desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
        // tex_desc.CPUAccessFlags     = 0;
        // tex_desc.MiscFlags          = ;

        D3D11_SUBRESOURCE_DATA tex_sub = { 0 };

        tex_sub.pSysMem = desc.data;
        tex_sub.SysMemPitch = tex_desc.Width * 4;  // TODO: this magic 4 is the # of color channels -- put it in the texture description?
        tex_sub.SysMemSlicePitch = 0;

        device->CreateTexture2D(&tex_desc, &tex_sub, &pTexture);

        D3D11_SHADER_RESOURCE_VIEW_DESC view_desc = { 0 };

        view_desc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
        view_desc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
        view_desc.Texture2D.MostDetailedMip = 0;
        view_desc.Texture2D.MipLevels       = tex_desc.MipLevels;

        device->CreateShaderResourceView(pTexture, &view_desc, &texture_view);

        pTexture->Release();
    }


    d3d11_texture::~d3d11_texture()
    {
    }


    void d3d11_texture::bind()
    {

    }

    ID3D11ShaderResourceView* d3d11_texture::get_it()
    {
        return texture_view;
    }
}
