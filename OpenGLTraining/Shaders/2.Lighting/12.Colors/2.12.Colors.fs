#version 330 core

out vec4 a_Color;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

void main()
{
    a_Color = vec4(u_LightColor * u_ObjectColor, 1.0);
}