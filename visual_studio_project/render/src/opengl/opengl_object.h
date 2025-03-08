#pragma once


#include "object.h"


#include "glad/glad.h"


namespace render
{
    class opengl_object : public object
    {
    public:
        opengl_object();
        ~opengl_object();

        void bind() override;
        void unbind() override;

        void bind_vbuf(buffer* vb) override;
        void bind_ibuf(buffer* ib) override;
        void bind_layout(layout* lo) override;

        void draw(int count) override;

    private:
        GLuint vao;
    };
}
