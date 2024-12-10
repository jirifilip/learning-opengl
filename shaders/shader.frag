#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 vertexTextureCoordinate;

uniform vec4 globalColor;
uniform sampler2D textureSampler1;
uniform sampler2D textureSampler2;

void main() {
    // FragColor = globalColor;
    FragColor = mix(
        texture(textureSampler1, vertexTextureCoordinate),
        texture(textureSampler2, vertexTextureCoordinate),
        0.2
    );
}