#include "assimp_model.h"

#include "engine_texture.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


void process_assimp_node(model_data* model, aiNode* node, const aiScene* scene);
mesh_data process_assimp_mesh(model_data* model, aiMesh* mesh, const aiScene* scene);
std::vector<mesh_texture> load_material_textures(model_data* model, aiMaterial* mat, aiTextureType type, std::string type_name);


void load_model(model_data* model, std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR: assimp model_load:" << import.GetErrorString() << std::endl;
        return;
    }
    model->directory = path.substr(0, path.find_last_of('/'));

    process_assimp_node(model, scene->mRootNode, scene);
}


void process_assimp_node(model_data* model, aiNode* node, const aiScene* scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        model->meshes.push_back(process_assimp_mesh(model, mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_assimp_node(model, node->mChildren[i], scene);
    }
}


mesh_data process_assimp_mesh(model_data* model, aiMesh* mesh, const aiScene* scene)
{
    std::vector<mesh_vertex> vertices;
    std::vector<u32> indices;
    std::vector<mesh_texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        mesh_vertex vertex;

        v3f position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        vertex.position = position;

        v3f normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
        vertex.normal = normal;

        v2f texcoord;
        if(mesh->mTextureCoords[0])
        {
            texcoord.x = mesh->mTextureCoords[0][i].x;
            texcoord.y = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            texcoord.x = 0.0f;
            texcoord.y = 0.0f;
        }
        vertex.texcoords = texcoord;

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);

            if(j > 2)
            {
                std::cout << j << std::endl;
            }
        }
    }

    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<mesh_texture> diffuse_maps = load_material_textures(model, material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

        std::vector<mesh_texture> specular_maps = load_material_textures(model, material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
    }

    return init_mesh_data(vertices, indices, textures);
}


std::vector<mesh_texture> load_material_textures(model_data* model, aiMaterial* mat, aiTextureType type, std::string type_name)
{
    std::vector<mesh_texture> textures;

    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;

        for(unsigned int j = 0; j < model->textures.size(); j++)
        {
            if(std::strcmp(model->textures[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(model->textures[j]);
                skip = true;
                break;
            }
        }

        if(!skip)
        {
            mesh_texture texture;
            texture.id = texture_from_file(model->directory, str.C_Str());
            texture.type = type_name;
            texture.path = str.C_Str();

            textures.push_back(texture);
            model->textures.push_back(texture);
        }

    }
    return textures;
}


