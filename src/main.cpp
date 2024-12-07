#include <iostream>
#include <fstream>

#include <glad.c>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>


void abortProgram(const std::string message) {
    glfwTerminate();
    std::cerr << message << std::endl;
    std::abort();
}


void handleKeyPress(
        [[maybe_unused]] GLFWwindow* window,
        int key,
        [[maybe_unused]] int scancode,
        [[maybe_unused]] int action,
        [[maybe_unused]] int mods
    ) {
    
    std::cout << "Key pressed: " << key << std::endl;
}


void processInput(GLFWwindow* window) {
    auto keyStatus = glfwGetKey(window, GLFW_KEY_ESCAPE);
    
    if (keyStatus == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


std::string readFileContent(const std::string fileName) {
    std::ifstream inputFileStream{ fileName };
    // TODO: look more into how this std::string constructor from range works 
    std::string content {
        std::istreambuf_iterator<char>{ inputFileStream },
        std::istreambuf_iterator<char>()
    };

    return content;
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == nullptr) {
        abortProgram("Failed to initialize window");
    }

    glfwMakeContextCurrent(window);

    // TODO: explore further
    auto loaded = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (!loaded) {
        abortProgram("Failed to initialize GLAD");
    }

    glViewport(0, 0, 800, 600);

    glfwSetKeyCallback(window, handleKeyPress);

    float vertices[] { 
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f 
    };

    unsigned int vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    const std::string vertexShaderCode = readFileContent("src/shader.vert");
    std::cout << vertexShaderCode << std::endl;

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwPollEvents();
        processInput(window);
    }

    glfwTerminate();
    return 0;
}