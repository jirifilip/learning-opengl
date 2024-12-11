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
    glEnable(GL_DEPTH_TEST);

    float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    Shader vertexShader{ "shaders/shader.vert", GL_VERTEX_SHADER };
    Shader fragmentShader { "shaders/shader.frag", GL_FRAGMENT_SHADER };
    std::vector shaders { vertexShader, fragmentShader };
    
    ShaderProgram shaderProgram { shaders };

    Texture wallTexture { "resources/wall.jpg" };
    Texture faceTexture { "resources/awesomeface.png" };

    unsigned int vertexBufferID, vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glGenBuffers(1, &vertexBufferID);

    glBindVertexArray(vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(cubeVertices),
        cubeVertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    shaderProgram.use();
    shaderProgram.setUniform("textureSampler1", 0);
    shaderProgram.setUniform("textureSampler2", 1);

    while (!glfwWindowShouldClose(window.get())) {
        glfwSwapBuffers(window.get());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 identity { 1 };
        auto modelMatrix = glm::rotate(
            identity,
            static_cast<float>(glfwGetTime()) * glm::radians(50.0f),
            glm::vec3{ 0.5, 1, 0 }
        );
        auto viewMatrix = glm::translate(identity, glm::vec3{ 0, 0, -3 });
        [[maybe_unused]] auto perspectiveProjectionMatrix = glm::perspective(
            glm::radians(45.0f), static_cast<float>(800 / 600), 0.1f, 100.0f
        );
        // TODO: come back to this
        [[maybe_unused]] auto orthographicProjectionMatrix = glm::ortho(
            0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f
        );
        shaderProgram.setUniform("modelMatrix", modelMatrix);
        shaderProgram.setUniform("viewMatrix", viewMatrix);
        shaderProgram.setUniform("projectionMatrix", perspectiveProjectionMatrix);
        
        wallTexture.use(GL_TEXTURE0);
        faceTexture.use(GL_TEXTURE1);

        glBindVertexArray(vertexArrayID);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
     
        glfwPollEvents();
        processInput(window.get());
    }

    return 0;
}