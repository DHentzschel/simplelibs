#include "monitor.h"

#include <GLFW/glfw3.h>

Vector2 Monitor::getSize()
{
    // TODO generic method to use CURRENT monitor, not primary
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    return Vector2(mode->width, mode->height);
}
