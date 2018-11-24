#include "imaximizewindowcallback.h"

void IMaximizeWindowCallback::invokeCallback(GLFWwindow* window, const Vector2& size)
{
    invoke(window, size);
}
