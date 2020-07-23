#version 330 core

uniform vec3 u_LightColor;

out vec4 o_Color;

void main()
{
    o_Color = vec4(u_LightColor, 1.0);
}