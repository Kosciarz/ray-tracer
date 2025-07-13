#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D raytracedTexture;

void main()
{
    FragColor = texture(raytracedTexture, TexCoord);
}
