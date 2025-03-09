#ifndef ENGINE_SHAPES_H
#define ENGINE_SHAPES_H


#include "engine_model.h"


void generate_sphere(model_data* model, s32 sector_count = 36, s32 stack_count = 18, f32 radius = 1.0f);

void generate_cylinder(model_data* model, s32 sector_count = 36, f32 radius = 1.0f, f32 height = 2.0f);
//void generate_cone(model_data* model, s32 sector_count, f32 r1, f32 r2, f32 height);

#endif /* ENGINE_SHAPES_H */
