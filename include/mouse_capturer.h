#include <GLFW/glfw3.h>

#include <functional>


class MouseCapturer {
private:
    const float sensitivity { 0.1 };

    float pitch { 0 };
    float yaw { -90 };

    GLFWwindow* window = nullptr;

    float lastMouseX = 0;
    float lastMouseY = 0;

    void handleMouseMove(double positionX, double positionY) {
        lastMouseX = positionX;
        lastMouseY = positionY;

        float offsetX { (positionX - lastMouseX) * sensitivity };
        float offsetY { (lastMouseY - positionY) * sensitivity };

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
    void captureFromWindow(GLFWwindow* window) {
        window = window;
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

    float getPitch() {
        return pitch;
    }

    float getYaw() {
        return yaw;
    }
};