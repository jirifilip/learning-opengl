#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "utils.h"
#include "shader.h"
#include "shader_program.h"


void processInput(GLFWwindow* window) {
    auto keyStatus = glfwGetKey(window, GLFW_KEY_ESCAPE);
    
    if (keyStatus == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


typedef std::function<void(GLFWwindow*)> GLFWWindowDeleter;

class GLFW {
public:
    GLFW() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    }

    ~GLFW() {
        glfwTerminate();
    }

    std::unique_ptr<GLFWwindow, GLFWWindowDeleter> createWindow() {
        GLFWwindow* rawWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

        if (rawWindow == nullptr) {
            abortProgram("Failed to initialize window");
        }

        return std::unique_ptr<GLFWwindow, GLFWWindowDeleter>(
            rawWindow,
            [](GLFWwindow* rawWindow) {
                if (rawWindow != nullptr) {
                    glfwDestroyWindow(rawWindow);
                }   
            }    
        );
    } 

    void setCurrent(GLFWwindow* window) {
        glfwMakeContextCurrent(window);
    }
};


void loadGLAD() {
    auto success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!success) {
        abortProgram("Failed to initialize GLAD");
    }
}


int main() {
    auto glfw = GLFW();
    auto window = glfw.createWindow();
    glfw.setCurrent(window.get());

    // TODO: explore further
    loadGLAD();

    glViewport(0, 0, 800, 600);


    float vertices[] { 
        0.5f,  0.5f, 0.0f,  1, 0, 0,  // top right
        0.5f, -0.5f, 0.0f,  0, 1, 0, // bottom right
        -0.5f, -0.5f, 0.0f,  0, 0, 1, // bottom left
        -0.5f,  0.5f, 0.0f,   0.5, 0.5, 0.5, // top left
    };
    unsigned int indices[] {
        0, 1, 3,  // first triangle
        1, 2, 3, // second triangle
    };
    
    /*    
    float textureCoordinates[] = {
        0, 0,
        1, 0,
        0.5, 1
    };

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    */

    Shader vertexShader{ "src/shader.vert", GL_VERTEX_SHADER };
    Shader fragmentShader { "src/shader.frag", GL_FRAGMENT_SHADER };
    std::vector shaders { vertexShader, fragmentShader };
    
    ShaderProgram shaderProgram { shaders };


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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*) (3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);
    
    while (!glfwWindowShouldClose(window.get())) {
        glfwSwapBuffers(window.get());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        double time { glfwGetTime() };
        double green { (std::sin(time) / 2.0f) + 0.5f };

        shaderProgram.use();
        shaderProgram.setUniform("globalColor", 0, static_cast<float>(green), 0, 1);

        glBindVertexArray(vertexArrayID);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
     
        glfwPollEvents();
        processInput(window.get());
    }

    return 0;
}