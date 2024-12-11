#version 330 core
out vec4 FragColor;

in vec2 vertexTextureCoordinate;

uniform sampler2D textureSampler1;
uniform sampler2D textureSampler2;

void main() {
    FragColor = mix(
        texture(textureSampler1, vertexTextureCoordinate),
        texture(textureSampler2, vertexTextureCoordinate),
        0.2
    );
}