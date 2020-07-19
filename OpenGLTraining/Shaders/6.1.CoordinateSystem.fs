#version 330 core

out vec4 FragColor;

in vec2 TextureCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TextureCoord),
                    texture(texture2, TextureCoord),
                    0.2);
}