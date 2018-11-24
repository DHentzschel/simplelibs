#include "iminimizewindowcallback.h"

void IMinimizeWindowCallback::invokeCallback(GLFWwindow* window)
{
    invoke(window);
}
