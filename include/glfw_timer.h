#pragma once

#include <GLFW/glfw3.h>


class GLFWTimer {
private:
    float timeAtPreviousTick { 0 };
    float timeDifferenceBetweenTicks { 0 };

public:    
    void tick();

    float getTimeDifference();
};