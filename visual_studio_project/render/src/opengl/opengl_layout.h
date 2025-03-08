#pragma once


#include "layout.h"


#include <vector>


namespace render
{
    class opengl_layout : public layout
    {
    public:
        opengl_layout(const layout_desc* desc, const int count);
        ~opengl_layout();

    private:
        std::vector<layout_desc> layout_data;
        int stride;
    };
}
