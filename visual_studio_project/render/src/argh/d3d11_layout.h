#pragma once


#include <vector>

#include "renderer_layout.h"


namespace renderer
{
    class d3d11_layout : public layout
    {
    public:
        d3d11_layout(layout_desc* desc, int count);
        ~d3d11_layout();

    private:
        void create(layout_desc* descs, int num_descs);
        void destroy();

        std::vector<layout_desc> layout_data;
        int stride;
    };
}
