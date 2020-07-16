#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TextureCoord;

out vec3 ourColor;
out vec2 TextureCoord;

void main()
{
	gl_Position = vec4(a_Pos, 1.0);
	ourColor = a_Color;
	TextureCoord = a_TextureCoord;
}