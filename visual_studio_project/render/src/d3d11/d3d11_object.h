#pragma once


#include "object.h"

#include <d3d11.h>

#include "buffer.h"

#include "d3d11_layout.h"



// TODO: Fix stride -- see .cpp
// TODO:
// TODO:
// TODO:
// Start making the object able to take and manipulate everything as if it were a PSO?
// This might look good on a resume in that it should have internal functions for manipulating
// objects of the associated render api type and public functions for receiving generic object
// types and converting them (with error checking) before calling the internal functions
// Look inside the object comments for hints about what calls are PSO-like or not




namespace render
{
    class d3d11_object : public object
    {
    public:
        d3d11_object(ID3D11Device* device, ID3D11DeviceContext* device_context);
        ~d3d11_object();

        void bind() override;
        void unbind() override;

        void bind_vbuf(buffer* vb) override;
        void bind_ibuf(buffer* ib) override;
        void bind_layout(layout* lo) override;

        void draw(int count) override;

    private:
        ID3D11Device*               m_pd3dDevice;
        ID3D11DeviceContext*        m_pd3dDeviceContext;

        ID3D11Buffer* vertex_buffer;
        ID3D11Buffer* index_buffer;

        int index_count;
        int layout_stride;
    };
}
