#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TextureCoord;

uniform float visibility;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TextureCoord),
                    texture(texture2, TextureCoord),
                    visibility);
}