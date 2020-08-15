#version 420 core

out vec4 FragColor;
layout (depth_greater) out float gl_FragDepth;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoords);
    gl_FragDepth = gl_FragCoord.z + 0.1;
}