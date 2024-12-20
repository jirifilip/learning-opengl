#pragma once

#include <iostream>

#include <GLFW/glfw3.h>

#include "camera.h"
#include "glfw_timer.h"
#include "mouse_capturer.h"


void processWindowQuit(GLFWwindow* window);

void processMovement(GLFWwindow* window, Camera& camera, GLFWTimer& timer);

void abortProgram(const std::string message);

std::string readFileContent(const std::string fileName);