#include "Input.h"
#include <iostream>
void processInputs(GLFWwindow* window)
{
    // move the camera
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        std::cout << "°´ÏÂW¼ü" << std::endl;
}