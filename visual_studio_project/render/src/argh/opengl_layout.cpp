#include "opengl_layout.h"


#include "glad/glad.h"


namespace renderer
{
    opengl_layout::opengl_layout(layout_desc* descs, int num_descs)
    {
        create(descs, num_descs);
        submit();
    }


    opengl_layout::~opengl_layout()
    {
    }


    void opengl_layout::create(layout_desc* descs, int num_descs)
    {
        layout_data = std::vector<layout_desc>(descs, descs + num_descs);

        stride = 0;
        for(layout_desc ld : layout_data)
        {
            stride += ld.size;
        }
    }


    void opengl_layout::destroy()
    {

    }


    void opengl_layout::submit()
    {
        int offset = 0;

        for(int index = 0; index < layout_data.size(); index++)
        {
            int size = layout_data[index].size;

            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));

            offset += size;
        }
    }
}
