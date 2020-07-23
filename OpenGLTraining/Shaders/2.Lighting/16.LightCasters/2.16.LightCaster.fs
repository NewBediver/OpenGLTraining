#version 330 core

struct Material {
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
};

struct Light {
    vec3 Position;
    vec3 Direction;
    float CutOff;
    float OuterCutOff;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    
    float Constant;
    float Linear;
    float Quadratic;
};

in vec3 o_Normals;
in vec3 o_FragmentPosition;
in vec2 o_TexCoords;

uniform vec3 u_ViewPosition;

uniform Material u_Material;
uniform Light u_Light;

out vec4 o_Color;

void main()
{
    // Directional Light Vector
    //vec3 lightDir = normalize(-u_Light.Direction);

    // Point light (Attenuation)
    //float distance = length(u_Light.Position - o_FragmentPosition);
    //float attenuation = 1.0 / (u_Light.Constant + u_Light.Linear * distance + u_Light.Quadratic * (distance * distance));

    // Spotlight
    vec3 lightDir = normalize(u_Light.Position - o_FragmentPosition);
    float theta = dot(lightDir, normalize(-u_Light.Direction));
    float epsilon = u_Light.CutOff - u_Light.OuterCutOff;
    float intensity = clamp((theta - u_Light.OuterCutOff) / epsilon, 0.0, 1.0);

   // ambient
    vec3 ambient = u_Light.Ambient * vec3(texture(u_Material.Diffuse, o_TexCoords));

    // diffuse
    vec3 norm = normalize(o_Normals);
    //vec3 lightDir = normalize(u_Light.Position - o_FragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.Diffuse * (diff * vec3(texture(u_Material.Diffuse, o_TexCoords)));

    // specular
    vec3 viewDir = normalize(u_ViewPosition - o_FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
    vec3 specular = u_Light.Specular * (spec * vec3(texture(u_Material.Specular, o_TexCoords)));

    //ambient *= attenuation;
    //diffuse *= attenuation;
    //specular *= attenuation;
    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;
    o_Color = vec4(result, 1.0);
}