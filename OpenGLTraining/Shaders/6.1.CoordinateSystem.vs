#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TextureCoord;

void main()
{
	gl_Position = projection * view * model * vec4(a_Pos, 1.0);
	TextureCoord = a_TextureCoord;
}