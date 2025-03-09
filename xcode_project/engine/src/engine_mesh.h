#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H


#include "engine_types.h"

#include "glad/glad.h"

#include <vector>
#include <string>


struct mesh_vertex
{
    v3f position;
    v3f normal;
    v2f texcoords;
};


struct mesh_texture
{
    u32 id;
    std::string type;
    std::string path;
};


struct mesh_data
{
    std::vector<mesh_vertex> vertices;
    std::vector<u32> indices;
    std::vector<mesh_texture> textures;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};


mesh_data init_mesh_data(std::vector<mesh_vertex> vertices,
                         std::vector<u32> indices,
                         std::vector<mesh_texture> textures);

void init_mesh_render(mesh_data* data);

void draw_mesh(mesh_data* mesh, GLuint shader);


#endif /* ENGINE_MESH_H */
