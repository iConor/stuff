#include "d3d11_layout.h"


namespace renderer
{
    d3d11_layout::d3d11_layout(layout_desc* desc, int count)
    {
        create(desc, count);
    }


    d3d11_layout::~d3d11_layout()
    {
    }


    void d3d11_layout::create(layout_desc* descs, int num_descs)
    {
        layout_data = std::vector<layout_desc>(descs, descs + num_descs);

        stride = 0;
        for(layout_desc ld : layout_data)
        {
            stride += ld.size;
        }
    }


    void d3d11_layout::destroy()
    {

    }
}
