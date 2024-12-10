#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoordinate;

out vec3 vertexColor;
out vec2 vertexTextureCoordinate;

uniform mat4 transformation;

void main() {
    gl_Position = transformation * vec4(position.xyz, 1.0);
    vertexColor = color;
    vertexTextureCoordinate = textureCoordinate;
}