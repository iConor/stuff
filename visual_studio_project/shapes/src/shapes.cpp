#include "shapes.h"



const float camera::f = 10.0f;
const float camera::n = 0.1f;
const float camera::aspect = 16.0f / 9.0f;


// OpenGL
const float camera::projection_matrix[] =
{
    1.0f/aspect,  0.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  f/(f-n),  -1.0f,
    0.0f,  0.0f,  (f*n)/(f-n),  0.0f,
};


// D3D11
// const float camera::projection_matrix[] =
// {
//     1.0f/aspect,  0.0f,  0.0f,  0.0f,
//     0.0f,  1.0f,  0.0f,  0.0f,
//     0.0f,  0.0f,  f/(n-f), -1.0f ,
//     0.0f,  0.0f,  (f*n)/(n-f),  0.0f,
// };


const float camera::view_matrix[] =
{
    1.0f,  0.0f,  0.0f,  0.0f,
    0.0f,  1.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  1.0f,  0.0f,
    0.0f,  0.0f,  0.0f,  1.0f,
};
