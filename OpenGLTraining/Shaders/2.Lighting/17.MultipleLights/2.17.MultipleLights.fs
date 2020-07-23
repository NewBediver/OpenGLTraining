#version 330 core

struct Material {
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
};

struct DirectionalLight {
    vec3 Direction;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct PointLight {
    vec3 Position;

    float Constant;
    float Linear;
    float Quadratic;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct SpotLight {
    vec3 Position;
    vec3 Direction;

    float CutOff;
    float OuterCutOff;

    float Constant;
    float Linear;
    float Quadratic;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

in vec3 o_Normals;
in vec3 o_FragmentPosition;
in vec2 o_TexCoords;

uniform vec3 u_ViewPosition;

uniform Material u_Material;

uniform DirectionalLight u_DirectionalLight;
#define NR_POINT_LIGHTS 4
uniform PointLight u_PointLights[NR_POINT_LIGHTS];
uniform SpotLight u_SpotLight;

out vec4 o_Color;

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // Properties
    vec3 norm = normalize(o_Normals);
    vec3 viewDir = normalize(u_ViewPosition - o_FragmentPosition);
    
    // Phase 1: Directional lighting
    vec3 result = CalcDirLight(u_DirectionalLight, norm, viewDir);

    // Phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; ++i)
        result += CalcPointLight(u_PointLights[i], norm, o_FragmentPosition, viewDir);

    // Phase 3: Spot light
    result += CalcSpotLight(u_SpotLight, norm, o_FragmentPosition, viewDir);

    o_Color = vec4(result, 1.0);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    // Directional Light Vector
    vec3 lightDir = normalize(-light.Direction);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);

    // Combine results
    vec3 ambient = light.Ambient * vec3(texture(u_Material.Diffuse, o_TexCoords));
    vec3 diffuse = light.Diffuse * diff * vec3(texture(u_Material.Diffuse, o_TexCoords));
    vec3 specular = light.Specular * spec * vec3(texture(u_Material.Specular, o_TexCoords));

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Position - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);

    // Attenuation
    float distance = length(light.Position - fragPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

    // Combine results
    vec3 ambient = light.Ambient * vec3(texture(u_Material.Diffuse, o_TexCoords));
    vec3 diffuse = light.Diffuse * diff * vec3(texture(u_Material.Diffuse, o_TexCoords));
    vec3 specular = light.Specular * spec * vec3(texture(u_Material.Specular, o_TexCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Position - fragPos);
    
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
    
    // Attenuation
    float distance = length(light.Position - fragPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));
    
    float theta = dot(lightDir, normalize(-light.Direction));
    float epsilon = light.CutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);

    // Combine results
    vec3 ambient = light.Ambient * vec3(texture(u_Material.Diffuse, o_TexCoords));
    vec3 diffuse = light.Diffuse * diff * vec3(texture(u_Material.Diffuse, o_TexCoords));
    vec3 specular = light.Specular * spec * vec3(texture(u_Material.Specular, o_TexCoords));
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    diffuse *= intensity;
    specular *= intensity;

    return (ambient + diffuse + specular);
}