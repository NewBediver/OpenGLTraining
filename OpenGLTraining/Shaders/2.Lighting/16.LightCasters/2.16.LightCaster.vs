#version 330 core

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec3 i_Normals;
layout (location = 2) in vec2 i_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 o_Normals;
out vec3 o_FragmentPosition;
out vec2 o_TexCoords;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(i_Position, 1.0);
	o_FragmentPosition = vec3(u_Model * vec4(i_Position, 1.0));
	o_Normals = mat3(transpose(inverse(u_Model))) * i_Normals;
	o_TexCoords = i_TexCoords;
}