#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H


#include "engine_mesh.h"


struct model_data
{
    std::vector<mesh_texture> textures;
    std::vector<mesh_data> meshes;
    std::string directory;
};


void draw_model(model_data* model, GLuint shader);


#endif /* ENGINE_MODEL_H */
