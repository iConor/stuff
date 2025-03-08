#include "camera.h"


namespace ex
{
    float f = 10.0f;
    float n = 0.1f;
    float aspect = 16.0f / 9.0f;

    float projection_matrix[] =
    {
        1.0f/aspect,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f, -2.0f/(f-n),  -(f+n)/(f-n),
        0.0f,  0.0f,  0.0f,  1.0f,
    };

    float view_matrix[] =
    {
         1.0f,  0.0f,  0.0f,  0.0f,
         0.0f,  1.0f,  0.0f,  0.0f,
         0.0f,  0.0f,  1.0f,  0.0f,
         0.0f,  0.0f,  0.0f,  1.0f,
    };

    float* camera::proj_mat()
    {
        return projection_matrix;
    }

    float* camera::view_mat()
    {
        return view_matrix;
    }
}
