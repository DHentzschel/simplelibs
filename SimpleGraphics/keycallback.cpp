#include "keycallback.h"

#include <GLFW/glfw3.h>

void KeyCallback::invokeCallback(GLFWwindow * window, int key, int scancode, int action, int mods) const
{
    keys_[key] = action == GLFW_PRESS;
    invoke(window, key, scancode, action, mods);
}

void KeyCallback::invoke(GLFWwindow* window, int key, int scancode, int action, int mods) const
{
}

