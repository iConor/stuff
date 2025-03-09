#include "engine_model.h"


void draw_model(model_data* model, GLuint shader)
{
    for(int i = 0; i < model->meshes.size(); i++)
    {
        draw_mesh(&model->meshes[i], shader);
    }
}
