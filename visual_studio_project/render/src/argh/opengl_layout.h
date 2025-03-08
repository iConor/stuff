#pragma once


#include "renderer_layout.h"

#include <vector>

namespace renderer
{
    class opengl_layout : public layout
    {
    public:
        opengl_layout(layout_desc* descs, int num_descs);
        ~opengl_layout();

    private:
        void create(layout_desc* descs, int num_descs);
        void destroy();

        void submit();

        std::vector<layout_desc> layout_data;
        int stride;

    };
}
