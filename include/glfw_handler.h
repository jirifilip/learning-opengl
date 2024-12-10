#pragma once

#include <memory>
#include <functional>

#include <GLFW/glfw3.h>


typedef std::function<void(GLFWwindow*)> GLFWWindowDeleter;


class GLFWHandler {
public:
    GLFWHandler();

    ~GLFWHandler();

    std::unique_ptr<GLFWwindow, GLFWWindowDeleter> createWindow();

    void setCurrent(GLFWwindow* window);
};