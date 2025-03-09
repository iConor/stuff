#version 330 core

out vec4 frag_color;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

struct d_Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
};

struct p_Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 position;

    float constant;
    float linear;
    float quadratic;
};

struct s_Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 position;
    vec3 direction;

    float constant;
    float linear;
    float quadratic;

    float inner;
    float outer;
};

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texcoords;

#define NR_P_LIGHTS 4
#define NR_S_LIGHTS 4

uniform Material material;
uniform d_Light d_light;
uniform p_Light p_light[NR_P_LIGHTS];
uniform s_Light s_light[NR_S_LIGHTS];

uniform vec3 view_position;


vec3 calc_d_light(d_Light light, vec3 normal, vec3 view_dir);
vec3 calc_p_light(p_Light light, vec3 normal, vec3 view_dir, vec3 frag_pos);
vec3 calc_s_light(s_Light light, vec3 normal, vec3 view_dir, vec3 frag_pos);


void main()
{
    vec3 normal = normalize(frag_normal);
    vec3 view_dir = normalize(view_position - frag_position);

    vec3 result = vec3(0.0);

    result += calc_d_light(d_light, normal, view_dir);
    result += calc_p_light(p_light[0], normal, view_dir, frag_position);
    result += calc_s_light(s_light[0], normal, view_dir, frag_position);

    frag_color = vec4(result, 1.0);
}


vec3 calc_d_light(d_Light light, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(-light.direction);

    float k_D = max(dot(normal, light_dir), 0.0);
    vec3 color_diffuse = vec3(texture(material.diffuse, frag_texcoords));

    vec3 reflect_dir = reflect(-light_dir, normal);
    float k_S = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 color_specular = vec3(texture(material.specular, frag_texcoords));

    vec3 ambient = light.ambient * color_diffuse;
    vec3 diffuse = light.diffuse * color_diffuse;
    vec3 specular = light.specular * color_specular;

    return (ambient + k_D * diffuse + k_S * specular);
}


vec3 calc_p_light(p_Light light, vec3 normal, vec3 view_dir, vec3 frag_pos)
{
    vec3 light_dir = normalize(light.position - frag_pos);

    float k_D = max(dot(normal, light_dir), 0.0);
    vec3 color_diffuse = vec3(texture(material.diffuse, frag_texcoords));

    vec3 reflect_dir = reflect(-light_dir, normal);
    float k_S = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 color_specular = vec3(texture(material.specular, frag_texcoords));

    float dist = length(light.position - frag_pos);
    float atten = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    vec3 ambient = atten * light.ambient * color_diffuse;
    vec3 diffuse = atten * light.diffuse * color_diffuse;
    vec3 specular = atten * light.specular * color_specular;

    return (ambient + k_D * diffuse + k_S * specular);
}


vec3 calc_s_light(s_Light light, vec3 normal, vec3 view_dir, vec3 frag_pos)
{
    vec3 light_dir = normalize(light.position - frag_pos);

    float k_D = max(dot(normal, light_dir), 0.0);
    vec3 color_diffuse = vec3(texture(material.diffuse, frag_texcoords));

    vec3 reflect_dir = reflect(-light_dir, normal);
    float k_S = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 color_specular = vec3(texture(material.specular, frag_texcoords));

    float dist = length(light.position - frag_pos);
    float atten = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    float theta = dot(light_dir, normalize(-light.direction));
    float epsilon = light.inner - light.outer;
    float intensity = clamp((theta - light.outer) / epsilon, 0.0, 1.0);

    vec3 ambient = intensity * atten * light.ambient * color_diffuse;
    vec3 diffuse = intensity * atten * light.diffuse * color_diffuse;
    vec3 specular = intensity * atten * light.specular * color_specular;

    return (ambient + k_D * diffuse + k_S * specular);
}
