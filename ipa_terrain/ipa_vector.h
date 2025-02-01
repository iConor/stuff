#ifndef IPA_VECTOR_H
#define IPA_VECTOR_H


union v2
{
    struct
    {
        float x;
        float y;
    };
    struct
    {
        float u;
        float v;
    };
    float e[2];
};


union v3
{
    struct
    {
        float x;
        float y;
        float z;
    };
    struct
    {
        float r;
        float g;
        float b;
    };
    struct
    {
        float h;
        float s;
        float v;
    };
    float e[3];
};

union v4
{
    struct
    {
        float x;
        float y;
        float z;
        float w;
    };
    struct
    {
        float r;
        float g;
        float b;
        float a;
    };
    float e[4];
};


////////////////////////////////////////////////////////////////////////////////
// v2 Operators


inline v2 V2(float x, float y)
{
    v2 inst;

    // TODO: clang on macOS does not like this, porque?
    // inst = { x, y };

    inst.x = x;
    inst.y = y;

    return inst;
}

inline v2 operator-(v2 rhs)
{
    v2 inverse;

    inverse.x = -rhs.x;
    inverse.y = -rhs.y;

    return inverse;
}


inline v2 operator+(v2 lhs, v2 rhs)
{
    v2 sum;

    sum.x = lhs.x + rhs.x;
    sum.y = lhs.y + rhs.y;

    return sum;
}


inline v2& operator+=(v2 &lhs, v2 rhs)
{
    lhs = lhs + rhs;

    return lhs;
}


inline v2 operator-(v2 lhs, v2 rhs)
{
    v2 difference;

    difference.x = lhs.x - rhs.x;
    difference.y = lhs.y - rhs.y;

    return difference;
}


inline v2& operator-=(v2 &lhs, v2 rhs)
{
    lhs = lhs - rhs;

    return lhs;
}


inline v2 operator*(v2 lhs, float rhs)
{
    v2 product;

    product.x = lhs.x * rhs;
    product.y = lhs.y * rhs;

    return product;
}


inline v2 operator*(float lhs, v2 rhs)
{
    return rhs * lhs;
}


inline v2& operator*=(v2 &lhs, float rhs)
{
    lhs = lhs * rhs;
    return lhs;
}


inline v2 operator/(v2 lhs, float rhs)
{
    v2 quotient;

    quotient.x = lhs.x / rhs;
    quotient.y = lhs.y / rhs;

    return quotient;
}


inline v2& operator/=(v2 &lhs, float rhs)
{
    lhs = lhs / rhs;
    return lhs;
}


inline float dot(v2 lhs, v2 rhs)
{
    float scalar;

    scalar = lhs.x * rhs.x + lhs.y * rhs.y; // FMA?

    return scalar;
}


inline v2 lerp(v2 v0, v2 v1, float t)
{
    v2 approx;

    // NOTE:
    //      With fused multiply-add:
    //      approx = v0 + t * (v1 - v0)
    approx = (1.0f - t) * v0 + t * v1;

    return approx;
}


inline v2 perp(v2 v0)
{
    v2 ortho;

    // TODO: clang on macOS does not like this, porque?
    // ortho = { -v0.y, v0.x };

    ortho.x = -v0.y;
    ortho.y =  v0.x;

    return ortho;
}


////////////////////////////////////////////////////////////////////////////////
// v3 Operators


inline v3 V3(float x, float y, float z)
{
    v3 inst;

    // TODO: clang on macOS does not like this, porque?
    // inst = { x, y, z, w };

    inst.x = x;
    inst.y = y;
    inst.z = z;

    return inst;
}


inline v3 operator-(v3 rhs)
{
    v3 inverse;

    inverse.x = -rhs.x;
    inverse.y = -rhs.y;
    inverse.z = -rhs.z;

    return inverse;
}


inline v3 operator+(v3 lhs, v3 rhs)
{
    v3 sum;

    sum.x = lhs.x + rhs.x;
    sum.y = lhs.y + rhs.y;
    sum.z = lhs.z + rhs.z;

    return sum;
}


inline v3& operator+=(v3 &lhs, v3 rhs)
{
    lhs = lhs + rhs;

    return lhs;
}


inline v3 operator-(v3 lhs, v3 rhs)
{
    v3 difference;

    difference.x = lhs.x - rhs.x;
    difference.y = lhs.y - rhs.y;
    difference.z = lhs.z - rhs.z;

    return difference;
}


inline v3& operator-=(v3 &lhs, v3 rhs)
{
    lhs = lhs - rhs;

    return lhs;
}


inline v3 operator*(v3 lhs, float rhs)
{
    v3 product;

    product.x = lhs.x * rhs;
    product.y = lhs.y * rhs;
    product.z = lhs.z * rhs;

    return product;
}


inline v3 operator*(float lhs, v3 rhs)
{
    return rhs * lhs;
}


inline v3& operator*=(v3 &lhs, float rhs)
{
    lhs = lhs * rhs;
    return lhs;
}


inline v3 operator/(v3 lhs, float rhs)
{
    v3 quotient;

    quotient.x = lhs.x / rhs;
    quotient.y = lhs.y / rhs;
    quotient.z = lhs.z / rhs;

    return quotient;
}


inline v3& operator/=(v3 &lhs, float rhs)
{
    lhs = lhs / rhs;
    return lhs;
}


inline float dot(v3 lhs, v3 rhs)
{
    float scalar;

    scalar = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; // FMA?

    return scalar;
}


inline v3 cross(v3 top, v3 bot)
{
    v3 product;

    product.x = top.y * bot.z - top.z * bot.y;
    product.y = top.x * bot.z - top.z * bot.x;
    product.z = top.x * bot.y - top.y * bot.x;

    return product;
}


inline v3 lerp(v3 v0, v3 v1, float t)
{
    v3 approx;

    // NOTE:
    //      With fused multiply-add:
    //      approx = v0 + t * (v1 - v0)
    approx = (1.0f - t) * v0 + t * v1;

    return approx;
}


inline v3 normalize(v3 weird)
{
    v3 norm;

    float mag = sqrtf(dot(weird, weird));

    norm = weird / mag;

    return norm;
}

////////////////////////////////////////////////////////////////////////////////
// v4 Operators


inline v4 V4(float x, float y, float z, float w)
{
    v4 inst;

    // TODO: clang on macOS does not like this, porque?
    // inst = { x, y, z, w };

    inst.x = x;
    inst.y = y;
    inst.z = z;
    inst.w = w;

    return inst;
}


inline v4 operator-(v4 rhs)
{
    v4 inverse;

    inverse.x = -rhs.x;
    inverse.y = -rhs.y;
    inverse.z = -rhs.z;
    inverse.w = -rhs.w;

    return inverse;
}


inline v4 operator+(v4 lhs, v4 rhs)
{
    v4 sum;

    sum.x = lhs.x + rhs.x;
    sum.y = lhs.y + rhs.y;
    sum.z = lhs.z + rhs.z;
    sum.w = lhs.w + rhs.w;

    return sum;
}


inline v4& operator+=(v4 &lhs, v4 rhs)
{
    lhs = lhs + rhs;

    return lhs;
}


inline v4 operator-(v4 lhs, v4 rhs)
{
    v4 difference;

    difference.x = lhs.x - rhs.x;
    difference.y = lhs.y - rhs.y;
    difference.z = lhs.z - rhs.z;
    difference.w = lhs.w - rhs.w;

    return difference;
}


inline v4& operator-=(v4 &lhs, v4 rhs)
{
    lhs = lhs - rhs;

    return lhs;
}


inline v4 operator*(v4 lhs, float rhs)
{
    v4 product;

    product.x = lhs.x * rhs;
    product.y = lhs.y * rhs;
    product.z = lhs.z * rhs;
    product.w = lhs.w * rhs;

    return product;
}


inline v4 operator*(float lhs, v4 rhs)
{
    return rhs * lhs;
}


inline v4& operator*=(v4 &lhs, float rhs)
{
    lhs = lhs * rhs;
    return lhs;
}


inline v4 operator/(v4 lhs, float rhs)
{
    v4 quotient;

    quotient.x = lhs.x / rhs;
    quotient.y = lhs.y / rhs;
    quotient.z = lhs.z / rhs;
    quotient.w = lhs.w / rhs;

    return quotient;
}


inline v4& operator/=(v4 &lhs, float rhs)
{
    lhs = lhs / rhs;
    return lhs;
}


inline float dot(v4 lhs, v4 rhs)
{
    float scalar;

    scalar = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w + rhs.w; // FMA?

    return scalar;
}


inline v4 lerp(v4 v0, v4 v1, float t)
{
    v4 approx;

    // NOTE:
    //      With fused multiply-add:
    //      approx = v0 + t * (v1 - v0)
    approx = (1.0f - t) * v0 + t * v1;

    return approx;
}


#endif /* IPA_VECTOR_H */
