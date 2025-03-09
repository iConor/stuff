#ifndef ENG_TYPES_H
#define ENG_TYPES_H


#include <stdint.h>


typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float    f32;
typedef double   f64;


union v2f
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


union v3f
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


union v4f
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


union m3f
{
    float m[3][3];
    float e[9];
};


union m4f
{
    float m[4][4];
    float e[16];
};


#endif /* ENG_TYPES_H */
