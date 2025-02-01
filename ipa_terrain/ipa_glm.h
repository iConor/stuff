#ifndef IPA_GLM_H
#define IPA_GLM_H

#include <glm/gtc/matrix_transform.hpp>

#include "ipa_math.h"
#include "ipa_matrix.h"

static glm::mat4 perspective(bool use_glm, float fovy, float aspect, float near, float far)
{
    glm::mat4 perspective = glm::mat4(1.0f);

    if(use_glm)
    {
        perspective = glm::perspective(fovy, aspect, near, far);
    }
    else
    {
        float focal_length = tanf(deg2rad(fovy / 2.0f));
        float m00 = focal_length;
        float m11 = focal_length * aspect;
        float m22 = (far + near) / (near - far);
        float m23 = 2.0f * far * near / (near - far);
        m4 projection_matrix =
        {
             m00, 0.0f,  0.0f,  0.0f,
            0.0f,  m11,  0.0f,  0.0f,
            0.0f, 0.0f,  m22,    m23,
            0.0f, 0.0f, -1.0f,  0.0f,
        };
    }

    return perspective;
}


static glm::mat4 camera(bool use_glm, float translate, float pitch, float yaw)
{
    glm::mat4 view_matrix = glm::mat4(1.0f);

    if(use_glm)
    {
        view_matrix = glm::mat4(1.0f);
        view_matrix = glm::translate(view_matrix, glm::vec3(0.0f, 0.0f, -translate));
        view_matrix = glm::rotate(view_matrix, pitch, glm::vec3(-1.0f, 0.0f, 0.0f));
        view_matrix = glm::rotate(view_matrix, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else
    {
        // float cx = cosf(pitch);
        // float sx = sinf(pitch);
        // float cy = cosf(yaw);
        // float sy = sinf(yaw);
        //
        // m4 rotation_matrix =
        // {
        //        cy, sx*sy, cx*sy, 0.0f,
        //      0.0f,    cx,   -sx, 0.0f,
        //       -sy, sx*cy, cx*cy, 0.0f,
        //      0.0f,  0.0f,  0.0f, 1.0f,
        // };
        //
        // v4 facing = rotation_matrix * pos;
        //
        // v3 eye = V3(facing.x, facing.y, facing.z);
        // v3 center = V3(0.0f, 0.0f, 0.0f);
        // v3 up = V3(0, 1, 0);
        //
        // v3 f = normalize(center - eye);
        // v3 s = normalize(cross(up, f));
        // v3 u = cross(f, s);

        // m4 view_matrix =
        // {
        //      s.x,  u.x, -f.x, -dot(s, eye),
        //      s.y,  u.y, -f.y, -dot(u, eye),
        //      s.z,  u.z, -f.z,  dot(f, eye),
        //     0.0f, 0.0f,  0.0f,  1.0f,
        // };

        // m4 view_matrix =
        // {
        //     1.0f, 0.0f,  0.0f,  0.0f,
        //     0.0f, 1.0f,  0.0f,  0.0f,
        //     0.0f, 0.0f,  1.0f,  0.0f,
        //     0.0f, 0.0f,  0.0f,  1.0f,
        // };
    }
    return view_matrix;
}


#endif
