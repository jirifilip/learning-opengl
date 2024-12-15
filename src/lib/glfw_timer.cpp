#include <GLFW/glfw3.h>

#include "glfw_timer.h"


void GLFWTimer::tick() {
    float timeAtCurrentTick = glfwGetTime();
    timeDifferenceBetweenTicks = timeAtCurrentTick - timeAtPreviousTick;
    timeAtPreviousTick = timeAtCurrentTick;
}


float GLFWTimer::getTimeDifference() {
    return timeDifferenceBetweenTicks;
}
