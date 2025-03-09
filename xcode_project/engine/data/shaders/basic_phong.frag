#version 330 core

out vec4 frag_color;

in vec3 frag_position;
in vec3 frag_normal;

uniform vec3 light_position;
uniform vec3 view_position;
uniform vec3 light_color;
uniform vec3 base_color;



void main()
{
    float k_A = 0.1;
    vec3 ambient = k_A * light_color;

    vec3 normal = normalize(frag_normal);
    vec3 light_direction = normalize(light_position - frag_position);
    float m_D = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = m_D * light_color;

    float k_S = 0.5;
    vec3 view_direction = normalize(view_position - frag_position);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float m_S = pow(max(dot(view_direction, reflection_direction), 0.0), 32);
    vec3 specular = m_S * k_S * light_color;

    vec3 light = ambient + diffuse + specular;
    vec3 color = light * base_color;
    frag_color = vec4(color, 1.0);
}

