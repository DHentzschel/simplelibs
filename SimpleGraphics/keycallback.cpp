#include "keycallback.h"

#include <GLFW/glfw3.h>

void KeyCallback::invoke(GLFWwindow* window,
    const int key,
    int scancode,
    const int action,
    int mods) const
{
    keys_[key] = action == GLFW_PRESS;
}
