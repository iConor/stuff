#pragma once


#include "layout.h"

#include <d3d11.h>
#include <vector>


namespace render
{
    class d3d11_layout : public layout
    {
    public:
        d3d11_layout(const layout_desc* desc, const int count, ID3D11Device* device, ID3D11DeviceContext* device_context);
        ~d3d11_layout();

        D3D11_INPUT_ELEMENT_DESC* get_it();
        int get_ct();

        int get_stride();

    private:
        ID3D11Device*               m_pd3dDevice;
        ID3D11DeviceContext*        m_pd3dDeviceContext;


        std::vector<layout_desc> layout_data;
        int stride;

        DXGI_FORMAT translate(int count);

        D3D11_INPUT_ELEMENT_DESC* ied;
        int ct;

        // ID3D11InputLayout* input_layout;
    };
}
