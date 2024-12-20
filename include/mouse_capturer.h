#pragma once

#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <functional>


class MouseCapturer {
private:
    float sensitivity { 0.1 };

    float pitch { 0 };
    float yaw { -90 };

    GLFWwindow* window = nullptr;

    float lastMouseX = 0;
    float lastMouseY = 0;

    void handleMouseMove(double positionX, double positionY) {
        float offsetX { (positionX - lastMouseX) * sensitivity };
        float offsetY { (lastMouseY - positionY) * sensitivity };

        lastMouseX = positionX;
        lastMouseY = positionY;

        yaw += offsetX;
        pitch += offsetY; 

        if (pitch > 89.f) {
            pitch = 89.f;
        } 
        else if (pitch < -89.f) {
            pitch = -89.f;
        } 
    }

    static void mouseCallback(GLFWwindow* window, double positionX, double positionY) {
        auto* capturer = static_cast<MouseCapturer*>(glfwGetWindowUserPointer(window));

        if (capturer) {
            capturer->handleMouseMove(positionX, positionY);
        }
    }

public:
    MouseCapturer(float sensitivity = 0.01): sensitivity(sensitivity) {};

    void captureForWindow(GLFWwindow* windowToCapture) {
        window = windowToCapture;
        glfwSetWindowUserPointer(window, this);

        int width;
        int height;
        glfwGetWindowSize(window, &width, &height);
        lastMouseX = width / 2;
        lastMouseY = height / 2;

        auto capturer = *this;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, MouseCapturer::mouseCallback);
    };

    glm::vec3 getPointingDirection() {
        glm::vec3 direction;
        
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        
        return glm::normalize(direction);
    }
};