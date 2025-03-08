#include "d3d11_layout.h"




namespace render
{
    d3d11_layout::d3d11_layout(const layout_desc* desc, const int count, ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        m_pd3dDevice = device;
        m_pd3dDeviceContext = device_context;

        layout_data = std::vector<layout_desc>(desc, desc + count);

        stride = 0;
        for(layout_desc ld : layout_data) { stride += ld.size; }


        // TODO: should this be called later? held on to or generated on the fly?
        ied = new D3D11_INPUT_ELEMENT_DESC[count];
        ct = count;

        int offset = 0;
        for(int i = 0; i < count; i++)
        {
            ied[i].SemanticName         = layout_data[i].semantic;
            ied[i].SemanticIndex        = 0;
            ied[i].Format               = translate(layout_data[i].size);
            ied[i].InputSlot            = 0;
            ied[i].AlignedByteOffset    = offset * sizeof(float);
            ied[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
            ied[i].InstanceDataStepRate = 0;

            offset += layout_data[i].size;
        }
        // stride = offset;

        // TODO: link this up with the shader as seen below
        // ID3D11InputLayout* input_layout;
        // m_pd3dDevice->CreateInputLayout(ied, 3, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), &input_layout);

    }


    int d3d11_layout::get_stride()
    {
        return stride;
    }


    DXGI_FORMAT d3d11_layout::translate(int count)
    {
        switch(count)
        {
            case 2: return DXGI_FORMAT_R32G32_FLOAT;
            case 3: return DXGI_FORMAT_R32G32B32_FLOAT;
        }
        return DXGI_FORMAT_UNKNOWN;
    }


    d3d11_layout::~d3d11_layout()
    {
        delete ied;
    }


    D3D11_INPUT_ELEMENT_DESC* d3d11_layout::get_it()
    {
        return ied;
    }

    int d3d11_layout::get_ct()
    {
        return ct;
    }
}
