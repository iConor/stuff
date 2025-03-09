#version 330 core

out vec4 frag_color;

in vec2 texture_coordinates;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;

void main()
{
    frag_color = texture(texture_diffuse0, texture_coordinates);
}
