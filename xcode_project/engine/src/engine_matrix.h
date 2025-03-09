#ifndef ENGINE_MATRIX_H
#define ENGINE_MATRIX_H


#include "engine_vector.h"


////////////////////////////////////////////////////////////////////////////////
// m3 Operators


////////////////////////////////////////////////////////////////////////////////
// m4f Operators


inline m4f M4()
{
    m4f inst =
    {{
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f },
    }};

    return inst;
}


inline m4f operator*(m4f lhs, m4f rhs)
{
    m4f product;

    // m*n times n*p matrix
    int m = 4;
    int n = 4;
    int p = 4;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < p; j++)
        {
            product.m[i][j] = 0;
            for(int k = 0; k < n; k++)
            {
                product.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
            }
        }
    }

    return product;
}


inline m4f operator*(float lhs, m4f rhs)
{
    m4f product = rhs;

    for(int i = 0; i < 16; i++)
    {
        product.e[i] *= lhs;
    }

    return product;
}


inline m4f operator*(m4f lhs, float rhs)
{
    return rhs * lhs;
}


inline m4f& operator*=(m4f &lhs, float rhs)
{
    lhs = lhs * rhs;

    return lhs;
}


inline v4f operator*(m4f lhs, v4f rhs)
{
    v4f product;

    product.x = lhs.m[0][0] * rhs.x +
                lhs.m[0][1] * rhs.y +
                lhs.m[0][2] * rhs.z +
                lhs.m[0][3] * rhs.w;

    product.y = lhs.m[1][0] * rhs.x +
                lhs.m[1][1] * rhs.y +
                lhs.m[1][2] * rhs.z +
                lhs.m[1][3] * rhs.w;

    product.z = lhs.m[2][0] * rhs.x +
                lhs.m[2][1] * rhs.y +
                lhs.m[2][2] * rhs.z +
                lhs.m[2][3] * rhs.w;

    product.w = lhs.m[3][0] * rhs.x +
                lhs.m[3][1] * rhs.y +
                lhs.m[3][2] * rhs.z +
                lhs.m[3][3] * rhs.w;

    return product;
}


inline m4f identity()
{
    m4f id =
    {{
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f },
    }};

    return id;
}


inline m4f rotation(v3f axis, float radians)
{
    f32 ct = cosf(radians);
    f32 st = sinf(radians);
    f32 ci = (1 - ct);

    axis = normalize(axis);

    f32 x = axis.x;
    f32 y = axis.y;
    f32 z = axis.z;

    m4f rot =
    {{
#ifdef ENGINE_ROW_MAJOR
        {     ct + x * x * ci, x * y * ci - z * st, x * y * ci + y * st, 0.0f },
        { y * x * ci + z * st,     ct + y * y * ci, y * z * ci - x * st, 0.0f },
        { z * x * ci - y * st, z * y * ci + x * st,     ct + z * z * ci, 0.0f },
        {                0.0f,                0.0f,                0.0f, 1.0f },
#else
        {     ct + x * x * ci, y * x * ci + z * st, z * x * ci - y * st, 0.0f},
        { x * y * ci - z * st,     ct + y * y * ci, z * y * ci + x * st, 0.0f},
        { x * z * ci + y * st, y * z * ci - x * st,     ct + z * z * ci, 0.0f},
        {                0.0f,                0.0f,                0.0f, 1.0f},
#endif
    }};

    return rot;
}


inline m4f scale(f32 x, f32 y, f32 z)
{
    m4f sca =
    {{
        {    x, 0.0f, 0.0f, 0.0f },
        { 0.0f,    y, 0.0f, 0.0f },
        { 0.0f, 0.0f,    y, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f },
    }};

    return sca;
}


inline m4f scale(v3f sca)
{
    return scale(sca.x, sca.y, sca.z);
}


inline m4f translation(f32 x, f32 y, f32 z)
{
    m4f trans =
    {{
#ifdef ENGINE_ROW_MAJOR
        { 1.0f, 0.0f, 0.0f,    x },
        { 0.0f, 1.0f, 0.0f,    y },
        { 0.0f, 0.0f, 1.0f,    z },
        { 0.0f, 0.0f, 0.0f, 1.0f },
#else
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        {    x,    y,    z, 1.0f },
#endif
    }};

    return trans;
}


inline m4f translation(v3f t)
{
    return translation(t.x, t.y, t.z);
}


// right hand
inline m4f perspective(f32 fovy_radians, f32 aspect_ratio, f32 near_z, f32 far_z)
{
//    f32 ys = 1.0f / tanf(fovy_radians * 0.5f);
//    f32 xs = ys / aspect_ratio;
//    f32 zs = far_z / (near_z - far_z);
//
//    m4f proj =
//    {{
//        {   xs, 0.0f,        0.0f,  0.0f },
//        { 0.0f,   ys,        0.0f,  0.0f },
//        { 0.0f, 0.0f,          zs, -1.0f },
//        { 0.0f, 0.0f, near_z * zs,  0.0f },
//    }};

//    f32 ys = 1.0f / tanf(fovy_radians * 0.5f);
//    f32 xs = ys / aspect_ratio;
//    f32 zs = (far_z - near_z);
//
//    m4f proj =
//    {{
//        {   xs, 0.0f,        0.0f,  0.0f },
//        { 0.0f,   ys,        0.0f,  0.0f },
//        { 0.0f, 0.0f,      -(far_z + near_z) / zs, -1.0f },
//        { 0.0f, 0.0f, -2.0f * far_z * near_z / zs,  0.0f },
//    }};

    f32 tan_half_fovy = tanf(fovy_radians * 0.5f);

    m4f proj =
    {{
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    }};

    proj.m[0][0] = 1.0f / (aspect_ratio * tan_half_fovy);
    proj.m[1][1] = 1.0f / tan_half_fovy;
    proj.m[2][2] = -(far_z + near_z) / (far_z - near_z);
    proj.m[2][3] = -1.0f;
    proj.m[3][2] = -(2.0f * far_z * near_z) / (far_z - near_z);


    return proj;
}


inline m4f look_at(v3f eye, v3f center, v3f up)
{
    v3f f = normalize(center - eye);
    v3f s = normalize(cross(f, up));
    v3f u = cross(s, f);

    m4f view =
    {{
        {          s.x,          u.x,         -f.x, 0.0f },
        {          s.y,          u.y,         -f.y, 0.0f },
        {          s.z,          u.z,         -f.z, 0.0f },
        { -dot(s, eye), -dot(u, eye),  dot(f, eye), 1.0f },
    }};

    return view;
}


inline m4f look_at_lh(v3f eye, v3f center, v3f up)
{
    v3f f = normalize(center - eye);
    v3f s = normalize(cross(up, f));
    v3f u = cross(f, s);

    m4f view =
    {{
        {          s.x,          u.x,          f.x, 0.0f },
        {          s.y,          u.y,          f.y, 0.0f },
        {          s.z,          u.z,          f.z, 0.0f },
        { -dot(s, eye), -dot(u, eye), -dot(f, eye), 1.0f },
    }};

    return view;
}


#endif /* ENGINE_MATRIX_H */
