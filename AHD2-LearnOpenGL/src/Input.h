#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "GLFW/glfw3.h"
void processCameraInputs(GLFWwindow* window, Camera& camera, const float& deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);