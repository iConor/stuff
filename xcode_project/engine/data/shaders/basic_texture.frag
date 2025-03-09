#version 330 core

out vec4 frag_color;

in vec2 texcoord;

uniform sampler2D tex_sampler;

void main()
{
    frag_color = texture(tex_sampler, texcoord);
}
