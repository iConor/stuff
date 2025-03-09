#include "engine_shapes.h"

#include "engine_math.h"
#include "engine_vector.h"



void generate_sphere(model_data* model, s32 sector_count, s32 stack_count, f32 radius)
{
    std::vector<mesh_vertex> vertices;
    std::vector<u32> indices;


    f32 stack_step = PI / stack_count;
    f32 sector_step = 2.0f * PI / sector_count;

    f32 len_inv = 1.0f / radius;

    for( int i = 0; i <= stack_count; i++)
    {
        f32 stack_angle = PI / 2.0f - i * stack_step;

        f32 xy = radius * cosf(stack_angle);
        f32 z  = radius * sinf(stack_angle);

        for(int j = 0; j <= sector_count; j++)
        {
            f32 sector_angle = j * sector_step;

            f32 x = xy * cosf(sector_angle);
            f32 y = xy * sinf(sector_angle);

            mesh_vertex vertex;

            v3f position;
            position.x = x;
            position.y = y;
            position.z = z;
            vertex.position = position;

            v3f normal;
            normal = position * len_inv;
            vertex.normal = normal;

            v2f texcoords;
            texcoords.x = (f32)j / sector_count;
            texcoords.y = (f32)i / stack_count;
            vertex.texcoords = texcoords;

            vertices.push_back(vertex);
        }
    }


    for(int i = 0; i < stack_count; i++)
    {
        s32 k1 = i * (sector_count + 1);
        s32 k2 = k1 + sector_count + 1;

        for(int j = 0; j < sector_count; j++)
        {
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if(i != (stack_count - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

            ++k1;
            ++k2;
        }
    }

    std::vector<mesh_texture> textures;
    model->meshes.push_back(init_mesh_data(vertices, indices, textures));
}



void generate_cylinder(model_data* model, s32 sector_count, f32 radius, f32 height)
{
//    generate_cone(model, sector_count, radius, radius, height);

//    s32 stack_count = 1;


    std::vector<mesh_vertex> vertices;
    std::vector<u32> indices;

    f32 sector_step = 2.0f * PI / sector_count;

    std::vector<f32> unit_vertices;
    for(int i = 0; i <= sector_count; i++)
    {
        f32 sector_angle = i * sector_step;

        f32 x = cosf(sector_angle);
        f32 y = sinf(sector_angle);

        unit_vertices.push_back(x);
        unit_vertices.push_back(y);
        unit_vertices.push_back(0);
    }

    for(int i = 0; i < 2; i++)
    {
        f32 h = -height / 2.0f  + i * height;
        f32 v = 1.0f - i;

        int k = 0;
        for(int j = 0; j <= sector_count; j++)
        {
            f32 ux = unit_vertices[k];
            f32 uy = unit_vertices[k+1];
            f32 uz = unit_vertices[k+2];

            mesh_vertex vertex;

            v3f position;
            position.x = ux * radius;
            position.y = uy * radius;
            position.z = h;
            vertex.position = position;

            v3f normal;
            normal.x = ux;
            normal.y = uy;
            normal.z = uz;
            vertex.normal = normal;

            v2f texcoords;
            texcoords.x = (f32)j / sector_count;
            texcoords.y = v;
            vertex.texcoords = texcoords;

            vertices.push_back(vertex);

            k += 3;
        }
    }

    int base_ctr_idx = (int)vertices.size();
    int top_ctr_idx = base_ctr_idx + sector_count + 1;

    for(int i = 0; i < 2; i++)
    {
        f32 h = -height / 2.0f + i * height;
        f32 n = -1.0f + 2.0f * i;

        mesh_vertex center_vertex;

        v3f position;
        position.x = 0.0f;
        position.y = 0.0f;
        position.z = h;
        center_vertex.position = position;

        v3f normal;
        normal.x = 0;
        normal.y = 0;
        normal.z = n;
        center_vertex.normal = normal;

        v2f texcoords;
        texcoords.x = 0.5f;
        texcoords.y = 0.5f;
        center_vertex.texcoords = texcoords;

        vertices.push_back(center_vertex);

        int k = 0;
        for(int j = 0; j < sector_count; j++)
        {
            f32 ux = unit_vertices[k];
            f32 uy = unit_vertices[k+1];

            mesh_vertex vertex;

            v3f position;
            position.x = ux * radius;
            position.y = uy * radius;
            position.z = h;
            vertex.position = position;

            v3f normal;
            normal.x = 0;
            normal.y = 0;
            normal.z = n;
            vertex.normal = normal;

            v2f texcoords;
            texcoords.x = ux * 0.5f + 0.5f;
            texcoords.y = uy * 0.5f + 0.5f;
            vertex.texcoords = texcoords;

            vertices.push_back(vertex);

            k += 3;
        }
    }


    int k1 = 0;
    int k2 = sector_count + 1;
    for(int i = 0; i < sector_count; i++)
    {
        indices.push_back(k1);
        indices.push_back(k1 + 1);
        indices.push_back(k2);

        indices.push_back(k2);
        indices.push_back(k1 + 1);
        indices.push_back(k2 + 1);

        ++k1;
        ++k2;
    }

    
    int k = base_ctr_idx + 1;
    for(int i = 0; i < sector_count; i++)
    {
        if(i < sector_count - 1)
        {
            indices.push_back(base_ctr_idx);
            indices.push_back(k + 1);
            indices.push_back(k);
        }
        else
        {
            indices.push_back(base_ctr_idx);
            indices.push_back(base_ctr_idx + 1);
            indices.push_back(k);
        }

        ++k;
    }

    k = top_ctr_idx + 1;
    for(int i = 0; i < sector_count; i++)
    {
        if(i < sector_count - 1)
        {
            indices.push_back(top_ctr_idx);
            indices.push_back(k);
            indices.push_back(k + 1);
        }
        else
        {
            indices.push_back(top_ctr_idx);
            indices.push_back(k);
            indices.push_back(top_ctr_idx + 1);
        }

        ++k;
    }

    std::vector<mesh_texture> textures;
    model->meshes.push_back(init_mesh_data(vertices, indices, textures));
}


//void generate_cone(model_data* model, s32 sector_count, f32 r1, f32 r2, f32 height)
//{
//}
