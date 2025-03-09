#version 330 core

out vec4 frag_color;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 position;
};

in vec3 frag_position;
in vec3 frag_normal;

uniform Material material;
uniform Light light;
uniform vec3 view_position;

void main()
{
    vec3 ambient = material.ambient * light.ambient;

    vec3 normal = normalize(frag_normal);
    vec3 light_direction = normalize(light.position - frag_position);
    float k_D = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = (k_D * material.diffuse) * light.diffuse;

    vec3 view_direction = normalize(view_position - frag_position);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float k_S = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
    vec3 specular = (k_S * material.specular) * light.specular;

    vec3 color = ambient + diffuse + specular;
    frag_color = vec4(color, 1.0);
}

