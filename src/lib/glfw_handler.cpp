#include <memory>

#include <GLFW/glfw3.h>

#include "glfw_handler.h"
#include "utils.h"


GLFWHandler::GLFWHandler() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


GLFWHandler::~GLFWHandler() {
    glfwTerminate();
}


std::unique_ptr<GLFWwindow, GLFWWindowDeleter> GLFWHandler::createWindow() {
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


void GLFWHandler::setCurrent(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
}
