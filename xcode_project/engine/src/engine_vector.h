#ifndef ENGINE_VECTOR_H
#define ENGINE_VECTOR_H


#include "engine_types.h"
#include "engine_math.h"


////////////////////////////////////////////////////////////////////////////////
// v2f Operators


inline v2f V2(float x, float y)
{
    v2f inst;

    // TODO: clang on macOS does not like this, porque?
    // inst = { x, y };

    inst.x = x;
    inst.y = y;

    return inst;
}

inline v2f operator-(v2f rhs)
{
    v2f inverse;

    inverse.x = -rhs.x;
    inverse.y = -rhs.y;

    return inverse;
}


inline v2f operator+(v2f lhs, v2f rhs)
{
    v2f sum;

    sum.x = lhs.x + rhs.x;
    sum.y = lhs.y + rhs.y;

    return sum;
}


inline v2f& operator+=(v2f &lhs, v2f rhs)
{
    lhs = lhs + rhs;

    return lhs;
}


inline v2f operator-(v2f lhs, v2f rhs)
{
    v2f difference;

    difference.x = lhs.x - rhs.x;
    difference.y = lhs.y - rhs.y;

    return difference;
}


inline v2f& operator-=(v2f &lhs, v2f rhs)
{
    lhs = lhs - rhs;

    return lhs;
}


inline v2f operator*(v2f lhs, float rhs)
{
    v2f product;

    product.x = lhs.x * rhs;
    product.y = lhs.y * rhs;

    return product;
}


inline v2f operator*(float lhs, v2f rhs)
{
    return rhs * lhs;
}


inline v2f& operator*=(v2f &lhs, float rhs)
{
    lhs = lhs * rhs;

    return lhs;
}


inline v2f operator/(v2f lhs, float rhs)
{
    v2f quotient;

    quotient.x = lhs.x / rhs;
    quotient.y = lhs.y / rhs;

    return quotient;
}


inline v2f& operator/=(v2f &lhs, float rhs)
{
    lhs = lhs / rhs;

    return lhs;
}


inline float dot(v2f lhs, v2f rhs)
{
    float scalar;

    scalar = lhs.x * rhs.x + lhs.y * rhs.y; // FMA?

    return scalar;
}


inline v2f lerp(v2f v0, v2f v1, float t)
{
    v2f approx;

    // NOTE:
    //      With fused multiply-add:
    //      approx = v0 + t * (v1 - v0)
    approx = (1.0f - t) * v0 + t * v1;

    return approx;
}


inline v2f perp(v2f v0)
{
    v2f ortho;

    // TODO: clang on macOS does not like this, porque?
    // ortho = { -v0.y, v0.x };

    ortho.x = -v0.y;
    ortho.y =  v0.x;

    return ortho;
}


////////////////////////////////////////////////////////////////////////////////
// v3f Operators


inline v3f V3(float x, float y, float z)
{
    v3f inst;

    // TODO: clang on macOS does not like this, porque?
    // inst = { x, y, z, w };

    inst.x = x;
    inst.y = y;
    inst.z = z;

    return inst;
}


inline v3f operator-(v3f rhs)
{
    v3f inverse;

    inverse.x = -rhs.x;
    inverse.y = -rhs.y;
    inverse.z = -rhs.z;

    return inverse;
}


inline v3f operator+(v3f lhs, v3f rhs)
{
    v3f sum;

    sum.x = lhs.x + rhs.x;
    sum.y = lhs.y + rhs.y;
    sum.z = lhs.z + rhs.z;

    return sum;
}


inline v3f& operator+=(v3f &lhs, v3f rhs)
{
    lhs = lhs + rhs;

    return lhs;
}


inline v3f operator-(v3f lhs, v3f rhs)
{
    v3f difference;

    difference.x = lhs.x - rhs.x;
    difference.y = lhs.y - rhs.y;
    difference.z = lhs.z - rhs.z;

    return difference;
}


inline v3f& operator-=(v3f &lhs, v3f rhs)
{
    lhs = lhs - rhs;

    return lhs;
}


inline v3f operator*(v3f lhs, float rhs)
{
    v3f product;

    product.x = lhs.x * rhs;
    product.y = lhs.y * rhs;
    product.z = lhs.z * rhs;

    return product;
}


inline v3f operator*(float lhs, v3f rhs)
{
    return rhs * lhs;
}


inline v3f& operator*=(v3f &lhs, float rhs)
{
    lhs = lhs * rhs;

    return lhs;
}


inline v3f operator/(v3f lhs, float rhs)
{
    v3f quotient;

    quotient.x = lhs.x / rhs;
    quotient.y = lhs.y / rhs;
    quotient.z = lhs.z / rhs;

    return quotient;
}


inline v3f& operator/=(v3f &lhs, float rhs)
{
    lhs = lhs / rhs;

    return lhs;
}


inline float dot(v3f lhs, v3f rhs)
{
    float scalar;

    scalar = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; // FMA?

    return scalar;
}


inline v3f cross(v3f top, v3f bot)
{
    v3f product;

    product.x = top.y * bot.z - top.z * bot.y;
    product.y = -(top.x * bot.z - top.z * bot.x);
    product.z = top.x * bot.y - top.y * bot.x;

    return product;
}


inline v3f lerp(v3f v0, v3f v1, float t)
{
    v3f approx;

    // NOTE:
    //      With fused multiply-add:
    //      approx = v0 + t * (v1 - v0)
    approx = (1.0f - t) * v0 + t * v1;

    return approx;
}


inline v3f normalize(v3f weird)
{
    v3f norm;

    float mag = sqrtf(dot(weird, weird));

    norm = weird / mag;

    return norm;
}


////////////////////////////////////////////////////////////////////////////////
// v4f Operators


inline v4f V4(float x, float y, float z, float w)
{
    v4f inst;

    // TODO: clang on macOS does not like this, porque?
    // inst = { x, y, z, w };

    inst.x = x;
    inst.y = y;
    inst.z = z;
    inst.w = w;

    return inst;
}


inline v4f operator-(v4f rhs)
{
    v4f inverse;

    inverse.x = -rhs.x;
    inverse.y = -rhs.y;
    inverse.z = -rhs.z;
    inverse.w = -rhs.w;

    return inverse;
}


inline v4f operator+(v4f lhs, v4f rhs)
{
    v4f sum;

    sum.x = lhs.x + rhs.x;
    sum.y = lhs.y + rhs.y;
    sum.z = lhs.z + rhs.z;
    sum.w = lhs.w + rhs.w;

    return sum;
}


inline v4f& operator+=(v4f &lhs, v4f rhs)
{
    lhs = lhs + rhs;

    return lhs;
}


inline v4f operator-(v4f lhs, v4f rhs)
{
    v4f difference;

    difference.x = lhs.x - rhs.x;
    difference.y = lhs.y - rhs.y;
    difference.z = lhs.z - rhs.z;
    difference.w = lhs.w - rhs.w;

    return difference;
}


inline v4f& operator-=(v4f &lhs, v4f rhs)
{
    lhs = lhs - rhs;

    return lhs;
}


inline v4f operator*(v4f lhs, float rhs)
{
    v4f product;

    product.x = lhs.x * rhs;
    product.y = lhs.y * rhs;
    product.z = lhs.z * rhs;
    product.w = lhs.w * rhs;

    return product;
}


inline v4f operator*(float lhs, v4f rhs)
{
    return rhs * lhs;
}


inline v4f& operator*=(v4f &lhs, float rhs)
{
    lhs = lhs * rhs;

    return lhs;
}


inline v4f operator/(v4f lhs, float rhs)
{
    v4f quotient;

    quotient.x = lhs.x / rhs;
    quotient.y = lhs.y / rhs;
    quotient.z = lhs.z / rhs;
    quotient.w = lhs.w / rhs;

    return quotient;
}


inline v4f& operator/=(v4f &lhs, float rhs)
{
    lhs = lhs / rhs;

    return lhs;
}


inline float dot(v4f lhs, v4f rhs)
{
    float scalar;

    scalar = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w + rhs.w; // FMA?

    return scalar;
}


inline v4f lerp(v4f v0, v4f v1, float t)
{
    v4f approx;

    // NOTE:
    //      With fused multiply-add:
    //      approx = v0 + t * (v1 - v0)
    approx = (1.0f - t) * v0 + t * v1;

    return approx;
}


#endif /* ENGINE_VECTOR_H */
