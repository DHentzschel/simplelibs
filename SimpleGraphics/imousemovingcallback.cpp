#include "imousemovingcallback.h"

void IMouseMovingCallback::invokeCallback(GLFWwindow* window, const Vector2d& position)
{
    invoke(window, position);
}
