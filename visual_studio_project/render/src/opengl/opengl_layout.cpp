#include "opengl_layout.h"


#include "glad/glad.h"


namespace render
{
    opengl_layout::opengl_layout(const layout_desc* desc, const int count)
    {
        layout_data = std::vector<layout_desc>(desc, desc + count);

        stride = 0;
        for(layout_desc ld : layout_data) { stride += ld.size; }

        int offset = 0;
        for(int index = 0; index < layout_data.size(); index++)
        {
            int size = layout_data[index].size;

            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));

            offset += size;
        }
    }


    opengl_layout::~opengl_layout()
    {
    }
}
