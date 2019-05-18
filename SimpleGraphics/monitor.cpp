#include "monitor.h"

#include <GLFW/glfw3.h>

Vector2i Monitor::getSize()
{
    // TODO generic method to use CURRENT monitor, not primary
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    return Vector2i(mode->width, mode->height);
}
