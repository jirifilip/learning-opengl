#include <iostream>
#include <fstream>

#include <GLFW/glfw3.h>

#include "camera.h"
#include "glfw_timer.h"
#include "mouse_capturer.h"


void processWindowQuit(GLFWwindow* window) {
    auto keyStatus = glfwGetKey(window, GLFW_KEY_ESCAPE);
    
    if (keyStatus == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } 
}


void processMovement(GLFWwindow* window, Camera& camera, GLFWTimer& timer) {
    auto dt = timer.getTimeDifference();
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
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
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.moveUp(dt);
    }
}


void abortProgram(const std::string message) {
    std::cerr << message << std::endl;
    std::abort();
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
