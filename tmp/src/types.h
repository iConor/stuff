#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>



typedef int8_t      s8;
typedef int16_t     s16;
typedef int32_t     s32;
typedef int64_t     s64;

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef float       f32;
typedef double      f64;



struct str8
{
    u8* data;
    u64 size;
};



struct str32
{
    u32* data;
    u64  size;
};



union v2f
{
    struct 
    {
        f32 x;
        f32 y;
    };
    struct
    {
        f32 u;
        f32 v;
    };
    f32 e[2];
};

union v3f
{
    struct 
    {
        f32 x;
        f32 y;
        f32 z;
    };
    struct
    {
        f32 r;
        f32 g;
        f32 b;
    };
    f32 e[3];
};

union v4f
{
    struct 
    {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    struct
    {
        f32 r;
        f32 g;
        f32 b;
        f32 a;
    };
    f32 e[4];
};



union v2s
{
    struct 
    {
        s32 x;
        s32 y;
    };
    s32 e[2];
};

union v3s
{
    struct 
    {
        s32 x;
        s32 y;
        s32 z;
    };
    s32 e[3];
};

union v4s
{
    struct 
    {
        s32 x;
        s32 y;
        s32 z;
        s32 w;
    };
    s32 e[4];
};



#endif /* TYPES_H */