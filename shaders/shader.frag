#version 330 core
out vec4 FragColor;

in vec3 vertexColor;

uniform vec4 globalColor;

void main() {
    // FragColor = globalColor;
    FragColor = vec4(vertexColor, 1.0);
}