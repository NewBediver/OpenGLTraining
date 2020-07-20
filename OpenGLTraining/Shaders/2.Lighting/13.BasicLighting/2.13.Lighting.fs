#version 330 core

in vec3 o_Normals;
in vec3 o_FragmentPosition;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_ViewPosition;

out vec4 o_Color;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_LightColor;

    vec3 norm = normalize(o_Normals);
    vec3 lightDir = normalize(u_LightPosition - o_FragmentPosition);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPosition - o_FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColor;

    vec3 result = (ambient + diffuse + specular) * u_ObjectColor;
    o_Color = vec4(result, 1.0);
}