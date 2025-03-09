#version 330 core

out vec4 frag_color;

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texcoords;

//uniform sampler2D texture_diffuse0;
//uniform sampler2D texture_specular0;

void main()
{
    frag_color = vec4(1.0, 1.0, 1.0, 1.0);
}
