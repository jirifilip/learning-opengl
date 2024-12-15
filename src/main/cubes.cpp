#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <cmath>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "utils.h"
#include "shader.h"
#include "shader_program.h"
#include "glfw_handler.h"
#include "glfw_timer.h"
#include "texture.h"
#include "camera.h"
#include "mouse_capturer.h"


Camera camera {
    glm::vec3{ 0, 0, 3 },
    glm::vec3{ 0, 0, -1 },
    5
};
GLFWTimer timer {};
MouseCapturer mouseCapturer {};



void processInput(GLFWwindow* window) {
    auto keyStatus = glfwGetKey(window, GLFW_KEY_ESCAPE);
    auto dt = timer.getTimeDifference();
    
    if (keyStatus == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } 
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.moveForward(dt);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.moveBackward(dt);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.moveLeft(dt);
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.moveRight(dt);
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

    auto windowRaw = window.get();
    mouseCapturer.captureForWindow(windowRaw);

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
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    Shader vertexShader{ "shaders/cubes/shader.vert", GL_VERTEX_SHADER };
    Shader fragmentShader { "shaders/cubes/shader.frag", GL_FRAGMENT_SHADER };
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

    glm::mat4 identity { 1 };
    [[maybe_unused]] auto perspectiveProjectionMatrix = glm::perspective(
        glm::radians(45.0f), static_cast<float>(800 / 600), 0.1f, 100.0f
    );
    // TODO: come back to this
    [[maybe_unused]] auto orthographicProjectionMatrix = glm::ortho(
        0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f
    );

    shaderProgram.use();
    shaderProgram.setUniform("textureSampler1", 0);
    shaderProgram.setUniform("textureSampler2", 1);
    shaderProgram.setUniform("projectionMatrix", perspectiveProjectionMatrix);

    while (!glfwWindowShouldClose(window.get())) {
        timer.tick();

        glfwSwapBuffers(window.get());

        auto viewMatrix = camera.lookThrough();
        shaderProgram.setUniform("viewMatrix", viewMatrix);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        wallTexture.use(GL_TEXTURE0);
        faceTexture.use(GL_TEXTURE1);

        glBindVertexArray(vertexArrayID);

        int i = 0;
        for (auto& cubePosition : cubePositions) {
            auto modelTranslate = glm::translate(identity, cubePosition);
            auto modelRotate = glm::rotate(
                modelTranslate,
                static_cast<float>(glfwGetTime()) * glm::radians((i + 1) * 20.0f),
                glm::vec3{ 0.5, 1, 0 }
            );
            
            shaderProgram.setUniform("modelMatrix", modelRotate);
            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            i++;
        }
        glBindVertexArray(0);

        float pitch = mouseCapturer.getPitch();
        float yaw = mouseCapturer.getYaw();

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        camera.setForward(direction);
        std::cout << direction.x << std::endl;

        glfwPollEvents();
        processInput(window.get());
    }

    return 0;
}