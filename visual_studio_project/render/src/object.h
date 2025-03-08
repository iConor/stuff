#pragma once


#include "buffer.h"
#include "layout.h"

namespace render
{
    class object
    {
    public:
        // object();
        // ~object();

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void bind_vbuf(buffer* vb) = 0;
        virtual void bind_ibuf(buffer* ib) = 0;

        virtual void bind_layout(layout* lo) = 0;

        virtual void draw(int count) = 0;
    };
}
