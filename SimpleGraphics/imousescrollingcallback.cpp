#include "imousescrollingcallback.h"

void IMouseScrollingCallback::invokeCallback(GLFWwindow* window, const Vector2d& offset)
{
    invoke(window, Vector2d(offset.x, offset.y));
}
