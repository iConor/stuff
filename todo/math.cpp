#define PI 3.14159265f


inline float radians(float deg)
{
    float rad;

    rad = deg * PI / 180.0f;

    return rad;
}


inline float degrees(float rad)
{
    float deg;

    deg = rad * 180.0f / PI;

    return deg;
}
