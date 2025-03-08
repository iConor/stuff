#pragma once

namespace render
{
    class util
    {
    public:
        static void clear(float r, float g, float b, float a);
        static void cull();
        static void depth();
    };
}
