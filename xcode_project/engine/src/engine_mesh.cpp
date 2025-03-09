#include "engine_mesh.h"


#include "opengl_shader.h"


#include <string>


mesh_data init_mesh_data(std::vector<mesh_vertex> vertices, std::vector<u32> indices, std::vector<mesh_texture> textures)
{
    mesh_data mesh;

    mesh.vertices = vertices;
    mesh.indices  = indices;
    mesh.textures = textures;

    init_mesh_render(&mesh);

    return mesh;
}


void init_mesh_render(mesh_data* mesh)
{
    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);

    glGenBuffers(1, &mesh->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(mesh_vertex),
                 &mesh->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &mesh->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(u32),
                 &mesh->indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex), (void*)offsetof(mesh_vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex), (void*)offsetof(mesh_vertex, texcoords));
    glEnableVertexAttribArray(2);
}


void draw_mesh(mesh_data* mesh, GLuint shader)
{
    u32 diffuse_num = 0;
    u32 specular_num = 0;

    for(int i = 0; i < mesh->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = mesh->textures[i].type;

        if(name == "texture_diffuse")
        {
            number = std::to_string(diffuse_num++);
        }
        else if(name == "texture_specular")
        {
            number = std::to_string(specular_num++);
        }

//        opengl_uniform_f32(shader, ("material." + name + number).c_str(), (f32)i);
        opengl_uniform_s32(shader, (name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
    }
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)mesh->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

//    glActiveTexture(GL_TEXTURE0);
}
