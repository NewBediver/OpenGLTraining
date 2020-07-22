#version 330 core

struct Material {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

struct Light {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    vec3 Position;
};

in vec3 o_Normals;
in vec3 o_FragmentPosition;

uniform vec3 u_ViewPosition;

uniform Material u_Material;
uniform Light u_Light;

out vec4 o_Color;

void main()
{
    // ambient
    vec3 ambient = u_Light.Ambient * u_Material.Ambient;

    // diffuse
    vec3 norm = normalize(o_Normals);
    vec3 lightDir = normalize(u_Light.Position - o_FragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.Diffuse * (diff * u_Material.Diffuse);
    
    // specular
    vec3 viewDir = normalize(u_ViewPosition - o_FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
    vec3 specular = u_Light.Specular * (spec * u_Material.Specular);

    vec3 result = ambient + diffuse + specular;
    o_Color = vec4(result, 1.0);
}