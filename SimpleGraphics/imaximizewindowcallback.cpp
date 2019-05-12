#include "imaximizewindowcallback.h"

void IMaximizeWindowCallback::invokeCallback(GLFWwindow* window, const Vector2i& size)
{
    invoke(window, size);
}
