#pragma once


#include "sampler.h"


namespace render
{
    class opengl_sampler : public sampler
    {
    public:
        opengl_sampler(const sampler_desc& desc);
        ~opengl_sampler();
    };
}
