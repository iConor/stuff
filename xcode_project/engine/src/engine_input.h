#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H


#include "engine_types.h"


typedef struct
{
    f32 left_x;
    f32 left_y;

    f32 right_x;
    f32 right_y;

    f32 left_trigger;
    f32 right_trigger;
    
    u8 up;
    u8 down;
    u8 left;
    u8 right;

    u8 a;
    u8 b;
    u8 x;
    u8 y;
	
    u8 left_stick;
    u8 right_stick;

    u8 left_shoulder;
    u8 right_shoulder;

    u8 back;
    u8 guide;
    u8 start;
    
} gamepad_state;


#endif /* ENGINE_INPUT_H */
