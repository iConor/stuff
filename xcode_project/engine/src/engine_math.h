#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H


#include <math.h>


#define PI 3.14159265f


inline f32 radians(f32 deg)
{
    f32 rad;

    rad = deg * PI / 180.f;

    return rad;
}


inline f32 degrees(f32 rad)
{
    f32 deg;

    deg = rad * 180.f / PI;

    return deg;
}


#endif /* ENGINE_MATH_H */
