#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "utils.h"
#include "shader.h"
#include "shader_program.h"
#include "glfw_handler.h"
#include "texture.h"


void processInput(GLFWwindow* window) {
    auto keyStatus = glfwGetKey(window, GLFW_KEY_ESCAPE);
    
    if (keyStatus == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


void loadGLAD() {
    auto success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!success) {
        abortProgram("Failed to initialize GLAD");
    }
}


int main() {
    auto glfw = GLFWHandler();
    auto window = glfw.createWindow();
    glfw.setCurrent(window.get());

    // TODO: explore further
    loadGLAD();

    glViewport(0, 0, 800, 600);


    float vertices[] { 
        0.5f,  0.5f, 0.0f,  1, 0, 0,  1, 1, // top right
        0.5f, -0.5f, 0.0f,  0, 1, 0,  1, 0, // bottom right
        -0.5f, -0.5f, 0.0f,  0, 0, 1,  0, 0, // bottom left
        -0.5f,  0.5f, 0.0f,   0.5, 0.5, 0.5,  0, 1 // top left
    };
    unsigned int indices[] {
        0, 1, 3,  // first triangle
        1, 2, 3, // second triangle
    };
    
    Shader vertexShader{ "shaders/shader.vert", GL_VERTEX_SHADER };
    Shader fragmentShader { "shaders/shader.frag", GL_FRAGMENT_SHADER };
    std::vector shaders { vertexShader, fragmentShader };
    
    ShaderProgram shaderProgram { shaders };

    Texture wallTexture { "resources/wall.jpg" };
    Texture faceTexture { "resources/awesomeface.png" };

    unsigned int vertexBufferID, vertexArrayID, elementBufferID;
    glGenVertexArrays(1, &vertexArrayID);
    glGenBuffers(1, &vertexBufferID);
    glGenBuffers(1, &elementBufferID);

    glBindVertexArray(vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*) (3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6*sizeof(float))
    );
    glEnableVertexAttribArray(2);

    shaderProgram.use();
    shaderProgram.setUniform("textureSampler1", 0);
    shaderProgram.setUniform("textureSampler2", 1);

    glm::mat4 identity { 1 };
    auto modelMatrix = glm::rotate(
        identity,
        glm::radians(-55.0f),
        glm::vec3{ 1, 0, 0 }
    );
    auto viewMatrix = glm::translate(identity, glm::vec3{ 0, 0, -3 });
    auto projectionMatrix = glm::perspective(
        glm::radians(45.0f), static_cast<float>(800 / 600), 0.1f, 100.0f
    );

    while (!glfwWindowShouldClose(window.get())) {
        glfwSwapBuffers(window.get());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.setUniform("modelMatrix", modelMatrix);
        shaderProgram.setUniform("viewMatrix", viewMatrix);
        shaderProgram.setUniform("projectionMatrix", projectionMatrix);
        
        wallTexture.use(GL_TEXTURE0);
        faceTexture.use(GL_TEXTURE1);

        glBindVertexArray(vertexArrayID);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
     
        glfwPollEvents();
        processInput(window.get());
    }

    return 0;
}